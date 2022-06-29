#ifndef DEVICEPORT_H
#define DEVICEPORT_H

#include <QObject>
class QTimer;
class QSerialPort;
#include "devicefilewriter.h"

class DevicePort : public QObject
{
    Q_OBJECT
public:
    explicit DevicePort(QObject* parent = nullptr, QString name = "");
    ~DevicePort();

public slots:
    void onWrite(QByteArray buffer);
    void onProcess();

signals:
    void receivedFromPort(QByteArray message);
    void changedStatusExistingData(bool isData);
    void ready(int returnCode);
    void sendedToFile(QString data, FileType type);

private slots:
    void onReadyRead();
    void onDataExistingTimer();

private:
    QTimer* _pDataExistingTimer;
    QSerialPort* _pPort;
    bool _isDataExist;
    QString _portName;
};

#endif // DEVICEPORT_H
