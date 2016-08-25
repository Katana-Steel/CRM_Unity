#ifndef __stat_tilb_h
#define __stat_tilb_h

#include <QObject>

#include <stat_interf.h>

class XmlHnd;
class Conn;
class Stat;
class QXmlSimpleReader;

class StatTilb : public QObject, public StatInterface
{
    Q_OBJECT
    Q_INTERFACES(StatInterface)
private:
    QWidget *parent;
    Conn *conn;
    Stat *status;
    XmlHnd *hnd;
    QXmlSimpleReader *xml;
public:
    StatTilb();
    ~StatTilb();
    QString name();
    int searchDialog();
    void xmlParse();
    void setDialogParent(QWidget *_p) { parent = _p; };
    void setConn(Conn *_c) { conn = _c; };
};

#endif
