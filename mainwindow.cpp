#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "device/devicefacade.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushStartWrite, &QPushButton::clicked, this, &MainWindow::onStartWrite);
    connect(ui->pushStartAlgorithm, &QPushButton::clicked, this, &MainWindow::onStartNavi);
    connect(ui->pushChooseDir, &QPushButton::clicked, this, &MainWindow::onChooseDir);
    connect(ui->pushChooseScript, &QPushButton::clicked, this, &MainWindow::onChooseScript);
    connect(ui->pushAdd, &QPushButton::clicked, this, &MainWindow::onAddDevice);
    connect(ui->pushUpdatePorts, &QPushButton::clicked, this, &MainWindow::onUpdate);
    _deviceIndex = 0;
    onUpdate();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onUpdate()
{
    _curPortsList.clear();

    QList<QSerialPortInfo> info = QSerialPortInfo::availablePorts();
    for (int i = info.count() - 1; i >= 0; --i) _curPortsList.append(info.at(i).portName());

    if (ui->comboPort->isEnabled())
    {
        QString curPortName = ui->comboPort->currentText();
        ui->comboPort->clear();
        ui->comboPort->addItems(_curPortsList);

        for (int i = 0; i < ui->comboPort->count(); ++i)
            if (ui->comboPort->itemText(i) == curPortName)
            {
                ui->comboPort->setCurrentIndex(i);
                break;
            }
    }
}

void MainWindow::onChooseDir()
{
    QString dirName = QFileDialog::getExistingDirectory(this, "Выбрать директорию записи");
    if (dirName.isEmpty() == false)
        ui->lineDir->setText(dirName);
}

void MainWindow::onChooseScript()
{
    QString fName = QFileDialog::getOpenFileName(this, tr("Открыть файл"));
    if (fName.isEmpty() == false)
        ui->lineScript->setText(fName);
}

void MainWindow::onAddDevice()
{
    DeviceFacade* temp = new DeviceFacade(nullptr, _deviceIndex, ui->lineEditName->text(), ui->comboPort->currentText(),
                                          ui->lineDir->text(), ui->lineScript->text());
    _deviceIndex++;
    if (temp->getError().isEmpty())
    {
        connect(this, &MainWindow::startedWrite, temp, &DeviceFacade::startFileWrite);
        connect(this, &MainWindow::stoppedWrite, temp, &DeviceFacade::stopFileWrite);
        connect(this, &MainWindow::startedNavi, temp, &DeviceFacade::startedNavi);
        connect(temp, &DeviceFacade::deleted, this, &MainWindow::onDeleteDevice);

        _devicesList.append(temp);
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(QSize(0, 170));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, reinterpret_cast<QWidget*>(temp->getDeviceWidget()));
        //        ui->listWidget->addItem(reinterpret_cast<QListWidgetItem*>(temp->getDeviceWidget()));
    }
    else
    {
        QMessageBox::warning(this, "Внимание!", temp->getError());
        delete temp;
    }
}

void MainWindow::onDeleteDevice(int index)
{
    int indexInList = -1;
    for (int i = 0; i < _devicesList.count(); i++)
    {
        if (_devicesList.at(i)->getDeviceIndex() == index)
        {
            indexInList = i;
            break;
        }
    }

    if (indexInList == -1)
        return;

    for (int i = 0; i < _devicesList.count(); i++)
    {
        if (reinterpret_cast<QWidget*>(_devicesList.at(indexInList)->getDeviceWidget()) ==
            ui->listWidget->itemWidget(ui->listWidget->item(i)))
        {
            QListWidgetItem* item = ui->listWidget->item(i);
            ui->listWidget->removeItemWidget(item);
            ui->listWidget->takeItem(i);
            delete item;
            break;
        }
    }

    DeviceFacade* temp = _devicesList.takeAt(indexInList);
    temp->deleteDevice();
    delete temp;
}

void MainWindow::onStartWrite()
{
    if (ui->pushStartWrite->text() == "Начать запись файла")
    {
        emit startedWrite();
        ui->pushStartWrite->setText("Закончить запись файла");
    }
    else
    {
        emit stoppedWrite();
        ui->pushStartWrite->setText("Начать запись файла");
    }
}

void MainWindow::onStartNavi() { emit startedNavi(); }
