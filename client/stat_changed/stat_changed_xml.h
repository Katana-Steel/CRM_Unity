#ifndef __stat_changed_xml_h
#define __stat_changed_xml_h 1

#include <QMap>
#include <QtXml>

class XmlHnd : public QXmlDefaultHandler
{
    QMap<QString,QString> map;
    bool err;
    QString curValue;
public:
    XmlHnd() : err(false) {};
    bool startElement (const QString &namespaceURI, const QString &localName,
                       const QString &qName, const QXmlAttributes &attributes);
    bool endElement (const QString &namespaceURI, const QString &localName,
                     const QString &qName);
    bool characters (const QString &str);
    QString getValue (const QString &key) { return map[key]; };
    bool srvErr () { return err; };
};

#endif
