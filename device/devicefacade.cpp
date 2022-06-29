#include "devicefacade.h"
#include "deviceinitializer.h"
#include <QMessageBox>

DeviceFacade::DeviceFacade(QObject* parent, int index, QString devName, QString portName, QString dirName,
                           QString scriptFileName)
    : QObject(parent)
{
    _deviceIndex = index;
    DeviceInitializer builder;
    _lastError = builder.init(this, devName, portName, dirName, scriptFileName);
}

void DeviceFacade::deleteDevice()
{
    DeviceInitializer destroyer;
    destroyer.deinit(this);
}

QString DeviceFacade::getError() { return _lastError; }

int DeviceFacade::getDeviceIndex() { return _deviceIndex; }

DeviceInformationWidget* DeviceFacade::getDeviceWidget() { return _pInformationWidget; }

void DeviceFacade::onDeleted() { emit deleted(_deviceIndex); }
