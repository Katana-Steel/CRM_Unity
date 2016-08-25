/**************************************************************************
    This file: main/conn.cc is part of Helhed Client.

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

    Copyright 2008, 2009, 2010 René Kjellerup aka Katana Steel
**************************************************************************/
#include <QtGui>
#include <QtNetwork>
#include "conn.h"

Conn::Conn(QString _h, QString script, bool ssl, QObject *parent) :
    QNetworkAccessManager(parent),cid(0),tls(ssl)
{
    QString h = "http";
    if(ssl) h += "s";
    h += "://" + _h + script;
    url= QUrl(h);
    auth = new QAuthenticator();
    connect(this, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestDone(QNetworkReply*)));
    data = new QFile("tmp.dat",this);
    data->open(QIODevice::ReadWrite|QIODevice::Truncate|QIODevice::Text|QIODevice::Unbuffered);
}

Conn::~Conn()
{
    delete auth;
    data->close();
    data->remove();
    delete data;
}

void
Conn::setUser(const QString &usr)
{
    auth->setUser(usr);
}

void
Conn::setPass(const QString &pwd)
{
    auth->setPassword(pwd);
}

void
Conn::setUserPass(const QString &usr, const QString &pwd)
{
    auth->setUser(usr);
    auth->setPassword(pwd);
}

void
Conn::setcid(QString str)
{
    cid = str.toInt(0,16);
}

void
Conn::errorLog(void)
{
    data->close();
    if(!data->copy("errorLog.xml")) {
        if(data->remove("errorLog.xml")) data->copy("errorLog.xml");
    }
}

void
Conn::requestDone(QNetworkReply *rep)
{
    QByteArray d((const char*)(0),0);
    url.setEncodedQuery(d);
    QTextStream out(this->data);
    out << rep->readAll();
}

QString
Conn::getU()
{
    return this->auth->user();
}

QFile*
Conn::Data()
{
    this->data->flush();
    return this->data;
}

void
Conn::addQueryItem(const QString &key, const QString &value)
{
    this->url.addQueryItem(key,value);
}

void
Conn::Command(const QString &cmd)
{
    if(data->isOpen())
    {
        data->close();
        while(data->isOpen()) {;}
    }
    data->open(QIODevice::ReadWrite|QIODevice::Truncate|QIODevice::Text|QIODevice::Unbuffered);
    url.addQueryItem("cmd",cmd);
    if(cmd == QString("login")) {
    url.addQueryItem("user",auth->user());
    url.addQueryItem("pass",auth->password());
    } else {
        url.addQueryItem("cid",QString::number(cid,16));
    }
    QByteArray d(url.encodedQuery());
    this->post(QNetworkRequest(url),d);
}
