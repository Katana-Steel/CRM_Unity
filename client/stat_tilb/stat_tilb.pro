TEMPLATE = lib
TARGET +=
DEPENDPATH += .
INCLUDEPATH += . ../include
VPATH += ../include ../main

QT = core gui xml network

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

SOURCES = conn.cc \
    stat_dlg.cc \
    stat_tilb.cc \
    stat_tilb_sdlg.cc \
    stat_tilb_rdlg.cc \
    stat_tilb_xml.cc

FORMS = stat_tilb_sdlg.ui stat_tilb_rdlg.ui

HEADERS = conn.h \
    stat.h \
    stat_interf.h \
    stat_tilb.h \
    stat_tilb_sdlg.h \
    stat_tilb_rdlg.h \
    stat_tilb_xml.h
