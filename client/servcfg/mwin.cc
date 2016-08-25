#include <QtCore>
#include <QtGui>
#include "config.h"
#include "mwin.h"

MainWin::MainWin(Config *c,QWidget *parent) :
    QDialog(parent)
{
    cfg = c;
    setupUi(this);
    this->setWindowIcon(QIcon("helhed.png"));
    QRect rc = stdLabel->rect();
    QSize sz = rc.size();
    sz.setHeight(22);
    labWebAddr->setMinimumSize(sz);
    webAddr->setText(cfg->webserver());
    tls_ssl->setMinimumSize(sz);
    tls_ssl->setChecked(cfg->ssl());
    labAppPath->setMinimumSize(sz);
    appPath->setText(cfg->serverscript());
    labFTPAddr->setMinimumSize(sz);
    ftpAddr->setText(cfg->ftpserver());
    ftpPort->setText(cfg->ftpport());
    labFTPUser->setMinimumSize(sz);
    ftpUser->setText(cfg->ftpuser());
    labFTPPass->setMinimumSize(sz);
    ftpPass->setText(cfg->ftppass());
    labUpPath->setMinimumSize(sz);
    ftpUpload->setText(cfg->ftpdir());
    stdLabel->setMinimumSize(sz);
    ftpTempUpload->setText(cfg->ftptmpdir());
    fontszLab->setMinimumSize(sz);
    defaultFontSize->setValue(cfg->dfontsz().toInt());
    setDefStyle(cfg->cstyle());
    connect(endDlg,SIGNAL(clicked()),this,SLOT(reject()));
    connect(Write,SIGNAL(clicked()),this,SLOT(writeXmlCfg()));
    connect(defStyle,SIGNAL(currentIndexChanged(int)), this, SLOT(setDefStyle(int)));
}

MainWin::~MainWin()
{
    delete cfg;
}

void
MainWin::setDefStyle(int idx)
{
    defStyle->setCurrentIndex(idx);
    QStyle *newStyle;
    switch(idx)
    {
    default:
        newStyle = new QCleanlooksStyle;
        break;
    case 1:
        newStyle = new QCDEStyle;
        break;
    case 2:
        newStyle = new QPlastiqueStyle;
        break;
#ifdef WIN32
    case 3:
        newStyle = new QWindowsXPStyle;
        break;
#endif
    }
    QApplication::setPalette(newStyle->standardPalette());
    QApplication::setStyle(newStyle);
}

void
MainWin::writeXmlCfg()
{
    if(QFile::exists("config.xml")) QFile::copy("config.xml","config.tmp");
    QFile *file = new QFile("config.xml");
    if(!file->open(QIODevice::WriteOnly |QIODevice::Text|QIODevice::Truncate)) {
        delete file;
        QFile::copy("config.tmp","config.xml");
        QFile::remove("config.tmp");
        reject();
    }
    QString namedStyle;
    switch(defStyle->currentIndex())
    {
    case 0:
        namedStyle = QString("cleanlooks");
        break;
    case 1:
        namedStyle = QString("CDE");
        break;
    case 2:
        namedStyle = QString("plastique");
        break;
    case 3:
        namedStyle = QString("winxp");
        break;
    default:
        namedStyle = QString("windows");
        break;
    }
    QTextStream out(file);
    out << "<?xml version=\"1.0\" ?>" << endl;
    out << "<config>" << endl;
    out << " <webhost>" << webAddr->text() << "</webhost>" << endl;
    out << " <ssl>" << tls_ssl->isChecked() << "</ssl>" << endl;
    out << " <apppath>" << appPath->text() << "</apppath>" << endl;
    out << " <ftphost>" << ftpAddr->text() << "</ftphost>" << endl;
    out << " <ftpport>" << ftpPort->text() << "</ftpport>" << endl;
    out << " <ftppath>" << ftpUpload->text() << "</ftppath>" << endl;
    out << " <ftptmp>" << ftpTempUpload->text() << "</ftptmp>" << endl;
    out << " <ftpuser>" << ftpUser->text() << "</ftpuser>" << endl;
    out << " <ftppass>" << ftpPass->text() << "</ftppass>" << endl;
    out << " <style>" << namedStyle << "</style>" << endl;
    out << " <font_size>" << defaultFontSize->cleanText() << "</font_size>" << endl;
    out << "</config>" << endl;
    file->close();
    delete file;
    QFile::remove("config.tmp");
    accept();
}
