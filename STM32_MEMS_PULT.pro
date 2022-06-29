#-------------------------------------------------
#
# Project created by QtCreator 2022-06-05T13:11:14
#
#-------------------------------------------------

QT       += core gui serialport opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = STM32_MEMS_PULT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        device/Core/devicefilewriter.cpp \
        device/Core/deviceparser.cpp \
        device/Core/deviceport.cpp \
        device/Views/deviceinformationwidget.cpp \
        device/Views/deviceview.cpp \
        device/devicefacade.cpp \
        device/deviceinitializer.cpp \
        main.cpp \
        mainwindow.cpp \
        widgets/yprpainter.cpp

HEADERS += \
        device/Core/devicefilewriter.h \
        device/Core/deviceparser.h \
        device/Core/deviceport.h \
        device/Views/deviceinformationwidget.h \
        device/Views/deviceview.h \
        device/devicefacade.h \
        device/deviceinitializer.h \
        mainwindow.h \
        widgets/yprpainter.h

FORMS += \
        device/Views/deviceinformationwidget.ui \
        device/Views/deviceview.ui \
        mainwindow.ui

RESOURCES += resources/resources.qrc

RC_FILE = res.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
