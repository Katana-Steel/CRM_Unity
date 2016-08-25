#include <QtGui>
#include <QtPlugin>
#include "stat_totsalg.h"
#include "conn.h"
#include "stat_totsalg_xml.h"
#include "stat_totsalg_sdlg.h"
#include "stat.h"

StatTotSalg::StatTotSalg()
{
    hnd = new XmlHnd;
    xml = new QXmlSimpleReader;
    xml->setContentHandler(hnd);
    stat=0;
}

StatTotSalg::~StatTotSalg()
{
    delete hnd;
    delete xml;
  if(stat) {
    stat->accept();
    delete stat;
    stat = 0;
  }
}

QString
StatTotSalg::name()
{
    return QString("Totalt Salg");
}

int
StatTotSalg::searchDialog()
{
    if(parent) {
        TotalSalg *win = new TotalSalg(conn,parent);
        int r = win->exec();
        delete win;
        if(r == QDialog::Accepted) {
            stat = new Stat("Finder, beregner og lister ordre...",parent);
            stat->place();
            stat->exec();
            delete stat;
            stat = 0;
        }
        else conn->plugin();
        return r;
    } else {
        return QMessageBox::information(0,"StatTotSalg","Kunne ikke vise dialog boxen","Ok",0,0);
    }
}

void
StatTotSalg::xmlParse()
{
  if(stat) {
    stat->accept();
  }
    QFile *file;
    conn->plugin();
    if(conn->Data()->isOpen())
    {
        file = conn->Data();
        file->reset();
        file->close();
        QXmlInputSource *XFile = new QXmlInputSource(file);
        if(!xml->parse(*XFile))
        {
            XFile->setData(conn->Data(1));
            if(!xml->parse(*XFile))
            {
                conn->errorLog();
                delete XFile;
                return;
            }
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
        hnd->dispRes(conn,parent);
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

Q_EXPORT_PLUGIN2(stat_totsalg,StatTotSalg)
