#include "deviceinformationwidget.h"
#include "ui_deviceinformationwidget.h"

#include <QMessageBox>

DeviceInformationWidget::DeviceInformationWidget(QWidget* parent) : QWidget(parent), ui(new Ui::DeviceInformationWidget)
{
    ui->setupUi(this);
    _pOnlinePixmap = new QPixmap(":/online.png");
    _pOfflinePixmap = new QPixmap(":/offline.png");
    clear();
    connect(ui->pushButtonShow, &QPushButton::clicked, this, &DeviceInformationWidget::onPushShow);
    connect(ui->pushButtonDelete, &QPushButton::clicked, this, &DeviceInformationWidget::onPushDelete);
}

DeviceInformationWidget::~DeviceInformationWidget()
{
    delete _pOnlinePixmap;
    delete _pOfflinePixmap;
    delete ui;
}

void DeviceInformationWidget::setPortName(QString name) { ui->labelPort->setText(name); }

void DeviceInformationWidget::setScriptName(QString name) { ui->labelScript->setText(name); }

void DeviceInformationWidget::setDirName(QString name) { ui->labelDir->setText(name); }

void DeviceInformationWidget::onShowDataExisting(bool isExist)
{
    ui->labelPortIndicator->setPixmap(isExist ? *_pOnlinePixmap : *_pOfflinePixmap);
}

void DeviceInformationWidget::onShowErrors(int counter) { ui->labelErrors->setText(QString::number(counter)); }

void DeviceInformationWidget::onShowFreq(int freq) { ui->labelFreq->setText(QString::number(freq)); }

void DeviceInformationWidget::onShowError(QString errorStr) { QMessageBox::critical(this, "Ошибка", errorStr); }

void DeviceInformationWidget::onPushDelete() { emit deleted(); }

void DeviceInformationWidget::onPushShow() { emit showed(); }

void DeviceInformationWidget::clear()
{
    ui->labelErrors->setText("0");
    ui->labelFreq->setText("0");
    ui->labelDir->setText("");
    ui->labelName->setText("");
    ui->labelPort->setText("");
    ui->labelScript->setText("");
    ui->labelPortIndicator->setPixmap(*_pOfflinePixmap);
}
