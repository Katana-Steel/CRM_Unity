/**************************************************************************
    This file: main/login.h is part of Helhed Client.

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
#ifndef __login_h
#define __login_h

#include "ui_login.h"
#include "conn.h"
#include <QDialog>

class QXmlSimpleReader;
class XmlHnd;
class QMessageBox;
class Stat;
/*! \class Login
 *  \brief The Login dialog
 *  \author René Kjellerup
 *  \version 0.4.17

   The login dialog is a very simple dialog with no border,
   two line inputs, a login button and close button.
*/
class Login : public QDialog, private Ui::login
{
    Q_OBJECT
    QString sVer;
public:
    Login(Conn *c=0, QWidget *parent=0);
    ~Login();
    void setServer(Conn *c) { conn = c; };
    QString servVersion() { return sVer; };

private:
    int retries;
    int cid;
    Conn *conn;
    XmlHnd *hnd;
    QXmlSimpleReader *xml;
    Stat *stat;
private slots:
    void doLogin();
    void doExit();
    void HttpDone(bool);
};

#endif
