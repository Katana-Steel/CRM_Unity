#ifndef __tab_rma_mwin_h
#define __tab_rma_mwin_h 1

#include <QMainWindow>

class Conn;
class KData;

class MWin : public QMainWindow
{
public:
    MWin(Conn*,QWidget*);

    void log(const QString &str);
    KData *getCusData();
};

#endif
