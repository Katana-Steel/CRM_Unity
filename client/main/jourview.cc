/**************************************************************************
    This file: main/jourview.cc is part of Helhed Client.

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
#include "jourview.h"
#include "k-j_data.h"
#include "conn.h"
#include "mwin.h"

VJour::VJour(MWin *w, Conn *c, QWidget *parent)
    :   QDialog(parent)
{
    win = w;
    conn = c;
    setupUi(this);
    emit log("main/jourview.cc","*  'VJour'  * Created");
}

VJour::~VJour()
{
    emit log("main/jourview.cc","*  'VJour'  * Destroyed");
}

void
VJour::setJour(JData *jd)
{
    emit log("main/jourview.cc","VJour::setJour");
    data = jd;
    if(jd->dato != QString("")) {
        QString icon;
        nr->setText(jd->nr);
        Luk_lab->hide();
        luk->hide();
        switch(jd->type)
        {
        case JData::T:
            icon = QString::fromUtf8(":/lst-tilbud.png");
            nr_txt->setText("Tilbuds nr:");
            Luk_lab->show();
            luk->show();
            break;
        case JData::O:
            icon = QString::fromUtf8(":/lst-ordre.png");
            nr_txt->setText("Ordre nr:");
            break;
        case JData::K:
            icon = QString::fromUtf8(":/lst-konsign.png");
            nr_txt->setText("Konsignation nr:");
            break;
        case JData::A:
            icon = QString::fromUtf8(":/lst-arbejd.png");
            nr_txt->setText("Arbejdskort nr:");
            break;
        case JData::S:
            icon = QString::fromUtf8(":/lst-salgsmaal.png");
            nr_txt->setText("Salgsmål nr:");
            break;
        case JData::X:
            icon = QString::fromUtf8(":/lst-slettet.png");
            nr_txt->setText("Slettet nr:");
            break;
        case JData::M:
            icon = QString::fromUtf8(":/lst-mail.png");
            nr_txt->setText("Ekstra mails til nr:");
            break;
        case JData::NONE:
            icon = QString::fromUtf8(":/phone.png");
            nr_txt->setText("");
            nr->setText("");
            Title->setText(jd->nr);
            break;
        default:
            icon = QString::fromUtf8(":/fax.png");
            nr_txt->setText("Felj i type. ");
            break;
        }
        setWindowIcon(QIcon(icon));
        luk->setValue(jd->luk);
        dato->setText(jd->dato);
        nota_text->setHtml(jd->nota_text);
        sid->setText(jd->sid);
    }
}

void
VJour::sendDelete()
{
    emit log("main/jourview.cc","VJour::sendDelete");
    if(QMessageBox::critical(this,"Helhed", "Vil du virkelig Annullere\ndette nr: '" + data->nr +"'?",
        QMessageBox::Yes,QMessageBox::No, QMessageBox::NoButton) == QMessageBox::No ) return;
    bool ok;
    QString email = QInputDialog::getText(this,"Helhed","Indtast E-Mails\n(adskildt af comma eller semi-colon)",QLineEdit::Normal,QString(),&ok);
    if(!ok) return;
    conn->Command("kill_order","case="+data->sid+"&k_email="+email);
    accept();
}

void
VJour::openPreview()
{
    emit log("main/jourview.cc","VJour::openPreview");
    win->modul = MWin::P;
    conn->Command("print","case="+data->sid);
}
