/**************************************************************************
    This file: main/mwin.h is part of Helhed Client.

    Helhed Client is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Helhed Client is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helhed Client.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2008, 2009 René Kjellerup aka Katana Steel
**************************************************************************/
/* insert GPL License here */
#ifndef __mwin_h
#define __mwin_h

#include <QtCore>
#include "ui_mwin.h"
#include "k-j_data.h"
#include "s_data.h"
#include "st_data.h"
#include "conn.h"
#include <QMainWindow>

#ifdef WIN32
/** sleep
 * --
 * this object is used as the unix sleep function. Because the Windows API for
 * doing the same are way to complicated so I leave it in Trolltech and QT most
 * capable hands.
 */
class sleep : public QThread
{
    void run() {};
public:
    sleep(unsigned long sec,QObject *parent=0) :
      QThread(parent)
    {
        QThread::sleep(sec);
    };
};
#endif

//! "Salgsmål" access level.
/*!
    how high does the userlevel need to be for the user to have access to the
    "Salgsmål" type.
*/
#define SLG_ACCESS 9

class JourHnd;
class SaleHnd;
class StatHnd;
class XmlHnd;
class NJour;
class VJour;
class QXmlSimpleReader;
class QTableWidgetItem;
class QFtp;
class Stat;
class StatInterface;
class TOKA;
class system_log;

/** \class MWin
 *  \brief the Main window.
 *  \author René Kjellerup
 *  \date 2006-2007
 *  \version 1.0.2.
 *
 *  The main window object which is created if the login was
 *  successfull.
 */
class MWin : public QMainWindow, private Ui::mwin
{
    Q_OBJECT
public:
    MWin(Conn *c, QWidget *parent=0);
    ~MWin();

    //! the active module type
    enum m { NONE,  //!< the default interface, also used with a tab plugin.
             J,     //!< the journal interface.
             S,     //!< the sales interface.
             ST,    //!< the statistics interface.
             P      //!< used by the journal viewer to open a preview.
           };
    m modul;        //!< which section are we working with atm.
    Stat *stat;     //!< Displays a status message during long
                    //!< network communication opperations.

    void show() { QMainWindow::show(); };
    QString version();
    void setCurrentTab(int i);
    void setCurrentType(int i);
    void setCustomer(KData kd);
    void addJournal(JData *jd);
    void dispJD();
    void showKList(QVector<KData*> &kl);
    void showGlist(QVector<SData*> &sl);
    void showTempList(QVector<SData*> &sl);
    void addNewOrder(QVector<SData*> &sl);
    void showMailList(QVector<QString> &ml,bool salg=true);
//    void log(const QString &str);
    KData *getCusData();
    inline QString svr_tr(const QString &str) { return conn->svr_tr(str); };

private:
    int usr;            //!< the current user's user level.
//  bool b;
    Conn *conn;         //!< the connection to the server.
    int ftp_id;         //!< an ftp connection id.
    QFontMetrics *fmx;  //!< the font matrix used to calculate.
    system_log *theLog;

    void loadPlugins();

/* XML handling */
private:
    JourHnd *jhnd;
    SaleHnd *shnd;
    StatHnd *sthnd;
    XmlHnd *hnd;
    QXmlSimpleReader *xml;

/* Custommer data and jounals */
private:
    int nid;             //!< temporary nota id (journal id).
    KData cus;           //!< the data of the current customer.
    NJour *newjour;      //!< a pointer to the window for creating a new journal.
    VJour *tw;           //!< the Window used to display the journal.
    TOKA *toka_w;        //!< the window to show the TOKA menu.
    bool toka_triggered; //!< QMenu signals triggered fired.
    int mailIdx;
    JData::tp jlist_filter;
    bool jour_filter;
    QVector<JData*> jlist;

    void initTabsJournal();
    void ParseJour();
    void dispCD();
    void clearJournal();

/* Sales */
private:
    bool adding;
//    bool cs; // clearing sales
    bool chtype;
    bool tmp;
    QString fromTOKA;
    QString title;
    SData gross;
    QDialog *swin;
    QTableWidget *lst;
    QLineEdit *svnr;
    QPushButton *add;
    QTableWidgetItem * item;
    QFtp *ftp;
    QByteArray *order;

    void initTabsSale();
    void ParseSale();
    void updateTot();

/* Statistic */
private:
    bool plugin_called;
    StatInterface *curStatInter;
    QVector<QString> statFNamePlug;

    void initTabsStat();
    void ParseStat();

/* general private slots */
private slots:
    void styleCDE();
    void styleStd();
    void stylePlast();
    void HttpDone(bool err);
    void ParseGeneral();
    void reCreateLst();
    void actModule(int idx);
    void toka( const QPoint &pos );
    void jourHelp();
    void AboutDialog();
    void logout();
    void ftp_check(int id,bool err);
    void ftp_init();

/* Custommer oriented slots */
private slots:
    void clearCust();
    void store_email();
    void createCus();
    void SeekCus();
    void getCust();
    void saveCust();
    void re_login();
    void KidFromItem(QListWidgetItem *li);
    void KidFromItem_get(QListWidgetItem *li);

/* Journal oriented slots */
public slots:
    void dispJour();
    void editJournal(JData *jd);
private slots:
    void setJourSort(int idx);
    void TokaTrigger();
    void NidFromItem(QListWidgetItem *li);
    void createJour();
    void multi_mail(const QString &str);
    void endToka();

/* Sales oriented slots */
private slots:
    void updateTotSale(QTableWidgetItem*);
    void updateTotExchange(QTableWidgetItem*);
    void tilbud_type(const QString &str);
    void gross_dlg();
    void seek_gross();
    void clearSD();
    void add_sale();
    void add_byt();
    void remove_line();
    void ftp_done(bool);
    void set_itemS(int r,int c);
    void set_itemB(int r,int c);
    void setSDataFromItem(QTableWidgetItem* i);
    void setSDataFromItem_get(QTableWidgetItem* i);
    void insertMail(QTableWidgetItem *twi);
    void fetchTemp(QTableWidgetItem *twi);
    void send_order();
    void save_temp();
    void get_temps();
    void get_mails();
    void clrSale();

/* Statistics oriented slots */
private slots:
    void fetchTOKA();
    void setCurStatPlugin(const QString &str);
    void launchStatDlg();
    void pluginDone();

signals:
    void log(QString mod,QString msg, int lvl=0);
};

#endif
