/** \file tab_infiles.cc

    \brief LVO main file.

 \verbatim
 ********************************************************
 * Author: René Kjellerup                               *
 *                                                      *
 * Purpose:                                             *
 *  This is the primary dialog handler for the file     *
 *  loader to run a multi entry update in the database. *
 *  And the dialog for a multi price editor.            *
 *                                                      *
 * Usage:                                               *
 *  The Filehandle:                                     *
 *    Simply click the "vælg fil" button to select the  *
 *    file to work with. Then select the "Funktion" and *
 *    "Fil type" which matches the selected file and    *
 *    then click the "Ok" button to upload the data.    *
 *  The Price editor:                                   *
 *    You make a grossery search and get a list like    *
 *    the one you get when creating an order. In the    *
 *    list just edit the line to what you like. Then    *
 *    mark the lines you've edited by clicking on the   *
 *    lines and holding <ctrl>, then click the button   *
 *    "Ret Valgte".                                     *
 *                                                      *
 ********************************************************\endverbatim
*/
#include <QtGui>
#include <QtXml>
#include "tab_infiles.h"
#include "tab_infiles_fh.h"
#include "tab_infiles_xml.h"
#include "conn.h"
#include "stat.h"

/*! \var Ui_fDlg::grossList
    \brief a QTableWidget list to hold sales items

  This is simular to the grossery list in the sales
  module main difference is this list is connected
  to functions which permits the user to modify
  existing, add new, or even delete items for sale.
*/
//! the constructor.
/*!
 * This initiates the plugin and makes it ready for
 * deployment.
 */
tabInFiles::tabInFiles() :
    pFile(""),ready(true),mod("tab_lvo/")
{
    c = 0;
    status = 0;
    input = 0;
    fmx = 0;
    fh = new FileHandler;
    hnd = new XmlHnd;
    xml = new QXmlSimpleReader;
    xml->setContentHandler(hnd);
    dk = new QLocale(QLocale::Danish);
    emit Log(mod+"tab_infiles.cc","(C)tabInFiles: LVO plugin ready");
}

//! the destructor.
/*!
 * This clean up the objects created during run.
 */
tabInFiles::~tabInFiles()
{
    emit Log(mod+"tab_infiles.cc","(C)tabInFiles: LVO is being destroyed");
    if(status) delete status;
    if(input) delete input;
    delete fh;
    delete hnd;
    delete xml;
    delete dk;
    if(fmx) delete fmx;
}

//! Design setup.
/*!
 * This sets up the visual parts of the plugin
 * and connect its various objects.
 */
void
tabInFiles::LoadInterface()
{
    emit Log(mod+"tab_infiles.cc","LoadInterface: initiating L.V.O. GUI");
    setupUi(this);
    QFont ft = grossList->font();
    fmx = new QFontMetrics(ft);
    connect(fh, SIGNAL(tick(int)), fileProgress, SLOT(setValue(int)));
    connect(fh, SIGNAL(finished()), this, SLOT(resetReady()));
    connect(getFile, SIGNAL(clicked()), this, SLOT(OpenFile()));
    connect(processFile, SIGNAL(clicked()), this, SLOT(startParse()));
    connect(fh, SIGNAL(tick(Case*)), this, SLOT(addCase(Case*)));
    connect(fh, SIGNAL(tick(KData*)), this, SLOT(addCust(KData*)));
    connect(fDlg::update, SIGNAL(clicked()), this, SLOT(multiUpdate()));
    connect(search, SIGNAL(clicked()), this, SLOT(searchGross()));
    connect(sInput, SIGNAL(returnPressed()), this, SLOT(searchGross()));
    connect(grossList, SIGNAL(itemChanged(QTableWidgetItem*)),this, SLOT(valueUpdate(QTableWidgetItem*)));
    connect(addLine, SIGNAL(clicked()), this, SLOT(addGross()));
    connect(delSelected, SIGNAL(clicked()), this, SLOT(multiDelete()));
    emit Log(mod+"tab_infiles.cc","LoadInterface: L.V.O. GUI builded");
}

//! The name of the plugin.
/*!
 * A string constant which identify the plugin.
 */
QString
tabInFiles::name()
{
    return QString("L.V.O.");
}

// is commented in tab_interf.h
int
tabInFiles::minUserAccess()
{
    return 9;
}

// is commented in tab_interf.h
void
tabInFiles::setConn(Conn *_c)
{
    c = _c;
}

// is commented in tab_interf.h
void
tabInFiles::ParseXML()
{
    if(status) status->accept();
    emit Log(mod+"tab_infiles.cc","ParseXML: processing request result");

    QFile *file;
    if(c->Data()->isOpen())
    {
        file = c->Data();
        file->reset();
        file->close();
        QXmlInputSource *XFile = new QXmlInputSource(file);
        hnd->reset();
        if(!xml->parse(*XFile))
        {
            XFile->setData(c->Data(1));
            if(!xml->parse(*XFile))
            {
                c->errorLog();
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
            c->errorLog();
            delete mb;
            return;
        }
        if(hnd->srvSuccess())
        {
            QMessageBox *mb = new QMessageBox("Helhed",
            hnd->getValue("success"),QMessageBox::Information,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            mb->exec();
            delete mb;
        }
        QVector<SData> sdata;
        if(hnd->getSDList(sdata))
        {
            showGList(sdata);
        }
        delete XFile;
    }
    emit Log(mod+"tab_infiles.cc","ParseXML: request processing finished.");
}

// is commented in tab_interf.h
void
tabInFiles::Shown()
{
    emit Log(mod+"tab_infiles.cc","Shown: Displaying L.V.O.");
    QMessageBox::information(this, "LVO", "Kunder/DC4 komninationen er kun lavet\ntil Danske kunder.\n\n"
                                          "Hvis du vil uploade en fil med udenlandske\nkunder i.\nKonverter "
                                          "da venligst filen til CSV og brug\nså Kunder/CSV i stedet",QMessageBox::Ok);
}

//! a Locale float converter.
/*!
  This take s a string with a floating point number and convertes it to a
  Danish looking floating point number and returns it.
*/
QString
tabInFiles::convertToDk(const QString &str)
{
    float f;
    bool ok;
    if(str.contains(',')) f = dk->toFloat(str,&ok);
    else                  f = str.toFloat(&ok);
    if(!ok) f = 0.0f;
    return dk->toString(f,'f',2);
}

//! search the database for items for sale.
/*!
  This requests a list of SData items and clears
  the grossery view list ( Ui_fDlg::grossList ).
*/
void
tabInFiles::searchGross()
{
    while(grossList->rowCount() > 0)
        grossList->removeRow(0);

    emit Log(mod+"tab_infiles.cc","searchGross: ");
    QString req = "vnr="+sInput->text();
    QString date = "";
    if(checkBox->isChecked()) {
        if(radioButton_2->isChecked())
            req += "&Y=";
        else
            req += "&O=";

        date = dateEdit->date().toString("yyyy-MM-dd");
    }
    req += date;
    c->Command("seek_gross",req);
    status = new Stat("Søger Vare/Sags nr.",this);
    status->place();
    status->exec();
    delete status;
    status=0;
}

//! display the list of the items searched for.
/*!
  This add a line per SData item found in the database
  to the grossery view list sorta like the MWin::showGList
  function does.
*/
void
tabInFiles::showGList(QVector<SData> &sdata)
{
    SData sd;
    int w,
        col0=grossList->columnWidth(0),
        col1=grossList->columnWidth(1),
        col2=150, // this column has a tendency to very wide so resetting it to smaller width is nessecery.
        col3=grossList->columnWidth(3);
    disconnect(grossList,0,0,0);
    QTableWidgetItem *twi;
    SDataListItem *sdli;
    foreach(sd,sdata) {
        grossList->insertRow(0);
        // rab is used for priority in this module... due to lazyness in not wanting to make another class for this.
        sdli = new SDataListItem(sd.rab);
        sdli->setData(sd);
        grossList->setItem(0,0,sdli);
        twi = new QTableWidgetItem(sd.vnr);
        grossList->setItem(0,1,twi);
        twi = new QTableWidgetItem(sd.vtxt);
        grossList->setItem(0,2,twi);
        sd.stk_p = convertToDk(sd.stk_p);
        twi = new QTableWidgetItem(sd.stk_p);
        twi->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        grossList->setItem(0,3,twi);

        w = fmx->width(sd.rab);
        if((w+10) > col0) col0 = w+10;
        w = fmx->width(sd.vnr);
        if((w+10) > col1) col1 = w+10;
        w = fmx->width(sd.vtxt);
        if((w+10) > col2) col2 = w+10;
        w = fmx->width(sd.stk_p);
        if((w+10) > col3) col3 = w+10;
    }

    grossList->setColumnWidth(0,col0);
    grossList->setColumnWidth(1,col1);
    if(col2 > 150) {
        grossList->setColumnWidth(2,150);
    } else {
        grossList->setColumnWidth(2,col2);
    }
    grossList->setColumnWidth(3,col3);

    for(int i=0;i<grossList->rowCount();i++)
        grossList->setRowHeight(i,20);

    connect(grossList, SIGNAL(itemChanged(QTableWidgetItem*)),this, SLOT(valueUpdate(QTableWidgetItem*)));
}

//! Updates/Inserts 1 or more grosseries.
/*!
    The function takes all the selected rows in the
    grossery list and sends them to the server one
    line at a time to a caching functions. Then calls
    an execute function that reads the cache and
    updates or inserts the lines into the database as
    necessary.
*/
void
tabInFiles::multiUpdate()
{
    QList<QTableWidgetItem*> ls = grossList->selectedItems();
    if(ls.empty()) {
        QMessageBox::information(this,"L.V.O.","Du skal vælge mindst én linje for at kunne opdater",QMessageBox::Ok);
        return;
    }
    fileProgress->setMaximum(ls.size());
    fileProgress->setValue(0);
    QTableWidgetItem *twi;
    SDataListItem *sdli;
    int lines = 0,items=0;
    disconnect(this,0,c,0);
    foreach(twi, ls) {
        fileProgress->setValue(++items);
        sdli = dynamic_cast<SDataListItem *>(twi);
        if(sdli == 0) continue;
        lines++;
        SData sd = sdli->data();
        QString type;
        switch(sd.type) {
        default:
        case SData::H:
            type = QString("H");
            break;
        case SData::S:
            type = QString("S");
            break;
        }
        c->Command("lvo",
              "f=" + QString("g_update") +
            "&id=" + QString::number(sd.sid) +
          "&type=" + type +
          "&sort=" + sd.rab +
           "&vnr=" + sd.vnr +
          "&vtxt=" + sd.vtxt.toLatin1() +
          "&pris=" + convertToDk(sd.stk_p));
    }
    c->Command("lvo", "f=" + QString("g_run"));
    status = new Stat("Opdatere...",this);
    status->place();
    status->exec();
    delete status;
    status = 0;
    if(sInput->text().isEmpty()) sInput->setText(grossList->item(0,0)->text());
    fileProgress->setValue(0);
    searchGross();
}

//! Deletes 1 or more grosseries.
/*!
    The function takes all the selected rows in the
    grossery list and sends them to the server one
    line at a time to a caching functions. Then calls
    an execute function that reads the cache and
    remove the grosseries the lines contains from the
    database.
*/
void
tabInFiles::multiDelete()
{
    int r = QMessageBox::warning(this,"L.V.O.","Er du sikker på at du vil\nslette ALLE de makerede vare?",QMessageBox::Yes,QMessageBox::No);
    if(QMessageBox::No == r) return;
    QList<QTableWidgetItem*> ls = grossList->selectedItems();
    if(ls.empty()) {
        QMessageBox::information(this,"L.V.O.","Du skal vælge mindst én linje for at kunne slette",QMessageBox::Ok);
        return;
    }
    fileProgress->setMaximum(ls.size());
    fileProgress->setValue(0);
    QTableWidgetItem *twi;
    SDataListItem *sdli;
    int lines = 0,items=0;
    foreach(twi, ls) {
        fileProgress->setValue(++items);
        sdli = dynamic_cast<SDataListItem *>(twi);
        if(sdli == 0) continue;
        lines++;
        SData sd = sdli->data();
        QString type;
        switch(sd.type) {
        default:
        case SData::H:
            type = QString("H");
            break;
        case SData::S:
            type = QString("S");
            break;
        }
        c->Command("lvo",
              "f=" + QString("g_delete") +
            "&id=" + QString::number(sd.sid) +
          "&type=" + type );
    }
    QMessageBox::information(this,"L.V.O.",QString::number(lines)+" vare er blevet slettet.",QMessageBox::Ok);
    if(sInput->text().isEmpty()) sInput->setText(grossList->item(0,0)->text());
    fileProgress->setValue(0);
    searchGross();
}

//! Updates the currently editted item.
/*!
    Updates the SData object stored in the first cell of the
    table.
*/
void
tabInFiles::valueUpdate(QTableWidgetItem *twi)
{
    disconnect(grossList,0,0,0);
    int r = grossList->row(twi);
    int c = grossList->column(twi);
    SDataListItem *sdli = dynamic_cast<SDataListItem *>(grossList->item(r,0));
    SData sd = sdli->data();
    switch(c) {
    case 0:
        sd.rab = twi->text();
        break;
    case 1:
        sd.vnr = twi->text();
        break;
    case 2:
        sd.vtxt = twi->text();
        break;
    case 3:
        sd.stk_p = convertToDk(twi->text());
        delete twi;
        twi = new QTableWidgetItem(sd.stk_p);
        twi->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        grossList->setItem(r,c,twi);
        break;
    }
    sdli->setData(sd);
    grossList->item(r,0)->setTextColor(QColor::fromRgb(0,0,255));
    grossList->item(r,1)->setTextColor(QColor::fromRgb(0,0,255));
    grossList->item(r,2)->setTextColor(QColor::fromRgb(0,0,255));
    grossList->item(r,3)->setTextColor(QColor::fromRgb(0,0,255));
    connect(grossList, SIGNAL(itemChanged(QTableWidgetItem*)),this, SLOT(valueUpdate(QTableWidgetItem*)));
}

//! The "Case" insert from file function.
/*!
    Sends the found cases in the input file to the server
    who then clears the case table (because the cases in
    the file is all the cases for sale). Then the server
    adds all the cases to the now empty table in the DB.
*/
void
tabInFiles::runSystem0()
{
    status = new Stat("Sender Sags filen til serveren...",this);
    status->show();
    status->place();
    fileProgress->setValue(0);
    fileProgress->setMaximum(caList.size());
    for(int i=0;(i<caList.size());i++) {
        c->Command("lvo",
              "f=" + QString("sag_insert") +
           "&cnr=" + caList.at(i)->cnr +
          "&ctxt=" + caList.at(i)->ctxt +
          "&cval=" + convertToDk(caList.at(i)->cval));
        fileProgress->setValue(i+1);
    }
    c->Command("lvo","f=sag_run");
    fileProgress->setValue(caList.size());
    status->hide();
    delete status;
    status = new Stat("Sender Sags filen til serveren...",this);
    status->place();
    status->exec();
    delete status;
    status=0;
}

//! Inserts grosseries from a file.
/*!
    Does almost the same as runSystem0 however
    the server doesn't deletes the case table.
    It only adds the found grosseries to the
    "machines" table.
*/
void
tabInFiles::runSystem1()
{
    status = new Stat("Sender Vare filen til serveren...",this);
    status->show();
    status->place();
    fileProgress->setValue(0);
    fileProgress->setMaximum(caList.size());
    for(int i=0;(i<caList.size());i++) {
        c->Command("lvo",
              "f=" + QString("g_update") +
           "&id=0" +
         "&type=H" +
           "&vnr=" + caList.at(i)->cnr +
          "&vtxt=" + caList.at(i)->ctxt +
          "&pris=" + convertToDk(caList.at(i)->cval));
        fileProgress->setValue(i+1);
    }
    c->Command("lvo", "f=" + QString("g_run"));
    fileProgress->setValue(caList.size());
    status->hide();
    delete status;
    status = new Stat("Sender Vare filen til serveren...",this);
    status->place();
    status->exec();
    delete status;
    status=0;
}

//! Updates/Inserts custommers from a file.
/*!
    Transmites the found custommers to the server which
    then update or insert the custommer as appropriate.
*/
void
tabInFiles::runSystem2()
{
    status = new Stat("Sender Kunde filen til serveren...",this);
    status->show();
    status->place();
    fileProgress->setValue(0);
    fileProgress->setMaximum(caList.size());
    for(int i=0;(i<kdList.size());i++) {
        c->Command("lvo",
              "f=" + QString("cust_que") +
           "&knr=" + kdList.at(i)->knr +
          "&navn=" + kdList.at(i)->navn +
           "&att=" + kdList.at(i)->att +
           "&adr=" + kdList.at(i)->adr +
          "&post=" + kdList.at(i)->post+
            "&by=" + kdList.at(i)->by +
          "&land=" + kdList.at(i)->land +
           "&ean=" + kdList.at(i)->ean_se +
           "&tlf=" + kdList.at(i)->tlf +
           "&fax=" + kdList.at(i)->fax +
         "&mobil=" + kdList.at(i)->mobil);
        fileProgress->setValue(i+1);
    }
    c->Command("lvo","f=cust_run");
    fileProgress->setValue(caList.size());
    status->hide();
    delete status;
    status = new Stat("Sender Kunde filen til serveren...",this);
    status->exec();
    delete status;
    status=0;
}
//! Creates the Gross/Case data dialog.
/*!
    Creates a dialog for Gross/Case data preview and
    final submition or refusal of said data to the
    database/system.
*/
void
tabInFiles::setupSystem0Dlg(QDialog *win)
{
    QFont font = QFont("Andale Mono");
    QVBoxLayout *vbl = new QVBoxLayout(win);
    QHBoxLayout *hbl = new QHBoxLayout;
    QTableWidget *lw = new QTableWidget;
    lw->setFont(font);
    lw->setColumnCount(3);
    QPushButton *ok = new QPushButton("Okay");
    QPushButton *can = new QPushButton("Annuller");
    vbl->addWidget(new QLabel(options->currentText()+ "," + fileType->currentText()));
    vbl->addWidget(lw);
    hbl->addWidget(ok);
    hbl->addStretch();
    hbl->addWidget(can);
    vbl->addLayout(hbl);
    win->resize(QSize(400,400));
    connect(ok,SIGNAL(clicked()),win,SLOT(accept()));
    connect(can,SIGNAL(clicked()),win,SLOT(reject()));
    int width, // the width of the current column
        fsw;   // stands for "Font String Width"
    QFontMetrics *fmx = new QFontMetrics(lw->font());
    for(int i=0;(i<caList.size()) && (i<10);i++) {
        int r = lw->rowCount();
        lw->insertRow(r);

        width = lw->columnWidth(0);
        fsw = fmx->width(caList.at(i)->cnr);
        lw->setItem(r,0,new QTableWidgetItem(caList.at(i)->cnr));
        if((fsw+10) < 50)
            if((fsw+10) > width) lw->setColumnWidth(0,fsw+10);

        width = lw->columnWidth(1);
        fsw = fmx->width(caList.at(i)->ctxt);
        lw->setItem(r,1,new QTableWidgetItem(caList.at(i)->ctxt));
        if((fsw+10) < 150)
            if((fsw+10) > width) lw->setColumnWidth(1,fsw+10);

        width = lw->columnWidth(2);
        fsw = fmx->width(caList.at(i)->cval);
        lw->setItem(r,2,new QTableWidgetItem(caList.at(i)->cval));
        if((fsw+10) < 100)
            if((fsw+10) > width) lw->setColumnWidth(2,fsw+10);
    }

    for(int i=0;i<lw->rowCount();i++)
        lw->setRowHeight(i,20);
}
//! Creates the Custommer data dialog.
/*!
    Creates a dialog for Custommer data preview and
    final submition or refusal of said data to the
    database/system.
*/
void
tabInFiles::setupSystem1Dlg(QDialog *win)
{
    QFont font = QFont("Andale Mono");
    QVBoxLayout *vbl = new QVBoxLayout(win);
    QHBoxLayout *hbl = new QHBoxLayout;
    QTableWidget *lw = new QTableWidget;
    lw->setFont(font);
    lw->setColumnCount(5);
    QPushButton *ok = new QPushButton("Okay");
    QPushButton *can = new QPushButton("Annuller");
    vbl->addWidget(new QLabel(options->currentText()+ "," + fileType->currentText()));
    vbl->addWidget(lw);
    hbl->addWidget(ok);
    hbl->addStretch();
    hbl->addWidget(can);
    vbl->addLayout(hbl);
    win->resize(QSize(400,400));
    connect(ok,SIGNAL(clicked()),win,SLOT(accept()));
    connect(can,SIGNAL(clicked()),win,SLOT(reject()));
    int width, // the width of the current column
        fsw;   // stands for "Font String Width"
    QRect rc;
    QFontMetrics *fmx = new QFontMetrics(lw->font());
    for(int i=0;(i<kdList.size()) && (i<10);i++) {
        int r = lw->rowCount();
        lw->insertRow(r);

        width = lw->columnWidth(0);
        fsw = fmx->width(kdList.at(i)->knr);
        lw->setItem(r,0,new QTableWidgetItem(kdList.at(i)->knr));
        if((fsw+10) < 50)
            if((fsw+10) > width) lw->setColumnWidth(0,fsw+10);

        width = lw->columnWidth(1);
        fsw = fmx->width(kdList.at(i)->navn);
        lw->setItem(r,1,new QTableWidgetItem(kdList.at(i)->navn));
        if((fsw+10) < 150)
            if((fsw+10) > width) lw->setColumnWidth(1,fsw+10);

        width = lw->columnWidth(2);
        fsw = fmx->width(kdList.at(i)->att);
        lw->setItem(r,2,new QTableWidgetItem(kdList.at(i)->att));
        if((fsw+10) < 100)
            if((fsw+10) > width) lw->setColumnWidth(2,fsw+10);

        width = lw->columnWidth(3);
        fsw = fmx->width(kdList.at(i)->adr);
        lw->setItem(r,3,new QTableWidgetItem(kdList.at(i)->adr));
        if((fsw+10) < 100)
            if((fsw+10) > width) lw->setColumnWidth(2,fsw+10);

        width = lw->columnWidth(4);
        fsw = fmx->width(kdList.at(i)->post);
        lw->setItem(r,4,new QTableWidgetItem(kdList.at(i)->post));
        if((fsw+10) < 100)
            if((fsw+10) > width) lw->setColumnWidth(2,fsw+10);
    }

    for(int i=0;i<lw->rowCount();i++)
        lw->setRowHeight(i,20);
}

//! Unused at the moment
/*!
    The skeletal function used to construct the dialogs
    to preview the data read from the input file.
*/
void
tabInFiles::setupSystem2Dlg(QDialog *win)
{
    QFont font = QFont("Andale Mono");
    win->setFont(font);
    QVBoxLayout *vbl = new QVBoxLayout(win);
    QPushButton *ok = new QPushButton("Annuller");
    vbl->addWidget(ok);
    vbl->addStretch();
    win->resize(QSize(400,400));
    connect(ok,SIGNAL(clicked()),win,SLOT(reject()));
}

//! Get the file to read.
/*!
    Opens a file dialog to get the path for the
    input file. Gets the file size to set the
    progress accordingly.
*/
void
tabInFiles::OpenFile()
{
    if(!ready) return;
    ready = false;
    if(input) { input->close(); delete input; input = 0; }
    pFile = QFileDialog::getOpenFileName(this,"Find filen der skal sættes ind.",pFile,"Alle Filer (*.*)");
    if(pFile != QString("")) {
        input = new QFile(pFile);
        if(input->exists()) {
            QFileInfo fi = QFileInfo(*input);
            fileProgress->setValue(0);
            fileProgress->setMaximum(input->size());
            fileName->setText(fi.fileName());
            pFile = fi.filePath();
        }
    }
}

//! Response function called after datafile was read.
/*!
    Displays a custom designed preview dialog according to
    the current options set. If the dialog is accepted it
    then submits the date to the server.

    After the preview dialog has been closed (accepted or
    otherwise) it does some clean up. The QVectors used
    to hold the data to be submitted to the server are
    cleared. The input is closed and the reference to it
    is destroyed. the Progress bar is reset to 0(zero).
    And the open file function is reactivated.
*/
void
tabInFiles::resetReady()
{
    ready = true;
    QDialog *win = new QDialog(this);
    switch(options->currentIndex()) {
     case 1: setupSystem0Dlg(win); break;
     case 2: setupSystem0Dlg(win); break;
     case 3: setupSystem1Dlg(win); break;
    }
    int r = win->exec();
    delete win;
    if(r == QDialog::Accepted) {
     switch(options->currentIndex()) {
      case 1: runSystem0(); break;
      case 2: runSystem1(); break;
      case 3: runSystem2(); break;
     }
    }
    while(!caList.empty()) {
        delete caList.back();
        caList.pop_back();
    }
    while(!kdList.empty()) {
        delete kdList.back();
        kdList.pop_back();
    }
    fileName->setText("");
    pFile = "";
    fileProgress->setValue(0);
    if(input) { input->close(); delete input; input = 0; }
}

//! Runs the reading of the input file.
/*!
    Sets up the options selected, does a bit of testing
    for the validity of the selected options.

    Then starts the file handling loop in a thread of its
    own using the FileHandler object.
*/
void
tabInFiles::startParse()
{
    if(options->currentIndex() <= 0) {
        QMessageBox::information(this,"Helhed","Du skal vælge hvilken type fil det er.",QMessageBox::Ok);
        return;
    }
    if(fileType->currentIndex() <= 0) {
        QMessageBox::information(this,"Helhed","Du skal vælge hvilken opbygning filen har.",QMessageBox::Ok);
        return;
    }
    if(input->exists()) {
        fileOptions fo;
        switch(fileType->currentIndex())
        {
        case 1:
            fo.ft = DC4;
            break;
        case 2:
            fo.ft = CSV;
            break;
        }
        switch(options->currentIndex())
        {
        case 1:
            fo.dbp = Sager;
            break;
        case 2:
            fo.dbp = Vare;
            break;
        case 3:
            fo.dbp = Kunder;
            break;
        }
        fh->setFile(input,fo);
        fh->start();
    }
}

//! Adds a gross/case to the case buffer.
void
tabInFiles::addCase(Case *str)
{
    caList.push_back(str);
}

//! Adds a custommer to the custommer buffer.
void
tabInFiles::addCust(KData *str)
{
    kdList.push_back(str);
}

//! Adds a line to the price editor.
/*!
    Creates a clean "Machine" grossery. Adds a line to
    the grossery list.

    Sets the line to match the data.

    Sets the line height to match the others.
*/
void
tabInFiles::addGross()
{
    SData sd;
    sd.clear();
    sd.type = SData::H;
    sd.stk_p = "0";
    disconnect(grossList,0,0,0);
    QTableWidgetItem *twi;
    SDataListItem *sdli;

    int r = grossList->rowCount();
    grossList->insertRow(r);
    sdli = new SDataListItem(sd.rab);
    sdli->setData(sd);
    grossList->setItem(r,0,sdli);
    twi = new QTableWidgetItem(sd.vnr);
    grossList->setItem(r,1,twi);
    twi = new QTableWidgetItem(sd.vtxt);
    grossList->setItem(r,2,twi);
    sd.stk_p = convertToDk(sd.stk_p);
    twi = new QTableWidgetItem(sd.stk_p);
    twi->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    grossList->setItem(r,3,twi);

    grossList->setRowHeight(r,20);
    connect(grossList, SIGNAL(itemChanged(QTableWidgetItem*)),this, SLOT(valueUpdate(QTableWidgetItem*)));
}

Q_EXPORT_PLUGIN2(tab_infile,tabInFiles)
