#ifndef __stat_stklist_rdlg_h
#define __stat_stklist_rdlg_h 1

#include <QDialog>
#include <QLabel>

class QTableWidget;
class QFontMetrics;
struct ItemData;

template <class T> class QVector;

class ResDlg : public QDialog
{
    Q_OBJECT
public:
    ResDlg(QWidget *parent);
    ~ResDlg();

    void addData(QVector<ItemData*> *idat);
    void setFromDato(QString str) { from->setText(str); };
    void setToDato(QString str) { to->setText(str); };
private:
    QLabel *to;
    QLabel *from;
    QTableWidget *lst;
    QFontMetrics *fmx;
};

#endif
