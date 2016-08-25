#include <QtGui>
#include <QtNetwork>
#include "mwin.h"
#include "conn.h"


MWin::MWin(QWidget *parent) :
    QWidget(parent),cout(stdout)
{
    resize(400,200);
    conn = new Conn("192.168.0.171","/index.html", false, this);
    conn->setUser("adm0");
    conn->setPass("0049");
    lay = new QVBoxLayout;
    pgb = new QProgressBar;
    pgb->setValue(0);
    lay->addWidget(pgb);
    setLayout(lay);
    connect(conn, SIGNAL(finished(QNetworkReply*)), this, SLOT(ready(QNetworkReply*)));
    connect(conn, SIGNAL(HttpDone()), this, SLOT(done()));
    cout << "MWin created" << endl;
}

void
MWin::setVisible(bool v)
{
    cout << "MWin::setVisible" << endl;
    QWidget::setVisible(v);
    if(v && conn) {
        this->conn->Command("login");
//    ready(this->conn->Data(1));
    }
}

void
MWin::show()
{
    cout << "MWin::show" << endl;
}

void
MWin::done()
{
    cout << "MWin::done" << endl;
    setLayout(lay);
}

void
MWin::updateBar(qint64 v, qint64 t)
{
    cout << "MWin::updateBar" << endl;
    pgb->setMaximum(t);
    pgb->setValue(v);
}

void
MWin::readNet()
{
    cout << "MWin::readNet" << endl;
    setLayout(0);
    delete lay;
    lay = new QVBoxLayout;
    QFile *data = conn->Data();
    QTextStream out(data);
    cout << out.readAll();

    setLayout(lay);
}

void
MWin::sslErr()
{
    cout << "MWin::sslErr" << endl;
}

void
MWin::err()
{
    cout << "MWin::err" << endl;
}

void
MWin::ready(QNetworkReply *rep)
{
    cout << "MWin::ready" << endl;
    reply = rep;
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(updateBar(qint64,qint64)));
//    connect(reply, SIGNAL(readyRead()), this, SLOT(readNet()));
    connect(reply, SIGNAL(sslErrors(const QList<QSslError> &)), this, SLOT(sslErr()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(err()));
    if(reply->error() == QNetworkReply::NoError) readNet();

}
