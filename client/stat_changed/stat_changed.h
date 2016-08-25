/********************************************************************************************************
 * PROGRAM      : stat_changed
 * DATE - TIME  : fredag 9 november 2007 - 10h07
 * AUTHOR       : René Kjellerup ( webmaster@keenan.dk )
 * FILENAME     : stat_changed.h
 * LICENSE      : GPL
 * COMMENTARY   :
 ********************************************************************************************************/
#ifndef __stat_changed_h
#define __stat_changed_h 1

#include <QObject>
#include <stat_interf.h>

class QXmlSimpleReader;
class XmlHnd;
class Stat;

class StatChanged : public QObject, public StatInterface
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
    StatChanged();
    ~StatChanged();
    QString name();
    int searchDialog();
    void xmlParse();
    void setDialogParent(QWidget *_p) { parent = _p; };
    void setConn(Conn *_c) { conn = _c; };
};

#endif
