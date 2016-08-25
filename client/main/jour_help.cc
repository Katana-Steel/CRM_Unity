/**************************************************************************
    This file: main/jour_help.cc is part of Helhed Client.

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
#include <QtGui>
#include "mwin.h"

void scalePixmap(QLabel *tico)
{
 QSize tico_sz(18,18);
 const QPixmap *icon;
 icon = tico->pixmap();
 if(icon) tico->setPixmap(icon->scaled(tico_sz,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
}

/** MWin::jourHelp()
 * --
 * the dialog to display an explaination of the icons used in the journal list.
 */
void
MWin::jourHelp()
{
 emit log("main/jour.cc","MWin::jourHelp");
 QDialog *win = new QDialog(this);
 QVBoxLayout *vbl = new QVBoxLayout(win);
 QLabel *tico = new QLabel;
 tico->setPixmap(QPixmap(QString(":/lst-tilbud.png")));
 scalePixmap(tico);
 QLabel *ttxt = new QLabel(QString(" <- Betyder Tilbud"));
 QHBoxLayout *thb = new QHBoxLayout;
 thb->addWidget(tico);
 thb->addWidget(ttxt);
 vbl->addLayout(thb);
 tico = new QLabel;
 tico->setPixmap(QPixmap(QString(":/lst-ordre.png")));
 scalePixmap(tico);
 ttxt = new QLabel(QString(" <- Betyder Ordre"));
 thb = new QHBoxLayout;
 thb->addWidget(tico);
 thb->addWidget(ttxt);
 vbl->addLayout(thb);
 tico = new QLabel;
 tico->setPixmap(QPixmap(QString(":/lst-lordre.png")));
 scalePixmap(tico);
 ttxt = new QLabel(QString(" <- Betyder Leveret Ordre"));
 thb = new QHBoxLayout;
 thb->addWidget(tico);
 thb->addWidget(ttxt);
 vbl->addLayout(thb);
 tico = new QLabel;
 tico->setPixmap(QPixmap(QString(":/lst-konsign.png")));
 scalePixmap(tico);
 ttxt = new QLabel(QString(" <- Betyder Konsignation"));
 thb = new QHBoxLayout;
 thb->addWidget(tico);
 thb->addWidget(ttxt);
 vbl->addLayout(thb);
 tico = new QLabel;
 tico->setPixmap(QPixmap(QString(":/lst-arbejd.png")));
 scalePixmap(tico);
 ttxt = new QLabel(QString(" <- Betyder Arbejdskort"));
 thb = new QHBoxLayout;
 thb->addWidget(tico);
 thb->addWidget(ttxt);
 vbl->addLayout(thb);
 tico = new QLabel;
 tico->setPixmap(QPixmap(QString(":/lst-salgsmaal.png")));
 scalePixmap(tico);
 ttxt = new QLabel(QString(" <- Betyder Salgsmål"));
 thb = new QHBoxLayout;
 thb->addWidget(tico);
 thb->addWidget(ttxt);
 vbl->addLayout(thb);
 tico = new QLabel;
 tico->setPixmap(QPixmap(QString(":/lst-slettet.png")));
 scalePixmap(tico);
 ttxt = new QLabel(QString(" <- Betyder Slettet Tilbud/Ordre/Konsignation/Arbejdskort"));
 thb = new QHBoxLayout;
 thb->addWidget(tico);
 thb->addWidget(ttxt);
 vbl->addLayout(thb);
 tico = new QLabel;
 tico->setPixmap(QPixmap(QString(":/lst-mail.png")));
 scalePixmap(tico);
 ttxt = new QLabel(QString(" <- Betyder Supplerende Mails"));
 thb = new QHBoxLayout;
 thb->addWidget(tico);
 thb->addWidget(ttxt);
 vbl->addLayout(thb);
 thb = new QHBoxLayout;
 thb->addStretch();
 QPushButton *done = new QPushButton(QString("Ok"));
 thb->addWidget(done);
 thb->addStretch();
 vbl->addLayout(thb);

 connect(done, SIGNAL(clicked()), win, SLOT(accept()));
 win->exec();
 delete win;
}
