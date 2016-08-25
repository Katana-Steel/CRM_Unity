#include <QtGui>
#include <QtXml>
#include "tab_admin.h"
#include "tab_admin_xml.h"
#include "conn.h"
#include "stat.h"

//! the constructor.
/*!
*/
tabAdmin::tabAdmin()
    : errorLog(false),mod("tab_admin/")
{
    c = 0;
    status = 0;
    radioG = new QButtonGroup(this);
    hnd = new XmlHnd;
    xml = new QXmlSimpleReader;
    xml->setContentHandler(hnd);
    emit Log(mod+"tab_admin.cc","(C)tabAdmin: Admin plugin ready");
}

//! the destructor.
/*!
*/
tabAdmin::~tabAdmin()
{
    emit Log(mod+"tab_admin.cc","(D)tabAdmin: Admin plugin is being destroyed");
    if(status) delete status;
    delete radioG;
    delete hnd;
    delete xml;
}

//! creates a request string based upon the UserData
QString
tabAdmin::makeReqFromUD(UserData *ud)
{
    QString ret = "user=" + ud->userName;
    if(ud->passWord != QString(""))
        ret += "&pass=" + ud->passWord;
    ret += "&email=" + ud->email;
    ret += "&fname=" + ud->fname;
    ret += "&lname=" + ud->lname;
    ret += "&mobil=" + ud->mobil;
    ret += "&tlf=" + ud->tlf;
    ret += "&usrnr=" + ud->usrNr;
    ret += "&tokanr=" + ud->tokaNr;
    return ret;
}

// commented in include/tab_interf.h
QString
tabAdmin::name()
{
    return QString("Admin");
}

// commented in include/tab_interf.h
int
tabAdmin::minUserAccess()
{
    return 10;
}

// commented in include/tab_interf.h
/*! @copydoc TabInterface::LoadInterface()

    Sets up the radio group to switch between the
    the different user functions.

    Makes the header for the mail rules table.
*/
void
tabAdmin::LoadInterface()
{
    emit Log(mod+"tab_admin.cc","LoadInterface: initiating the GUI");
    setupUi(this);
    radioG->addButton(editUser,0);
    radioG->addButton(createUser,1);
    radioG->addButton(deleteUser,2);
    mailRules->setColumnCount(5);
    mailRules->setHorizontalHeaderItem(0,new QTableWidgetItem("Aktiv"));
    mailRules->setHorizontalHeaderItem(1,new QTableWidgetItem("Type"));
    mailRules->setHorizontalHeaderItem(2,new QTableWidgetItem("Betingelse"));
    mailRules->setHorizontalHeaderItem(3,new QTableWidgetItem("Test"));
    mailRules->setHorizontalHeaderItem(4,new QTableWidgetItem("Mail liste"));
    connect(radioG,SIGNAL(buttonClicked(int)),this,SLOT(radioChanged(int)));
    connect(userName,SIGNAL(currentIndexChanged(int)),this,SLOT(availableUsers(int)));
    connect(userName,SIGNAL(currentIndexChanged(int)),this,SLOT(showUserData(int)));
    connect(sendF,SIGNAL(clicked()),this,SLOT(sendQuery()));
    connect(refresh,SIGNAL(clicked()),this,SLOT(resetUD()));
    connect(uEmails,SIGNAL(clicked()),this,SLOT(sendUpdMail()));
    radioChanged(0);
    connect(addLine, SIGNAL(clicked()), this, SLOT(addMailRule()));
    connect(rmLine, SIGNAL(clicked()), this, SLOT(rmMailRule()));
    connect(updateRules, SIGNAL(clicked()), this, SLOT(updateRule()));
    connect(usrAL, SIGNAL(currentIndexChanged(int)), tokaAL, SLOT(setCurrentIndex(int)));
    emit Log(mod+"tab_admin.cc","LoadInterface: GUI builded");
}

// commented in include/tab_interf.h
void
tabAdmin::setConn(Conn *_c)
{
    c = _c;
}

// commented in include/tab_interf.h
void
tabAdmin::ParseXML()
{
    if(status) status->accept();

    emit Log(mod+"tab_admin.cc","ParseXML: Processing request result");
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
            if(!xml->parse(*XFile))
            {
                if(errorLog) c->errorLog();
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
        if(hnd->hasUserInfo()) {
            emit Log(mod+"tab_admin.cc","ParseXML: Putting UserData in the combo box");
            hnd->loadUserInfo(admin::userName);
        } else if(hnd->hasMailRules()) {
            emit Log(mod+"tab_admin.cc","ParseXML: Filling the 'mailRules' table.");
            hnd->loadMailRules(admin::mailRules);
        } else Shown();
        delete XFile;
    }
}

// commented in include/tab_interf.h
void
tabAdmin::Shown()
{
    emit Log(mod+"tab_admin.cc","Shown: Displays admin plugin.");
    radioG->button(0)->animateClick();
    errorLog = true;
    c->addQueryItem("type","user");
    c->addQueryItem("f","get");
    c->Command("admin");
    status = new Stat("Henter Bruger...");
    status->place();
    status->exec();
    delete status;
    status = 0;

    errorLog = false;
    c->addQueryItem("type","mailrule");
    c->addQueryItem("f","get");
    c->Command("admin");
    status = new Stat("Henter Mail Regler...");
    status->place();
    status->exec();
    delete status;
    status = 0;
}

//! Sends a mail to all users.
/*!
    Sends a mail telling the users that there is
    a new update ready and optionally including
    a description of the update.
*/
void
tabAdmin::sendUpdMail()
{
    emit Log(mod+"tab_admin.cc","sendUpdMail: Sending a mail to all users.");

    c->Command("admin","type=update&msg="+updMsg->toPlainText());
    status = new Stat("Sender mails til brugerne...");
    status->place();
    status->exec();
    delete status;
    status = 0;
}

//! Handles the change user admin function.
void
tabAdmin::radioChanged(int idx)
{
    emit Log(mod+"tab_admin.cc","radioChanged: Updating dialog.");
    switch(idx) {
    case 0:
        labPass->setText("Ny Adgangskode:");
        password->clear();
        email->clear();
        fname->clear();
        lname->clear();
        phone->clear();
        cell->clear();
        newUserName->setVisible(false);
        label_3->setVisible(false);
        takeOver->setVisible(false);
        userName->setVisible(true);
        labPass->setVisible(true);
        password->setVisible(true);
        label_7->setVisible(true);
        usrAL->setVisible(true);
        label_8->setVisible(true);
        email->setVisible(true);
        label_5->setVisible(true);
        fname->setVisible(true);
        label_6->setVisible(true);
        lname->setVisible(true);
        label_9->setVisible(true);
        phone->setVisible(true);
        label_4->setVisible(true);
        cell->setVisible(true);
        showUserData(userName->currentIndex());
        break;
    case 1:
        labPass->setText("Adgangskode:");
        password->clear();
        email->clear();
        fname->clear();
        lname->clear();
        phone->clear();
        cell->clear();
        userName->setVisible(false);
        label_3->setVisible(false);
        takeOver->setVisible(false);
        newUserName->setVisible(true);
        labPass->setVisible(true);
        password->setVisible(true);
        label_7->setVisible(true);
        usrAL->setVisible(true);
        label_8->setVisible(true);
        email->setVisible(true);
        label_5->setVisible(true);
        fname->setVisible(true);
        label_6->setVisible(true);
        lname->setVisible(true);
        label_9->setVisible(true);
        phone->setVisible(true);
        label_4->setVisible(true);
        cell->setVisible(true);
        break;
    case 2:
        newUserName->setVisible(false);
        labPass->setVisible(false);
        password->setVisible(false);
        label_7->setVisible(false);
        usrAL->setVisible(false);
        label_8->setVisible(false);
        email->setVisible(false);
        label_5->setVisible(false);
        fname->setVisible(false);
        label_6->setVisible(false);
        lname->setVisible(false);
        label_9->setVisible(false);
        phone->setVisible(false);
        label_4->setVisible(false);
        cell->setVisible(false);
        userName->setVisible(true);
        label_3->setVisible(true);
        takeOver->setVisible(true);
        availableUsers(userName->currentIndex());
        break;
    }
}

//! Make the take over list.
/*!
    To include all the user that is in the user list
    except the one currently selected. And only if the
    delete user function is active.
*/
void
tabAdmin::availableUsers(int idx)
{
    emit Log(mod+"tab_admin.cc","availableUsers: ");
    if(!deleteUser->isChecked()) return;
    takeOver->clear();
    for(int i=0;i< userName->count();i++)
    {
        if(i==idx) continue;
        takeOver->addItem(userName->itemText(i),userName->itemData(i));
    }
}

//! Display the UserData.
/*!
    This fetches the data of the just selected user and fills
    the information in there respective fields.
*/
void
tabAdmin::showUserData(int idx)
{
    if(idx < 0) return;
    emit Log(mod+"tab_admin.cc","showUserData: Displaying User Data");
    UserData *dat;
    dat = (UserData *)userName->itemData(idx).toInt();
    tokaAL->setCurrentIndex(dat->tokaNr.toInt()-1);
    usrAL->setCurrentIndex(dat->usrNr.toInt()-1);
    fname->setText(dat->fname);
    lname->setText(dat->lname);
    email->setText(dat->email);
    phone->setText(dat->tlf);
    cell->setText(dat->mobil);
    password->clear();
}

//! Creates, updates, or deletes the user.
/*!
    This sends the query to either create, delete, or
    update a user depending which option is selected.
*/
void
tabAdmin::sendQuery()
{
    UserData *dat;
    QString req;
    switch(radioG->checkedId())
    {
    case 0:
        emit Log(mod+"tab_admin.cc","sendQuery: Updating User Information");
        dat = (UserData *)userName->itemData(userName->currentIndex()).toInt();
        if(password->text() != QString("")) dat->passWord = password->text();
        if(fname->text() != QString("")) dat->fname = fname->text();
        if(lname->text() != QString("")) dat->lname = lname->text();
        if(email->text() != QString("")) dat->email = email->text();
        if(phone->text() != QString("")) dat->tlf = phone->text();
        if(cell->text() != QString("")) dat->mobil = cell->text();
        dat->usrNr = usrAL->currentText();
        dat->tokaNr = tokaAL->currentText();
        req = makeReqFromUD(dat);
        req += "&f=edit&type=user";
        c->Command("admin",req);
        status = new Stat("Retter Bruger...");
        status->place();
        status->exec();
        delete status;
        status = 0;
        break;
    case 1:
        emit Log(mod+"tab_admin.cc","sendQuery: Creating a new user");
        dat = new UserData;
        if(newUserName->text() != QString("")) dat->userName = newUserName->text();
        else {
            QMessageBox *mb = new QMessageBox("Helhed",
            "Man kan ikke oprette\nen bruger uden navn",QMessageBox::Warning,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            mb->exec();
            delete mb;
            delete dat;
            return;
        }
        if(password->text() != QString("")) dat->passWord = password->text();
        else {
            QMessageBox *mb = new QMessageBox("Helhed",
            "Man kan ikke oprette\nen bruger uden adgangskode",QMessageBox::Warning,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            mb->exec();
            delete mb;
            delete dat;
            return;
        }
        if(fname->text() != QString("")) dat->fname = fname->text();
        if(lname->text() != QString("")) dat->lname = lname->text();
        if(email->text() != QString("")) dat->email = email->text();
        else {
            QMessageBox *mb = new QMessageBox("Helhed",
            "Man kan ikke oprette\nen bruger uden email adresse",QMessageBox::Warning,
            QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
            mb->exec();
            delete mb;
            delete dat;
            return;
        }
        if(phone->text() != QString("")) dat->tlf = phone->text();
        if(cell->text() != QString("")) dat->mobil = cell->text();
        dat->usrNr = usrAL->currentText();
        dat->tokaNr = tokaAL->currentText();
        req = makeReqFromUD(dat);
        req += "&f=create&type=user";
        delete dat;
        c->Command("admin",req);
        status = new Stat("Opretter Bruger...");
        status->place();
        status->exec();
        delete status;
        status = 0;
        break;
    case 2:
        emit Log(mod+"tab_admin.cc","sendQuery: Deleting user");
        req  = "user=" + userName->currentText();
        req += "&replace=" + takeOver->currentText();
        req += "&f=delete&type=user";
        c->Command("admin",req);
        status = new Stat("Sletter Bruger...");
        status->place();
        status->exec();
        delete status;
        status = 0;
        break;
    }
    password->clear();
}

//! Adds a line to the mailRules table.
/*!
    Takes the options as set and add a line with
    a check box in the first field. The second and
    third field as read-only with the infomation
    from the two option combo boxes. This is to
    ensure the Type of the rule and the Condition
    is spelled right when applied to the database.
*/
void
tabAdmin::addMailRule()
{
    emit Log(mod+"tab_admin.cc","addMailRule: addind a new MailRule to the table.");
    QTableWidgetItem *twi;
    QCheckBox *cbx;
    MailRule mr;
    mr.clear();
    int r = mailRules->rowCount();
    mailRules->insertRow(r);

    cbx = new QCheckBox();
    cbx->setTristate(false);
    cbx->setCheckState(Qt::Checked);
    twi = new QTableWidgetItem(0);
    twi->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    mailRules->setItem(r,0,twi);
    mailRules->setCellWidget(r,0,cbx);
    mailRules->setColumnWidth(0,45);

    mr.type = vType->currentText();
    twi = new QTableWidgetItem(mr.type);
    twi->setFlags(Qt::ItemIsSelectable);
    mailRules->setItem(r,1,twi);
    mailRules->setColumnWidth(1,40);

    mr.cond = condition->currentText();
    twi = new QTableWidgetItem(mr.cond);
    twi->setFlags(Qt::ItemIsSelectable);
    mailRules->setItem(r,2,twi);

    twi = new QTableWidgetItem;
    mailRules->setItem(r,3,twi);
    twi = new QTableWidgetItem;
    mailRules->setItem(r,4,twi);

    mailRules->setRowHeight(r,20);

    mailRules->setColumnWidth(4,200);
}

//! Removes a rule from the table.
/*!
    This will not remove it from the database. It
    only removes the line from the table either
    securing it or removing an incorrectly created
    entry.
*/
void
tabAdmin::rmMailRule()
{
    emit Log(mod+"tab_admin.cc","rmMailRule: deleting the selected MailRule from the Table");
    mailRules->removeRow(mailRules->currentRow());
}

//! Updates/creates the selected rules.
/*!
    This updates an existing entry or creates a new
    entry only if the maillist field isn't empty.
    However if it is then if it's an existing entry
    it will delete it otherwise it will just ignore
    it.
*/
void
tabAdmin::updateRule()
{
    QList<QTableWidgetItem*> twil = mailRules->selectedItems();
    QTableWidgetItem *twi;
    QCheckBox *cbx;
    int cc=0;
    int r;
    MailRule mr;
    foreach(twi, twil) {
        if(mailRules->column(twi) == 0) {
            emit Log(mod+"tab_admin.cc","updateRule: Inserting new MailRule in the Database");
            r = mailRules->row(twi);
            mr.clear();
            mr.id = twi->type();
            cbx = qobject_cast<QCheckBox*>(mailRules->cellWidget(r,0));
            if(cbx) mr.active = (cbx->checkState() == Qt::Checked);
            mr.type = mailRules->item(r,1)->text();
            mr.cond = mailRules->item(r,2)->text();
            mr.test = mailRules->item(r,3)->text();
            mr.list = mailRules->item(r,4)->text();
            if((mr.id != 0) || ((mr.id == 0) && (mr.list != QString("")))) {
                QString req =  "type=mailrule&f=update&id="+QString::number(mr.id);
                if(mr.active)
                    req += "&act=1";
                else
                    req += "&act=0";
                req += "&t="+mr.type+"&cond="+mr.cond+"&test="+mr.test+"&list="+mr.list;
                c->Command("admin",req);
                ++cc;
            }
            // send update here...
        }
    }
    while(mailRules->rowCount() != 0)
        mailRules->removeRow(0);



    QMessageBox::information(this,"Admin",QString::number(cc) + QString(" regler er blive opdateret"),QMessageBox::Ok);
    emit Log(mod+"tab_admin.cc","updateRule: Requesting the MailRule data");
    c->Command("admin","type=mailrule&f=get");
    status = new Stat("Henter Mail Regler...");
    status->place();
    status->exec();
    delete status;
    status = 0;
}

Q_EXPORT_PLUGIN2(tab_admin,tabAdmin)
