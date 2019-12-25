#-------------------------------------------------
#
# Project created by QtCreator 2019-12-17T10:12:48
#
#-------------------------------------------------

QT       += core gui
QT       += network
RC_ICONS = Qmrsi.ico
QT       +=  printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qmrsi
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += WRCHARTING_STATICLIB
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    NetWork.cpp \
    qlineeditip.cpp \
    utils.cpp \
    Desktop.cpp \
    MeasDesktop.cpp \
    TcpClient.cpp \
    UdpServer.cpp \
    Comman.cpp \
    MeasSwitch.cpp \
    Measure.cpp \
    RXFFM.cpp \
    DataThread.cpp \
    RXPSCAN.cpp \
    SpectroThread.cpp

HEADERS += \
        mainwindow.h \
    NetWork.h \
    qlineeditip.h \
    utils.h \
    Desktop.h \
    MeasDesktop.h \
    TcpClient.h \
    UdpServer.h \
    Comman.h \
    MeasSwitch.h \
    datadef.h \
    Measure.h \
    RXFFM.h \
    DataThread.h \
    RXPSCAN.h \
    SpectroThread.h \
    SpecParams.h

FORMS += \
        mainwindow.ui \
    NetWork.ui \
    Desktop.ui \
    MeasDesktop.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    res.qrc

LIBS += -lWs2_32

CONFIG(release, debug|release){
    LIBS += -L$$PWD/lib/WRCharting -lWRCharting
}
CONFIG(debug, debug|release){
    LIBS += -L$$PWD/lib/WRCharting -lWRChartingd
}

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
