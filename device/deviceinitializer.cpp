#include "deviceinitializer.h"

#include "Core/devicefilewriter.h"
#include "Core/deviceparser.h"
#include "Core/deviceport.h"
#include "Views/deviceinformationwidget.h"
#include "Views/deviceview.h"
#include "devicefacade.h"
#include <QEventLoop>
#include <QObject>
#include <QThread>

DeviceInitializer::DeviceInitializer(QObject* parent) : QObject(parent) {}

QString DeviceInitializer::init(DeviceFacade* facade, QString devName, QString portName, QString dirName,
                                QString scriptFileName)
{
    //Memory allocation
    facade->_pParser = new DeviceParser(nullptr, scriptFileName);
    facade->_pPort = new DevicePort(nullptr, portName);
    facade->_pView = new DeviceView(nullptr, devName);
    facade->_pFileWriter = new DeviceFileWriter(nullptr, dirName, devName);
    facade->_pInformationWidget = new DeviceInformationWidget();

    facade->_pPortThread = new QThread();
    facade->_pFileThread = new QThread();
    facade->_pParseThread = new QThread();

    //setup threads
    facade->_pFileWriter->moveToThread(facade->_pFileThread);
    facade->_pFileThread->start();

    QEventLoop loop;
    connect(facade->_pPort, &DevicePort::ready, &loop, &QEventLoop::exit);
    connect(facade->_pPortThread, &QThread::started, facade->_pPort, &DevicePort::onProcess);
    facade->_pPort->moveToThread(facade->_pPortThread);
    facade->_pPortThread->start();
    int errCode = loop.exec();

    if (errCode != 0)
    {
        deinit(facade);
        return "Возникла ошибка при попытке открыть порт";
    }

    connect(facade->_pParser, &DeviceParser::ready, &loop, &QEventLoop::exit);
    connect(facade->_pParseThread, &QThread::started, facade->_pParser, &DeviceParser::onProcess);
    facade->_pParser->moveToThread(facade->_pParseThread);
    facade->_pParseThread->start();
    errCode = loop.exec();
    if (errCode != 0)
    {
        deinit(facade);
        return "Возникла ошибка при попытке инициализировать парсер";
    }

    //other setups
    facade->_pInformationWidget->setDirName(dirName);
    facade->_pInformationWidget->setScriptName(scriptFileName);
    facade->_pInformationWidget->setPortName(portName);

    //connections
    setupConnections(facade);

    return "";
}

void DeviceInitializer::deinit(DeviceFacade* facade)
{
    //Порн надо удалять отправляя сигнал, и дожидаясь, пока дело не сделано.

    facade->_pPortThread->terminate();
    facade->_pFileThread->terminate();
    facade->_pParseThread->terminate();

    delete facade->_pPort;
    delete facade->_pParser;
    delete facade->_pFileWriter;
    delete facade->_pView;
    delete facade->_pInformationWidget;

    delete facade->_pPortThread;
    delete facade->_pParseThread;
    delete facade->_pFileThread;
}

void DeviceInitializer::setupConnections(DeviceFacade* facade)
{
    connect(facade->_pPort, &DevicePort::receivedFromPort, facade->_pParser, &DeviceParser::onIncomingData);
    connect(facade->_pPort, &DevicePort::changedStatusExistingData, facade->_pView, &DeviceView::onShowExistingData);
    connect(facade->_pPort, &DevicePort::changedStatusExistingData, facade->_pInformationWidget,
            &DeviceInformationWidget::onShowDataExisting);

    connect(facade->_pFileWriter, &DeviceFileWriter::showedError, facade->_pInformationWidget,
            &DeviceInformationWidget::onShowError);

    connect(facade, &DeviceFacade::startFileWrite, facade->_pFileWriter, &DeviceFileWriter::onStart);
    connect(facade, &DeviceFacade::stopFileWrite, facade->_pFileWriter, &DeviceFileWriter::onStop);
    connect(facade, &DeviceFacade::startedNavi, facade->_pParser, &DeviceParser::onStartNavi);

    connect(facade->_pParser, &DeviceParser::sendedToFile, facade->_pFileWriter, &DeviceFileWriter::onWrite);
    connect(facade->_pPort, &DevicePort::sendedToFile, facade->_pFileWriter, &DeviceFileWriter::onWrite);

    connect(facade->_pParser, &DeviceParser::showedRawData, facade->_pView, &DeviceView::onShowRawData);
    connect(facade->_pParser, &DeviceParser::showedNaviData, facade->_pView, &DeviceView::onShowNaviData);
    connect(facade->_pParser, &DeviceParser::showedFreq, facade->_pInformationWidget,
            &DeviceInformationWidget::onShowFreq);
    connect(facade->_pParser, &DeviceParser::showedErrors, facade->_pInformationWidget,
            &DeviceInformationWidget::onShowErrors);

    connect(facade->_pInformationWidget, &DeviceInformationWidget::showed, facade->_pView, &DeviceView::show);
    connect(facade->_pInformationWidget, &DeviceInformationWidget::deleted, facade, &DeviceFacade::onDeleted);
}
