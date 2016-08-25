/**************************************************************************
    This file: main/jour.cc is part of Helhed Client.

    Helhed Client is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Helhed Client is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helhed Client.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2008, 2009, 2010 René Kjellerup aka Katana Steel
**************************************************************************/
#include <QtCore>
#include <QtGui>
#include "mwin.h"
#include "stat.h"
#include "xml_c_handle.h"
#include "jourview.h"
#include "newjour.h"
#include "toka.h"
#include "log.h"

/*
 *
 * --
 *
 */
void
MWin::addJournal(JData *jd)
{
    jlist.push_back(jd);
}

/*
 * MWin::clearCust()
 * --
 * resets the Custommer Info and Journal data
 */
void
MWin::clearCust()
{
    emit log("main/jour.cc","clearCust: Clearing the customer sheet");
    cus.clear();
    mwin::date->clear();
    knr_in->clear();
    navn->clear();
    att->clear();
    adr->clear();
    post->clear();
    by->clear();
    land->clear();
    ean_se->clear();
    email->clear();
    tlf->clear();
    fax->clear();
    mobil->clear();
    notat->clear();
    land->clear();
    ean_se->clear();
    selectMail->setCurrentIndex(0);
    mailIdx = 0;
    mwin::create->setEnabled(false);
    clearJournal();
    clrSale();
}

/*
 * MWin::clearJournal()
 * --
 * clears the Journal data and
 * the journal list.
 */
void
MWin::clearJournal()
{
    emit log("main/jour.cc","clearJournal: Clearing the journal list.");
    if(!jlist.empty()) {
        int size = jlist.size();
        for(int i=0;i<size;i++)
        {
            JData *j = jlist[0];
            jlist.pop_front();
            delete j;
        }
    }
    mwin::jour->clear();
    mwin::jour->setDragDropMode(QAbstractItemView::NoDragDrop);
    mwin::jour->setDragEnabled(false);
    mwin::jour->setAcceptDrops(false);
}

/*
 *
 * --
 *
 */
void
MWin::createCus()
{
    if(QMessageBox::question(this,"Helhed",
    "Er alle oplysningerne korrekte og\nvil du fortsætte med oprettelsen af kunde?",
    QMessageBox::Yes,QMessageBox::No,0) == QMessageBox::No) return;
    emit log("main/jour.cc","createCus: Creating a customer");
    cus.clear();
    saveCust();
}

/*
 *
 * --
 *
 */
void
MWin::createJour()
{
    emit log("main/jour.cc","createJour: opening the Journal Writer");
    if(newjour == 0) newjour = new NJour(cus.kid,usr,conn);
    if(newjour->exec() == QDialog::Accepted) {
        delete newjour;
        newjour = 0;
    }
}

/*
 *
 * --
 *
 */
void
MWin::dispCD()
{
    emit log("main/jour.cc","dispCD: Displaying Customer Data");
    mwin::date->setText("Oprettet d. "+cus.dato);
    knr_in->setText(cus.knr);
    navn->setText(cus.navn);
    att->setText(cus.att);
    adr->setText(cus.adr);
    post->setText(cus.post);
    by->setText(cus.by);
    land->setText(cus.land);
    ean_se->setText(cus.ean_se);
    tlf->setText(cus.tlf);
    fax->setText(cus.fax);
    mobil->setText(cus.mobil);
    if(cus.email.size()>0) email->setText(cus.email[0]);
    notat->setPlainText(cus.nota);
}

/*
 *
 * --
 *
 */
void
MWin::dispJD()
{
    emit log("main/jour.cc","dispJD: Displaying Journal data");
    jour->clear();
    mwin::show->setEnabled(false);
    for(int i=0;i<jlist.size();i++)
    {
        if(jour_filter && jlist_filter == jlist[i]->type)
            jlist[i]->addAsItem(jour);
        else if(!jour_filter)
            jlist[i]->addAsItem(jour);
    }
}

/*
 *
 * --
 *
 */
void
MWin::dispJour()
{
    emit log("main/jour.cc","MWin::dispJour");
    JData *jd = new JData;
    jd->nid = nid;
    for(int i=0;i<jlist.size();i++)
    {
        if(*jd == *(jlist[i])){
            delete jd;
            jd = jlist[i];
            break;
        }
    }
    tw = new VJour(this,conn,this);
    connect(tw, SIGNAL(log(QString,QString,int)), theLog, SLOT(log(QString,QString,int)));
    tw->setJour(jd);
    tw->exec();
    delete tw;
}

void
MWin::editJournal(JData *jd)
{
    emit log("main/jour.cc","MWin::editJournal");
    if(newjour == 0) newjour = new NJour(cus.kid,usr,conn);
    newjour->addJournal(jd);
    createJour();
}

void
MWin::endToka()
{
    emit log("main/jour.cc","MWin::endToka");
    if(toka_w) delete toka_w;
    toka_w = 0;
    toka_triggered = false;
}

/*
 *
 * --
 *
 */
void
MWin::getCust()
{
    emit log("main/jour.cc","MWin::getCust");
    clearJournal();
    conn->addQueryItem("kid", QString::number(cus.kid));
    conn->Command("k_seek");
}

/*
 *
 * --
 *
 */
KData*
MWin::getCusData()
{
    emit log("main/jour.cc","MWin::getCusData");
    return &cus;
}

/*
 * MWin::initTabsJournal()
 * --
 * this initiates objects and sets up
 * connections of the Journal interface.
 */
void
MWin::initTabsJournal()
{
    emit log("main/jour.cc","MWin::initTabsJournal");

    newjour = 0;
    jlist_filter = JData::NONE;
    jour_filter = false;
    toka_w = 0;
    toka_triggered = false;

    cus.clear(); // holds the customer data
    jhnd = new JourHnd(this); // create the Journal XML handler

    connect(clearCustBtn, SIGNAL(clicked()), this, SLOT(clearCust()));
    connect(seek, SIGNAL(clicked()), this, SLOT(SeekCus()));
    connect(jour, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(NidFromItem(QListWidgetItem*)));
    connect(jour, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(dispJour()));
    connect(jour, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(toka(const QPoint&)));
    connect(jourSort, SIGNAL(currentIndexChanged(int)), this, SLOT(setJourSort(int)));
    connect(knr_in, SIGNAL(returnPressed()),this, SLOT(SeekCus()));
    connect(navn, SIGNAL(returnPressed()),this, SLOT(SeekCus()));
    connect(att, SIGNAL(returnPressed()),this, SLOT(SeekCus()));
    connect(adr, SIGNAL(returnPressed()),this, SLOT(SeekCus()));
    connect(post, SIGNAL(returnPressed()),this, SLOT(SeekCus()));
    connect(by, SIGNAL(returnPressed()),this, SLOT(SeekCus()));
    connect(mwin::show, SIGNAL(clicked()), this, SLOT(dispJour()));
    connect(mwin::create, SIGNAL(clicked()), this, SLOT(createJour()));
    connect(mwin::clearCus, SIGNAL(clicked()), this, SLOT(createCus()));
    connect(mwin::save, SIGNAL(clicked()), this, SLOT(saveCust()));
    connect(selectMail, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(multi_mail(const QString &)));
    connect(email, SIGNAL(returnPressed()),this, SLOT(store_email()));
}

/*
 * MWin::KidFromItem(QListWidgetItem *)
 * --
 *
 */
void
MWin::KidFromItem(QListWidgetItem *li)
{
    emit log("main/jour.cc","MWin::KidFromItem");
    cus.kid = li->type();
}

/*
 * MWin::KidFromItem_get(QListWidgetItem *)
 * --
 *
 */
void
MWin::KidFromItem_get(QListWidgetItem *li)
{
    emit log("main/jour.cc","MWin::KidFromItem_get");
    cus.kid = li->type();
    getCust();
}

/*
 * MWin::multi_mail(const QString &)
 * --
 * this handles the assigning of one or more emails
 * to the same customer
 */
void
MWin::multi_mail(const QString &)
{
  emit log("main/jour.cc","MWin::multi_mail");
  int mail = cus.email.size();
  QString tmp = mwin::email->text();
  mwin::email->clear();
  if(tmp != QString("")){
    if(mailIdx < mail){
      if(tmp != cus.email[mailIdx]) cus.email.replace(mailIdx,tmp);
    } else cus.email.push_back(tmp);
  }
  if(mail > 0) {
    if(selectMail->currentIndex() < mail) {
      tmp = cus.email[selectMail->currentIndex()];
      mwin::email->setText(tmp);
    }
  }
  mailIdx = selectMail->currentIndex();
}

/*
 *
 * --
 *
 */
void
MWin::NidFromItem(QListWidgetItem *li)
{
    emit log("main/jour.cc","MWin::NidFromItem");
    mwin::show->setEnabled(true);
    nid = li->type();
}

/*
 * MWin::ParseJour()
 * --
 * examens the server reply using JourHnd (xml_jour_hnd.cc)
 * which is a XML handler.
 */
void
MWin::ParseJour()
{
    emit log("main/jour.cc","MWin::ParseJour");
    QFile *file;
    xml->setContentHandler(jhnd);
    if(conn->Data()->isOpen())
    {
        file = conn->Data();
        file->reset();
        file->close();
        QXmlInputSource *XFile = new QXmlInputSource(file);
        if(!xml->parse(*XFile))
        {
            XFile->setData(conn->Data(1));
            if(!xml->parse(XFile)) {
                conn->errorLog();
                delete XFile;
                return;
            }
        }
        if(jhnd->srvErr())
        {
            QMessageBox *mb = new QMessageBox("Helhed",
            jhnd->getValue("error"),QMessageBox::Warning,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            mb->exec();
            delete XFile;
            conn->errorLog();
            delete mb;
            return;
        }
        if(jhnd->resSuccess())
        {
            QMessageBox *mb = new QMessageBox("Helhed",
            jhnd->getValue("success"),QMessageBox::Information,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            mb->exec();
            delete XFile;
            delete mb;
            getCust();
            return;
        }
        if(tmp) {
            tabWidget->setCurrentIndex(2);
            tmp = false;
        }
    }
}

/*
 * MWin::saveCust()
 * --
 * creates a new or updates an existing
 * customer.
 */
void
MWin::saveCust()
{
    emit log("main/jour.cc","MWin::saveCust");
    if(cus.knr != knr_in->text() && cus.kid != 0) {
        if(QMessageBox::question(this,"Helhed",
        "Du er ved at opdatere kunden nummeret!\nVil du fortsætte?",
        QMessageBox::Yes,QMessageBox::No,0) == QMessageBox::No) return;
    }
    QString req = "knr="+knr_in->text();
    req += "&navn="+navn->text();
    req += "&att="+att->text();
    req += "&adr="+adr->text();
    req += "&post="+post->text();
    req += "&by="+by->text();
    req += "&land="+land->text();
    req += "&eanse="+ean_se->text();
    req += "&email=";
    for(int i = 0;i<cus.email.size();i++) {
        if(i>0) req += ";"; // seperate the emails with a ;
        req += cus.email[i];
    }
    if(cus.email.size() == 0 && mwin::email->text().contains('@'))
        req += mwin::email->text();
    req += "&tlf="+tlf->text();
    req += "&fax="+fax->text();
    req += "&mobil="+mobil->text();
    req += "&notat="+notat->toPlainText();
    if(cus.kid != 0) req += "&kid="+QString::number(cus.kid);
    conn->Command("update",req);
    SeekCus();
    return;
}

/*
 * MWin::SeekCus()
 * --
 * sends a search request and then calls clearCust()
 */
void
MWin::SeekCus()
{
    emit log("main/jour.cc","MWin::SeekCus");
//    QMessageBox::information(this,"Kunde nr",knr_in->text());
    QString empty("");
    if(knr_in->text() != empty)
    { conn->addQueryItem("knr", knr_in->text()); }
    else if(navn->text() != empty)
    { conn->addQueryItem("knavn", navn->text()); }
    else if(att->text() != empty)
    { conn->addQueryItem("katt", att->text()); }
    else if(adr->text() != empty)
    { conn->addQueryItem("kadr", adr->text()); }
    else if(post->text() != empty)
    { conn->addQueryItem("kpost", post->text()); }
    else if(by->text() != empty)
    { conn->addQueryItem("kby", by->text()); }
    conn->Command("k_seek");
    clearCust();
    stat = new Stat(lstr("Søget Kunde"),this);
    stat->place();
    stat->exec();
    delete stat;
    stat = 0;
}

/*
 *
 * --
 *
 */
void
MWin::setCustomer(KData kd)
{
    emit log("main/jour.cc","MWin::setCustomer");
    mwin::create->setEnabled(true);
    cus = kd;
    dispCD();
}

/*
 *
 * --
 *
 */
void
MWin::setJourSort(int idx)
{
    switch(idx)
    {
    case 0:
        jour_filter = false;
        break;
    case 1:
        jour_filter = true;
        jlist_filter = JData::NONE;
        break;
    case 2:
        jour_filter = true;
        jlist_filter = JData::T;
        break;
    case 3:
        jour_filter = true;
        jlist_filter = JData::O;
        break;
    case 4:
        jour_filter = true;
        jlist_filter = JData::K;
        break;
    case 5:
        jour_filter = true;
        jlist_filter = JData::A;
        break;
    case 6:
        jour_filter = true;
        jlist_filter = JData::S;
        break;
    case 7:
        jour_filter = true;
        jlist_filter = JData::X;
        break;
    case 8:
        jour_filter = true;
        jlist_filter = JData::M;
        break;
    }
    dispJD();
}

/*
 *
 * --
 *
 */
void
MWin::showKList(QVector<KData*> &kl)
{
    emit log("main/jour.cc","MWin::showKList");
    QDialog *w = new QDialog;
    w->setModal(true);
    QListWidget *list = new QListWidget;
    QVBoxLayout *vlay = new QVBoxLayout(w);
    vlay->addWidget(list);

    QPushButton *ok = new QPushButton(lstr("Indsæt"));
    QPushButton *can = new QPushButton("Annuller");
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(ok);
    hbox->addWidget(can);
    vlay->addLayout(hbox);

    connect(can, SIGNAL(clicked()), w, SLOT(reject()));
    connect(list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(KidFromItem(QListWidgetItem*)));
    connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(KidFromItem_get(QListWidgetItem*)));
    connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), w, SLOT(accept()));
    connect(ok, SIGNAL(clicked()), this, SLOT(getCust()));
    connect(ok, SIGNAL(clicked()), w, SLOT(accept()));

    for(int i=0;i<kl.size();i++)
    {
        QListWidgetItem *l = new QListWidgetItem(list,kl[i]->kid);
        l->setText(kl[i]->knr + QString(", ") + kl[i]->navn + QString(" ") + kl[i]->att + QString(", ") +kl[i]->post + QString(" ") + kl[i]->by );
    }

    w->exec();
    delete w;
}

/*
 * MWin::store_email()
 * --
 * adds or removes an email from the internal list,
 * which is displayed using
 */
void
MWin::store_email()
{
  emit log("main/jour.cc","MWin::store_email");
  int mail = cus.email.size();
  if(mwin::email->text() != QString("")){
    if(mailIdx < mail){
      if(mwin::email->text() != cus.email[mailIdx]) cus.email.replace(mailIdx,mwin::email->text());
    } else cus.email.push_back(mwin::email->text());
  } else {
    cus.email.remove(mailIdx,1);
  }
}

/*! Shows the TOKA menu.
 *
 *  This creates and display the TOKA menu at
 *  the location of the right click of the
 *  mouse.
 */
void
MWin::toka(const QPoint &pos)
{
  emit log("main/jour.cc","MWin::toka");
  if(cus.kid != 0) {
    JData *jd = new JData;
    jd->nid = nid;
    jd->sid = QString("");
    for(int i=0;i<jlist.size();i++)
    {
        if(*jd == *(jlist[i])){
            delete jd;
            jd = jlist[i];
            break;
        }
    }
    if(jd->sid != QString("")) {
        shnd->clearSL();
        if(toka_w) {
             toka_w->setJour(jd);
             toka_w->setPos(jour->mapToGlobal(pos));
        } else {
            toka_w = new TOKA(conn,jd,jour->mapToGlobal(pos),this);
            connect(toka_w, SIGNAL(log(QString,QString,int)), theLog, SLOT(log(QString,QString,int)));
            connect(toka_w, SIGNAL(accept()), this, SLOT(endToka()));
            connect(toka_w, SIGNAL(triggered(QAction*)), this, SLOT(TokaTrigger()));
        }
        toka_w->exec();
        if(!toka_triggered) { endToka(); return; }
    }
  }
}

//! Set the TOKA triggered flag.
void
MWin::TokaTrigger()
{
    emit log("main/jour.cc","MWin::TokaTrigger");
    toka_triggered = true;
}
