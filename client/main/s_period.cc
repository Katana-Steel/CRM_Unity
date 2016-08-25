/**************************************************************************
    This file: main/s_period.cc is part of Helhed Client.

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
#include "s_period.h"

speriod::speriod(QWidget *parent) :
    QDialog(parent,Qt::Dialog|Qt::FramelessWindowHint)
{
    this->setAutoFillBackground(true);
    this->setBackgroundRole(QApplication::palette().Shadow);

    QHBoxLayout *hf = new QHBoxLayout(this);
    hf->setMargin(1);
    QFrame *f = new QFrame;
    hf->addWidget(f);

    QVBoxLayout *vf = new QVBoxLayout(f);

    hf = new QHBoxLayout;
    QLabel *txt = new QLabel("Fra Dato: ");
    Start = new QDateEdit(QDate::currentDate());
    hf->addWidget(txt);
    hf->addWidget(Start);
    vf->addLayout(hf);

    txt = new QLabel("Til Dato: ");
    End = new QDateEdit(QDate::currentDate().addMonths(2));
    hf = new QHBoxLayout;
    hf->addWidget(txt);
    hf->addWidget(End);
    vf->addLayout(hf);

    QPushButton *btn = new QPushButton("Ok");
    hf = new QHBoxLayout;
    hf->addStretch(5);
    hf->addWidget(btn);
    hf->addStretch(5);
    vf->addLayout(hf);

    f->resize(200,100);
    f->setAutoFillBackground(true);
    f->setBackgroundRole(QApplication::palette().Window);
    f->setLineWidth(2);
    f->setMidLineWidth(1);
    f->setFrameStyle(QFrame::Panel|QFrame::Raised);

    Start->setMinimumDate(Start->date());
    End->setMinimumDate(Start->date());

    connect(btn, SIGNAL(clicked()), this, SLOT(accept()));
}
