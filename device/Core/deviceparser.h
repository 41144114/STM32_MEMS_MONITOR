#ifndef DEVICEPARSER_H
#define DEVICEPARSER_H

#include <QObject>
class QTimer;
#include "devicefilewriter.h"
//struct LED
//{
//    unsigned short header;
//    unsigned char led : 3;
//    unsigned char cmd : 5;
//    unsigned char reserved[3];
//    unsigned short crc16_ccitt;
//} cmd_data_t;

typedef struct sensor_data_t
{
    unsigned short magic;
    unsigned char pack_num;
    int8_t gyro_temp;
    short acc_temp;
    short acc_x;
    short acc_y;
    short acc_z;
    short gyro_x;
    short gyro_y;
    short gyro_z;
    short mag_x;
    short mag_y;
    short mag_z;
    unsigned short crc16;

    void init()
    {
        magic = 0;
        pack_num = 0;
        gyro_temp = 0;
        acc_temp = 0;
        acc_x = 0;
        acc_y = 0;
        acc_z = 0;
        gyro_x = 0;
        gyro_y = 0;
        gyro_z = 0;
        mag_x = 0;
        mag_y = 0;
        mag_z = 0;
        crc16 = 0;
    }
} sensor_data_t;

struct RawData
{
    short wx;
    short wy;
    short wz;
    short ax;
    short ay;
    short az;
    short mx;
    short my;
    short mz;

    void init()
    {
        wx = 0;
        wy = 0;
        wz = 0;
        ax = 0;
        ay = 0;
        az = 0;
        mx = 0;
        my = 0;
        mz = 0;
    }
};

struct NaviData
{
    float yaw;
    float pitch;
    float roll;
    float Vn;
    float Ve;
    float Vup;
    float x;
    float y;
    float z;

    void init()
    {
        yaw = 0.0f;
        pitch = 0.0f;
        roll = 0.0f;
        Vn = 0.0f;
        Ve = 0.0f;
        Vup = 0.0f;
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }
};

class DeviceParser : public QObject
{
    Q_OBJECT
public:
    explicit DeviceParser(QObject* parent = nullptr, QString settingsFileName = "");

public slots:
    void onIncomingData(QByteArray data);
    void onProcess();
    void onStartNavi();

signals:
    void showedFreq(int freq);
    void showedRawData(sensor_data_t data);
    void showedNaviData(NaviData data);
    void showedErrors(int errCounter);
    void ready(int code);
    void sendedToFile(QString data, FileType type);

private slots:
    void onUpdateRawData();
    void onUpdateNaviData();
    void onUpdateFreqData();

private:
    QByteArray _incomingBuffer;
    QTimer* _pTimerRawDataUpdater;
    QTimer* _pTimerNaviDataUpdater;
    QTimer* _pTimerFreqUpdate;
    int _freqCounter;
    int _errorCounter;

    NaviData _actualNaviData;
    sensor_data_t _actualRawData;

    void parsePack();
    void parseSettings(QString fileName);
};

#endif // DEVICEPARSER_H
