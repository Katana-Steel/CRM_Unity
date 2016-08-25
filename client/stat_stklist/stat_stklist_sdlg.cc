#include <QtCore>
#include <QtGui>
#include "stat_stklist_sdlg.h"
#include "conn.h"

SearchDlg::SearchDlg(Conn *_c, QWidget *parent) :
    QDialog(parent)
{
    c = _c;
    setupUi(this);
    p_To->setDate(QDate::currentDate());
    connect(seek,SIGNAL(clicked()), this, SLOT(SendSearch()));
}

void
SearchDlg::SendSearch()
{
    if(seekTxtInput->text() == QString("")) {
        QMessageBox::information(this,"Multi Søgning","Du kan ikke lave en søgning\nmed en tom tekst streng", QMessageBox::Ok);
        return;
    }
    QString req = "type=stklist&str=" + seekTxtInput->text();
    if(SeekT->isChecked()) req += "&T=1";
    if(SeekO->isChecked()) req += "&O=1";
    if(SeekK->isChecked()) req += "&K=1";
    QDate from = p_From->date();
    req += "&from=" + from.toString("yyyy-MM-dd");
    QDate to = p_To->date();
    req += "&to=" + to.toString("yyyy-MM-dd");
    c->Command("stat",req);
    accept();
}
