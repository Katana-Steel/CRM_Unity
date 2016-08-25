DEPENDPATH	= .
VPATH	= ../include ../main
AUTHOR	= René Kjellerup
TEMPLATE	= lib
EMAIL	= webmaster@keenan.dk
QT	= network gui core xml
LANGUAGE	= C++
INCLUDEPATH	= . ../include
CONFIG	+= debug_and_release plugin
LICENSE	= GPL

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
    DESTDIR = ../install
    unix:OBJECTS_DIR = ../plug_release
    RCC_DIR = release
    win32:dll_clean.commands = -@echo [File] - Cleaning dll build enviroment && del ..\release\stat_dll_res.o
}

SOURCES	= conn.cc \
	stat_dlg.cc \
	stat_sogning.cc \
	stat_sogning_dato.cc \
	stat_sogning_kunde.cc \
	stat_sogning_sdlg.cc \
    stat_sogning_xml.cc


FORMS	= stat_sogning_sdlg.ui stat_sogning_res_dlg.ui

HEADERS	= conn.h \
	stat.h \
	stat_interf.h \
	stat_sogning.h \
	stat_sogning_data.h \
	stat_sogning_dato.h \
	stat_sogning_kunde.h \
	stat_sogning_sdlg.h \
    stat_sogning_xml.h

