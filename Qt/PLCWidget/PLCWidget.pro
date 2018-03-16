#-------------------------------------------------
#
# Project created by QtCreator 2018-03-13T13:20:10
#
#-------------------------------------------------

QT       += core gui
LIBS     += -LE:\Projects\qt_qtcreator\PLCWidget -lOle32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


#win32 {
#    QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
#    QMAKE_LFLAGS_CONSOLE = /SUBSYSTEM:CONSOLE,5.01

#    DEFINES += _ATL_XP_TARGETING
#    QMAKE_CFLAGS += /D_USING_V140_SDK71_
#    QMAKE_CXXFLAGS += /D_USING_V140_SDK71_
#    LIBS += -L$$quote(C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib)
#    INCLUDEPATH += $$quote(C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include)
#    }


TARGET = PLCWidget
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


SOURCES += \
        main.cpp \
        plc_widget.cpp

HEADERS += \
        plc_widget.h
