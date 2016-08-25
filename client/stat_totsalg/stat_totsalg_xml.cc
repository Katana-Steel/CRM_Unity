#include "stat_totsalg_xml.h"
#include "stat_totsalg_rdlg.h"

bool XmlHnd::startElement(const QString &/*namespaceURI*/, const QString &/*localName*/,
                          const QString &qName, const QXmlAttributes &/*attributes*/)
{
    if(qName == QString("res")) { s_list.clear(); err = false; success = false; map.clear(); }
    if(qName == QString("salger")) { curSalger.clear(); }
    if(qName == QString("order")) { curOrder.clear(); }
    curValue.clear();
    return true;
}

bool XmlHnd::endElement (const QString &/*namespaceURI*/, const QString &/*localName*/,
                         const QString &qName)
{
    if(qName == QString("res")) return true;
    if(qName == QString("error")) err = true; 
    if(qName == QString("success")) success = true; 
    if(qName == QString("salger")) { s_list.push_back(curSalger); return true; }
    if(qName == QString("order")) { curSalger.orders.push_back(curOrder); return true; }
    if(qName == QString("id")) { curSalger.name.id = curValue; }
    if(qName == QString("nr")) { curOrder.id = curValue; }
    if(qName == QString("salg")) { curSalger.name.salg = curValue; }
    if(qName == QString("bytte")) { curSalger.name.bytte = curValue; }
    if(qName == QString("total")) { curSalger.name.total = curValue; }
    if(qName == QString("osalg")) { curOrder.salg = curValue; }
    if(qName == QString("obytte")) { curOrder.bytte = curValue; }
    if(qName == QString("ototal")) { curOrder.total = curValue; }
    map[qName] = curValue;
    return true;
}

bool XmlHnd::characters(const QString &str)
{
    curValue += str;
    return true;
}

int
XmlHnd::dispRes(Conn *c,QWidget *parent)
{
    ResDialog *win = new ResDialog(s_list,c,parent);
    win->setDate(map["from"],map["to"]);
    win->exec();
    delete win;
    return 0;
}
