#include <QtGui>
#include "stat_sogning_dato.h"
#include "conn.h"

ResDatoDlg::ResDatoDlg(const QVector<stat_dato> &d,Conn *_c,QWidget *parent) :
    QDialog(parent),dat(d),width(22)
{
    c = _c;
    setupUi(this);
    exportXLS->setVisible(false);
    send_lst->setVisible(false);
    connect(closeDlg,SIGNAL(clicked()),this,SLOT(accept()));
    cBoxLab->setText(QString("Dato:"));
    lst->setColumnCount(3);
    lst->setHorizontalHeaderItem(0,new QTableWidgetItem("Kunde nr"));
    lst->setHorizontalHeaderItem(1,new QTableWidgetItem("nr"));
    lst->setHorizontalHeaderItem(2,new QTableWidgetItem(" "));
    if(!dat.empty()) {
      stat_dato i;
      foreach(i,dat) {
          knr->addItem(i.dato,0);
      }
      showDato(knr->currentIndex());
    } else {
      lst->setDisabled(true);
      knr->setDisabled(true);
      return;
    }
    connect(knr,SIGNAL(currentIndexChanged(int)),this,SLOT(showDato(int)));
    connect(lst,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(showTOKA(int,int)));
    connect(lst,SIGNAL(cellClicked(int,int)),this,SLOT(showKnd(int,int)));
}

void
ResDatoDlg::showDato(int i)
{
    labName->setText(QString(""));
    labAtt->setText(QString(""));
    labAddr->setText(QString(""));
    labZipCity->setText(QString(""));
    clearLst();
    datodata d;
    int r=0;
    foreach(d, dat[i].data) {
        lst->insertRow(r);
        lst->setItem(r,0,new QTableWidgetItem(d.kunde.kunde_nr));
        lst->setItem(r,1,new QTableWidgetItem(d.toka_nr));
        if(d.toka_nr.mid(0,2) == QString("24")) {
         QTableWidgetItem *i = new QTableWidgetItem(d.lev);
         int s = d.lev.size();
         if(width < (s*7)) width = (s*7);
         lst->setItem(r,2,i);
        }
        r++;
    }
    for(r=0;r<lst->rowCount();r++)
        lst->setRowHeight(r,22);
    lst->setColumnWidth(2,width);
}

void
ResDatoDlg::showTOKA(int r,int)
{
    QString req = "onr=" + lst->item(r,1)->text();
    c->Command("get_print",req);
}

void
ResDatoDlg::showKnd(int r,int)
{
    int i = knr->currentIndex();
    labName->setText(dat[i].data[r].kunde.Firma);
    labAtt->setText(dat[i].data[r].kunde.Att);
    labAddr->setText(dat[i].data[r].kunde.Adr);
    labZipCity->setText(dat[i].data[r].kunde.PostBy);
}

void
ResDatoDlg::clearLst()
{
    while(lst->rowCount() > 0)
        lst->removeRow(0);
}
