#ifndef __tab_rma_xml_h
#define __tab_rma_xml_h 1
#include <QMap>
#include <QtXml>

class QTreeWidget;

class XmlHnd : public QXmlDefaultHandler
{
    QMap<QString,QString> map;
    QString curValue;
    QStringList strList;
    bool err;
    int col;
    QTreeWidget *rma_list;
    QTreeWidgetItem *rma_inf;
    QTreeWidgetItem *rma_dat;
//    bool success;
public:
    XmlHnd();
    bool startElement (const QString &namespaceURI, const QString &localName,
                       const QString &qName, const QXmlAttributes &attributes);
    bool endElement (const QString &namespaceURI, const QString &localName,
                     const QString &qName);
    bool characters (const QString &str);
    QString getValue (const QString &key) { return map[key]; };
    void setTreeWidget(QTreeWidget *list);


    //! returns the error flag.
    bool srvErr () { return err; };
/*    //! returns the success flag.
    bool srvSuccess() { return success; }; */
};

#endif
