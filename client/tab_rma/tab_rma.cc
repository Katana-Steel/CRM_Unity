#include <QtGui>
#include "tab_rma.h"
#include "conn.h"
#include <stat.h>
#include "k-j_data.h"
#include "tab_rma_xml.h"
#include "tab_rma_replace_dlg.h"

/*
    a test of source structure regarding plugins.
    instead of having the export macro at the end
    of the file then put it at the top to visualize
    it better, and to ensure it isn't forgotten.
*/
Q_EXPORT_PLUGIN2(tab_rma,TabRMA)

TabRMA::TabRMA()
    : mod("tab_rma/")
{
    cus = 0;
    curNode = 0;
    fetch = false;
    status = 0;
    xml = new QXmlSimpleReader;
    hnd = new XmlHnd;
    xml->setContentHandler(hnd);
}

TabRMA::~TabRMA()
{
    if(hnd) delete hnd;
    if(xml) delete xml;
}

QString
TabRMA::name()
{
    return QString("RMA Sager");
}

int
TabRMA::minUserAccess()
{
    return 4;
}

void
TabRMA::LoadInterface()
{
    setupUi(this);
    hnd->setTreeWidget(treeWidget);
    treeWidget->setEnabled(false);
    int w=0;
    QDesktopWidget *root = QApplication::desktop();
    QRect rc = root->availableGeometry(dynamic_cast<const QWidget*>(this->parent()));
    w = (int)((double)rc.width() * ( 4.0 / 13.0 )); // 4/13 of the available screen width or little less than 1 third of the width.
    if(w == 0) w = 350;
    treeWidget->setMaximumWidth(w);
    groupBox->setMaximumWidth(w);
    treeWidget->setMinimumWidth(w);
    groupBox->setMinimumWidth(w);

    w = (int)((double)rc.width() * 0.5);
    groupBox_2->setMaximumWidth(w);
    groupBox_3->setMaximumWidth(w);
    groupBox_2->setMinimumWidth(w);
    groupBox_3->setMinimumWidth(w); // now using 21/26 or ~80.8% of the available screen width.
    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(rma_select(QTreeWidgetItem*,int)));
    connect(addResponce, SIGNAL(clicked()), this, SLOT(newRMANode()));
    connect(dataMsg, SIGNAL(textChanged()), this, SLOT(updRMANode()));
    connect(sendRMA, SIGNAL(clicked()), this, SLOT(txRMANode()));
}

void
TabRMA::setConn(Conn *_c)
{
    c = _c;
}

void
TabRMA::setKData(KData *_kd)
{
    if(_kd) {
        if(!cus || _kd->knr != cus->knr) {
            cus = new KData(*_kd);
            fetch = true;
        }
    } else {
        cus = 0;
        curNode = 0;
        addResponce->setEnabled(false);
        treeWidget->clear();
    }
}

void
TabRMA::ParseXML()
{
    if(status) status->accept();

    QFile *file;
    if(c->Data()->isOpen())
    {
        file = c->Data();
        file->reset();
        file->close();
        QXmlInputSource *XFile = new QXmlInputSource(file);
        if(!xml->parse(*XFile))
        {
            XFile->setData(c->Data(1));
            if(!xml->parse(XFile)) {
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
        delete XFile;
    }
}

void
TabRMA::Shown()
{
    if(!curNode) {
        disconnect(dataMsg, NULL, NULL, NULL);
        stkLabel->setText("Stk.        : ");
        vnrLabel->setText("Vare nr.    : ");
        vtxtLabel->setText("Vare tekst  : ");
        prisLabel->setText("Orginal pris: ");
        estkLabel->setText("Erstat. Stk.        : ");
        evnrLabel->setText("Erstat. Vare nr.    : ");
        evtxtLabel->setText("Erstat. Vare tekst  : ");
        eprisLabel->setText("Erstat. pris        : ");
        onrLabel->setText("Ang Ordre nr: ");
        eMailLabel->setText("E-Post adresse: ");
        dateLabel->setText("Start dato: ");
        ddateLabel->setText("Dato: ");
        dataMsg->setPlainText("");
        connect(dataMsg, SIGNAL(textChanged()), this, SLOT(updRMANode()));
    }
    if(cus) {
        groupBox->setTitle(cus->knr);
        label->setText(cus->navn);
        label_2->setText(cus->att);
        label_3->setText(cus->adr);
        label_4->setText(cus->post + " " + cus->by);
        label_5->setText(cus->land);
        treeWidget->setEnabled(true);
        checkBox->setEnabled(true);
        checkBox_2->setEnabled(true);
        checkBox_3->setEnabled(true);
        if(fetch) {
            c->Command("rma","f=get%20all&knr=" + cus->knr);
            status = new Stat("Henter RMA sager",this);
            status->exec();
            delete status;
            status = 0;
        }

    } else {
        groupBox->setTitle("Ingen Kunde Fundet");
        label->setText("navn:");
        label_2->setText("adresse1:");
        label_3->setText("adresse2:");
        label_4->setText("post & by:");
        label_5->setText("land:");
        treeWidget->setEnabled(false);
        checkBox->setEnabled(false);
        checkBox_2->setEnabled(false);
        checkBox_3->setEnabled(false);
    }
    fetch = false;
}

void
TabRMA::rma_select(QTreeWidgetItem *twi, int /*col*/)
{
    checkBox_3->setCheckState(Qt::Unchecked);
    addResponce->setEnabled(true);
    if(twi->parent()) {
        checkBox->setCheckState(Qt::Checked);
        if(curNode != twi->parent()) {
            curNode = twi->parent();
            displayCurNode();
        }
    } else {
        checkBox->setChecked(Qt::Unchecked);
        if(twi != curNode) {
            curNode = twi;
            displayCurNode();
        }
    }

    dataMsg->setEnabled(true);
    sendRMA->setEnabled(true);
    if(twi->childCount() > 0) {
        checkBox_2->setCheckState(Qt::Checked);
        ddateLabel->setText("Dato: "+twi->child(0)->text(9));
        dataMsg->setPlainText(twi->child(0)->text(10));
    } else {
        checkBox_2->setCheckState(Qt::Unchecked);
        ddateLabel->setText("Dato: "+twi->text(9));
        dataMsg->setPlainText(twi->text(10));
    }
    if(twi->text(11).isEmpty()) {
        dataMsg->setEnabled(false);
        sendRMA->setEnabled(false);
    }
}

void
TabRMA::displayCurNode()
{
    checkBox_3->setCheckState(Qt::Checked);
    onrLabel->setText("Ang Ordre nr: " + curNode->text(2));
    eMailLabel->setText("E-Post adresse: " + curNode->text(3));
    dateLabel->setText("Start dato: " + curNode->text(4));
    QTreeWidgetItem *child = curNode->child(0);
    stkLabel->setText("Stk.        : " + child->text(1));
    vnrLabel->setText("Vare nr.    : " + child->text(2));
    vtxtLabel->setText("Vare tekst  : " + child->text(3));
    prisLabel->setText("Orginal pris: " + child->text(4));
    estkLabel->setText("Erstat. Stk.        : " + child->text(5));
    evnrLabel->setText("Erstat. Vare nr.    : " + child->text(6));
    evtxtLabel->setText("Erstat. Vare tekst  : " + child->text(7));
    eprisLabel->setText("Erstat. pris        : " + child->text(8));

}

void
TabRMA::newRMANode()
{
    QTreeWidgetItem *child = new QTreeWidgetItem(curNode);
    child->setText(0,"Ny");
    child->setText(11,"1");
}

void
TabRMA::updRMANode()
{
    QTreeWidgetItem *child = treeWidget->currentItem();
    child->setText(10,dataMsg->toPlainText());
}

void
TabRMA::txRMANode()
{
    QTreeWidgetItem *child = treeWidget->currentItem();
    ReplaceDlg *win = new ReplaceDlg(this);
    int i = win->exec();
    c->Command("rma", "f=Append&rma_nr="+curNode->text(0)+"&txt="+child->text(10));
    if(i == QDialog::Accepted) {
        c->Command("rma", "f=Add&estk="+ win->stk->text() +
                               "&evnr="+ win->vnr->text() +
                               "&evtxt="+win->vtxt->text()+
                               "&epris="+win->pris->text());
    }
            status = new Stat("Behandler....",this);
            status->exec();
            delete status;
            status = 0;
/*    c->Data()->reset();
    c->Data()->close(); */
    c->Command("rma","f=get%20all&knr=" + cus->knr);
            status = new Stat("Henter RMA sager",this);
            status->exec();
            delete status;
            status = 0;
}
