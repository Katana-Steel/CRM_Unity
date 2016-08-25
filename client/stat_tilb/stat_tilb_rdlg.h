#ifndef __stat_tilb_rdlg_h
#define __stat_tilb_rdlg_h

#include "ui_stat_tilb_rdlg.h"
#include "st_data.h"
#include <QDialog>
#include <QVector>

class Conn;

class ResDialog : public QDialog, private Ui::resForm
{
    Q_OBJECT
    QVector<CustNr> tmp;
    Conn *c;
public:
    ResDialog(const QVector<CustNr> &data, Conn *_c, QWidget *parent=0);
    void clearTable();
public slots:
    void showTilbud();
    void fillTable(int idx);
};

#endif
