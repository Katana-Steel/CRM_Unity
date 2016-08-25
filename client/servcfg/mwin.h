#ifndef __mwin_h
#define __mwin_h

#include <QDialog>
#include "ui_main.h"

class Config;

class MainWin : public QDialog, private Ui::main
{
    Q_OBJECT
    Config *cfg;
public:
    MainWin(Config *c,QWidget *parent=0);
    ~MainWin();

private slots:
    void writeXmlCfg();
    void setDefStyle(int);
};

#endif
