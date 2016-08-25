#include <QtGui>
#include "stat_sogning.h"
#include "stat_sogning_sdlg.h"
#include "stat_sogning_xml.h"
#include "stat.h"
#include <conn.h>

Stat_Sogning::Stat_Sogning()
{
    conn=0;
    stat=0;
    parent=0;
    hnd = new XmlHnd;
    xml = new QXmlSimpleReader;
    xml->setContentHandler(hnd);
    xml->setErrorHandler(hnd);
}

Stat_Sogning::~Stat_Sogning()
{
    delete xml;
    delete hnd;
}

QString
Stat_Sogning::name()
{
    return QString("Tekst Multi-Søgning");
}

int
Stat_Sogning::searchDialog()
{
    MultiSearch *win = new MultiSearch(conn,parent);
    int r = win->exec();
    delete win;
    if(r == QDialog::Accepted)
    {
        stat = new Stat("Søger efter emner...",parent);
        stat->place();
        stat->exec();
        delete stat;
        stat = 0;
    }
    else conn->plugin();
    return r;
}

void
Stat_Sogning::xmlParse()
{
    if(stat) stat->accept();
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
                if(conn->getUA()==10) {
                    QMessageBox *mb = new QMessageBox("Helhed",
                    hnd->getValue("parseerror"),QMessageBox::Warning,
                    QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
                    mb->exec();
                    delete mb;
                }
                conn->errorLog();
                delete XFile;
                return;
            }
        }
        if(hnd->srvErr()) {
            QMessageBox *mb = new QMessageBox("Helhed",
            hnd->getValue("error"),QMessageBox::Warning,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            mb->exec();
            delete mb;
            delete XFile;
            return;
        }
        hnd->dispRes(conn,parent);
        delete XFile;
    }
}

Q_EXPORT_PLUGIN2(stat_sogning,Stat_Sogning)
