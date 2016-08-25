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
    QNetworkAccessManager(parent),cid(0),tls(ssl),lastReply(""),expected()
{
    QString h = "http";
    if(ssl) h += "s";
    h += "://" + _h + script;
    url = QUrl(h);
    auth = new QAuthenticator();
    connect(this, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestDone(QNetworkReply*)));
    connect(this, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError>&)), this, SLOT(sslErr(QNetworkReply*, const QList<QSslError>&)));
    data = new QFile("tmp.dat",this);
    data->open(QIODevice::ReadWrite|QIODevice::Truncate|QIODevice::Text|QIODevice::Unbuffered);
    if(ssl) {
        QList<QSslCertificate> cert = QSslCertificate::fromPath(QLatin1String("plugins/server.cert"));
        expected.append(QSslError(QSslError::SelfSignedCertificate, cert.at(0)));

    }
    reply = 0;
}

Conn::~Conn()
{
    delete auth;
    data->close();
    data->remove();
    delete data;
}

QString
Conn::getU()
{
    return auth->user();
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
    if(reply) data->write(reply->errorString().toAscii());
    data->flush();
    data->close();
    if(!data->copy("errorLog.xml")) {
        if(data->remove("errorLog.xml")) data->copy("errorLog.xml");
    }
    reply = 0;
}

void
Conn::requestDone(QNetworkReply *rep)
{
    if(rep->error() == QNetworkReply::NoError) {
        rep->waitForReadyRead(-1);
        QByteArray d((const char*)(0),0);
        url.setEncodedQuery(d);
        QTextStream out(this->data);
        this->lastReply = rep->readAll();
        out << this->lastReply;
        data->flush();

        emit done(true);
    } else {
        reply = rep;
        errorLog();

        emit done(false);
    }
}

void
Conn::sslErr(QNetworkReply *r, const QList<QSslError> &lSslE)
{
    reply = r;
    foreach(QSslError err, lSslE)
    {
        QString line = err.errorString() + "\n";
        data->write(line.toAscii());
    }
    errorLog();
    emit done(false);
}

void
Conn::addQueryItem(const QString &key, const QString &value)
{
    this->url.addQueryItem(key,value);
}

QString
Conn::svr_tr(const QString &str)
{
    QString ret = str;
    ret.replace(QString("\303\246"),lstr("\346"));
    ret.replace(QString("\303\206"),lstr("\306"));
    ret.replace(QString("\303\245"),lstr("\345"));
    ret.replace(QString("\303\205"),lstr("\305"));
    ret.replace(QString("\303\270"),lstr("\370"));
    ret.replace(QString("\303\230"),lstr("\330"));
    return ret;
}

void
Conn::Command(const QString &cmd, const QString &r)
{
    emit log("main/conn.cc","Command: " + cmd + " - " + r);
    if(data->isOpen())
    {
        data->close();
        while(data->isOpen()) {;}
    }
    data->open(QIODevice::ReadWrite|QIODevice::Truncate|QIODevice::Text|QIODevice::Unbuffered);
    url.addQueryItem("cmd",cmd);
    if(cmd == QString("login")) {
        this->url.addQueryItem("user",auth->user());
        this->url.addQueryItem("pass",auth->password());
    } else {
        this->url.addQueryItem("cid",QString::number(cid,16));
    }
    postData.clear();
    postData.append(url.encodedQuery());
    postData.append("&"+r);
    emit log("main/conn.cc","PostData: " + QString(postData),1);
    QNetworkReply *nre = this->post(QNetworkRequest(this->url),postData);
    nre->ignoreSslErrors();
}
