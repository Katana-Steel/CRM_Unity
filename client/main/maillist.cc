/**************************************************************************
    This file: main/maillist.cc is part of Helhed Client.

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

#include "maillist.h"

/*! the MailList constructor.
 *
 *  @param[in] t      The table containing the mail list.
 *  @param[in] out    The line edit to compile the selected mails.
 *  @param[in] parent The parent widget, needed as per the QT definition.
 *
 *  The constructor creates the design of the mail
 *  selection dialog. It actually has 2 designs which
 *  are basicly the same one with 1 button and no line
 *  edit and one with 2 buttons and 1 line edit
 *  depending on whether 'out' is a valid pointer.
 *
 *  If 'out' is not a valid pointer one will be created
 *  internally and the dialog will be able to return
 *  positive or negative, and the created line edit will
 *  be added to the design.
 *
 *  On the other hand if 'out' is a valid pointer. It is
 *  assumed that it is handled by the calling function
 *  and it will not be added to the design nor will the
 *  dialog be able to return positively.
 */
MailList::MailList (QTableWidget *t, QLineEdit *out, QWidget *parent) :
    QDialog(parent,Qt::Dialog)
{
    QVBoxLayout *m_win = new QVBoxLayout(this);
    QHBoxLayout *btn_box = 0;
    QPushButton *done = 0;
    QPushButton *cancel = 0;
    if(out) lineout = out;
    else {
        lineout = new QLineEdit();
        m_win->addWidget(lineout);
        done = new QPushButton("Ok");
        cancel = new QPushButton("Annuller");
        btn_box = new QHBoxLayout;
        btn_box->addWidget(done);
        btn_box->addStretch();
        btn_box->addWidget(cancel);
    }
    m_win->addWidget(t);
    if(!btn_box) {
        cancel = new QPushButton("luk");
        btn_box = new QHBoxLayout;
        btn_box->addStretch();
        btn_box->addWidget(cancel);
    }
    m_win->addLayout(btn_box);
    connect(cancel, SIGNAL(clicked()),this, SLOT(reject()));
    if(done) connect(done, SIGNAL(clicked()),this, SLOT(accept()));
    connect(t, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(insertMail(QTableWidgetItem*)));
}

QString
MailList::res(void)
{
    if(lineout) {
        return lineout->text();
    }
    return QString("");
}

void
MailList::insertMail(QTableWidgetItem *twi)
{
    QString sep = (lineout->text()==QString("")) ? QString("") : QString(";");
    lineout->setText(lineout->text()+sep+twi->text());
}
