/**************************************************************************
    This file: main/stat_dlg.cc is part of Helhed Client.

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
#include "stat.h"

//! the status message dialog constructor.
Stat::Stat(const QString &msg, QWidget *parent) :
    QDialog(parent,Qt::Dialog|Qt::FramelessWindowHint)
{
    this->setAutoFillBackground(true);
    this->setBackgroundRole(QPalette::Shadow);
    QHBoxLayout *hb = new QHBoxLayout(this);
    hb->setMargin(1);
    QLabel *lab = new QLabel(msg);
    hb->addWidget(lab);
    lab->setAutoFillBackground(true);
    lab->setBackgroundRole(QPalette::Window);
    lab->setLineWidth(2);
    lab->setMidLineWidth(1);
    lab->setFrameStyle(QFrame::Panel|QFrame::Raised);
    lab->setAlignment(Qt::AlignCenter);
}

//! Places the status message dialog.
/*!
    Places the status message dialog on the center of the
    screen and makes sure it doesn't fill to much but enough
    to show the message.
*/
void
Stat::place()
{
    QRect ct = this->geometry();
    ct.setWidth(250);
    if(ct.height() < 50 || ct.height() > 100) ct.setHeight(50);
    ct.moveCenter(QApplication::desktop()->availableGeometry().center());
    this->setGeometry(ct);
}
