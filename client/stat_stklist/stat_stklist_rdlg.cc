#include <QtCore>
#include <QtGui>
#include "stat_stklist_rdlg.h"
#include "stat_stklist_data.h"

ResDlg::ResDlg(QWidget *parent) :
    QDialog(parent, Qt::Dialog)
{
    QFont fn = font();
    fn.setFamily("Andale Mono");
    setFont(fn);
    fmx = new QFontMetrics(fn);
    to = new QLabel();
    from = new QLabel();
    lst = new QTableWidget();
    lst->setColumnCount(3);
    lst->setHorizontalHeaderItem(0,new QTableWidgetItem("Stk."));
    lst->setColumnWidth(0,50);
    lst->setHorizontalHeaderItem(1,new QTableWidgetItem("Vare Nr."));
    lst->setHorizontalHeaderItem(2,new QTableWidgetItem("Vare Tekst"));
    QPushButton *luk = new QPushButton("Luk");
    connect(luk, SIGNAL(clicked()), this, SLOT(accept()));
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setMargin(3);
    vbox->setSpacing(0);
    QHBoxLayout *hbox = new QHBoxLayout();
    QLabel *lab = new QLabel("Fra : ");
    hbox->addWidget(lab);
    hbox->addWidget(from);
    hbox->addStretch();
    hbox->addWidget(luk);
    vbox->addLayout(hbox);
    lab = new QLabel("Til : ");
    hbox = new QHBoxLayout();
    hbox->addWidget(lab);
    hbox->addWidget(to);
    hbox->addStretch();
    vbox->addLayout(hbox);
    vbox->addWidget(lst);
    QRect rc = this->geometry();
    rc.setWidth(500);
    rc.setHeight(350);
    rc.moveCenter(QApplication::desktop()->geometry().center());
    setGeometry(rc);
}

ResDlg::~ResDlg()
{
    delete fmx;
    delete to;
    delete from;
    delete lst;
}

void
ResDlg::addData(QVector<ItemData*> *idat)
{
    ItemData *dat;
    QRect rc;
    int colw[3];
    delete fmx;
    fmx = new QFontMetrics(this->font());
    for(int i = 0;i<3;i++) colw[i] = lst->columnWidth(i);
    for(int i = 0; idat->size() > i; i++)
    {
        dat = idat->at(i);
        lst->insertRow(i);
        lst->setItem(i,0,new QTableWidgetItem(dat->stk));
        rc = fmx->boundingRect(dat->stk).normalized();
        if(rc.isValid() && colw[0] < (rc.width()+5)) {
            colw[0] = rc.width()+5;
        }
        lst->setItem(i,1,new QTableWidgetItem(dat->vnr));
        rc = fmx->boundingRect(dat->vnr).normalized();
        if(rc.isValid() && colw[1] < (rc.width()+8)) {
            colw[1] = rc.width()+8;
        }
        lst->setItem(i,2,new QTableWidgetItem(dat->vtxt));
        int e = (dat->vtxt.count() * 7)+8;
        if(colw[2] < e)
            colw[2] = e;


        for(int j=0;j<3;j++) lst->setColumnWidth(j,colw[j]);

        lst->setRowHeight(i,20);
    }
}
