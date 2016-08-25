#ifndef __tab_rma_replace_dlg_h
#define __tab_rma_replace_dlg_h 1

#include <QDialog>
class QLineEdit;
class QCheckBox;


class ReplaceDlg : public QDialog
{
    Q_OBJECT

    QCheckBox *chk;
public:
    ReplaceDlg(QWidget *parent);
    QLineEdit *stk;
    QLineEdit *vnr;
    QLineEdit *vtxt;
    QLineEdit *pris;
private slots:
    void check();
    void okay();
};

#endif
