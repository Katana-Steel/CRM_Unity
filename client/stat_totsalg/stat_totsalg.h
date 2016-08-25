#ifndef __stat_tilb_h
#define __stat_tilb_h

#include <QObject>
#include <QString>

#include <stat_interf.h>

class XmlHnd;
class Conn;
class Stat;
class QXmlSimpleReader;

class StatTotSalg : public QObject, public StatInterface
{
    Q_OBJECT
    Q_INTERFACES(StatInterface)
private:
    QWidget *parent;
    Conn *conn;
    XmlHnd *hnd;
    QXmlSimpleReader *xml;
    Stat *stat;
public:
    StatTotSalg();
    ~StatTotSalg();
    QString name();
    int searchDialog();
    void xmlParse();
    void setDialogParent(QWidget *_p) { parent = _p; };
    void setConn(Conn *_c) { conn = _c; };
};

#endif
