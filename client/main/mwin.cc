/**************************************************************************
    This file: main/mwin.cc is part of Helhed Client.

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
#include "mwin.h"
#include "xml_c_handle.h"
#include "newjour.h"
#include "stat.h"
#include "config.h"
#include <QFtp>
#include "stat_interf.h"
#include "tab_interf.h"
#include "toka.h"
#include "log.h"

/** MWin::MWin(Conn*,QWidget*)
 * --
 * The Constructor of the main window as well as the primary loader
 * of the various plugins from the "plugins" directory.
 */
MWin::MWin(Conn *c, QWidget *parent) :
     QMainWindow(parent),modul(J),ftp_id(0),adding(false),chtype(false),tmp(false),title(""),plugin_called(false)
{
    conn = c;
    theLog = new system_log(this);
    connect(this, SIGNAL(log(QString,QString,int)), theLog, SLOT(log(QString,QString,int)));
    connect(conn, SIGNAL(log(QString,QString,int)), theLog, SLOT(log(QString,QString,int)));
    emit log("main/mwin.cc", "MWin: Creating the main dialog");
    //b = false;
    hnd = new XmlHnd;
    hnd->setConn(c);

    usr = conn->getUA();
    stat = 0;

    xml = new QXmlSimpleReader;

    setupUi(this);
    theLog->setList(actionLog);
#ifndef WIN32
    bool ok;
    int pixz = 12;
    cfg->dfontsz().toInt(&ok);
    if(ok) pixz = cfg->dfontsz().toInt(&ok);

    QFont fn = this->font();
    fn.setPixelSize(pixz);
    this->setFont(fn);
    menubar->setFont(fn);
    fn.setPixelSize(pixz-2);
    statusbar->setFont(fn);
#endif

    fmx = new QFontMetrics(sSalgTable->font());

    loadPlugins(); //  the loading of plugins

//  the saved ftp initation
/*    mwin::tabWidget->setTabEnabled(2,false);
    mwin::tabWidget->setTabEnabled(3,false);
    connect(ftp,SIGNAL(commandFinished(int,bool)),this,SLOT(ftp_check(int,bool)));
    ftp_init(); */

    initTabsJournal(); // this takes care of initiating the journal tab.
    initTabsSale();    // this takes care of initiating the sales tabs.
    initTabsStat();    // this takes care of initiating the statistics tabs.

    connect(conn, SIGNAL(done(bool)),this,SLOT(HttpDone(bool)));
    connect(conn, SIGNAL(plugDone()),this, SLOT(pluginDone()));
    connect(mwin::tabWidget, SIGNAL(currentChanged(int)), this, SLOT(actModule(int)));
    connect(mwin::CDEItm, SIGNAL(triggered()), this, SLOT(styleCDE()));
    connect(mwin::PlastiqueItm, SIGNAL(triggered()), this, SLOT(stylePlast()));
    connect(mwin::StandardItm, SIGNAL(triggered()), this, SLOT(styleStd()));
    connect(mwin::exitItm, SIGNAL(triggered()), this, SLOT(logout()));
    connect(mwin::actionJourhlp, SIGNAL(triggered()), this, SLOT(jourHelp()));
    connect(mwin::actionAbout, SIGNAL(triggered()), this, SLOT(AboutDialog()));
    connect(reLogin, SIGNAL(clicked()), this, SLOT(re_login()));

    emit log("main/mwin.cc", "MWin: Dialog created.");
}

/** MWin::~MWin()
 * --
 * The Destructor of the main window and destroyer of the programs web access
 */
MWin::~MWin()
{
    disconnect(lst,0,0,0);
    delete lst;
    if(!jlist.empty()) {
        int size = jlist.size();
        for(int i=0;i<size;i++)
        {
            JData *j = jlist[0];
            jlist.pop_front();
            delete j;
        }
    }
    if(newjour != 0) delete newjour;
    if(toka_w) delete toka_w;
    delete xml;
    delete jhnd;
    delete shnd;
    delete fmx;
}

/** MWin::actModule(int)
 * --
 * The function connected to the tabWidget's currentIndexChanged(int) signal.
 * Meaning that whenever the user change to another tab this function is called
 * with an int containing the index(0,1,2,...) of the tab selected and it then
 * sets the modul enum to an apropriate value.
 * "modul" is used by httpDone to determine which parser to use.
 */
void
MWin::actModule(int idx)
{
    emit log("main/mwin.cc","actModule " + QString::number(idx)+ ": Setting active module");
    switch(idx)  // jump to the apropriate section based on the index
    {
    default:
        modul = NONE; // NONE actualy just mean it's not any of the build in tabs
        break;
    case 1:
        modul = J;  // J means it's the journal module that's active
        break;
    case 3:
        if(cus.knr != QString("")) {
          if(!chtype) {
            chtype = true;
            QMessageBox::warning(this,"Helhed",lstr("Du skal huske at sætte typen."),QMessageBox::Ok,0,0);
          }
        }
    case 2:
        if(cus.knr != QString("")) { // has there been found a custommer to work with?
            dispCD();
            modul = S; // S means it's the sales module that's active
        } else {  // if not then send to user back to the journal/customer part
            QMessageBox::warning(this,"Helhed",lstr("Du skal søge en kunde før\ndu kan sælge noget."),QMessageBox::Ok,0,0);
            mwin::tabWidget->setCurrentIndex(1);
        }
        break;
    case 4:
        modul = ST; // ST means it's the statistic module that's active
        break;
    }

    // if it was a tab plugin that was selected then execute it Shown() function.
    TabInterface *tabDlg=0;
    tabDlg = qobject_cast<TabInterface*>(tabWidget->currentWidget());
    if(tabDlg) {
        emit log("main/mwin.cc", tabDlg->name() + " - TabInterface::Shown");
        if(cus.knr != QString("")) {
            tabDlg->setKData(&cus);
        } else {
            tabDlg->setKData(0);
        }
        tabDlg->Shown();
    }
}

/** MWin::ftp_check(int,bool)
 * --
 * used by the currently inactive ftp initiations check.
 * this recives the result of the ftp communication attempt.
 */
void
MWin::ftp_check(int id, bool err)
{
    emit log("main/mwin.cc","ftp_check: Checking that there is a viable FTP link.");
    if(id != ftp_id) return;
    if(err) {
       if(QMessageBox::No == QMessageBox::information(0,"Helhed",lstr("Kunne ikke få forbindelse\ntil serveren.\n\nVil du prøve igen?"),QMessageBox::Yes,QMessageBox::No)) return;
       ftp_init();
       return;
    }
    mwin::tabWidget->setTabEnabled(2,true);
    mwin::tabWidget->setTabEnabled(3,true);
    disconnect(ftp,SIGNAL(commandFinished(int,bool)),0,0);
    ftp->close();
}

/** MWin::ftp_init()
 * --
 * used by the currently inactive ftp initiations check.
 * this is the function to initiate the ftp test.
 */
void
MWin::ftp_init()
{
    emit log("main/mwin.cc","ftp_init: Initiating the connection to the FTP server.");
    ftp_id = ftp->connectToHost(cfg->ftpserver(),cfg->ftpport().toInt());
}

/** MWin::HttpDone(bool)
 * --
 * the caller of the various xml parser base on the current value of modul
 */
void
MWin::HttpDone(bool)
{
    emit log("main/mwin.cc","HttpDone: The request is now ready to be processed.");
    if(stat != 0) { // is there a blocking label dialog?
        stat->accept();
    }
    TabInterface *tabDlg=0;
    switch(modul) {
    case NONE:
        tabDlg = qobject_cast<TabInterface*>(tabWidget->currentWidget());
        if(tabDlg) { // should perhaps be (tabDlg != 0) which is actually the same
            emit log("main/mwin.cc",tabDlg->name() + " - TabInterface::ParseXML");
            tabDlg->ParseXML();
        } else {
            ParseGeneral();
        }
        break;
    case J:
        ParseJour();
        break;
    case S:
//        if(cs) { ParseJour(); cs=false; break; }
        ParseSale();
        break;
    case P:
        modul = J;
        break;
    case ST:
        if(plugin_called) { curStatInter->xmlParse(); }
        else ParseStat();

        break;
    default:
        break;
    }
}

/** MWin::loadPlugins()
 * --
 * the plugin loading function
 */
void
MWin::loadPlugins()
{
    emit log("main/mwin.cc","loadPlugins: loading Plugins");

    int i=0;
    QDir plugs = QDir(qApp->applicationDirPath());
    if(plugs.cd("plugins")) {
     TabInterface *tabDlg;
     foreach(QString filename, plugs.entryList(QDir::Files))
     {
        QPluginLoader loader(plugs.absoluteFilePath(filename));
        QObject *plugin = loader.instance();
        bool used = false; // is the plugin pointer needed after it's found?
        if (plugin) {
            curStatInter = qobject_cast<StatInterface *>(plugin);
            if(curStatInter) {
//                used = true;
                statSearch->addItem(curStatInter->name(),i++);
                statFNamePlug.push_back(plugs.absoluteFilePath(filename));
            }

            tabDlg = qobject_cast<TabInterface *>(plugin);
            if(tabDlg) {
                connect(tabDlg, SIGNAL(Log(QString,QString,int)), theLog, SLOT(log(QString,QString,int)));
                if(usr >= tabDlg->minUserAccess()) {
                    used = true;
                    tabWidget->addTab(tabDlg,tabDlg->name());
                    tabDlg->LoadInterface();
                    tabDlg->setConn(conn);
                }
            }
            tabDlg=0;
            if(!used) delete plugin;
        }
     }
    }
}

/** MWin::log(const QString&)
 * --
 * the function call log
 */
/*void
MWin::log(const QString &str)
{
    mwin::actionLog->addItem(str);
}*/

/** MWin::logout()
 * --
 * the shutdown function
 */
void
MWin::logout()
{
    emit log("main/mwin.cc","logout: ");
    disconnect(conn,0,0,0);
    conn->Command("logout");
    close();
}

/** MWin::ParseGeneral()
 * --
 * this calls the general XML parser
 */
void
MWin::ParseGeneral()
{
    emit log("main/mwin.cc","ParseGeneral: ");
    QFile *file;
    xml->setContentHandler(hnd);
    if(conn->Data()->isOpen())
    {
        file = conn->Data();
        file->reset();
        file->close();
        QXmlInputSource *XFile = new QXmlInputSource(file);
        if(!xml->parse(*XFile))
        {
            XFile->setData(conn->Data(1));
            if(!xml->parse(XFile)) {
                conn->errorLog();
                delete XFile;
                return;
            }
        }
        if(hnd->srvErr())
        {
            QMessageBox *mb = new QMessageBox("Helhed",
            hnd->getValue("error"),QMessageBox::Critical,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            delete XFile;
            conn->errorLog();
    	    hnd->RSTErr();
            mb->exec();
            delete mb;
            return;
        }
        delete XFile;
        if(conn->CID() != 0)
        {
            conn->setUA(hnd->getValue("usr").toInt());
            QMessageBox *mb = new QMessageBox("Helhed",
            "Dit C.ID er blevet fornyet.",QMessageBox::Information,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            mb->exec();
            delete mb;
        }
    }
}

/** MWin::re_Login()
 * --
 * sends the login details again. This is used
 * if one has had two or more applications logged
 * in with the same user.
 */
void
MWin::re_login()
{
    emit log("main/mwin.cc","re_login: ");
    conn->Command("login");
}

/** MWin::setCurrentTab(int)
 * --
 * sets the tab on the tabWidget
 */
void
MWin::setCurrentTab(int i)
{
  emit log("main/mwin.cc","setCurrentTab: ");
  if(i < mwin::tabWidget->count())
    mwin::tabWidget->setCurrentIndex(i);
}

/** MWin::styleCDE()
 * --
 * sets the current style to CDE
 */
void
MWin::styleCDE()
{
    emit log("main/mwin.cc","styleCDE: ");
    QStyle *st = new QCDEStyle;
    QApplication::setPalette(st->standardPalette());
    QApplication::setStyle(st);
}
/** MWin::stylePlast()
 * --
 * sets the current style to Plastique
 */
void
MWin::stylePlast()
{
    emit log("main/mwin.cc","stylePlast: ");
    QStyle *st = new QPlastiqueStyle;
    QApplication::setPalette(st->standardPalette());
    QApplication::setStyle(st);
}

/** MWin::styleStd()
 * --
 * sets the current style to Plastique
 */
void
MWin::styleStd()
{
    emit log("main/mwin.cc","styleStd: ");
    QStyle *st = cfg->getStyleHint();
    QApplication::setPalette(st->standardPalette());
    QApplication::setStyle(st);
}
