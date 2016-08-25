#ifndef __stat_tilb_xml_h
#define __stat_tilb_xml_h

#include <QMap>
#include <QtXml>
#include "st_data.h"

class Conn;
class QWidget;

class XmlHnd : public QXmlDefaultHandler
{
    QMap<QString,QString> map;
    QString curValue;
    QVector<CustNr> c_list;
    CustNr curCust;
    bool err;
    bool success;
public:
    XmlHnd() : err(false),success(false) {};
    ~XmlHnd() {};
    
    bool startElement (const QString &namespaceURI, const QString &localName, 
                       const QString &qName, const QXmlAttributes &attributes);
    bool endElement (const QString &namespaceURI, const QString &localName,
                     const QString &qName);
    bool characters (const QString &str);
    QString getValue (const QString &key) { return map[key]; };
    bool srvErr () { return err; };
    bool resSuccess () { return success; };
    int dispRes(QWidget *parent,Conn *c);
};

#endif
