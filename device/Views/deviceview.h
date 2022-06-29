#ifndef DEVICEVIEW_H
#define DEVICEVIEW_H

#include "device/Core/deviceparser.h"
#include <QWidget>

namespace Ui
{
class DeviceView;
}

class DeviceView : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceView(QWidget* parent = nullptr, QString devName = "");
    ~DeviceView();

public slots:
    void onShowRawData(sensor_data_t data);
    void onShowNaviData(NaviData data);
    void onShowExistingData(bool isExist);

private:
    Ui::DeviceView* ui;
    QString _deviceName;
};

#endif // DEVICEVIEW_H
