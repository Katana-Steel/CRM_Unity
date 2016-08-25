#ifndef __stat_changed_sdlg_h
#define __stat_changed_sdlg_h 1

#include <QDialog>
#include "ui_stat_changed_sdlg.h"

class Conn;

class SearchDlg : public QDialog, private Ui::sForm
{
    Q_OBJECT
    Conn *c;
public:
    SearchDlg(Conn *_c,QWidget *p);
public slots:
    void CompileSQL();
};

#endif
