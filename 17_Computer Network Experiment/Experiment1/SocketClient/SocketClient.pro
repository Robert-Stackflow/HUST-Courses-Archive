QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG -= debug_and_release
DEFINES += WIN32_LEAN_AND_MEAN
DESTDIR = bin
INCLUDEPATH = header
UI_DIR = temp/ui
MOC_DIR = temp/moc
RCC_DIR = temp/rcc
OBJECTS_DIR = temp/obj
TEMPLATE = app
LIBS += -lws2_32
RC_ICONS = icon.ico
TARGET = SocketClient
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/dialog/aboutdialog.cpp \
    source/main.cpp \
    source/clientwidget.cpp \
    source/socket/client.cpp \
    source/socket/response.cpp \
    source/util/cvalidator.cpp \
    source/util/filehelper.cpp \
    source/util/socketconfig.cpp \
    source/socket/thread.cpp \
    source/socket/socket.cpp \
    source/util/sockethelper.cpp \
    source/widget/floatbox.cpp \
    source/widget/cmessagebox.cpp \
    source/widget/framelesswidget.cpp

HEADERS += \
    header/dialog/aboutdialog.h \
    header/socket/client.h \
    header/socket/packet.h \
    header/socket/response.h \
    header/util/cvalidator.h \
    header/util/filehelper.h \
    header/util/loggerconfig.h \
    header/util/socketconfig.h \
    header/clientwidget.h \
    header/socket/thread.h \
    header/socket/socket.h \
    header/util/sockethelper.h \
    header/widget/cmessagebox.h \
    header/widget/floatbox.h \
    header/widget/framelesswidget.h

FORMS += \
    ui/dialog/aboutdialog.ui \
    ui/clientwidget.ui \
    ui/widget/cmessagebox.ui \
    ui/widget/floatbox.ui

RESOURCES += \
    style/style.qrc

QSLOG_PARENTPATH=./lib/QsLog
QSLOG_HEADERPATH=./lib/QsLog/
QSLOG_SOURCEPATH=./lib/QsLog/
include(./lib/QsLog/QsLog.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
