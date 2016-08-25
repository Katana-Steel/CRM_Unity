#ifndef __tab_infiles_xml_h
#define __tab_infiles_xml_h
#include <QMap>
#include <QtXml>
#include "s_data.h"

//! The Xml Handler.
/*!
    This handles the XML file returned from the server for
    the infiles/large operations plugin.
 */
class XmlHnd : public QXmlDefaultHandler
{
    QMap<QString,QString> map; //!< the tag/value map of the document being parsed.
    QString curValue; //!< the value from the tag being read.
    bool err; //!< did we get an error message?
    bool success; //!< did we get a success message?
    SData curSD; //!< the current SData
    QVector<SData> SDList; //!< a list of SData
public:
    XmlHnd() : err(false),success(false) {};
    ~XmlHnd() {};

    bool startElement (const QString &namespaceURI, const QString &localName,
                       const QString &qName, const QXmlAttributes &attributes);
    bool endElement (const QString &namespaceURI, const QString &localName,
                     const QString &qName);
    bool characters (const QString &str);
    QString getValue (const QString &key) { return map[key]; };

    //! returns the error flag.
    bool srvErr () { return err; };
    //! returns the success flag.
    bool srvSuccess() { return success; };
    //! makes the SDList available.
    bool getSDList(QVector<SData> &sdata);
    void reset() { err = false; success = false; };
};

#endif
