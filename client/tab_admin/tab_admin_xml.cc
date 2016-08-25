#include "tab_admin_xml.h"
#include <QComboBox>
#include <QCheckBox>
#include <QTableWidget>

#define PTR sizeof(char*);

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
    if(qName == QString("res")) { map.clear(); udat.clear(); rdat.clear(); err=false; success=false; }
    if(qName == QString("user")) { curUser = new UserData; }
    if(qName == QString("rule")) { curRule = new MailRule; curRule->clear(); }
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
    if(qName == QString("res")) return true;
    if(qName == QString("error")) err = true;
    if(qName == QString("success")) success = true;
    if(qName == QString("user"))     { udat.push_back(curUser); return true; }
    if(qName == QString("username")) curUser->userName = curValue;
    if(qName == QString("tokanr"))   curUser->tokaNr = curValue;
    if(qName == QString("usrnr"))    curUser->usrNr = curValue;
    if(qName == QString("fname"))    curUser->fname = curValue;
    if(qName == QString("lname"))    curUser->lname = curValue;
    if(qName == QString("email"))    curUser->email = curValue;
    if(qName == QString("mobil"))    curUser->mobil = curValue;
    if(qName == QString("tlf"))      curUser->tlf = curValue;

    if(qName == QString("rule")) { rdat.push_back(curRule); return true; }
    if(qName == QString("id")) curRule->id = curValue.toInt();
    if(qName == QString("active")) curRule->active = (curValue.toInt() == 1);
    if(qName == QString("type")) curRule->type = curValue;
    if(qName == QString("cond")) curRule->cond = curValue;
    if(qName == QString("test")) curRule->test = curValue;
    if(qName == QString("list")) curRule->list = curValue;

    map[qName] = curValue;
    return true;
}

//! adds the data to curValue.
/*!
    This appends the data of the current tag to
    the curValue member.
*/
bool
XmlHnd::characters(const QString &str)
{
    curValue += str;
    return true;
}

//! Fill the UserList.
/*!
    First it checks that the User combo box is
    empty and if not it clears it in an orderly
    fashion. Fills the User combo box with the
    user data from the udat buffer.
*/
void
XmlHnd::loadUserInfo(QComboBox *cb)
{
    UserData *dat;
    while(cb->count()>0)
    {
        #if __LP64__ == 1
            dat = (UserData*)cb->itemData(0).toLongLong();
        #else
            dat = (UserData*)cb->itemData(0).toInt();
        #endif
        cb->removeItem(0);
        delete dat;
    }
    foreach(dat,udat) {
        #if __LP64__ == 1
            cb->addItem(dat->userName,(long long)dat);
        #else
            cb->addItem(dat->userName,(int)dat);
        #endif
    }
}

//! Fill the Mail Rule table.
/*!
    First it checks that the table is empty and
    if not it clears. Fills the table with the
    mailrules from the rdat buffer.
*/
void
XmlHnd::loadMailRules(QTableWidget *tw)
{
    QTableWidgetItem *twi;
    QCheckBox *cbx;
    MailRule *mr;
    QFontMetrics fmx = tw->fontMetrics();
    while(tw->rowCount() != 0)
        tw->removeRow(0);

    foreach(mr, rdat) {
        int r = tw->rowCount();
        tw->insertRow(r);

        cbx = new QCheckBox();
        cbx->setTristate(false);
        if(mr->active)
            cbx->setCheckState(Qt::Checked);
        else
            cbx->setCheckState(Qt::Unchecked);

        twi = new QTableWidgetItem(mr->id);
        twi->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        tw->setItem(r,0,twi);
        tw->setCellWidget(r,0,cbx);
        tw->setColumnWidth(0,45);

        twi = new QTableWidgetItem(mr->type);
        twi->setFlags(Qt::ItemIsSelectable);
        tw->setItem(r,1,twi);
        tw->setColumnWidth(1,40);

        twi = new QTableWidgetItem(mr->cond);
        twi->setFlags(Qt::ItemIsSelectable);
        tw->setItem(r,2,twi);

        twi = new QTableWidgetItem(mr->test);
        tw->setItem(r,3,twi);

        twi = new QTableWidgetItem(mr->list);
        tw->setItem(r,4,twi);

        tw->setRowHeight(r,20);

        int w = tw->columnWidth(4);
        if(w < (fmx.width(mr->list)+20))
            tw->setColumnWidth(4,fmx.width(mr->list)+20);
    }
}
