/**************************************************************************
    This file: main/stat.cc is part of Helhed Client.

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
#include <QtCore>
#include <QtGui>
#include "mwin.h"
#include "stat.h"
#include "xml_c_handle.h"
#include "stat_interf.h"

/*
 *
 * --
 *
 */
void
MWin::fetchTOKA()
{
    emit log("main/stat.cc","MWin::fetchTOKA");
    QString req = "onr=" + mwin::tokaNr->text();
    conn->Command("get_print",req);
}

/*
 * MWin::initTabsStat()
 * --
 * this initiates objects and sets up
 * connections for the Statistic interface.
 */
void
MWin::initTabsStat()
{
    emit log("main/stat.cc","MWin::initTabsStat");

    sthnd = new StatHnd(this);

    if(statFNamePlug.size() != 0) {
        QPluginLoader loader(statFNamePlug[0]);
        curStatInter = qobject_cast<StatInterface *>(loader.instance());
    } else {
        curStatInter = 0;
        launchStat->setEnabled(false);
        statSearch->setEnabled(false);
    }

    connect(mwin::showTOKAnr, SIGNAL(clicked()), this, SLOT(fetchTOKA()));
    connect(mwin::tokaNr, SIGNAL(returnPressed()), this, SLOT(fetchTOKA()));
    connect(statSearch, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(setCurStatPlugin(const QString&)));
    connect(launchStat, SIGNAL(clicked()), this, SLOT(launchStatDlg()));
}

/*
 *
 * --
 *
 */
void
MWin::launchStatDlg()
{
    emit log("main/stat.cc","MWin::launchStatDlg");
    plugin_called = true;
    curStatInter->setDialogParent(this);
    curStatInter->setConn(conn);
    curStatInter->searchDialog();
}

/*
 *
 * --
 *
 */
void
MWin::ParseStat()
{
    emit log("main/stat.cc","MWin::ParseStat");
    QFile *file;
    xml->setContentHandler(sthnd);
    if(conn->Data()->isOpen())
    {
        file = conn->Data();
        file->reset();
        file->close();
        QXmlInputSource *XFile = new QXmlInputSource(file);
        if(!xml->parse(*XFile))
        {
            delete XFile;
            return;
        }
        if(sthnd->srvErr())
        {
            QMessageBox *mb = new QMessageBox("Helhed",
            sthnd->getValue("error"),QMessageBox::Warning,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            mb->exec();
            delete XFile;
            conn->errorLog();
            delete mb;
            return;
        }
        if(sthnd->resSuccess())
        {
            QMessageBox *mb = new QMessageBox("Helhed",
            sthnd->getValue("success"),QMessageBox::Information,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            mb->exec();
            delete XFile;
            delete mb;
            return;
        }
        delete XFile;
    }
}

/*
 *
 * --
 *
 */
void
MWin::pluginDone()
{
    emit log("main/stat.cc","MWin::pluginDone");
    plugin_called = false;
}

/*
 *
 * --
 *
 */
void
MWin::setCurStatPlugin(const QString &str)
{
    emit log("main/stat.cc","MWin::setCurStatPlugin");
    if(curStatInter) delete curStatInter;
    int i = statSearch->itemData(statSearch->currentIndex()).toInt();
    QPluginLoader loader(statFNamePlug[i]);
    curStatInter = qobject_cast<StatInterface *>(loader.instance());
}
