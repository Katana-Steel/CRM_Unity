#include <QApplication>
#include "mwin.h"

int main(int c, char **v) {
    QApplication a(c,v);
    QWidget *win = new MWin();
    win->show();
    return a.exec();
}