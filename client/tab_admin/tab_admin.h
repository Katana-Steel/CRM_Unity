#ifndef __tab_admin_h
#define __tab_admin_h
#include "tab_interf.h"
#include "ui_tab_admin2.h"
class QButtonGroup;
class QXmlSimpleReader;
class XmlHnd;
class Stat;
class KData;
struct UserData;

//! The Administration plugin object
/*!
*/
class tabAdmin : public TabInterface, private Ui::admin
{
    Q_OBJECT
    Q_INTERFACES(TabInterface)
    QButtonGroup *radioG; //!< the user functions manager group.
    Conn *c; //!< the applications comunications object.
    QXmlSimpleReader *xml; //!< the XML parser.
    XmlHnd *hnd; //!< the XML handler.
    Stat *status; //!< a Status Message Dialog.
    bool errorLog;
    QString makeReqFromUD(UserData *ud);
    QString mod;
public:
    tabAdmin();
    ~tabAdmin();
    QString name();
    int minUserAccess();
    void LoadInterface();
    void setConn(Conn *_c);
    void setKData(KData *) {};
    void ParseXML();
    void Shown();
private slots:
    void radioChanged(int);
    void availableUsers(int);
    void showUserData(int);
    void sendQuery();
    void resetUD() { Shown(); };
    void sendUpdMail();
    void addMailRule();
    void updateRule();
    void rmMailRule();
signals:
    void Log(QString mod,QString msg,int lvl=0);
};

#endif
