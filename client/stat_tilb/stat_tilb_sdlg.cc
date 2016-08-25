#include <QtCore>
#include <QtGui>
#include "stat_tilb_sdlg.h"
#include "conn.h"

SearchDlg::SearchDlg(Conn* c,QWidget *parent) :
    QDialog(parent)
{
    conn = c;
    setupUi(this);
    
    connect(findTilb, SIGNAL(clicked()), this, SLOT(runSearch()));
}

void
SearchDlg::runSearch()
{
    QString req = "type=lukk";
    if(greaterThan->isChecked()) req += "&G=1";
    else req += "&L=1";
    req += "&pro=" + QString::number(lukkPro->value());
    conn->Command("stat",req);
    accept();
}
