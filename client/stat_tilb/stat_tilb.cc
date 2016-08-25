#include <QtGui>
#include <QtXml>
#include <QtPlugin>
#include "stat_tilb.h"
#include "conn.h"
#include "stat_tilb_sdlg.h"
#include "stat_tilb_xml.h"
#include "stat.h"

StatTilb::StatTilb()
{
    hnd = new XmlHnd;
    xml = new QXmlSimpleReader;
    xml->setContentHandler(hnd);
    status = 0;
}

StatTilb::~StatTilb()
{
    delete hnd;
    delete xml;
}

QString
StatTilb::name()
{
    return QString("Tilbuds lukke procent");
}

int
StatTilb::searchDialog()
{
    if(parent) {
        SearchDlg *win = new SearchDlg(conn,parent);
        int r = win->exec();
        delete win;
        if(r == QDialog::Accepted) {
            status = new Stat("Finder og lister kunder...",parent);
            status->place();
            status->exec();
            delete status;
            status = 0;
        }
        else conn->plugin();
        return r;
    } else {
        return QMessageBox::information(0,"StatTilb","Kunne ikke vise dialog boxen","Ok",0,0);
    }
}

void
StatTilb::xmlParse()
{
  if(status) {
    status->accept();
  }
    conn->plugin();
    QFile *file;
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
        if(hnd->srvErr())
        {
            QMessageBox *mb = new QMessageBox("Helhed",
            hnd->getValue("error"),QMessageBox::Warning,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            mb->exec();
            delete XFile;
            conn->errorLog();
            delete mb;
            return;
        }
        hnd->dispRes(parent,conn);
        if(hnd->resSuccess())
        {
            QMessageBox *mb = new QMessageBox("Helhed",
            hnd->getValue("success"),QMessageBox::Information,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            mb->exec();
            delete XFile;
            delete mb;
            return;
        }
        delete XFile;
    }
}

Q_EXPORT_PLUGIN2(stat_tilb,StatTilb)
