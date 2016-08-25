#include <QtCore>
#include <QtGui>
#include "config.h"
#include "mwin.h"

int
main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(new QPlastiqueStyle);
    MainWin *win = new MainWin(new Config("config.xml"));
	QFont fn = win->font();
	fn.setPointSize(10);
	QApplication::setFont(fn);
    if(win->exec() == QDialog::Rejected) {
        QMessageBox::information(0,"Helhed Configuration Writer","'config.xml' er ikke blevet opdateret",QMessageBox::Ok);
    } else {
        QMessageBox::information(0,"Helhed Configuration Writer","'config.xml' er nu blevet opdateret",QMessageBox::Ok);
    }
    delete win;
    return 0;
}
