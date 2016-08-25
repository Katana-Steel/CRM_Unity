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
    unix:OBJECTS_DIR = ../plug_release
    DESTDIR = ../install
    RCC_DIR = release
    win32:dll_clean.commands = -@echo [File] - Cleaning dll build enviroment && del ..\release\stat_dll_res.o
}

SOURCES	= conn.cc \
	stat_dlg.cc \
	stat_stklist.cc \
	stat_stklist_rdlg.cc \
	stat_stklist_sdlg.cc \
	stat_stklist_xml.cc


FORMS	= stat_stklist_sdlg.ui

HEADERS	= conn.h \
	stat.h \
	stat_interf.h \
	stat_stklist.h \
	stat_stklist_data.h \
	stat_stklist_rdlg.h \
	stat_stklist_sdlg.h \
	stat_stklist_xml.h
