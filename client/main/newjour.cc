/**************************************************************************
    This file: main/newjour.cc is part of Helhed Client.

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
#include "newjour.h"
#include "conn.h"
#include "k-j_data.h"

NJour::NJour(int kid, int uid, Conn *c, QWidget *parent)
    : QDialog(parent)
{
    conn=c;
    custid = QString::number(kid);
    setupUi(this);

    nkontakt->setDate(QDate::currentDate());
    usrlvl->addItem("Standand", uid);
    for(int i=1;i<uid;i++)
        usrlvl->addItem(QString::number(i), i);

    connect(insert, SIGNAL(clicked()), this, SLOT(transmit_journal()));
    connect(save,SIGNAL(clicked()), this, SLOT(reject()));
    connect(cancel,SIGNAL(clicked()), this, SLOT(accept()));
    title->setFocus();
}

void
NJour::transmit_journal()
{
    QString params = "ulvl="+ QString::number(usrlvl->itemData(usrlvl->currentIndex()).toInt());
    params += "&title=" + title->text();
    params += "&nota=" + nota->toPlainText();
    params += "&cust=" + custid;
    params += "&ndat=" + nkontakt->date().toString("yyyy-MM-dd");
    if(nid != QString("")) {
        params += "&nid=" + nid;
        conn->Command("update_jour", params);
    } else {
        conn->Command("create_jour", params);
    }
    accept();
}

void
NJour::addJournal(JData *jd)
{
    setWindowTitle("Rediger Journal");
    nid = QString::number(jd->nid);
    int sp = jd->title.indexOf(QChar(' '));
    title->setText(jd->title.mid(sp+1));
    nota->setText(jd->nota_text);
}
