#include <QtGui>
#include <conn.h>
#include <stat.h>
#include "stat_changed.h"
#include "stat_changed_sdlg.h"
#include "stat_changed_xml.h"

StatChanged::StatChanged()
{
    conn=0;
    stat=0;
    parent=0;
    hnd = new XmlHnd;
    xml = new QXmlSimpleReader;
    xml->setContentHandler(hnd);
    xml->setErrorHandler(hnd);
}

StatChanged::~StatChanged()
{
    delete hnd;
    delete xml;
}

QString
StatChanged::name()
{
    return QString("(Ikke) Ændret Vare");
}

int
StatChanged::searchDialog()
{
    conn->plugin();
    QDialog *win = new SearchDlg(conn, parent);

    return win->exec();
}

void
StatChanged::xmlParse()
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
        delete XFile;
    }
}

Q_EXPORT_PLUGIN2(stat_changed,StatChanged)

