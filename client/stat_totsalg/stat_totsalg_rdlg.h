#ifndef __stat_totsalg_rdlg_h
#define __stat_totsalg_rdlg_h

#include <QDialog>
#include <QVector>
#include "stat_totsalg_data.h"
#include "ui_stat_totsalg_rdlg.h"

class Conn;

class ResDialog : public QDialog, private Ui::resultDlg
{
    Q_OBJECT
    QVector<Salger> data;
    Conn *c;
    QString to;
    QString from;
public:
    ResDialog(const QVector<Salger> &d,Conn *_c, QWidget *parent=0);
    void clearTable();

public slots:
    void fillTable(int idx);
    void getOrder(QTableWidgetItem *item);
    void getList();
    void setDate(const QString &_f, const QString &_t) { from = _f; to = _t; };
};

#endif
