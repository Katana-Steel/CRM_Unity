/**************************************************************************
    This file: main/login.cc is part of Helhed Client.

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
#include "login.h"
#include "xml_c_handle.h"
#include "stat.h"

Login::Login (Conn *c, QWidget *parent) :
    QDialog(parent,Qt::Dialog|Qt::FramelessWindowHint),retries(3),cid(0)
{
    QFrame *f = new QFrame(this);
    setupUi(f);
    xml = new QXmlSimpleReader;
    hnd = new XmlHnd;
    stat = 0;
    setModal(true);
    if(c==0) {
        conn = new Conn;
    } else {
        conn = c;
    }
    hnd->setConn(conn);
    xml->setContentHandler(hnd);
    f->setLineWidth(2);
    f->setMidLineWidth(1);
    f->setFrameStyle(QFrame::Panel|QFrame::Raised);
    pass->setEchoMode(QLineEdit::Password);
    user->setFocus();
    sVer = QString("");

    connect (lbtn, SIGNAL(clicked()), this, SLOT(doLogin()));
    connect (qbtn, SIGNAL(clicked()), this, SLOT(doExit()));
    connect (conn, SIGNAL(done(bool)), this, SLOT(HttpDone(bool)));
}

Login::~Login()
{
    conn->disconnect(this);
    delete xml;
    delete hnd;
}

void
Login::doExit()
{
    reject();
}
void
Login::doLogin()
{
    if(user->text().isEmpty())
    {
        user->setFocus();
        return;
    }
    conn->setUser(user->text());
    if(pass->text().isEmpty())
    {
        pass->setFocus();
        return;
    }
    if(retries < 1) { reject(); return; }
    conn->setPass(pass->text());
    conn->Command("login");
    stat = new Stat("Sender Login...",this);
    stat->place();
    stat->exec();
    delete stat;
    stat = 0;
}

void
Login::HttpDone(bool)
{
    QFile *file = conn->Data();
    if(stat != 0) {
        stat->accept();
    }
    if(!file->isOpen())
        file->open(QIODevice::ReadOnly|QIODevice::Text);
    if(file->isOpen())
    {
        file->reset();
        QXmlInputSource *XFile = new QXmlInputSource(file);
        if(!xml->parse(*XFile))
        {
            XFile->setData(conn->Data(1));
            if(!xml->parse(XFile)) {
                conn->errorLog();
                delete XFile;
                return;
            }
        }
        if(hnd->srvErr())
        {
            QMessageBox *mb = new QMessageBox("Helhed",
            hnd->getValue("error"),QMessageBox::Critical,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            delete XFile;
            conn->errorLog();
            retries--;
    	    hnd->RSTErr();
            mb->exec();
            return;
        }
        if(!hnd->getValue("version").isNull()) sVer = hnd->getValue("version");
        delete XFile;
        if(conn->CID() != 0)
        {
            conn->setUA(hnd->getValue("usr").toInt());
            conn->setToka(hnd->getValue("toka").toInt());
            accept();
        } else {
            retries--;
        }
        if(retries < 0) reject();
    }
}
