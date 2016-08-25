#ifndef __stat_sogning_xml_h
#define __stat_sogning_xml_h

#include <QMap>
#include <QtXml>
#include "stat_sogning_data.h"

class Conn;

class XmlHnd : public QXmlDefaultHandler
{
    QMap<QString,QString> map;
    bool err;
    QString curValue;
    stat_knd curKnd;
    knddata kdata;
    stat_dato curDato;
    datodata ddata;
    unsigned int order;
    QVector<stat_knd> kndvec;
    QVector<stat_dato> datovec;
public:
    XmlHnd() : err(false),order(0) {};
    ~XmlHnd() {};

    bool startElement (const QString &namespaceURI, const QString &localName, 
                       const QString &qName, const QXmlAttributes &attributes);
    bool endElement (const QString &namespaceURI, const QString &localName,
                     const QString &qName);
    bool characters (const QString &str);
    bool fatalError(const QXmlParseException &exception);

    QString getValue (const QString &key) { return map[key]; };
    bool srvErr () { return err; };
    void dispRes(Conn *c,QWidget *parent);
};

#endif
