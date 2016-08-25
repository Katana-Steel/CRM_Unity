/**************************************************************************
    This file: main/about.cc is part of Helhed Client.

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

QString
MWin::version()
{
    return QString("1.1.0");
}

void
MWin::AboutDialog()
{
 emit log("main/about.cc","Creating & Displaying AboutDialog");
 QDialog *win = new QDialog(this,Qt::Tool);
 QVBoxLayout *vbl = new QVBoxLayout(win);
 vbl->setAlignment(Qt::AlignHCenter);
 QLabel *ttxt = new QLabel(QString("Helheds Modul"));
 QHBoxLayout *thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 ttxt = new QLabel(QString("Klient Version:"));
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 ttxt = new QLabel(this->version());
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 ttxt = new QLabel(QString(" "));
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 ttxt = new QLabel(QString("Copyright 2006-2010 René Kjellerup"));
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 ttxt = new QLabel(QString("Created by Alchemiestick IS"));
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 ttxt = new QLabel(QString("In association with Evalsystems"));
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 ttxt = new QLabel(QString(" "));
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 ttxt = new QLabel(QString("Published under the terms of GNU General Public License"));
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 ttxt = new QLabel(QString("version 2.0 this means the Program is free of use and at"));
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 ttxt = new QLabel(QString("your option you may request the source code and modify"));
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 ttxt = new QLabel(QString("the program to your needs. For full explanations under"));
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 ttxt = new QLabel(QString("which conditions please examine the COPYING and the LICENSE"));
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 ttxt = new QLabel(QString("files."));
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 ttxt = new QLabel(QString(" "));
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(ttxt);
 thb->addStretch();
 vbl->addLayout(thb);
 QPushButton *done = new QPushButton(QString("Luk"));
 QSizePolicy sp = done->sizePolicy();
 QRect rc = done->geometry();
 sp.setHorizontalPolicy(QSizePolicy::Fixed);
 rc.setWidth(50);
 thb = new QHBoxLayout;
 thb->addStretch();
 thb->addWidget(done);
 thb->addStretch();
 done->setSizePolicy(sp);
 done->setGeometry(rc);
 vbl->addLayout(thb);

 win->setWindowTitle("Om Helhed");
 win->setSizeGripEnabled(false);

 connect(done, SIGNAL(clicked()), win, SLOT(accept()));
 win->exec();
 delete win;
}
