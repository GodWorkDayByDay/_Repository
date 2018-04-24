#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T09:32:49
#
#-------------------------------------------------

QT += core gui

INCLUDEPATH += $$PWD\MELSEC\Include \
               $$PWD\pylon\include \
               $$PWD\pylon\sample_include \
               $$PWD\Mil\Include

LIBS += -L$$PWD\Mil\LIB -lMil \
                        -lMilpat \
                        -lmilcolor\
                        -lMilim
                        #-lMIL-little

LIBS += -L$$PWD -lOle32

LIBS += -L$$PWD\pylon\lib\win32 \
                            -lGCBase_MD_VC120_v3_0_Basler_pylon_v5_0 \
                            -lGenApi_MD_VC120_v3_0_Basler_pylon_v5_0 \
                            -lPylonBase_MD_VC120_v5_0 \
                            -lPylonC_MD_VC120 \
                            -lPylonGUI_MD_VC120_v5_0 \
                            -lPylonUtility_MD_VC120_v5_0

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PLCBasler
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
        main_window.cpp \
    plc.cpp \
    image_window.cpp \
    milc.cpp \
    gallery_widget.cpp \
    admin_dialog.cpp

HEADERS += \
        main_window.h \
    plc.h \
    image_window.h \
    milc.h \
    gallery_widget.h \
    admin_dialog.h
