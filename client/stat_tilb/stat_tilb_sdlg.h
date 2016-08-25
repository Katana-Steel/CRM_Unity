#ifndef __stat_tilb_sdlg_h
#define __stat_tilb_sdlg_h

#include <QDialog>
#include "ui_stat_tilb_sdlg.h"

class Conn;

class SearchDlg : public QDialog, private Ui::tilbSearchDlg
{
    Q_OBJECT
    Conn *conn;
public:
    SearchDlg(Conn *c,QWidget *parent);

public slots:
    void runSearch();
};

#endif
