#include <QtCore>
#include <QtGui>
#include "stat_totsalg_sdlg.h"
#include "conn.h"

TotalSalg::TotalSalg(Conn *_c,QWidget *parent) :
    QDialog(parent)
{
    conn = _c;
    setupUi(this);
    if(conn->getUA() > 8) totSalgAllIndv->setEnabled(true);
    totSalgTo->setDate(QDate::currentDate());
    connect(totSalg, SIGNAL(clicked()), this, SLOT(GetTotalSalg()));
}

void
TotalSalg::GetTotalSalg()
{
    QString req = "type=tot_salg";
    req += "&from=" + totSalgFrom->date().toString("yyyy-MM-dd");
    req += "&to=" + totSalgTo->date().toString("yyyy-MM-dd");
    if(totSalgAllIndv->isChecked()) req += "&all=1";
    conn->Command("stat",req);
    accept();
}
