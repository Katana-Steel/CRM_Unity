#ifndef __stat_sogning_dato_h
#define __stat_sogning_dato_h

#include "ui_stat_sogning_res_dlg.h"
#include "stat_sogning_data.h"
#include <QDialog>

class Conn;

class ResDatoDlg : public QDialog, private Ui::rForm
{
    Q_OBJECT
    QVector<stat_dato> dat;
    Conn *c;
    int width;
    void clearLst();
public:
    ResDatoDlg(const QVector<stat_dato> &d,Conn *_c,QWidget *parent=0);
private slots:
    void showDato(int i);
    void showTOKA(int r,int col);
    void showKnd(int r,int col);
};

#endif
