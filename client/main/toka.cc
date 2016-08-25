/**************************************************************************
    This file: main/toka.cc is part of Helhed Client.

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

    Copyright 2008, 2009 René Kjellerup aka Katana Steel
**************************************************************************/
#include <QtCore>
#include <QtGui>
#include "toka.h"
#include "k-j_data.h"
#include "conn.h"
#include "mwin.h"
#include "stat.h"
#include "maillist.h"

TOKA::TOKA(Conn *c,JData *jd,const QPoint &pos,MWin *p) :
    QMenu("TOKAX",p)
{
    data = jd;
    conn = c;
    win = p;

    setPos(pos);

    ShowJ     = addAction(tr("Vis Journal"),       this->parent(),  SLOT(dispJour())      );
    Delete    = addAction(tr("Slet"),              this,            SLOT(sendDelete())    );
    reEnable  = addAction(tr("Gør Gyldig"),        this,            SLOT(sendReEnable())  );
    toTilbud  = addAction(tr("Til Nyt Tilbud"),    this,            SLOT(toTil())         );
    toOrder   = addAction(tr("Til Ordre"),         this,            SLOT(toOrd())         );
    toKonsig  = addAction(tr("Til Konsignation"),  this,            SLOT(toKon())         );
    Delivered = addAction(tr("Leveret"),           this,            SLOT(sendDelivered()) );
    Print     = addAction(tr("Vis Udskrift"),      this,            SLOT(showprint())     );
    Mails     = addAction(tr("Send Ekstra Mails"), this,            SLOT(sendXMails())    );

    connect(ShowJ, SIGNAL(triggered()), this, SLOT(dispJour()));

    statusChk();
    emit log("main/toka.cc","*  'TOKA'  * Created");
}

TOKA::~TOKA()
{
    emit log("main/toka.cc","*  'TOKA'  * Destroyed");
}

void
TOKA::setJour(JData *jd)
{
    emit log("main/toka.cc","TOKA::setJour");
    data = jd;
    statusChk();
}

void
TOKA::setPos(const QPoint &pos)
{
    emit log("main/toka.cc","TOKA::setPos");
    QRect rc = this->geometry();
    rc.setTopLeft(pos);
    this->setGeometry(rc);
}

MailList *
TOKA::GetDMails()
{
    emit log("main/toka.cc","TOKA::GetDMails");
    QTableWidget *lst = new QTableWidget;
    int i;
    lst->setColumnCount(3);
    for(i=0;i<3;i++) {
        lst->setColumnWidth(i,120);
        lst->setHorizontalHeaderItem(i,new QTableWidgetItem(""));
    }
    QStringList str_lst = data->nota_text.split(' ');
    QString str;
    i=0;
    foreach(str, str_lst) {
        if(!str.contains('@')) continue;
        str = str.remove("<br>");
        if(i%3 == 0) { lst->insertRow(i/3); lst->setRowHeight(i/3,22); }
        lst->setItem(i/3,i%3,new QTableWidgetItem(str));
        i++;
    }
    return new MailList(lst,0,win);
}

void
TOKA::sendDelete()
{
    emit log("main/toka.cc","TOKA::sendDelete");
    if(QMessageBox::critical(this,"Helhed", "Vil du virkelig Annullere\ndette nr: '" + data->nr +"'?",
        QMessageBox::Yes,QMessageBox::No, QMessageBox::NoButton) == QMessageBox::No ) return;
    MailList *mail = GetDMails();
    mail->show();
    QRect rc = mail->rect();
    mail->hide();
    rc.setWidth(450);
    mail->resize(QSize(rc.width(),rc.height()));
    if (mail->exec() == QDialog::Accepted) {
      QString email = mail->res();
      conn->Command("kill_order","case="+QString::number(data->nid)+"&k_email="+email);
    }
    delete mail;
    emit accept();
}

void
TOKA::sendReEnable()
{
    emit log("main/toka.cc","TOKA::sendReEnable");
    if(data->type == JData::NONE) {
        win->editJournal(data);
    } else {
     if(QMessageBox::critical(this,"Helhed", "Vil du virkelig gøre\ndette nr: '" + data->nr +"' aktivt igen?",
        QMessageBox::Yes,QMessageBox::No, QMessageBox::NoButton) == QMessageBox::No ) return;
     conn->Command("reenable","case="+QString::number(data->nid));
    }
    emit accept();
}

void
TOKA::sendDelivered()
{
    emit log("main/toka.cc","TOKA::sendDelivered");
    if(QMessageBox::critical(this,"Helhed", "Er dette nr: '" + data->nr +"'\nblevet leveret?",
        QMessageBox::Yes,QMessageBox::No, QMessageBox::NoButton) == QMessageBox::No ) return;
    conn->Command("delivered","case="+QString::number(data->nid));
    emit accept();
}

void
TOKA::statusChk()
{
    emit log("main/toka.cc","TOKA::statusChk");
    reEnable->setVisible(false);
    Delivered->setVisible(false);
    ShowJ->setVisible(true);
    Delete->setVisible(true);
    toTilbud->setVisible(true);
    toOrder->setVisible(true);
    toKonsig->setVisible(true);
    Print->setVisible(true);
    Mails->setVisible(true);

    switch(data->type)
    {
     case JData::S:
        if(conn->getUA() < SLG_ACCESS) {
            toTilbud->setVisible(false);
            toOrder->setVisible(false);
            toKonsig->setVisible(false);
            Mails->setVisible(false);
            Delete->setVisible(false);
            break;
        } else
            toTilbud->setText(tr("Til Nyt Salgsmål"));
     case JData::T:
        Delete->setText("Annuller");
        break;
     case JData::O:
        if(data->lev == JData::IACT) Delivered->setVisible(true);
     case JData::K:
        toOrder->setText("Til Arbejdskort");
        toKonsig->setVisible(false);
        toTilbud->setVisible(false);
        break;
     case JData::A:
        toOrder->setVisible(false);
        toKonsig->setVisible(false);
        toTilbud->setVisible(false);
        Delete->setVisible(false);
        break;
     case JData::NONE:
        Print->setVisible(false);
        reEnable->setText("Rediger Journal");
     default:
        toTilbud->setVisible(false);
        toOrder->setVisible(false);
        toKonsig->setVisible(false);
        Mails->setVisible(false);
        Delete->setVisible(false);
        break;
    }
    if(data->status == JData::IACT) {
        if(data->sid == conn->getU() || conn->getToka() > 8 ) {
            reEnable->setVisible(true);
        } else {
            Delete->setVisible(false);
        }
        toOrder->setVisible(false);
        toKonsig->setVisible(false);
        toTilbud->setVisible(false);
    }
}

void
TOKA::sendXMails()
{
    emit log("main/toka.cc","TOKA::sendXMails");
    conn->Command("get_mail","nid="+QString::number(data->nid));
    emit accept();
}

void
TOKA::showprint()
{
    emit log("main/toka.cc","TOKA::showprint");
    conn->Command("get_print","onr="+data->nr);
    emit accept();
}

void
TOKA::to()
{
    emit log("main/toka.cc","TOKA::to");
    win->setCurrentTab(2);
}

void
TOKA::toTil()
{
    emit log("main/toka.cc","TOKA::toTil");
    to();
    if(JData::S == data->type) {
        win->setCurrentType(4);
        conn->Command("toka","type=S&nr="+data->nr);
    } else {
        win->setCurrentType(0);
        conn->Command("toka","type=T&nr="+data->nr);
    }
    win->stat = new Stat("Henter "+ toTilbud->text().mid(4),win);
    win->stat->place();
    win->stat->exec();
    delete win->stat;
    win->stat = 0;
    emit accept();
}

void
TOKA::toOrd()
{
    emit log("main/toka.cc","TOKA::toOrd");
    to();
    if(data->type == JData::T || data->type == JData::S) {
        win->setCurrentType(1);
        conn->Command("toka","type=O&nr="+data->nr);
    } else {
        win->setCurrentType(3);
        conn->Command("toka","type=A&nr="+data->nr);
    }
    win->stat = new Stat("Henter "+ toOrder->text().mid(4),win);
    win->stat->place();
    win->stat->exec();
    delete win->stat;
    win->stat = 0;
    emit accept();
}

void
TOKA::toKon()
{
    emit log("main/toka.cc","TOKA::toKon");
    to();
    win->setCurrentType(2);
    conn->Command("toka","type=K&nr="+data->nr);
    win->stat = new Stat("Henter "+ toKonsig->text().mid(4),win);
    win->stat->place();
    win->stat->exec();
    delete win->stat;
    win->stat = 0;
    emit accept();
}

void
TOKA::dispJour()
{
    emit log("main/toka.cc","TOKA::dispJour");
    emit accept();
}
