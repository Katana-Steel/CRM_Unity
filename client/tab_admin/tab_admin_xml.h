#ifndef __tab_admin_xml_h
#define __tab_admin_xml_h
#include <QMap>
#include <QVector>
#include <QtXml>
#include "tab_admin_data.h"

class QComboBox;
class QTableWidget;

//! The Xml Handler.
/*!
    This handles the XML file returned from the server for
    the administration plugin.
 */
class XmlHnd : public QXmlDefaultHandler
{
    QMap<QString,QString> map; //!< the tag/value map of the document being parsed.
    QString curValue; //!< the value from the tag being read.
    QVector<UserData*> udat; //!< a UserDate buffer.
    QVector<MailRule*> rdat; //!< a MailRule buffer.
    UserData *curUser; //!< the current UserData recived from the server.
    MailRule *curRule; //!< the current MailRule recived from the server.
    bool err; //!< did we get an error message?
    bool success; //!< did we get a success message?
    void clearUdat();
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
    bool srvSuccess() { return success; };
    bool hasUserInfo() { return !udat.empty(); };
    bool hasMailRules() { return !rdat.empty(); };
    void loadUserInfo(QComboBox *cb);
    void loadMailRules(QTableWidget *tw);
};

#endif
