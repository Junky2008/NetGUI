#-------------------------------------------------
#
# Project created by QtCreator 2015-05-15T00:37:35
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

target.path = /home/pi/programs/$${TARGET}/bin
INSTALLS += target

TARGET = NetGraph
TEMPLATE = app


SOURCES += main.cpp\
        netgui.cpp \
    editnode.cpp \
    node.cpp \
    baseconfig.cpp

HEADERS  += netgui.h \
    editnode.h \
    node.h \
    baseconfig.h

FORMS    += netgui.ui \
    editnode.ui
