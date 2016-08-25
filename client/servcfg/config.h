#ifndef __config_h
#define __config_h

class QString;

class Config
{
    QString _ws;
    QString _ss;
    bool _ssl;
    QString _fs;
    QString _fsp;
    QString _fu;
    QString _fp;
    QString _fd;
    QString _ftd;
    QString _fsize;
    int _style;
public:
    Config(const QString &filename);

    QString webserver() { return _ws; };
    bool ssl() {return _ssl; };
    QString serverscript() { return _ss; };
    QString ftpserver() { return _fs; };
    QString ftpport() { return _fsp; };
    QString ftpuser() { return _fu; };
    QString ftppass() { return _fp; };
    QString ftpdir() { return _fd; };
    QString ftptmpdir() { return _ftd; };
    QString dfontsz() { return _fsize; };
    int cstyle() { return _style; };
};

#endif
