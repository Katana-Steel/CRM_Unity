#include <QtGui>
#include <conn.h>
#include "stat_changed_sdlg.h"

SearchDlg::SearchDlg(Conn *_c, QWidget *p) :
    QDialog(p)
{
    c = _c;
    setupUi(this);

    QButtonGroup *btnG = new QButtonGroup(this);
    btnG->addButton(radioButton);   // ændret
    btnG->addButton(radioButton_2); // ikke ændret
    btnG = new QButtonGroup(this);
    btnG->addButton(radioButton_3); // efter
    btnG->addButton(radioButton_4); // før
    radioButton->setChecked(true);
    radioButton_3->setChecked(true);
    connect(pushButton, SIGNAL(clicked()), this, SLOT(CompileSQL()));
}

void
SearchDlg::CompileSQL()
{
    QString sql = "select id,varenr,varetekst,pris,sort,sidst_red from Maskiner where sidst_red";
    bool aendret = radioButton->isChecked();
    if(radioButton_3->isChecked()) {
        if(aendret) sql += " > ";
        else        sql += " < ";
    } else if(radioButton_4->isChecked()) {
        if(aendret) sql += " < ";
        else        sql += " > ";
    }
    QDate dat = dateEdit->date();
    sql += "\\'" + dat.toString("yyyy-MM-dd") + "\\' and varenr like \\'" + lineEdit->text() + "%\\' ";
    sql += "order by sort,varenr,sidst_red";
    c->Command("get_changed","sql="+sql);
    accept();
}
