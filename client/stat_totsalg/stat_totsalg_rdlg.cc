#include <QtCore>
#include <QtGui>
#include "stat_totsalg_rdlg.h"
#include "conn.h"

ResDialog::ResDialog(const QVector<Salger> &d,Conn *_c,QWidget *parent) :
    QDialog(parent), data(d),to(""),from("")
{
    c = _c;
    setupUi(this);
    if(data.size() != 0) {
      foreach(Salger name, data)
      {
        salger->addItem(name.name.id);
      }
      fillTable(0);
    } else {
      salger->setEnabled(false);
      salg->setEnabled(false);
      bytte->setEnabled(false);
      total->setEnabled(false);
      order_list->setEnabled(false);
    }

    connect(prnLst, SIGNAL(clicked()), this, SLOT(getList()));
    connect(closeFrm, SIGNAL(clicked()), this, SLOT(accept()));
    connect(salger,SIGNAL(currentIndexChanged(int)),this,SLOT(fillTable(int)));
    connect(order_list, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(getOrder(QTableWidgetItem*)));
}

void
ResDialog::fillTable(int idx)
{
    clearTable();
    Salger tmp = data[idx];
    resultDlg::salg->setText(tmp.name.salg);
    resultDlg::bytte->setText(tmp.name.bytte);
    resultDlg::total->setText(tmp.name.total);
    bool red = false;
    QColor bg(220,220,255);
    QColor txt(255,0,0);
    foreach(SalgData d, tmp.orders)
    {
        order_list->insertRow(0);
        if(d.total.at(0) == QChar('-')) {
            red = true;
        }
        QTableWidgetItem *twi = new QTableWidgetItem(d.id);
        twi->setTextAlignment(Qt::AlignRight);
        if(red) {
            twi->setBackgroundColor(bg);
            twi->setTextColor(txt);
            QFont f = twi->font(); f.setBold(true); twi->setFont(f);
        }
        order_list->setItem(0,0,twi);
        twi = new QTableWidgetItem(d.salg);
        twi->setTextAlignment(Qt::AlignRight);
        if(red) {
            twi->setBackgroundColor(bg);
            twi->setTextColor(txt);
            QFont f = twi->font(); f.setBold(true); twi->setFont(f);
        }
        order_list->setItem(0,1,twi);
        twi = new QTableWidgetItem(d.bytte);
        twi->setTextAlignment(Qt::AlignRight);
        if(red) {
            twi->setBackgroundColor(bg);
            twi->setTextColor(txt);
            QFont f = twi->font(); f.setBold(true); twi->setFont(f);
        }
        order_list->setItem(0,2,twi);
        twi = new QTableWidgetItem(d.total);
        twi->setTextAlignment(Qt::AlignRight);
        if(red) {
            twi->setBackgroundColor(bg);
            twi->setTextColor(txt);
            QFont f = twi->font(); f.setBold(true); twi->setFont(f);
        }
        order_list->setItem(0,3,twi);
        red = false;
    }
    for(int i=0;i<order_list->rowCount();i++)
    {
        order_list->setRowHeight(i,20);
    }
}

void
ResDialog::clearTable()
{
    while(order_list->rowCount() != 0)
    {
        order_list->removeRow(0);
    }
}

void
ResDialog::getOrder(QTableWidgetItem *)
{
    int r = order_list->currentRow();
    QString req = "onr=" + order_list->item(r,0)->text();
    c->Command("get_print",req);
}

void
ResDialog::getList()
{
    if(salger->currentIndex() == salger->count()-1 && salger->count()!= 1) return;

    QString req = "sid=" + salger->currentText();
    req += "&from=" + from;
    req += "&to=" + to;
    c->Command("get_print",req);
}
