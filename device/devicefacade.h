#ifndef DEVICEFACADE_H
#define DEVICEFACADE_H

#include <QObject>
class DeviceView;
class DeviceInformationWidget;
class DeviceParser;
class DeviceFileWriter;
class DevicePort;
class QThread;

class DeviceFacade : public QObject
{
    Q_OBJECT
public:
    explicit DeviceFacade(QObject* parent = nullptr, int index = 0, QString devName = "", QString portName = "",
                          QString dirName = "", QString scriptFileName = "");

    void deleteDevice();
    QString getError();
    int getDeviceIndex();
    DeviceInformationWidget* getDeviceWidget();

    friend class DeviceInitializer;

signals:
    void deleted(int index);
    void startFileWrite();
    void stopFileWrite();
    void startedNavi();

public slots:

private slots:
    void onDeleted();

private:
    DevicePort* _pPort;
    DeviceView* _pView;
    DeviceParser* _pParser;
    DeviceFileWriter* _pFileWriter;
    DeviceInformationWidget* _pInformationWidget;

    QThread* _pPortThread;
    QThread* _pFileThread;
    QThread* _pParseThread;

    QString _lastError;
    int _deviceIndex;
};

#endif // DEVICEFACADE_H
