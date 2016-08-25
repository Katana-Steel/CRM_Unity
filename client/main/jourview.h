/**************************************************************************
    This file: main/jourview.h is part of Helhed Client.

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
#ifndef __viewjour_h
#define __viewjour_h

#include <QtCore>
#include <QtGui>
#include "ui_jourview.h"

class JData;
class Conn;
class MWin;

class VJour : public QDialog, private Ui::jourview
{
    Q_OBJECT
public:
    VJour(MWin *w,Conn *c, QWidget *parent=0);
    ~VJour();

    void setJour(JData *jd);

private:
    JData *data;
    Conn *conn;
    MWin *win;

private slots:
    void sendDelete();
    void openPreview();
signals:
    void log(QString mod,QString msg,int lvl=0);
};

#endif
