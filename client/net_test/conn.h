/**************************************************************************
    This file: include/conn.h is part of Helhed Client.

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
#ifndef __conn_h
#define __conn_h 1

#include <QNetworkAccessManager>
#include <QUrl>

class QFile;
class QAuthenticator;
class QNetworkReply;

//! a HTTP communication object
class Conn : public QNetworkAccessManager
{
    Q_OBJECT
    int cid;
    int ua;
    int toka;
    QUrl url;
    QAuthenticator *auth;
    QNetworkReply *reply;
    bool valid;
    bool tls; ///< using TLS/SSL to connect to the server
    QFile *data;
public:
    Conn(QString host="localhost", QString script="/helhed/app.php", bool ssl=false, QObject *parent=0);
    ~Conn();
    void setUA(int _u) { ua = _u; };
    int getUA() { return ua; };
    void setToka(int _u) { toka = _u; };
    int getToka() { return (toka<ua)?ua:toka; };
    QString getU();
    void setUser(const QString &usr);
    void setPass(const QString &pwd);
    void setUserPass(const QString &usr, const QString &pwd);
    void setcid(QString str);
    int CID() { return cid; };
    void errorLog(void);
    void setHtUser(const QString &usr, const QString &pwd=QString()) { this->setUserPass(usr,pwd); };
    void addQueryItem(const QString &key, const QString &value);
    void Command(const QString &cmd);
    QFile *Data(void);
    QNetworkReply *Data(int) { return reply; };
    void plugin() { emit plugDone(); };
private slots:
    void requestDone(QNetworkReply *r);
signals:
    void plugDone();
    void HttpDone();

};

#endif
