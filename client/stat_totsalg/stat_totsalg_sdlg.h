#ifndef __stat_totsalg_sdlg_h
#define __stat_totsalg_sdlg_h

#include "ui_stat_totsalg_sdlg.h"
#include <QDialog>
class Conn;

class TotalSalg : public QDialog, private Ui::totSalgFrm
{
    Q_OBJECT
    Conn *conn;
public:
    TotalSalg(Conn *_c,QWidget *parent=0);

public slots:
    void GetTotalSalg();
};

#endif
