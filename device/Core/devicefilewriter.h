#ifndef DEVICEFILEWRITER_H
#define DEVICEFILEWRITER_H

#include <QObject>
class QFile;

enum FileType
{
    Raw = 0,
    Navi = 1,
    OtherFile = 2,
};

class DeviceFileWriter : public QObject
{
    Q_OBJECT
public:
    explicit DeviceFileWriter(QObject* parent = nullptr, QString dirName = "", QString devName = "");
    ~DeviceFileWriter();

signals:
    void showedError(QString error);

public slots:
    void onWrite(QString data, FileType type);
    void onStart();
    void onStop();

private:
    QString _devName;
    QString _dirName;

    QFile* _pRawFile;
    QFile* _pNaviFile;
    QFile* _pOtherFile;

    bool _isStarted;
};

#endif // DEVICEFILEWRITER_H
