/********************************************************************************************************
 * PROGRAM      : stat_sogning
 * DATE - TIME  : torsdag 22 marts 2007 - 11h13
 * AUTHOR       : René Kjellerup ( webmaster@keenan.dk )
 * FILENAME     : stat_sogning_sdlg.h
 * LICENSE      : GPL
 * COMMENTARY   : 
 ********************************************************************************************************/
#ifndef __stat_sogning_sdlg_h
#define __stat_sogning_sdlg_h

#include <QDialog>
#include "ui_stat_sogning_sdlg.h"

class Conn;

class MultiSearch : public QDialog, private Ui::sForm
{
    Q_OBJECT
    Conn *c;
public:
    MultiSearch(Conn *conn,QWidget *parent=0);
    ~MultiSearch();

private slots:
    void runSearch();
};

#endif
