#include "stat_sogning_xml.h"
#include "stat_sogning_kunde.h"
#include "stat_sogning_dato.h"
#include "conn.h"

bool
XmlHnd::startElement(const QString &/*namespaceURI*/, const QString &/*localName*/,
                       const QString &qName, const QXmlAttributes &/*attributes*/)
{
    if(qName == QString("res")) { err = false; map.clear(); kndvec.clear(); datovec.clear(); }
    if(qName == QString("kdat")) {
        if(order == 1 || order == 3) {
            curKnd.kunde.clear();
            curKnd.data.clear();
        } else {
            curDato.dato.clear();
            curDato.data.clear();
        }
    }
    if(qName == QString("type")) {
        if(order == 1 || order == 3) {
            kdata.clear();
        } else {
            ddata.clear();
        }
    }
    curValue.clear();
    return true;
}

bool
XmlHnd::endElement(const QString &/*namespaceURI*/, const QString &/*localName*/,
                       const QString &qName)
{
    if(qName == QString("error")) err = true;
    if(qName == QString("order")) order = curValue.toInt();
    if(order == 1 || order == 3) { // sorted by custommer number
      if(qName == QString("knr")) curKnd.kunde.kunde_nr = curValue;
      if(qName == QString("kfirma")) curKnd.kunde.Firma = curValue;
      if(qName == QString("katt")) curKnd.kunde.Att = curValue;
      if(qName == QString("kadr")) curKnd.kunde.Adr = curValue;
      if(qName == QString("kpost")) curKnd.kunde.PostBy = curValue;
      if(qName == QString("kby")) curKnd.kunde.PostBy += " " + curValue;
      if(qName == QString("nr")) kdata.toka_nr = curValue;
      if(qName == QString("lev")) kdata.lev = curValue;
      if(qName == QString("dato")) kdata.dato = curValue;
      if(qName == QString("stk")) kdata.stk = curValue;
      if(qName == QString("vnr")) kdata.vnr = curValue;
      if(qName == QString("vtxt")) kdata.vtxt = curValue;
      if(qName == QString("type")) curKnd.data.push_back(kdata);
      if(qName == QString("kdat")) kndvec.push_back(curKnd);
    }
    if(order == 2) { // sorted by date
      if(qName == QString("dato")) curDato.dato = curValue;
      if(qName == QString("knr")) ddata.kunde.kunde_nr = curValue;
      if(qName == QString("kfirma")) ddata.kunde.Firma = curValue;
      if(qName == QString("katt")) ddata.kunde.Att = curValue;
      if(qName == QString("kadr")) ddata.kunde.Adr = curValue;
      if(qName == QString("kpost")) ddata.kunde.PostBy = curValue;
      if(qName == QString("kby")) ddata.kunde.PostBy += " " + curValue;
      if(qName == QString("nr")) ddata.toka_nr = curValue;
      if(qName == QString("lev")) ddata.lev = curValue;
      if(qName == QString("type")) curDato.data.push_back(ddata);
      if(qName == QString("kdat")) datovec.push_back(curDato);
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

bool
XmlHnd::fatalError(const QXmlParseException &exception)
{
    err = true;
    map["parseerror"] = exception.message() + "\nat Line nr: '" + QString::number(exception.lineNumber())+"'";
    return false;
}

void
XmlHnd::dispRes(Conn *c,QWidget *parent)
{
    QDialog *win;
    if(order == 0) return;
    if(order == 1 || order == 3) {
        ResKndDlg *tmp = new ResKndDlg(kndvec,c,parent);
        tmp->setSQL(map["sqlstr"]);
        tmp->setType(order);
        win = tmp;
    } else {
        win = new ResDatoDlg(datovec,c,parent);
    }
    win->exec();
    delete win;
}
