#ifndef DEVICEINFORMATIONWIDGET_H
#define DEVICEINFORMATIONWIDGET_H

#include <QListWidgetItem>
#include <QWidget>
class QPixmap;

namespace Ui
{
class DeviceInformationWidget;
}

class DeviceInformationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceInformationWidget(QWidget* parent = nullptr);
    ~DeviceInformationWidget();

    void setPortName(QString name);
    void setScriptName(QString name);
    void setDirName(QString name);

public slots:
    void onShowDataExisting(bool isExist);
    void onShowErrors(int counter);
    void onShowFreq(int freq);
    void onShowError(QString errorStr);

signals:
    void showed();
    void deleted();

private slots:
    void onPushDelete();
    void onPushShow();

private:
    Ui::DeviceInformationWidget* ui;
    QPixmap* _pOnlinePixmap;
    QPixmap* _pOfflinePixmap;
    void clear();
};

#endif // DEVICEINFORMATIONWIDGET_H
