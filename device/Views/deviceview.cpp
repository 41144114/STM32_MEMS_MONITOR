#include "deviceview.h"
#include "ui_deviceview.h"
#include <QDebug>

DeviceView::DeviceView(QWidget* parent, QString devName) : QWidget(parent), ui(new Ui::DeviceView)
{
    ui->setupUi(this);
    _deviceName = devName;
    setWindowTitle(_deviceName);
    ui->widgetYpr->setBackgroundColor(this->palette().background().color());
}

DeviceView::~DeviceView() { delete ui; }

void DeviceView::onShowRawData(sensor_data_t data)
{
    ui->lineWx->setText(QString::number(data.gyro_x));
    ui->lineWy->setText(QString::number(data.gyro_y));
    ui->lineWz->setText(QString::number(data.gyro_z));
    ui->lineAx->setText(QString::number(data.acc_x));
    ui->lineAy->setText(QString::number(data.acc_y));
    ui->lineAz->setText(QString::number(data.acc_z));
    ui->lineMx->setText(QString::number(data.mag_x));
    ui->lineMy->setText(QString::number(data.mag_y));
    ui->lineMz->setText(QString::number(data.mag_z));
    ui->lineTgyro->setText(QString::number(data.gyro_temp));
    ui->lineTacc->setText(QString::number(data.acc_temp));
}

void DeviceView::onShowNaviData(NaviData data)
{
    ui->widgetYpr->setYPR(data.yaw, data.pitch, data.roll);

    ui->lineX->setText(QString::number(data.x));
    ui->lineY->setText(QString::number(data.y));
    ui->lineZ->setText(QString::number(data.z));

    ui->lineVe->setText(QString::number(data.Ve));
    ui->lineVn->setText(QString::number(data.Vn));
    ui->lineVup->setText(QString::number(data.Vup));

    ui->lineYaw->setText(QString::number(data.yaw));
    ui->linePitch->setText(QString::number(data.pitch));
    ui->lineRoll->setText(QString::number(data.roll));
}

void DeviceView::onShowExistingData(bool isExist)
{
    ui->lineX->setEnabled(isExist);
    ui->lineY->setEnabled(isExist);
    ui->lineZ->setEnabled(isExist);

    ui->lineVe->setEnabled(isExist);
    ui->lineVn->setEnabled(isExist);
    ui->lineVup->setEnabled(isExist);

    ui->lineYaw->setEnabled(isExist);
    ui->linePitch->setEnabled(isExist);
    ui->lineRoll->setEnabled(isExist);

    ui->lineWx->setEnabled(isExist);
    ui->lineWy->setEnabled(isExist);
    ui->lineWz->setEnabled(isExist);
    ui->lineAx->setEnabled(isExist);
    ui->lineAy->setEnabled(isExist);
    ui->lineAz->setEnabled(isExist);

    ui->lineMx->setEnabled(isExist);
    ui->lineMy->setEnabled(isExist);
    ui->lineMz->setEnabled(isExist);

    ui->lineTacc->setEnabled(isExist);
    ui->lineTgyro->setEnabled(isExist);
}
