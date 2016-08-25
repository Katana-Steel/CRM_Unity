/**************************************************************************
    This file: main/config.h is part of Helhed Client.

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
#ifndef __config_h
#define __config_h

class QString;
class QStyle;
class Conn;

class Config
{
    QString _ws;
    QString _ss;
    bool _ssl;
    QString _fs;
    QString _fsp;
    QString _fu;
    QString _fp;
    QString _fd;
    QString _ftd;
    QString _fsize;
    QString _style;
public:
    Config(const QString &filename);

    QString webserver() { return _ws; };
    QString serverscript() { return _ss; };
    QString ftpserver() { return _fs; };
    QString ftpport() { return _fsp; };
    QString ftpuser() { return _fu; };
    QString ftppass() { return _fp; };
    QString ftpdir() { return _fd; };
    QString ftptmpdir() { return _ftd; };
    QString dfontsz() { return _fsize; };

    Conn *getConn();
    QStyle* getStyleHint();
};

extern Config *cfg;
#endif
