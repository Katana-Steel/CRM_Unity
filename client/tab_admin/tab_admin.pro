DEPENDPATH	= .
VPATH	= ../include ../main
AUTHOR	= René Kjellerup
TEMPLATE	= lib
TARGET = tab_admin
EMAIL	= webmaster@keenan.dk
QT	= network gui core xml
LANGUAGE	= C++
INCLUDEPATH	= . ../include
CONFIG	+= debug_and_release plugin
LICENSE	= GPL

win32:QMAKE_EXTRA_TARGETS = dll_clean

CONFIG(debug, debug|release) {
    DESTDIR = ../plugins
    OBJECTS_DIR = ../debug
    unix:OBJECTS_DIR = ../plug_debug
    RCC_DIR = debug
    win32:dll_clean.commands = -@echo [File] - Cleaning dll build enviroment && del ..\debug\tab_dll_res.o
} else {
    OBJECTS_DIR = ../release
    unix:OBJECTS_DIR = ../plug_release
    DESTDIR = ../install
    RCC_DIR = release
    win32:dll_clean.commands = -@echo [File] - Cleaning dll build enviroment && del ..\release\tab_dll_res.o
}
win32:PRE_TARGETDEPS = dll_clean

win32:RC_FILE += tab_dll.rc

SOURCES	= conn.cc \
	stat_dlg.cc \
	tab_admin.cc \
    tab_admin_xml.cc


FORMS	= tab_admin2.ui

HEADERS	= conn.h \
	stat.h \
	tab_interf.h \
	tab_admin.h  \
    tab_admin_xml.h

