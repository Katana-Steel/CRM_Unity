#include <QtGui>
#include "stat_sogning_kunde.h"
#include "conn.h"

ResKndDlg::ResKndDlg(const QVector<stat_knd> &d,Conn *_c,QWidget *parent) :
    QDialog(parent),dat(d),width(22),ext(false)
{
    c = _c;
    setupUi(this);
    connect(closeDlg,SIGNAL(clicked()),this,SLOT(accept()));
    cBoxLab->setText(QString("Kunde nr:"));
    if(!dat.empty()) {
      stat_knd i;
      foreach(i,dat) {
          knr->addItem(i.kunde.kunde_nr,0);
      }
    } else {
      lst->setDisabled(true);
      knr->setDisabled(true);
      return;
    }
    connect(knr,SIGNAL(currentIndexChanged(int)),this,SLOT(showKnd(int)));
    connect(lst,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(showTOKA(int,int)));
    connect(exportXLS,SIGNAL(clicked()),this, SLOT(reqXLSList()));
    connect(send_lst,SIGNAL(clicked()),this, SLOT(reqCurrentList()));
}

void
ResKndDlg::showKnd(int i)
{
    labName->setText(dat[i].kunde.Firma);
    labAtt->setText(dat[i].kunde.Att);
    labAddr->setText(dat[i].kunde.Adr);
    labZipCity->setText(dat[i].kunde.PostBy);
    clearLst();
    knddata d;
    int r=0;
    foreach(d, dat[i].data) {
        lst->insertRow(r);
        lst->setItem(r,0,new QTableWidgetItem(d.dato));
        lst->setItem(r,1,new QTableWidgetItem(d.toka_nr));
        if(d.toka_nr.mid(0,2) == QString("24")) {
         QTableWidgetItem *i = new QTableWidgetItem(d.lev);
         int s = d.lev.size();
         if(width < (s*7)) width = (s*7);
         lst->setItem(r,2,i);
        }
        if(ext) {
         lst->setItem(r,3,new QTableWidgetItem(d.stk));
         lst->setItem(r,4,new QTableWidgetItem(d.vnr));
         lst->setItem(r,5,new QTableWidgetItem(d.vtxt));
        }
        r++;
    }
    for(r=0;r<lst->rowCount();r++)
        lst->setRowHeight(r,22);
    lst->setColumnWidth(2,width);
}

void
ResKndDlg::showTOKA(int r,int)
{
    QString req = "onr=" + lst->item(r,1)->text();
    c->Command("get_print",req);
}

void
ResKndDlg::reqXLSList()
{
    QString req = "sql=" + sqlstr;
    c->Command("get_xls",req);
}

void
ResKndDlg::reqCurrentList()
{
    QString req = "sql=" + sqlstr;
    req += "&knr=" + knr->currentText();
    c->Command("get_curlist",req);
}

void
ResKndDlg::clearLst()
{
    while(lst->rowCount() > 0)
        lst->removeRow(0);
}

void
ResKndDlg::setType(int order)
{
  if(order == 1) {
    ext = false;
    lst->setColumnCount(3);
    lst->setHorizontalHeaderItem(0,new QTableWidgetItem("dato"));
    lst->setHorizontalHeaderItem(1,new QTableWidgetItem("nr"));
    lst->setHorizontalHeaderItem(2,new QTableWidgetItem(" "));
    send_lst->hide();
  } else {
    ext = true;
    lst->setColumnCount(6);
    lst->setHorizontalHeaderItem(0,new QTableWidgetItem("dato"));
    lst->setHorizontalHeaderItem(1,new QTableWidgetItem("nr"));
    lst->setHorizontalHeaderItem(2,new QTableWidgetItem(" "));
    lst->setHorizontalHeaderItem(3,new QTableWidgetItem("stk"));
    lst->setHorizontalHeaderItem(4,new QTableWidgetItem("vare nr."));
    lst->setHorizontalHeaderItem(5,new QTableWidgetItem("tekst"));
  }
  if(!dat.empty()) (knr->currentIndex());
}
