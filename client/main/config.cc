/**************************************************************************
    This file: main/config.cc is part of Helhed Client.

    Helhed Client is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Helhed Client is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helhed Client.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2008, 2009, 2010 René Kjellerup aka Katana Steel
**************************************************************************/
#include <QtCore>
#include <QtGui>
#include "config.h"
#include "conn.h"
#include "conf_xml.h"

Config::Config(const QString &filename) :
    _ws(""),_ss(""),_ssl(false),_fs(""),_fsp(""),_fu(""),_fp(""),_fd(""),_fsize("")
{
    QFile *file = new QFile(filename);
    if(file->exists()) file->open(QIODevice::ReadOnly|QIODevice::Text|QIODevice::Unbuffered);
    else { delete file; return; }
    ConfHnd *hnd = new ConfHnd;
    QXmlSimpleReader *xml = new QXmlSimpleReader;
    xml->setContentHandler(hnd);
        QXmlInputSource *XFile = new QXmlInputSource(file);
        if(!xml->parse(*XFile))
        {
            delete XFile;
            delete xml;
            delete hnd;
            file->close();
            delete file;
        }
        _ws = hnd->getValue("webhost");
        _ss = hnd->getValue("apppath");
        _ssl = (hnd->getValue("ssl") == QString("1")) ? true : false;
        _fs = hnd->getValue("ftphost");
        _fsp = hnd->getValue("ftpport");
        _fu = hnd->getValue("ftpuser");
        _fp = hnd->getValue("ftppass");
        _fd = hnd->getValue("ftppath");
        _ftd = hnd->getValue("ftptmp");
        _fsize = hnd->getValue("font_size");
        _style = hnd->getValue("style");
        delete XFile;
    delete xml;
    delete hnd;
    file->close();
    delete file;
}

Conn*
Config::getConn()
{
    return new Conn(_ws,_ss,_ssl);
}

QStyle*
Config::getStyleHint()
{
    QStyle *ret=0;
    if(_style == QString("CDE"))
        ret = new QCDEStyle;
    if(_style == QString("plastique"))
        ret = new QPlastiqueStyle;
#ifdef WIN32
    if(_style == QString("winxp"))
        ret = new QWindowsXPStyle;
#endif
    if(_style == QString("cleanlooks") || !ret)
        ret = new QCleanlooksStyle;
    return ret;
}
