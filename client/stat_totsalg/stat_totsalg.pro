TEMPLATE = lib
TARGET +=
DEPENDPATH += .
INCLUDEPATH += . ../include
VPATH += ../include ../main
CONFIG += debug_and_release plugin

win32:QMAKE_EXTRA_TARGETS = dll_clean
win32:PRE_TARGETDEPS = dll_clean
win32:RC_FILE += stat_dll.rc

CONFIG(debug, debug|release) {
    DESTDIR = ../plugins
    OBJECTS_DIR = ../debug
    unix:OBJECTS_DIR = ../plug_debug
    RCC_DIR = debug
    win32:dll_clean.commands = -@echo [File] - Cleaning dll build enviroment && del ..\debug\stat_dll_res.o
} else {
    OBJECTS_DIR = ../release
    unix:OBJECTS_DIR = ../plug_release
    DESTDIR = ../install
    RCC_DIR = release
    win32:dll_clean.commands = -@echo [File] - Cleaning dll build enviroment && del ..\release\stat_dll_res.o
}

QT += xml network

FORMS += stat_totsalg_rdlg.ui stat_totsalg_sdlg.ui
HEADERS += conn.h stat_interf.h stat.h stat_totsalg.h stat_totsalg_data.h
HEADERS += stat_totsalg_rdlg.h stat_totsalg_sdlg.h stat_totsalg_xml.h
SOURCES += conn.cc stat_totsalg.cc stat_dlg.cc stat_totsalg_rdlg.cc
SOURCES += stat_totsalg_sdlg.cc stat_totsalg_xml.cc
