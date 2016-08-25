#include <QtGui>
#include "stat_stklist.h"
#include "stat_stklist_xml.h"
#include "stat_stklist_sdlg.h"
#include "stat.h"
#include <conn.h>

//! The Plugin constructor.
/*!
    It sets up the plugin to be ready for use
    by creating the xml handler and parser.
*/
Stat_StkList::Stat_StkList()
{
    conn=0;
    stat=0;
    parent=0;
    hnd = new XmlHnd;
    xml = new QXmlSimpleReader;
    xml->setContentHandler(hnd);
    xml->setErrorHandler(hnd);
}

//! The Plugin destructor
/*!
    It clears up the data it has allocated
    while running.
*/
Stat_StkList::~Stat_StkList()
{
    delete xml;
    delete hnd;
}

//! The Plugin name.
QString
Stat_StkList::name()
{
    return QString("Stk. Liste");
}

//! Opens the Search Dialog.
int
Stat_StkList::searchDialog()
{
    QDialog *win = new SearchDlg(conn,parent);
    int r = win->exec();
    delete win;
    if(r == QDialog::Accepted) {
        stat = new Stat("Finder Vare...",parent);
        stat->place();
        stat->exec();
        delete stat;
        stat = 0;

    }
    else conn->plugin();
    return r;
}

//! The XML parser.
/*!
    Parses the return from the server and takes
    appopriate action.
*/
void
Stat_StkList::xmlParse()
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
        hnd->dispRes(parent);
        delete XFile;
    }
}

Q_EXPORT_PLUGIN2(stat_stklist,Stat_StkList)
