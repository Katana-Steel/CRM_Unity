/**************************************************************************
    This file: include/k-j_data.h is part of Helhed Client.

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
#ifndef __k_j_data_h
#define __k_j_data_h 1

#include <QtCore>
#include <QtGui>

class KData
{
public:
    int kid;
    QString knr;
    QString navn;
    QString att;
    QString adr;
    QString post;
    QString by;
    QString land;
    QString ean_se;
    QVector<QString> email;
    QString tlf;
    QString fax;
    QString mobil;
    QString nota;
    QString dato;
    void clear() {
        kid=0;
        knr.clear();
        navn.clear();
        att.clear();
        adr.clear();
        post.clear();
        by.clear();
        land.clear();
        ean_se.clear();
        email.clear();
        tlf.clear();
        fax.clear();
        mobil.clear();
        nota.clear();
        dato.clear();
    };
};

class JData
{
public:
    int nid;
    QString sid;
    QString nr;
    enum tp{ NONE,T,O,K,A,S,X,M };
    tp type;
    QString dato;
    QString title;
    QString nota_text;
    int luk;
    enum _st { IACT,ACT };
    _st status;
    _st lev;
    void addAsItem(QListWidget *listbox)
    {
        QListWidgetItem *i = new QListWidgetItem(listbox,nid);
        switch(type)
        {
        case NONE:
            title = dato +", "+ nr;
            break;
        case T:
            title = dato +", nr: "+nr;
            i->setIcon(QIcon(QString::fromUtf8(":/lst-tilbud.png")));
            break;
        case O:
            title = dato +", nr: "+nr;
            if(lev == ACT) {
             title += " L";
             i->setIcon(QIcon(QString::fromUtf8(":/lst-lordre.png")));
            } else {
             i->setIcon(QIcon(QString::fromUtf8(":/lst-ordre.png")));
            }
            break;
        case K:
            title = dato +", nr: "+nr;
            i->setIcon(QIcon(QString::fromUtf8(":/lst-konsign.png")));
            break;
        case A:
            title = dato +", nr: "+nr;
            i->setIcon(QIcon(QString::fromUtf8(":/lst-arbejd.png")));
            break;
        case S:
            title = dato +", nr: "+nr;
            i->setIcon(QIcon(QString::fromUtf8(":/lst-salgsmaal.png")));
            break;
        case X:
            title = dato +", nr: "+nr;
            i->setIcon(QIcon(QString::fromUtf8(":/lst-slettet.png")));
            break;
        case M:
            title = dato +", til nr: "+nr;
            i->setIcon(QIcon(QString::fromUtf8(":/lst-mail.png")));
            break;
        };
        i->setText(QApplication::translate("mwin", title.toUtf8(), 0, QApplication::UnicodeUTF8));
        nota_text.replace("\n","<br>\n");
    };
    bool operator==(const JData &o) { return this->nid == o.nid; };
};

#endif
