#ifndef __stat_stklist_sdlg_h
#define __stat_stklist_sdlg_h 1

#include "ui_stat_stklist_sdlg.h"
#include <QDialog>

class Conn;

class SearchDlg : public QDialog, private Ui::sForm
{
    Q_OBJECT
    Conn *c;
public:
    SearchDlg(Conn *_c, QWidget *parent);
private slots:
    void SendSearch();
};

#endif
