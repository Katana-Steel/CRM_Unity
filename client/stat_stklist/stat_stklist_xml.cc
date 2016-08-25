#include "stat_stklist_xml.h"
#include "stat_stklist_rdlg.h"
#include "stat_stklist_data.h"

bool
XmlHnd::startElement(const QString &/*namespaceURI*/, const QString &/*localName*/,
                       const QString &qName, const QXmlAttributes &/*attributes*/)
{
    if(qName == QString("res"))  { curDat = 0; err = false; map.clear(); clearData(); }
    if(qName == QString("item")) { curDat = new ItemData; }
    curValue.clear();
    return true;
}

bool
XmlHnd::endElement(const QString &/*namespaceURI*/, const QString &/*localName*/,
                       const QString &qName)
{
    if(qName == QString("error")) err = true;
    if(qName == QString("stk"))   curDat->stk  = curValue;
    if(qName == QString("vnr"))   curDat->vnr  = curValue;
    if(qName == QString("vtxt"))  curDat->vtxt = curValue;
    if(qName == QString("item"))  dat.push_back(curDat);

    map[qName] = curValue;
    return true;
}

bool
XmlHnd::characters(const QString &str)
{
    curValue += str;
    return true;
}

void
XmlHnd::clearData()
{
    if(!dat.empty()) {
        for(int i=0;i<dat.size();i++)
        {
            delete dat.at(i);
       }
       dat.clear();
    }
}

void
XmlHnd::dispRes(QWidget *parent)
{
    ResDlg *win = new ResDlg(parent);
    win->setWindowTitle("Resultat vdr. \""+ map["str"]+"\" <"+ map["flags"]+">");
    win->setFromDato(map["fdat"]);
    win->setToDato(map["tdat"]);
    win->addData(&dat);
    win->exec();
    delete win;
}
