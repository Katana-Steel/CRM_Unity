#include "stat_tilb_xml.h"
#include "stat_tilb_rdlg.h"
#include "conn.h"

bool
XmlHnd::startElement(const QString &/*namespaceURI*/, const QString &/*localName*/,
                          const QString &qName, const QXmlAttributes &/*attributes*/)
{
    if(QString("res") == qName) { c_list.clear(); err = false; success = false; map.clear(); }
    if(QString("tlist") == qName) { curCust.clear(); }
    curValue.clear();
    return true;
}

bool
XmlHnd::endElement (const QString &/*namespaceURI*/, const QString &/*localName*/,
                         const QString &qName)
{
    if(qName == QString("res")) return true;
    if(qName == QString("error")) err = true; 
    if(qName == QString("success")) success = true; 
    if(qName == QString("tlist")) { c_list.push_back(curCust); }
    if(qName == QString("knr")) { curCust.cust.knr = curValue; }
    if(qName == QString("kid")) { curCust.cust.kid = curValue.toInt(); }
    if(qName == QString("firma")) { curCust.cust.navn = curValue; }
    if(qName == QString("name")) { curCust.cust.att = curValue; }
    if(qName == QString("tnr")) { 
        TOKAnr tmp;
        tmp.nr = curValue;
        curCust.list.push_back(tmp); 
    }
    map[qName] = curValue;
    return true;
}

bool 
XmlHnd::characters(const QString &str)
{
    curValue += str;
    return true;
}

int
XmlHnd::dispRes(QWidget *parent,Conn *c)
{
    ResDialog *win = new ResDialog(c_list,c,parent);
    win->exec();
    delete win;
    return 0;
}
