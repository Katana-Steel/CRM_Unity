#ifndef __stat_sogning_kunde_h
#define __stat_sogning_kunde_h

#include "ui_stat_sogning_res_dlg.h"
#include "stat_sogning_data.h"

#include <QDialog>

class Conn;

class ResKndDlg : public QDialog, private Ui::rForm
{
    Q_OBJECT
    QVector<stat_knd> dat;
    Conn *c;
    int width;
    bool ext;
    void clearLst();
    QString sqlstr;
public:
    ResKndDlg(const QVector<stat_knd> &d,Conn *_c,QWidget *parent=0);
    void setSQL(QString &str) { sqlstr = str; };
    void setType(int order);
private slots:
    void showKnd(int i);
    void showTOKA(int r,int col);
    void reqXLSList();
    void reqCurrentList();
};

#endif
