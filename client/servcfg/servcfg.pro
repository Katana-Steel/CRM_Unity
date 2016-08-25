DEPENDPATH	= .
VPATH	= ../include ../main
AUTHOR	= René Kjellerup
TEMPLATE	= app
EMAIL	= webmaster(at)keenan(dot)dk
QT	= core gui xml
INCLUDEPATH	= . ../include ../main
CONFIG	+= debug_and_release
TARGET	= ServCFG

CONFIG(debug, debug|release) {
    OBJECTS_DIR = debug
    DESTDIR = ../
    } else {
    OBJECTS_DIR = release
    DESTDIR = ../install
}

SOURCES	= conf_xml.cc \
	config.cc \
	main.cc \
	mwin.cc

FORMS	= main.ui

HEADERS	= conf_xml.h \
	config.h \
	mwin.h

