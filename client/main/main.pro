DEPENDPATH	= .
VPATH	= ../include
AUTHOR	= René Kjellerup
TEMPLATE	= app
EMAIL	= rk (dot) katana (dot) steel (at) keenan (dot) dk
QT	= core gui xml network
INCLUDEPATH	= . ../include
TARGET	= helhed
win32:RC_FILE	+= helhed.rc
LICENSE	= GPL
RESOURCES	= helhed.qrc
CONFIG += debug_and_release warn_off
#unix:QMAKE_CXXFLAGS += -fPIC
CONFIG(debug, debug|release) {
    OBJECTS_DIR = ../debug
    DESTDIR = ../
    CONFIG += console
} else {
    OBJECTS_DIR = ../release
    DESTDIR = ../install
}

SOURCES	= about.cc \
    browser.cc \
	conf_xml.cc \
	config.cc \
	conn.cc \
	jour.cc \
	jour_help.cc \
	jourview.cc \
	log.cc \
	login.cc \
	maillist.cc \
	main.cc \
	mwin.cc \
	newjour.cc \
	next_contact.cc \
    s_data_list.cc \
    s_period.cc \
	salg.cc \
	stat.cc \
	stat_dlg.cc \
	toka.cc \
	xml_jour_hnd.cc \
	xml_login_hnd.cc \
	xml_sale_hnd.cc \
	xml_stat_hnd.cc

FORMS	= login.ui \
	mwin.ui \
	jourview.ui \
	newjour.ui

HEADERS	= browser.h \
	conf_xml.h \
	config.h \
    conn.h \
	jourview.h \
	k-j_data.h \
	log.h \
	login.h \
	maillist.h \
	mwin.h \
	newjour.h \
	next_contact.h \
	s_data.h \
    s_period.h \
    st_data.h \
    stat.h \
    stat_interf.h \
    tab_interf.h \
	toka.h \
    xml_c_handle.h


