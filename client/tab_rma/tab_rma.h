#ifndef __tab_rma_h
#define __tab_rma_h 1

#include <tab_interf.h>
#include "ui_tab_rma.h"

class KData;
class QXmlSimpleReader;
class XmlHnd;
class Stat;
/*! A RMA interface. */
/*!
    An interface to handle all concerning
    a RMA case
*/
class TabRMA : public TabInterface,  private Ui::Form
{
    Q_OBJECT
    Q_INTERFACES(TabInterface)
public:
    TabRMA();
    ~TabRMA();

    QString name();
    int minUserAccess();
    void LoadInterface();
    void setConn(Conn *_c);
    void setKData(KData *);
    void ParseXML();
    void Shown();

private:
    Conn *c;
    KData *cus;
    QTreeWidgetItem *curNode;
    QXmlSimpleReader *xml;
    XmlHnd *hnd;
    bool fetch;
    Stat *status;
    QString mod;
    void displayCurNode();
private slots:
    void rma_select(QTreeWidgetItem*,int);
    void newRMANode();
    void updRMANode();
    void txRMANode();
signals:
    void Log(QString,QString,int lvl=0);
};

#endif
