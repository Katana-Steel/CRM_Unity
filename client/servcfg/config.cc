#include <QtCore>
#include "config.h"
#include "conf_xml.h"

Config::Config(const QString &filename) :
    _ws(""),_ss(""),_ssl(false),_fs(""),_fsp(""),_fu(""),_fp(""),_fd(""),_fsize(""),_style(0)
{
    QFile *file = new QFile(filename);
    if(file->exists()) file->open(QIODevice::ReadOnly|QIODevice::Text|QIODevice::Unbuffered);
    else { delete file; return; }
    ConfHnd *hnd = new ConfHnd;
    QXmlSimpleReader *xml = new QXmlSimpleReader;
    xml->setContentHandler(hnd);
        QXmlInputSource *XFile = new QXmlInputSource(file);
        if(!xml->parse(*XFile))
        {
            delete XFile;
            delete xml;
            delete hnd;
            file->close();
            delete file;
        }
        _ws = hnd->getValue("webhost");
        _ss = hnd->getValue("apppath");
        _ssl = (hnd->getValue("ssl") == QString("1")) ? true : false;
        _fs = hnd->getValue("ftphost");
        _fsp = hnd->getValue("ftpport");
        _fu = hnd->getValue("ftpuser");
        _fp = hnd->getValue("ftppass");
        _fd = hnd->getValue("ftppath");
        _ftd = hnd->getValue("ftptmp");
        _fsize = hnd->getValue("font_size");
        QString tmp = hnd->getValue("style");
        if(QString("CDE") == tmp)
            _style = 1;
        if(QString("plastique") == tmp)
            _style = 2;
        if(QString("winxp") == tmp)
            _style = 3;
        delete XFile;
    delete xml;
    delete hnd;
    file->close();
    delete file;
}
