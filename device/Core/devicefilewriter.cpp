#include "devicefilewriter.h"
#include <QDateTime>
#include <QDir>
#include <QFile>

DeviceFileWriter::DeviceFileWriter(QObject* parent, QString dirName, QString devName) : QObject(parent)
{
    _isStarted = false;
    _dirName = dirName;
    _devName = devName;

    QDir dir(dirName);
    if (dir.exists() == false)
        if (dir.mkpath(dirName) == false)
            emit showedError(QString("Невозможно работать с директорией: %1  :(").arg(_dirName));
    //Написанное выше было сделано так из-за душевной травмы, нанесённой тестировщиками по поводу регистратора
    //телеметрии Кама-НС-В...
}

DeviceFileWriter::~DeviceFileWriter() { onStop(); }

void DeviceFileWriter::onStart()
{
    _pRawFile = new QFile(QString("%1/%2_raw_%3.txt")
                              .arg(_dirName)
                              .arg(_devName)
                              .arg(QDateTime::currentDateTime().toString("dd_MM_yyyy_hh_mm_ss")));

    _pNaviFile = new QFile(QString("%1/%2_navi_%3.txt")
                               .arg(_dirName)
                               .arg(_devName)
                               .arg(QDateTime::currentDateTime().toString("dd_MM_yyyy_hh_mm_ss")));

    _pOtherFile = new QFile(QString("%1/%2_other_%3.txt")
                                .arg(_dirName)
                                .arg(_devName)
                                .arg(QDateTime::currentDateTime().toString("dd_MM_yyyy_hh_mm_ss")));

    bool isOk = true;
    isOk &= _pRawFile->open(QIODevice::WriteOnly);
    if (isOk == false)
        emit showedError(QString("Не получилось открыть файл: %1. :(").arg(_pRawFile->fileName()));
    isOk &= _pNaviFile->open(QIODevice::WriteOnly);
    if (isOk == false)
        emit showedError(QString("Не получилось открыть файл: %1. :(").arg(_pRawFile->fileName()));
    isOk &= _pOtherFile->open(QIODevice::WriteOnly);
    if (isOk == false)
        emit showedError(QString("Не получилось открыть файл: %1. :(").arg(_pRawFile->fileName()));
    _isStarted = true;
}

void DeviceFileWriter::onStop()
{
    _isStarted = false;
    _pRawFile->close();
    _pNaviFile->close();
    _pOtherFile->close();

    delete _pRawFile;
    delete _pNaviFile;
    delete _pOtherFile;
}

void DeviceFileWriter::onWrite(QString data, FileType type)
{
    if (_isStarted == false)
        return;

    switch (type)
    {
        case FileType::Raw:
            _pRawFile->write(data.toLocal8Bit());
            break;
        case FileType::Navi:
            _pNaviFile->write(data.toLocal8Bit());
            break;
        case FileType::OtherFile:
            _pOtherFile->write(data.toLocal8Bit());
            break;
    }
}
