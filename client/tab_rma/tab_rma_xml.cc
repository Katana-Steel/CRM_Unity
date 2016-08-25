#include <QtGui>
#include "tab_rma_xml.h"

XmlHnd::XmlHnd() :
    err(false)
{
}

//! the open tag has been encountered.
/*!
    Does we know the tag, and does we need to set someting
    up to parse this tag properly.

    This clears the value of curValue.
*/
bool
XmlHnd::startElement(const QString &/*namespaceURI*/, const QString &/*localName*/,
                          const QString &qName, const QXmlAttributes &/*attributes*/)
{
    if(qName == QString("res"))   { map.clear(); err = false; rma_list->clear(); }
    if(qName == QString("rma"))   {
        col = 0;
        rma_inf = new QTreeWidgetItem(rma_list);
        rma_dat = new QTreeWidgetItem(rma_inf);
    }
    if(qName == QString("vare"))   { col++; }
    /*
      A revision of how the 'rma_dat' object is handled regarding the 'col' counter
      is required.
      The first child of will contain the gross and the replacement gross.
     */
    if(qName == QString("data"))   { rma_dat = new QTreeWidgetItem(rma_inf); }
    curValue.clear();
    return true;
}

//! the close tag has been encountered.
/*!
    Does we know the tag then take the appropriate action.
    Else just add the tag to the tag/value map so the main
    program can get the value through getValue() if needed.
*/
bool
XmlHnd::endElement (const QString &/*namespaceURI*/, const QString &/*localName*/,
                         const QString &qName)
{
    if(qName == QString("res"))     return true;
    if(qName == QString("error"))   err = true;
    if(qName == QString("title"))   rma_inf->setText(0,curValue);
    if(qName == QString("type"))    {
        if(QString("K") == curValue)    {
            rma_dat->setText(0,"Kundens Svar");
        }
        if(QString("V") == curValue)    {
            rma_dat->setText(0,"Vores Svar ");
        }
        if(QString("I") == curValue)    {
            rma_inf->child(0)->setText(0,"RMA sag startet");
            if(!rma_dat->text(9).isEmpty())
                rma_inf->child(0)->setText(9,rma_dat->text(9));
            if(!rma_dat->text(10).isEmpty())
                rma_inf->child(0)->setText(10,rma_dat->text(10));
            delete rma_dat;
        }
    }

    if(qName == QString("id"))      rma_inf->setText(1,curValue);
    if(qName == QString("onr"))     rma_inf->setText(2,curValue);
    if(qName == QString("email"))   rma_inf->setText(3,curValue);
    if(qName == QString("dato"))    rma_inf->setText(4,curValue);
    if(qName == QString("vnr"))     rma_inf->child(0)->setText(2,curValue);
    if(qName == QString("vtxt"))    rma_inf->child(0)->setText(3,curValue);
    if(qName == QString("vstk"))    rma_inf->child(0)->setText(1,curValue);
    if(qName == QString("vpris"))   rma_inf->child(0)->setText(4,curValue);
    if(qName == QString("ddato"))   rma_dat->setText(9,curValue);
    if(qName == QString("msg"))     rma_dat->setText(10,curValue);
    if(qName == QString("sid") && map["type"] == QString("V"))     {
        QString tmp = rma_dat->text(0);
        tmp += "(" + curValue + ")";
        rma_dat->setText(0,tmp);
    }

    map[qName] = curValue;
    return true;
}

//! adds the data to curValue.
/*!
    This appends the data of the current tag to the
    curValue member.
*/
bool
XmlHnd::characters(const QString &str)
{
    curValue += str;
    return true;
}

void
XmlHnd::setTreeWidget(QTreeWidget *list)
{
    rma_list = list;
}
