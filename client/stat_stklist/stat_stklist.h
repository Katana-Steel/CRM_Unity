/********************************************************************************************************
 * PROGRAM      : stat_stklist
 * DATE - TIME  : torsdag 18 oktober 2007 - 11h08
 * AUTHOR       : René Kjellerup ( webmaster@keenan.dk )
 * FILENAME     : stat_stklist.h
 * LICENSE      : GPL
 * COMMENTARY   :
 ********************************************************************************************************/
#ifndef __stat_stklist_h
#define __stat_stklist_h 1

#include <QObject>
#include <stat_interf.h>

class QXmlSimpleReader;
class XmlHnd;
class Stat;

class Stat_StkList : public QObject, public StatInterface
{
    Q_OBJECT
    Q_INTERFACES(StatInterface)
private:
    QWidget *parent;
    Conn *conn;
    QXmlSimpleReader *xml;
    XmlHnd *hnd;
    Stat *stat;
public:
    Stat_StkList();
    ~Stat_StkList();
    QString name();
    int searchDialog();
    void xmlParse();
    void setDialogParent(QWidget *_p) { parent = _p; };
    void setConn(Conn *_c) { conn = _c; };
};

#endif
