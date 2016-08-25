#include <QtGui>
#include "tab_rma_replace_dlg.h"

ReplaceDlg::ReplaceDlg(QWidget *parent)
    : QDialog(parent)
{
    setMaximumHeight(240);
    setMaximumWidth(240);
    setMinimumHeight(240);
    setMinimumWidth(240);
    stk = new QLineEdit("Stk.");
    vnr = new QLineEdit("Vare nr.");
    vtxt = new QLineEdit("Vare Tekst");
    pris = new QLineEdit("Pris");
    QPushButton *ok = new QPushButton("Ok");
    connect(ok, SIGNAL(clicked()), this, SLOT(okay()));
    chk = new QCheckBox("");

    QVBoxLayout *vlay = new QVBoxLayout(this);
    vlay->addWidget(chk);
    vlay->addWidget(stk);
    vlay->addWidget(vnr);
    vlay->addWidget(vtxt);
    vlay->addWidget(pris);
    QHBoxLayout *hlay = new QHBoxLayout;
    hlay->addStretch();
    hlay->addWidget(ok);
    hlay->addStretch();
    vlay->addLayout(hlay);
}

void
ReplaceDlg::check()
{
}

void
ReplaceDlg::okay()
{
    if(chk->isChecked())
        accept();
    else
        reject();
}
