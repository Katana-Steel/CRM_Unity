/********************************************************************************************************
 * PROGRAM      : stat_sogning
 * DATE - TIME  : torsdag 22 marts 2007 - 11h08
 * AUTHOR       : René Kjellerup ( webmaster@keenan.dk )
 * FILENAME     : stat_sogning.h
 * LICENSE      : GPL
 * COMMENTARY   : 
 ********************************************************************************************************/
#ifndef __stat_sogning_h
#define __stat_sogning_h

#include <QObject>
#include <stat_interf.h>

class QXmlSimpleReader;
class XmlHnd;
class Stat;

class Stat_Sogning : public QObject, public StatInterface
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
    Stat_Sogning();
    ~Stat_Sogning();
    QString name();
    int searchDialog();
    void xmlParse();
    void setDialogParent(QWidget *_p) { parent = _p; };
    void setConn(Conn *_c) { conn = _c; };
};

#endif
