#include <QtCore>
#include <QtGui>
#include "stat_sogning_sdlg.h"
#include "conn.h"

MultiSearch::MultiSearch(Conn *conn, QWidget *parent) :
    QDialog(parent)
{
    c = conn;
    setupUi(this);

    p_To->setDate(QDate::currentDate());
    connect(nr_txtSeek, SIGNAL(clicked()), this, SLOT(runSearch()));
}

MultiSearch::~MultiSearch()
{
}

void
MultiSearch::runSearch()
{
    if(seekTxtInput->text() == QString("")) {
        QMessageBox::information(this,"Multi Søgning","Du kan ikke lave en søgning\nmed en tom tekst streng", QMessageBox::Ok);
        return;
    }
    QString req = "type=multi&str=" + seekTxtInput->text();
    if(cust_order->isChecked()) req += "&order=1";
    else if(date_order->isChecked()) req += "&order=2";
    else req += "&order=3";
    if(SeekT->isChecked()) req += "&T=1";
    if(SeekO->isChecked()) req += "&O=1";
    if(SeekK->isChecked()) req += "&K=1";
    if(SeekA->isChecked()) req += "&A=1";
    if(SeekTxt->isChecked()) req += "&Txt=1";
    QDate from = p_From->date();
    req += "&from=" + from.toString("yyyy-MM-dd");
    QDate to = p_To->date();
    req += "&to=" + to.toString("yyyy-MM-dd");
    c->Command("stat",req);
    accept();
}
