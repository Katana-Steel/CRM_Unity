#include <QtGui>
#include "stat_tilb_rdlg.h"
#include "conn.h"

ResDialog::ResDialog(const QVector<CustNr> &data, Conn *_c, QWidget *parent) :
    QDialog(parent),tmp(data)
{
    c = _c;
    setupUi(this);
    int i=0;
    if(tmp.size() != 0) {
      foreach(CustNr x, tmp) 
      {
        klist->addItem(x.cust.navn + " " + x.cust.att, i++);
      }
      fillTable(0);
    } else {
      klist->setEnabled(false);
      tilb_list->setEnabled(false);
      knr->setEnabled(false);
    }
    connect(closeForm, SIGNAL(clicked()), this, SLOT(accept()));
    connect(showNr,SIGNAL(clicked()), this, SLOT(showTilbud()));
    connect(klist,SIGNAL(currentIndexChanged(int)),this,SLOT(fillTable(int)));
    connect(tilb_list, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this, SLOT(showTilbud()));
}

void
ResDialog::fillTable(int idx)
{
    QVector<TOKAnr> x(tmp[idx].list);
    QTableWidgetItem *twi;
    clearTable();
    knr->setText(tmp[idx].cust.knr);
    for(int i=0; i*3<x.size();i++) 
    {  
        tilb_list->insertRow(i);
        twi = new QTableWidgetItem(x.at(i*3).nr,1);
        tilb_list->setItem(i,0,twi);
        if(i*3+1 < x.size()) {
          twi = new QTableWidgetItem(x.at(i*3+1).nr,1);
          tilb_list->setItem(i,1,twi);
        } else { return; }
        if(i*3+2 < x.size()) {
          twi = new QTableWidgetItem(x.at(i*3+2).nr,1);
          tilb_list->setItem(i,2,twi);
        } else { return; }
    }    
}

void
ResDialog::clearTable()
{
    while(tilb_list->rowCount() != 0)
    {
        tilb_list->removeRow(0);
    }
}

void
ResDialog::showTilbud() 
{
    QString req = "onr=" + tilb_list->currentItem()->text();
    c->Command("get_print",req);
}
