/**************************************************************************
    This file: main/xml_c_handle.h is part of Helhed Client.

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

    Copyright 2008, 2009 René Kjellerup aka Katana Steel
**************************************************************************/
#ifndef __xml_c_handle_h
#define __xml_c_handle_h

#include <QMap>
#include <QtXml>
#include "browser.h"
#include "k-j_data.h"
#include "s_data.h"
#include "st_data.h"
class Conn;
class MWin;

class XmlHnd : public QXmlDefaultHandler
{
    QMap<QString,QString> map;
    QString curValue;
    bool err;
    Conn *c;
public:
    XmlHnd() : err(false) {};
    ~XmlHnd() {};

    void setConn(Conn *_c) { c = _c; };

    bool startElement (const QString &namespaceURI, const QString &localName,
                       const QString &qName, const QXmlAttributes &attributes);
    bool endElement (const QString &namespaceURI, const QString &localName,
                     const QString &qName);
    bool characters (const QString &str);
    QString getValue (const QString &key) { return map[key]; };
    bool srvErr () { return err; };
    void RSTErr () { err = false; };
};

class JourHnd : public QXmlDefaultHandler
{
    QMap<QString,QString> map;
    QString curValue;
    bool err;
    bool j;
    bool k;
    bool cl;
    bool mail;
    bool success;
    QVector<KData*> kl;
    QVector<QString> ml;
    KData *kd;
    JData *jd;
    MWin *parent;
    void clearKL();
public:
    JourHnd(MWin *p) : err(false),j(false),k(false),cl(true),mail(false),success(false) { parent = p;};
    ~JourHnd() {};

    bool startElement (const QString &namespaceURI, const QString &localName,
                       const QString &qName, const QXmlAttributes &attributes);
    bool endElement (const QString &namespaceURI, const QString &localName,
                     const QString &qName);
    bool characters (const QString &str);
    QString getValue (const QString &key) { return map[key]; };
    bool srvErr () { return err; };
    bool resSuccess () { return success; };
    void clearML();
    int nid;

};

class SaleHnd : public QXmlDefaultHandler
{
    QMap<QString,QString> map;
    QString curValue;
    QVector<SData*> sl;
    QVector<QString> ml;
    SData *sd;
    MWin *parent;
    bool err;
    bool success;
    bool cs;
    bool l; // lev adr
public:
    SaleHnd(MWin *p) : err(false),success(false),cs(true),l(false) { parent = p; };
    ~SaleHnd() {};

    bool startElement (const QString &namespaceURI, const QString &localName,
                       const QString &qName, const QXmlAttributes &attributes);
    bool endElement (const QString &namespaceURI, const QString &localName,
                     const QString &qName);
    bool characters (const QString &str);
    QString getValue (const QString &key) { return map[key]; };
    bool srvErr () { return err; };
    bool resSuccess () { return success; };
    bool lev () { return l; };
    void clearSL();
    void clearML();

};

class StatHnd : public QXmlDefaultHandler
{
    QMap<QString,QString> map;
    QString curValue;
    bool err;
    bool success;
    MWin *parent;
public:
    StatHnd(MWin *p) : err(false),success(false) { parent = p; };
    ~StatHnd() {};

    bool startElement (const QString &namespaceURI, const QString &localName,
                       const QString &qName, const QXmlAttributes &attributes);
    bool endElement (const QString &namespaceURI, const QString &localName,
                     const QString &qName);
    bool characters (const QString &str);
    QString getValue (const QString &key) { return map[key]; };
    bool srvErr () { return err; };
    bool resSuccess () { return success; };

};
#endif
