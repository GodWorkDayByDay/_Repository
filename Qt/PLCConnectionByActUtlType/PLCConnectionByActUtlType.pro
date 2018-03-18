
QT       += core gui

LIBS     += -L$$PWD -lOle32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET    = PLCConnectionByActUtlType
TEMPLATE  = app
DEFINES  += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        plc_widget.cpp

HEADERS += \
        plc_widget.h
