#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "device/devicefacade.h"
#include <QMainWindow>
class QListWidgetItem;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void onUpdate();
    void onChooseDir();
    void onChooseScript();
    void onAddDevice();
    void onDeleteDevice(int index);
    void onStartWrite();
    void onStartNavi();

signals:
    void startedWrite();
    void stoppedWrite();
    void startedNavi();

private:
    Ui::MainWindow* ui;
    QStringList _curPortsList;
    QList<DeviceFacade*> _devicesList;
    int _deviceIndex;
};

#endif // MAINWINDOW_H
