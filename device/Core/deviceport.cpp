#include "deviceport.h"
#include <QSerialPort>
#include <QTimer>

DevicePort::DevicePort(QObject* parent, QString name) : QObject(parent)
{
    _isDataExist = false;
    _portName = name;
    _pPort = nullptr;
    _pDataExistingTimer = nullptr;
}

DevicePort::~DevicePort()
{
    _pPort->close();
    delete _pDataExistingTimer;
    delete _pPort;
}

void DevicePort::onProcess()
{
    _pPort = new QSerialPort();

    _pPort->setPortName(_portName);
    _pPort->open(QIODevice::ReadWrite);
    if (_pPort->isOpen() == false)
    {
        emit ready(-1);
        delete _pPort;
        return;
    }

    bool isOk = true;
    isOk &= _pPort->setBaudRate(QSerialPort::Baud115200);
    isOk &= _pPort->setParity(QSerialPort::Parity::NoParity);
    isOk &= _pPort->setDataBits(QSerialPort::Data8);
    isOk &= _pPort->setStopBits(QSerialPort::OneStop);
    isOk &= _pPort->setFlowControl(QSerialPort::NoFlowControl);

    if (isOk == false)
    {
        emit ready(-1);
        delete _pPort;
        return;
    }

    connect(_pPort, &QSerialPort::readyRead, this, &DevicePort::onReadyRead);

    _pDataExistingTimer = new QTimer();
    _pDataExistingTimer->setInterval(500);
    _pDataExistingTimer->setSingleShot(false);
    connect(_pDataExistingTimer, &QTimer::timeout, this, &DevicePort::onDataExistingTimer);
    _pDataExistingTimer->start();

    emit ready(0);
}

void DevicePort::onReadyRead()
{
    _isDataExist = true;
    QByteArray temp = _pPort->readAll();
    emit receivedFromPort(temp);
    emit sendedToFile(temp, Raw);
}

void DevicePort::onDataExistingTimer()
{
    emit changedStatusExistingData(_isDataExist);
    _isDataExist = false;
}

void DevicePort::onWrite(QByteArray buffer)
{
    if (_pPort != nullptr)
        _pPort->write(buffer);
}
