/**************************************************************************
    This file: main/salg.cc is part of Helhed Client.

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
#include <QtCore>
#include <QtGui>
#include <QtXml>
#include <QFtp>
#include "stat.h"
#include "st_data.h"
#include "config.h"
#include "xml_c_handle.h"
#include "maillist.h"
#include "s_period.h"

/*
 * MWin::add_byt()
 * --
 * this adds a blank line to the exchange table.
 */
void
MWin::add_byt()
{
    emit log("main/salg.cc","MWin::add_byt");
    adding = true;
    int row = sBytteTable->currentRow();
    if(row < 0) row = sBytteTable->rowCount();
    sBytteTable->insertRow(row);

    QTableWidgetItem *it;
    for(int i=0; i<5; i++) {
        switch(i) {
            case 0:
            it = new QTableWidgetItem(tr("1,00"));
            it->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            break;
            case 1:
            case 2:
            it = new QTableWidgetItem(tr(" "));
            break;
            default:
            it = new QTableWidgetItem(tr("0,00"));
            it->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            break;
        }
        sBytteTable->setItem(row,i,it);
    }
    adding = false;

    // adjust the row height
    for(int i=0;i<sBytteTable->rowCount();i++)
    {
        sBytteTable->setRowHeight(i,20);
    }
}

/*
 * MWin::add_sale()
 * --
 * this adds either a blank line or
 * a line with the data from the
 * SData gross object to the sales
 * table.
 */
void
MWin::add_sale()
{
    emit log("main/salg.cc","MWin::add_sale");
    adding = true;
    int row = sSalgTable->rowCount();
    sSalgTable->insertRow(row);
    QTableWidgetItem *it;
    if(gross.type == SData::N) {
      for(int i=0; i<6; i++) {
        switch(i) {
            case 0:
            it = new QTableWidgetItem(tr("1,00"));
            it->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            break;
            case 1:
            case 2:
            it = new QTableWidgetItem(tr(" "));
            break;
            default:
            it = new QTableWidgetItem(tr("0,00"));
            it->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            break;
        }
        sSalgTable->setItem(row,i,it);
      }
    } else {
        it = new QTableWidgetItem(tr("1,00"));
        it->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        sSalgTable->setItem(row,0,it);
        it = new QTableWidgetItem(gross.vnr);
        sSalgTable->setItem(row,1,it);
        it = new QTableWidgetItem(gross.vtxt);
        sSalgTable->setItem(row,2,it);
        it = new QTableWidgetItem(gross.stk_p);
        it->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        sSalgTable->setItem(row,3,it);
        it = new QTableWidgetItem(tr("0,00"));
        it->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        sSalgTable->setItem(row,4,it);
        it = new QTableWidgetItem(gross.stk_p);
        it->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        sSalgTable->setItem(row,5,it);

        // getting and adjusting, if nessesary, the width of the gross nr. column
        int curWidth = sSalgTable->columnWidth(1);
        QRect rc = fmx->boundingRect(gross.vnr.trimmed());
        if((rc.width()+10) < 500) {  // set a max width on 500 pixels
            if((rc.width()+10) > curWidth) sSalgTable->setColumnWidth(1,rc.width()+10);
        } else {
            sSalgTable->setColumnWidth(1,500);
        }

        // getting and adjusting, if nessesary, the width of the gross text column
        curWidth = sSalgTable->columnWidth(2);
        rc = fmx->boundingRect(gross.vtxt.trimmed());
        if((rc.width()+10) < 500) {  // set a max width on 500 pixels
            if((rc.width()+10) > curWidth) sSalgTable->setColumnWidth(2,rc.width()+10);
        } else {
            sSalgTable->setColumnWidth(2,500);
        }

        // reset the gross structure
        gross.clear();
    }
    adding = false;

    // adjust the row height
    for(int i=0;i<sSalgTable->rowCount();i++)
    {
        sSalgTable->setRowHeight(i,20);
    }
}

/*
 * MWin::addNewOrder(QVector<SData*>&)
 * --
 * Takes the data recived and parsed from the server and
 * enters it into its designated tables and lineedits.
 * This comes from two sources either from a saved set-up
 * or from a previously made "order" trough the TOKA
 * module.
 */
void
MWin::addNewOrder(QVector<SData*> &sl)
{
    emit log("main/salg.cc","MWin::addNewOrder");
    clrSale();
    QLocale dk(QLocale::Danish); // a locale to make danish looking number strings from floats/ints
    QTableWidgetItem *sit=0;
    QTableWidgetItem *bit=0;
    int row;
    disconnect(sSalgTable,SIGNAL(itemChanged(QTableWidgetItem*)),0,0);
    disconnect(sBytteTable,SIGNAL(itemChanged(QTableWidgetItem*)),0,0);
    chtype = true;

    QString type = shnd->getValue("type");
    fromTOKA = shnd->getValue("from");
    if(type == QString("0")) mwin::stype->setCurrentIndex(0);
    else if(type == QString("1")) mwin::stype->setCurrentIndex(1);
    else if(type == QString("2")) mwin::stype->setCurrentIndex(2);
    else if(type == QString("3")) mwin::stype->setCurrentIndex(3);
    else if(type == QString("4")) mwin::stype->setCurrentIndex(4);
    else chtype = false;

    if(type == QString("3")){
        sBemark->setPlainText(shnd->getValue(QString("int_msg"))+"\n"+shnd->getValue(QString("bemark")));
    } else {
        internalMsg->setPlainText(shnd->getValue(QString("int_msg")));
        sBemark->setPlainText(shnd->getValue(QString("bemark")));
    }

    int curWidth;
    QRect rc;
    for(int i=0;i<sl.size();i++)
    {
        if(sl[i]->type == SData::S) {
            row = sSalgTable->rowCount();
            sSalgTable->insertRow(row);
            sit = new QTableWidgetItem(sl[i]->stk);
            sit->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            sSalgTable->setItem(row,0,sit);
            sit = new QTableWidgetItem(sl[i]->vnr);
            sSalgTable->setItem(row,1,sit);
            sit = new QTableWidgetItem(sl[i]->vtxt);
            sSalgTable->setItem(row,2,sit);
            sit = new QTableWidgetItem(sl[i]->stk_p);
            sit->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            sSalgTable->setItem(row,3,sit);
            sit = new QTableWidgetItem(sl[i]->rab);
            sit->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            sSalgTable->setItem(row,4,sit);
            float rab = (100.0f - dk.toFloat(sl[i]->rab))/100.0f;
            QString tot = dk.toString((dk.toFloat(sl[i]->stk)*dk.toFloat(sl[i]->stk_p)*rab),'f',2);
            sit = new QTableWidgetItem(tot);
            sit->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            sSalgTable->setItem(row,5,sit);

            // getting and adjusting, if nessesary, the width of the gross nr. column
            curWidth = sSalgTable->columnWidth(1);
            rc = fmx->boundingRect(sl[i]->vnr);
            if((rc.width()+10) > curWidth) sSalgTable->setColumnWidth(1,rc.width()+10);

            // getting and adjusting, if nessesary, the width of the gross text column
            curWidth = sSalgTable->columnWidth(2);
            rc = fmx->boundingRect(sl[i]->vtxt);
            if((rc.width()+10) > curWidth) sSalgTable->setColumnWidth(2,rc.width()+10);
        } else {
            row = sBytteTable->rowCount();
            sBytteTable->insertRow(row);
            bit = new QTableWidgetItem(sl[i]->stk);
            bit->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            sBytteTable->setItem(row,0,bit);
            bit = new QTableWidgetItem(sl[i]->vnr);
            sBytteTable->setItem(row,1,bit);
            bit = new QTableWidgetItem(sl[i]->vtxt);
            sBytteTable->setItem(row,2,bit);
            bit = new QTableWidgetItem(sl[i]->stk_p);
            bit->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            sBytteTable->setItem(row,3,bit);
            QString tot = dk.toString((dk.toFloat(sl[i]->stk)*dk.toFloat(sl[i]->stk_p)),'f',2);
            bit = new QTableWidgetItem(tot);
            bit->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            sBytteTable->setItem(row,4,bit);

            // getting and adjusting, if nessesary, the width of the gross nr. column
            curWidth = sBytteTable->columnWidth(1);
            rc = fmx->boundingRect(sl[i]->vnr);
            if((rc.width()+10) > curWidth) sBytteTable->setColumnWidth(1,rc.width()+10);

            // getting and adjusting, if nessesary, the width of the gross text column
            curWidth = sBytteTable->columnWidth(2);
            rc = fmx->boundingRect(sl[i]->vtxt);
            if((rc.width()+10) > curWidth) sBytteTable->setColumnWidth(2,rc.width()+10);
        }
    }
    if(sit != 0) updateTotSale(sit);
    connect(sSalgTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(updateTotSale(QTableWidgetItem*)));
    if(bit != 0) updateTotExchange(bit);
    connect(sBytteTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(updateTotExchange(QTableWidgetItem*)));
    updateTot();

    rek_nr->setText(shnd->getValue(QString("reknr")));
    sLev->setText(shnd->getValue(QString("levb")));
    sBet->setText(shnd->getValue(QString("betb")));
    stype->setCurrentIndex(shnd->getValue(QString("type")).toInt());
    if(shnd->lev()) {
        levNavn->setText(shnd->getValue(QString("lev_navn")));
        levAtt->setText(shnd->getValue(QString("lev_att")));
        levAdr->setText(shnd->getValue(QString("lev_adr")));
        levPost->setText(shnd->getValue(QString("lev_post")));
        levBy->setText(shnd->getValue(QString("lev_by")));
    }

    // adjust the row height of the sales table
    for(int i=0;i<sSalgTable->rowCount();i++)
    {
        sSalgTable->setRowHeight(i,20);
    }

    // adjust the row height of the exchange table
    for(int i=0;i<sBytteTable->rowCount();i++)
    {
        sBytteTable->setRowHeight(i,20);
    }
}

/*
 * MWin::clearSD()
 * --
 * clears the gross data
 */
void
MWin::clearSD()
{
    emit log("main/salg.cc","MWin::clearSD");
    gross.clear();
}

/*
 * MWin::clrSale()
 * --
 * this clean up and resets the sales module.
 */
void
MWin::clrSale()
{
    emit log("main/salg.cc","MWin::clrSale");
    QLocale dk(QLocale::Danish);
    chtype = false;
    for(; 0<sSalgTable->rowCount();)
        sSalgTable->removeRow(0);
    for(; 0<sBytteTable->rowCount();)
        sBytteTable->removeRow(0);
    mwin::stbyt->setText(dk.toString(0.0f,'f',2));
    mwin::stsalg->setText(dk.toString(0.0f,'f',2));
    updateTot();
    sLev->clear();
    sBet->clear();
    smails->clear();
    rek_nr->clear();
    levNavn->clear();
    levAtt->clear();
    levAdr->clear();
    levPost->clear();
    levBy->clear();
    mwin::nkontakt->setDate(QDate::currentDate());
    stype->setCurrentIndex(0);
    lukke_pro->setValue(0);
    mwin::klar->setChecked(false);
    mwin::sBemark->clear();
    mwin::internalMsg->clear();
//    cs = false;
    fromTOKA="";
}

/*
 * MWin::fetchTemp(QTableWidgetItem*)
 * --
 * requests a saved set-up to be loaded.
 */
void
MWin::fetchTemp(QTableWidgetItem *twi)
{
    emit log("main/salg.cc","MWin::fetchTemp");
    swin->accept();
    SDataListItem *li = dynamic_cast<SDataListItem*>(twi);
    SData sd = li->data();
    QString req = "id="+QString::number(sd.sid);
    shnd->clearSL();
    conn->Command("get_temps",req);
    stat = new Stat("Henter Gemt '"+twi->text()+"'");
    stat->place();
    stat->exec();
    delete stat;
    stat = 0;
}

/*
 * MWin::ftp_done(bool)
 * --
 * takes care of making the appropriate requests
 * depending on that which has been transfered via
 * FTP.
 */
void
MWin::ftp_done(bool err)
{
    emit log("main/salg.cc","MWin::ftp_done");
    delete order;
    order = 0;
    if(err) {
        if(stat) stat->accept();
        QMessageBox::critical(this,"Helhed",ftp->errorString(),QMessageBox::Ok,0);
        return;
    }
    if(QFile::exists(cus.knr + ".xml")) QFile::remove(cus.knr + ".xml");
    if(tmp) {
        conn->Command("save_temp", "title="+title+"&file="+conn->getU()+ "." + title + ".xml");
        title = "";
    } else {
        conn->Command("create_order", "file="+ cus.knr +".xml");
    }
    tabWidget->setCurrentIndex(1);
}
/*
 * MWin::get_mails()
 * --
 * this requests the frequently used mail addresses of the user.
 */
void
MWin::get_mails()
{
  emit log("main/salg.cc","MWin::get_mails");
  shnd->clearML();
  conn->Command("get_mail");
  stat = new Stat("Henter Mail adresser");
  stat->place();
  stat->exec();
  delete stat;
  stat = 0;
}

/*
 * MWin::get_temps()
 * --
 * this requests a list of the user's saved set-ups.
 */
void
MWin::get_temps()
{
  emit log("main/salg.cc","MWin::get_temps");
  shnd->clearSL();
  conn->Command("get_temps");
  stat = new Stat("Henter Gemte");
  stat->place();
  stat->exec();
  delete stat;
  stat = 0;
}

/*
 * MWin::gross_dlg()
 * --
 * this creates the dialog to display a list of items for sale.
 */
void
MWin::gross_dlg()
{
  emit log("main/salg.cc","MWin::gross_dlg");
  if(swin == 0) {
    swin = new QDialog(this);
    QVBoxLayout *vlay = new QVBoxLayout(swin);
    QHBoxLayout *hbox = new QHBoxLayout;
    svnr = new QLineEdit;
    QPushButton *seek = new QPushButton("Søg");
    QPushButton *addB = new QPushButton("Tilføj Blank");
    add = new QPushButton("Indsæt");
    hbox->addWidget(svnr);
    hbox->addWidget(seek);
    hbox->addWidget(add);
    hbox->addWidget(addB);
    vlay->addLayout(hbox);
    vlay->addWidget(lst);
    swin->resize(QSize(485,500));

    connect(seek, SIGNAL(clicked()), this, SLOT(seek_gross()));
    connect(addB, SIGNAL(clicked()), this, SLOT(clearSD()));
    connect(addB, SIGNAL(clicked()), swin, SLOT(accept()));
    connect(lst, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(setSDataFromItem(QTableWidgetItem*)));
    connect(lst, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(setSDataFromItem_get(QTableWidgetItem*)));
    connect(add, SIGNAL(clicked()), swin, SLOT(accept()));
  }
    add->setEnabled(false);
    if(swin->exec() == QDialog::Accepted) add_sale();
}

/*
 * MWin::initTabsSale()
 * --
 * this initiates objects and sets up
 * connections.
 */
void
MWin::initTabsSale()
{
    emit log("main/salg.cc","MWin::initTabsSale");

    order = 0; // contains the created xml file to be uploaded.
    item = 0; // the currently selected cell in the sales tab.
    swin = 0;
    add = 0;
    svnr = 0;

    ftp = new QFtp(this);
    shnd = new SaleHnd(this); // create the Sales XML handler

    lst = new QTableWidget;
    lst->setColumnCount(3);
    lst->setHorizontalHeaderItem(0,new QTableWidgetItem("Vare nr"));
    lst->setHorizontalHeaderItem(1,new QTableWidgetItem("Vare tekst"));
    lst->setHorizontalHeaderItem(2,new QTableWidgetItem("Pris"));
    lst->setColumnWidth(1,220);

    if(conn->getUA() < SLG_ACCESS)  stype->removeItem(4);

    updateTot();

    mwin::nkontakt->setDate(QDate::currentDate());
    // create the accessable userlevel list
    mwin::usrlvl->addItem("Standard", usr);
    for(int i=1;i<usr;i++)
        mwin::usrlvl->addItem(QString::number(i), i);

    connect(lst,SIGNAL(destroyed()),this,SLOT(reCreateLst()));
    connect(mwin::stype, SIGNAL(currentIndexChanged(const QString &)),this,SLOT(tilbud_type(const QString &)));
    connect(addGross, SIGNAL(clicked()), this, SLOT(gross_dlg()));
    connect(addExchange, SIGNAL(clicked()), this, SLOT(add_byt()));
    connect(deleteLine, SIGNAL(clicked()), this, SLOT(remove_line()));
    connect(sSalgTable, SIGNAL(cellClicked(int,int)),this, SLOT(set_itemS(int,int)));
    connect(sSalgTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(updateTotSale(QTableWidgetItem*)));
    connect(sBytteTable, SIGNAL(cellClicked(int,int)),this, SLOT(set_itemB(int,int)));
    connect(sBytteTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(updateTotExchange(QTableWidgetItem*)));
    connect(mwin::sokay, SIGNAL(clicked()), this, SLOT(send_order()));
    connect(mwin::cls_sale, SIGNAL(clicked()), this, SLOT(clrSale()));
    connect(mwin::smails, SIGNAL(returnPressed()), this, SLOT(get_mails()));
    connect(saveTmp, SIGNAL(clicked()),this,SLOT(save_temp()));
    connect(loadTmp, SIGNAL(clicked()),this,SLOT(get_temps()));
    connect(ftp, SIGNAL(done(bool)), this, SLOT(ftp_done(bool)));
}

/*
 * MWin::insertMail(QTableWidgetItem*)
 * --
 * this adds a mail address to the mail field under sales
 * information from a list of the users frequently used mails.
 */
void
MWin::insertMail(QTableWidgetItem *twi)
{
    emit log("main/salg.cc","MWin::insertMail");
    QString sep = (mwin::smails->text()==QString("")) ? QString("") : QString(";");
    mwin::smails->setText(mwin::smails->text()+sep+twi->text());
}

/*
 * MWin::ParseSale()
 * --
 * this calls the sales XML parser and displays a
 * dialog if either the error or the success tag
 * was parsed.
 */
void
MWin::ParseSale()
{
    emit log("main/salg.cc","MWin::ParseSale");
    QFile *file;
    xml->setContentHandler(shnd);
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
        if(shnd->srvErr())
        {
            QMessageBox *mb = new QMessageBox("Helhed",
            shnd->getValue("error"),QMessageBox::Warning,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            mb->exec();
            delete XFile;
            conn->errorLog();
            delete mb;
            return;
        }
        if(shnd->resSuccess())
        {
            QMessageBox *mb = new QMessageBox("Helhed",
            shnd->getValue("success"),QMessageBox::Information,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            mb->exec();
            delete XFile;
            delete mb;
            clrSale();
            return;
        }
        delete XFile;
    }
}

/*
 * MWin::reCreateLst()
 * --
 * reinitialize the list headers on for the gross dialog
 * after it has been deleted.
 */
void
MWin::reCreateLst()
{
    emit log("main/salg.cc","MWin::reCreateLst");
    disconnect(lst,0,0,0);
    lst = new QTableWidget;
    lst->setColumnCount(3);
    lst->setHorizontalHeaderItem(0,new QTableWidgetItem("Vare nr"));
    lst->setHorizontalHeaderItem(1,new QTableWidgetItem("Vare tekst"));
    lst->setHorizontalHeaderItem(2,new QTableWidgetItem("Pris"));
    lst->setColumnWidth(1,220);
    connect(lst,SIGNAL(destroyed()),this,SLOT(reCreateLst()));
}

/*
 * MWin::remove_line()
 * --
 * this removes the last selected line from either the
 * sales or the exchange tables.
 */
void
MWin::remove_line()
{
    emit log("main/salg.cc","MWin::remove_line");
    if(item != 0) {
        QTableWidget *table = item->tableWidget();
        int row = table->currentRow();
        table->removeRow(row);

        if(table->rowCount() > 0) {
            item = table->item(0,0);
        } else {
            item = 0;
        }
        if(table->objectName().mid(1,1) == QString("S")) {
            if(item != 0) {
                updateTotSale(item);
            } else {
                stsalg->setText("0,00");
                updateTot();
            }
        } else {
            if(item != 0) {
                updateTotExchange(item);
            } else {
                stbyt->setText("0,00");
                updateTot();
            }
        }
    }
}

/*
 * MWin::save_temp()
 * --
 * this creates a XML of the current set-up and
 * transfers it via FTP to the server where it's
 * to be stored for furture use.
 */
void
MWin::save_temp()
{
    emit log("main/salg.cc","MWin::save_temp");
    if(sSalgTable->rowCount() == 0 && sBytteTable->rowCount() == 0) {
      QMessageBox::information(this,"helhed","Du kan ikke gemme en tom!",QMessageBox::Ok);
      return;
    }
    QLocale dk(QLocale::Danish);
    if(!order) {
        order = new QByteArray;
    } else {
        delete order;
        order = new QByteArray;
    }
    QTextStream out(order);
    out << "<?xml version=\"1.0\" ?>" << endl;
    out << "<toka>" << endl;
    out << "<rek_nr>" << rek_nr->text() << "</rek_nr>" << endl;
    out << "<lev_navn>" << levNavn->text() << "</lev_navn>" << endl;
    out << "<lev_att>" << levAtt->text() << "</lev_att>" << endl;
    out << "<lev_adr>" << levAdr->text() << "</lev_adr>" << endl;
    out << "<lev_post>" << levPost->text() << "</lev_post>" << endl;
    out << "<lev_by>" << levBy->text() << "</lev_by>" << endl;
    out << "<levb>" << sLev->text() << "</levb>" << endl;
    out << "<betb>" << sBet->text() << "</betb>" << endl;
    out << "<ndato>" << mwin::nkontakt->date().toString("yyyy-MM-dd") << "</ndato>" << endl;
    out << "<bemark>" << mwin::sBemark->toPlainText() << "</bemark>" << endl;
    if(!internalMsg->toPlainText().isEmpty()) out << "<int_msg>" << mwin::internalMsg->toPlainText() << "</int_msg>" << endl;
    for(int i = 0; i<sSalgTable->rowCount();i++)
    {
        out << "<salg>" << endl;
        out << "<stk>" << dk.toFloat(sSalgTable->item(i,0)->text()) << "</stk>" << endl;
        out << "<nr>" << sSalgTable->item(i,1)->text() << "</nr>" << endl;
        out << "<txt>" << sSalgTable->item(i,2)->text() << "</txt>" << endl;
        out << "<pris>" << dk.toFloat(sSalgTable->item(i,3)->text()) << "</pris>" << endl;
        out << "<rab>" << dk.toFloat(sSalgTable->item(i,4)->text()) << "</rab>" << endl;
        out << "</salg>" << endl;
    }
    for(int i = 0; i<sBytteTable->rowCount();i++)
    {
        out << "<byt>" << endl;
        out << "<stk>" << dk.toFloat(sBytteTable->item(i,0)->text()) << "</stk>" << endl;
        out << "<nr>" << sBytteTable->item(i,1)->text() << "</nr>" << endl;
        out << "<txt>" << sBytteTable->item(i,2)->text() << "</txt>" << endl;
        out << "<pris>" << dk.toFloat(sBytteTable->item(i,3)->text()) << "</pris>" << endl;
        out << "</byt>" << endl;
    }
    out << "</toka>" << endl;
    bool ok;
    while(title == QString("")){
      title = QInputDialog::getText(this,"helhed","Hvad vil du kalde tilbudet/ordren?",QLineEdit::Normal,QString(),&ok);
      if(!ok) break;
    }
    if(!ok) {
        delete order;
        order = 0;
        title = "";
        return;
    }
    ftp->connectToHost(cfg->ftpserver(),cfg->ftpport().toInt());

    ftp->login(cfg->ftpuser(),cfg->ftppass());
    ftp->cd(cfg->ftptmpdir());
    ftp->put(*order,conn->getU()+ "." + title + ".xml",QFtp::Binary);
    ftp->rawCommand("SITE CHMOD 666 " + conn->getU()+ "." + title + ".xml");
    ftp->close();
    tmp = true;
    stat = new Stat("Sender "+stype->currentText()+"...",this);
    stat->place();
    stat->exec();
    delete stat;
    stat = 0;
}

/*
 * MWin::seek_gross()
 * --
 * requests a list of items for sale made from a search string.
 */
void
MWin::seek_gross()
{
    emit log("main/salg.cc","MWin::seek_gross");
    shnd->clearSL();
    conn->Command("seek_gross","vnr="+svnr->text());
    stat = new Stat(lstr("Søger Vare/Sags nr."),this);
    stat->place();
    stat->exec();
    delete stat;
    stat=0;
}

/*
 * MWin::save_temp()
 * --
 * this creates a XML of the current set-up and
 * transfers it via FTP to the server where it's
 * made to the corresponding "TOKA".
 */
void
MWin::send_order()
{
    emit log("main/salg.cc","MWin::send_order");
    speriod *per = 0;
    if(stype->currentText().mid(0,1) == QString("S")) {
        per = new speriod(this);
        per->exec();
    }
    if(sSalgTable->rowCount() == 0 && sBytteTable->rowCount() == 0) return;
    QLocale dk(QLocale::Danish);
    if(!order) {
        order = new QByteArray;
    } else {
        delete order;
        order = new QByteArray;
    }
    QTextStream out(order);
    out << "<?xml version=\"1.0\" ?>" << endl;
    out << "<" << stype->currentText().mid(0,1) << ">" << endl;
    if(stype->currentText().mid(0,1) == QString("T"))
        out << "<luk>" << ((lukke_pro->value()==100) ? 1 : lukke_pro->value()) << "</luk>" << endl;
    if(fromTOKA != QString(""))
        out << "<disable>" << fromTOKA << "</disable>" << endl;
    out << "<kid>" << cus.kid << "</kid>" << endl;
    out << "<rek_nr>" << rek_nr->text() << "</rek_nr>" << endl;
    out << "<lev_navn>" << levNavn->text() << "</lev_navn>" << endl;
    out << "<lev_att>" << levAtt->text() << "</lev_att>" << endl;
    out << "<lev_adr>" << levAdr->text() << "</lev_adr>" << endl;
    out << "<lev_post>" << levPost->text() << "</lev_post>" << endl;
    out << "<lev_by>" << levBy->text() << "</lev_by>" << endl;
    out << "<email>";
    if(mwin::email->text() != QString("") && stype->currentIndex() != 3) { out << mwin::email->text(); if(smails->text() != QString("")) { out << ";"; } }
    out << smails->text() << "</email>" << endl;
    out << "<klar>" << ( (mwin::klar->isChecked()) ? "true" : "false" ) << "</klar>" << endl;
    out << "<levomk>" << ((mwin::fragt->checkState() == Qt::Checked) ? "true":"false") << "</levomk>" << endl;
    out << "<niv>" << usrlvl->itemData(usrlvl->currentIndex()).toInt() << "</niv>" << endl;
    out << "<lev_beta>" << sLev->text() << ";" << sBet->text() << "</lev_beta>" << endl;
    if(per) {
        out << "<period>" << per->Start->date().toString("yyyy-MM-dd") << ";";
        out << per->End->date().toString("yyyy-MM-dd") << "</period>" << endl;
    }
    out << "<ndato>" << mwin::nkontakt->date().toString("yyyy-MM-dd") << "</ndato>" << endl;
    out << "<bemark>" << mwin::sBemark->toPlainText() << "</bemark>" << endl;
    if(!internalMsg->toPlainText().isEmpty()) out << "<int_msg>" << mwin::internalMsg->toPlainText() << "</int_msg>" << endl;
    for(int i = 0; i<sSalgTable->rowCount();i++)
    {
        out << "<salg>" << endl;
        out << "<stk>" << dk.toFloat(sSalgTable->item(i,0)->text()) << "</stk>" << endl;
        out << "<nr>" << sSalgTable->item(i,1)->text() << "</nr>" << endl;
        out << "<txt>" << sSalgTable->item(i,2)->text() << "</txt>" << endl;
        out << "<pris>" << dk.toFloat(sSalgTable->item(i,3)->text()) << "</pris>" << endl;
        out << "<rabat>" << dk.toFloat(sSalgTable->item(i,4)->text()) << "</rabat>" << endl;
        out << "</salg>" << endl;
    }
    for(int i = 0; i<sBytteTable->rowCount();i++)
    {
        out << "<byt>" << endl;
        out << "<stk>" << dk.toFloat(sBytteTable->item(i,0)->text()) << "</stk>" << endl;
        out << "<nr>" << sBytteTable->item(i,1)->text() << "</nr>" << endl;
        out << "<txt>" << sBytteTable->item(i,2)->text() << "</txt>" << endl;
        out << "<pris>" << dk.toFloat(sBytteTable->item(i,3)->text()) << "</pris>" << endl;
        out << "</byt>" << endl;
    }
    out << "</" << stype->currentText().mid(0,1) << ">" << endl;
    ftp->connectToHost(cfg->ftpserver(),cfg->ftpport().toInt());

    ftp->login(cfg->ftpuser(),cfg->ftppass());
    ftp->cd(cfg->ftpdir());
    ftp->put(*order,cus.knr + ".xml",QFtp::Binary);
    ftp->rawCommand("SITE CHMOD 666 " + cus.knr + ".xml");
    ftp->close();
    stat = new Stat("Sender "+stype->currentText()+"...",this);
    stat->place();
    stat->exec();
    delete stat;
    stat = 0;
    clrSale();
}

/*
 * MWin::set_itemB(int,int)
 * --
 * sets the current item to be the selected
 * cell in the exchange table
 */
void
MWin::set_itemB(int r,int c)
{
    emit log("main/salg.cc","MWin::set_itemB");
    item = sBytteTable->item(r,c);
}

/*
 * MWin::set_itemS(int,int)
 * --
 * sets the current item to be the selected
 * cell in the sales table
 */
void
MWin::set_itemS(int r,int c)
{
    emit log("main/salg.cc","MWin::set_itemS");
    item = sSalgTable->item(r,c);
}

/*
 * MWin::setCurrentType(int)
 * --
 * sets the current sales TOKA type
 */
void
MWin::setCurrentType(int i)
{
    mwin::stype->setCurrentIndex(i);
}

/*
 * MWin::setSDataFromItem(QTableWidgetItem*)
 * --
 * gets the sales data for an item for sale and
 * make it available as 'gross'.
 */
void
MWin::setSDataFromItem(QTableWidgetItem *)
{
    emit log("main/salg.cc","MWin::setSDataFromItem");
    SDataListItem *li = dynamic_cast<SDataListItem*>(lst->item(lst->currentRow(),0));
    gross = li->data();
    add->setEnabled(true);
}

/*
 * MWin::setSDataFromItem_get(QTableWidgetItem*)
 * --
 * gets the sales data for an item for sale, makes
 * it available as 'gross', and add it to the sales
 * table.
 */
void
MWin::setSDataFromItem_get(QTableWidgetItem *)
{
    emit log("main/salg.cc","MWin::setSDataFromItem_get");
    SDataListItem *li = dynamic_cast<SDataListItem*>(lst->item(lst->currentRow(),0));
    gross = li->data();
    add->setEnabled(true);
    add_sale();
}

/*
 * MWin::showGlist(QVector<SData*>&)
 * --
 * takes the recived data requested by MWin::seek_gross()
 * and fills it into the grossery list table.
 */
void
MWin::showGlist(QVector<SData*> &sl)
{
    emit log("main/salg.cc","MWin::showGlist");
    SDataListItem *sdlst;
    QTableWidgetItem *twi;
    while(lst->rowCount()>0)
    {
        lst->removeRow(0);
    }

    for(int i=0;i<sl.size();i++)
    {
        lst->insertRow(0);
        sdlst = new SDataListItem(sl[i]->vnr); sdlst->setData(*sl[i]);
        lst->setItem(0,0,sdlst);
        twi = new QTableWidgetItem(sl[i]->vtxt);
        lst->setItem(0,1,twi);
        twi = new QTableWidgetItem(sl[i]->stk_p);
        twi->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lst->setItem(0,2,twi);
    }
    for(int i=0;i<sl.size();i++)
    {
        lst->setRowHeight(i,20);
    }
}

/*
 * MWin::showMailList(QVector<QString*>&)
 * --
 * takes the recived data requested by MWin::get_mails()
 * and fills it into the grossery list table which then
 * is modified to hold mail addresses. And create and
 * display the mail list dialog.
 */
void
MWin::showMailList(QVector<QString> &ml, bool salg)
{
    emit log("main/salg.cc","MWin::showMailList");
    if(swin != 0) { delete swin; swin = 0; }
    lst->clear();
    for(int i=0;i<3;i++) {
        lst->setColumnWidth(i,120);
        lst->setHorizontalHeaderItem(i,new QTableWidgetItem(""));
    }
    for(int i=0;i<ml.size();i++){
        if(i%3 == 0) { lst->insertRow(i/3); lst->setRowHeight(i/3,22); }
        lst->setItem(i/3,i%3,new QTableWidgetItem(ml.at(i)));
    }

    if(salg) {
        swin = new MailList(lst,mwin::smails,this);
    } else {
        swin = new MailList(lst,0,this);
        jhnd->clearML();
    }
/*    QVBoxLayout *vlay = new QVBoxLayout(swin);
    QHBoxLayout *hbox = new QHBoxLayout;
    add = new QPushButton("Luk");
    hbox->addWidget(add);
    hbox->addStretch();
    vlay->addLayout(hbox);
    vlay->addWidget(lst);
    connect(lst, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(insertMail(QTableWidgetItem*)));
    connect(add, SIGNAL(clicked()), swin, SLOT(accept()));
*/
    swin->show();
    QRect rc = swin->rect();
    swin->hide();
    rc.setWidth(450);
    swin->resize(QSize(rc.width(),rc.height()));
    int r = swin->exec();

    if(r == QDialog::Accepted) {
        JData *jd = new JData;
        jd->nid = jhnd->nid;
        jd->sid = QString("");
        for(int i=0;i<jlist.size();i++)
        {
            if(*jd == *(jlist[i])){
                delete jd;
                jd = jlist[i];
                break;
            }
        }
        QString mails = qobject_cast<MailList*>(swin)->res();
        conn->Command("extra_mails","k_mail="+mails+"&tnr="+jd->nr);

    }
    delete swin;
    swin = 0;
}

/*
 * MWin::showTempList(QVector<SData*>&)
 * --
 * modifies the gross list to hold the names of the
 * recived data requested by MWin::get_temps()
 * and then fills it into the costomized grossery list
 * table and displays the saved set-ups dialog.
 */
void
MWin::showTempList(QVector<SData*> &sl)
{
    emit log("main/salg.cc","MWin::showTempList");
    SDataListItem *sdlst;
    if(swin != 0) { delete swin; swin = 0; }
    lst->clear();
    lst->setColumnCount(1);
    lst->setColumnWidth(0,320);
    lst->setHorizontalHeaderItem(0,new QTableWidgetItem("Dobbelt klik for at hente"));

    swin = new QDialog(this);
    QVBoxLayout *vlay = new QVBoxLayout(swin);
    QHBoxLayout *hbox = new QHBoxLayout;
    add = new QPushButton("Luk");
    hbox->addWidget(add);
    hbox->addStretch();
    vlay->addLayout(hbox);
    vlay->addWidget(lst);

    for(int i=0;i<sl.size();i++)
    {
        lst->insertRow(i);
        sdlst = new SDataListItem(sl[i]->vtxt); sdlst->setData(*sl[i]);
        lst->setItem(i,0,sdlst);
        lst->setRowHeight(i,20);
    }
    connect(lst, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(fetchTemp(QTableWidgetItem*)));
    connect(add, SIGNAL(clicked()), swin, SLOT(accept()));
    swin->resize(QSize(370, 370));
    swin->exec();
    delete swin;
    swin = 0;
}

/*
 * MWin::tilbud_type(const QString&)
 * --
 * this is used change the look of sales info depending
 * on what type is currently selected.
 */
void
MWin::tilbud_type(const QString &str)
{
    emit log("main/salg.cc","MWin::tilbud_type");
    if(QString("Tilbud") == str) {
        usrlvl->setCurrentIndex(0);
        mwin::lukke_pro->setEnabled(true);
        mwin::lukke_lab->setEnabled(true);
    } else {
        mwin::lukke_pro->setEnabled(false);
        mwin::lukke_lab->setEnabled(false);
    }
    if(QString("Ordre") == str || QString("Konsignation") == str) {
        if(usrlvl->count() > 8) {
            usrlvl->setCurrentIndex(8);
        }
    }
    if(QString("Arbejdskort") == str) {
        usrlvl->setCurrentIndex(6);
        mwin::label_39->setVisible(false);
        mwin::internalMsg->setVisible(false);
    } else {
        mwin::label_39->setVisible(true);
        mwin::internalMsg->setVisible(true);
    }
    if(QString("Salgsmål") == str) {
        usrlvl->setCurrentIndex(0);
        mwin::label_39->setText("Vores forventninger & tiltag");
        mwin::label_40->setText("Salgsmåls type ");
        mwin::label_48->setText("Kundens forventninger & tiltag");
        mwin::fragt->setEnabled(false);
        mwin::klar->setEnabled(false);
    } else {
        mwin::label_39->setText("Vedr. Arbejdskort");
        mwin::label_40->setText("Rekvisitions nr ");
        mwin::label_48->setText("Bemærning");
        mwin::fragt->setEnabled(true);
        mwin::klar->setEnabled(true);
    }
}

/*
 * MWin::updateTot()
 * --
 * this updates the grand total on the sales page.
 * this includes the pris ex. tax, tax, and pris with tax.
 */
void
MWin::updateTot()
{
    emit log("main/salg.cc","MWin::updateTot");
    QLocale dk(QLocale::Danish);
    bool ok = true;
    float ts = dk.toFloat(mwin::stsalg->text(),&ok);
    if(!ok) {
        ts = 0.0f;
        mwin::stsalg->setText(dk.toString(ts,'f',2));
    }
    float te = dk.toFloat(mwin::stbyt->text(),&ok);
    if(!ok) {
        te = 0.0f;
        mwin::stbyt->setText(dk.toString(te,'f',2));
    }
    float net = ts - te;
    mwin::netto->setText(dk.toString(net,'f',2));
    float vat = net * 0.25f;
    mwin::moms->setText(dk.toString(vat,'f',2));
    float tot = net + vat;
    mwin::totalt->setText(dk.toString(tot,'f',2));
}

/*
 * MWin::updateTotExchange(QTableWidgetItem* item)
 * --
 * this updates the total of the exchange table on the sales page.
 */
void
MWin::updateTotExchange(QTableWidgetItem* item)
{
  emit log("main/salg.cc","MWin::updateTotExchange");
  QLocale dk(QLocale::Danish);
  if(!adding) {
    adding = true;
    int c = item->tableWidget()->column(item);
    int ec = 4;
    switch(c) {
      case 4:
        ec = 3;
        break;
      case 1:
      case 2:
        adding = false;
        return;
        break;
      default:
        break;
    }
    int r = item->tableWidget()->row(item);
    bool ok;
    float stk, spris, tpris;
    if(ec == 4) {
        stk = dk.toFloat(sBytteTable->item(r,0)->text(),&ok);
        if(!ok) { stk = 1.0f; sBytteTable->item(r,0)->setText("1"); }
        spris = dk.toFloat(sBytteTable->item(r,3)->text(),&ok);
        if(!ok) { spris = 0.0f; sBytteTable->item(r,3)->setText("0,00"); }
        tpris = stk * spris;
        sBytteTable->item(r,4)->setText(dk.toString(tpris,'f',2));
    } else {
        stk = dk.toFloat(sBytteTable->item(r,0)->text(),&ok);
        if(!ok) { stk = 1.0f; sBytteTable->item(r,0)->setText("1"); }
        tpris = dk.toFloat(sBytteTable->item(r,4)->text(),&ok);
        if(!ok) { tpris = 0.0f; sBytteTable->item(r,4)->setText("0,00"); }
        spris = tpris / stk;
        sBytteTable->item(r,3)->setText(dk.toString(spris,'f',2));
    }
    float tmp = dk.toFloat(item->text());
    item->setText(dk.toString(tmp,'f',2));
    adding = false;
  }
  int maxrow = sBytteTable->rowCount();
  float sum = 0.0f;
  for(int i = 0;i<maxrow;i++)
  {
      QTableWidgetItem *t = sBytteTable->item(i,4);
      if(t) sum += dk.toFloat(t->text());
  }

  mwin::stbyt->setText(dk.toString(sum,'f',2));
  updateTot();
}

/** MWin::updateTotSale(QTableWidgetItem* item)
 * --
 * this updates the total of the sales table on the sales page.
 */
void
MWin::updateTotSale(QTableWidgetItem *item)
{
  emit log("main/salg.cc","MWin::updateTotSale");
  QLocale dk(QLocale::Danish);
  if(!adding) {
    adding = true;
    int c = item->tableWidget()->column(item);
    int ec = 5;
    switch(c) {
      case 5:
        ec = 3;
        break;
      case 1:
      case 2:
        adding = false;
        return;
        break;
      default:
        break;
    }
    int r = item->tableWidget()->row(item);
    bool ok;
    float stk, spris, rab, tpris;
    if(ec == 5) {
        stk = dk.toFloat(sSalgTable->item(r,0)->text(),&ok);
        if(!ok) { stk = 1.0f; sSalgTable->item(r,0)->setText("1"); }
        spris = dk.toFloat(sSalgTable->item(r,3)->text(),&ok);
        if(!ok) { spris = 0.0f; sSalgTable->item(r,3)->setText("0,00"); }
        rab = (100 - dk.toFloat(sSalgTable->item(r,4)->text(),&ok)) / 100;
        if(!ok) { rab = 1.0f; sSalgTable->item(r,4)->setText("0,00"); }
        tpris = stk * spris * rab;
        sSalgTable->item(r,5)->setText(dk.toString(tpris,'f',2));
    } else {
        stk = dk.toFloat(sSalgTable->item(r,0)->text(),&ok);
        if(!ok) { stk = 1.0f; sSalgTable->item(r,0)->setText("1"); }
        tpris = dk.toFloat(sSalgTable->item(r,5)->text(),&ok);
        if(!ok) { spris = 0.0f; sSalgTable->item(r,5)->setText("0,00"); }
        rab = (100 - dk.toFloat(sSalgTable->item(r,4)->text(),&ok)) / 100;
        if(!ok || rab == 0.0f) { rab = 1.0f; sSalgTable->item(r,4)->setText("0,00"); }
        spris = (tpris / rab)/stk;
        sSalgTable->item(r,3)->setText(dk.toString(spris,'f',2));
    }
    float tmp = dk.toFloat(item->text());
    item->setText(dk.toString(tmp,'f',2));
    adding = false;
  }
  int maxrow = sSalgTable->rowCount();
  float sum = 0.0f;
  for(int i = 0;i<maxrow;i++)
  {
      QTableWidgetItem *t = sSalgTable->item(i,5);
      if(t) sum += dk.toFloat(t->text());
  }
  mwin::stsalg->setText(dk.toString(sum,'f',2));
  updateTot();
}
