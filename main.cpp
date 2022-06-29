#include "mainwindow.h"
#include <QApplication>

#include "device/Views/deviceview.h"
#include <QDateTime>
#include <QDebug>
#include <QDir>

void errMessageOutput(QtMsgType type, const QMessageLogContext& contex, const QString& msg)
{
    Q_UNUSED(contex);
    static QString logPath = QString("%1/%2").arg(QDir::homePath()).arg("MemsPult/Logs/");
    static QString hidedProgDir = QString("%1/%2").arg(QDir::homePath()).arg("MemsPult/");

    QDir dir;
    dir.setPath(logPath);
    if (!dir.exists())
        dir.mkpath(logPath);

    QFile outFile(logPath + QDate::currentDate().toString("log(dd_MM_yyyy).log"));
    QFileInfo info(outFile);

    outFile.open(QIODevice::Append);

    QString txt = QString("[%1] ").arg(QDateTime::currentDateTime().toString("dd.MM.yy hh:mm:ss:z"));
    while (txt.length() < 24) txt.append(" ");

    switch (type)
    {
        case QtDebugMsg:
            txt.append("(Debug)   ");
            break;
        case QtWarningMsg:
            txt.append("(Warning) ");
            break;
        case QtCriticalMsg:
            txt.append("(Critical)");
            break;
        case QtInfoMsg:
            txt.append("(Info)    ");
            break;
        case QtFatalMsg:
            txt.append("(Fatal)   ");
            txt.append(msg);
            outFile.write(txt.toLocal8Bit());
            outFile.write("\r\n");
            outFile.close();
            abort();
    }
    txt.append(msg);
    outFile.write(txt.toLocal8Bit());
    outFile.write("\r\n");
    outFile.close();
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("Fusion");
    qInstallMessageHandler(errMessageOutput);
    qRegisterMetaType<RawData>("RawData");
    qRegisterMetaType<NaviData>("NaviData");
    qRegisterMetaType<sensor_data_t>("sensor_data_t");
    qRegisterMetaType<FileType>("FileType");

    MainWindow w;
    qDebug() << "start app!";
    w.show();

    return a.exec();
}
