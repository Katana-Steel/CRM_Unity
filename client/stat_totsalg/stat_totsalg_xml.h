#ifndef __stat_tilb_xml_h
#define __stat_tilb_xml_h

#include <QMap>
#include <QtXml>
#include <QVector>
#include "stat_totsalg_data.h"

class Conn;

class XmlHnd : public QXmlDefaultHandler
{
    QMap<QString,QString> map;
    QString curValue;
    QVector<Salger> s_list;
    Salger curSalger;
    SalgData curOrder;
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
    int dispRes(Conn *c,QWidget *parent);
};

#endif
