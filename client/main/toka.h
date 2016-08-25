/**************************************************************************
    This file: main/toka.h is part of Helhed Client.

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
#ifndef __toka_h
#define __toka_h

#include <QMenu>
class JData;
class QAction;
class Conn;
class MWin;
class MailList;

class TOKA : public QMenu
{
    Q_OBJECT
public:
    TOKA(Conn *c,JData *jd, const QPoint &pos, MWin *p=0);
    ~TOKA();
    void setJour(JData *jd);
    void setPos(const QPoint &pos);
private:
    JData *data;  //!< the Journal Data to be worked upon.
    Conn *conn;   //!< The HTTP communication object
    MWin *win;
    QAction *ShowJ;
    QAction *Delete;
    QAction *Print;
    QAction *toTilbud;
    QAction *toOrder;
    QAction *toKonsig;
    QAction *Mails;
    QAction *reEnable;
    QAction *Delivered;
private slots:
    MailList *GetDMails();
    void sendDelete();
    void to();
    void toTil();
    void toOrd();
    void toKon();
    void statusChk();
    void sendXMails();
    void showprint();
    void sendReEnable();
    void sendDelivered();
    void dispJour();
signals:
    void accept();
    void log(QString mod,QString msg, int lvl=0);
};

#endif
