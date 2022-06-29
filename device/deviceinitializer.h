#ifndef DEVICEINITIALIZER_H
#define DEVICEINITIALIZER_H

#include <QObject>
class DeviceFacade;

class DeviceInitializer : public QObject
{
    Q_OBJECT
public:
    explicit DeviceInitializer(QObject* parent = nullptr);
    QString init(DeviceFacade* facade, QString devName, QString portName, QString dirName, QString scriptFileName);
    void deinit(DeviceFacade* facade);

private:
    void setupConnections(DeviceFacade* facade);
};

#endif // DEVICEINITIALIZER_H
