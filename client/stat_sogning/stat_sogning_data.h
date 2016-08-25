#ifndef __stat_sogning_data_h
#define __stat_sogning_data_h

#include <QtCore>

struct kndstam {
    QString kunde_nr;
    QString Firma;
    QString Att;
    QString Adr;
    QString PostBy;
    void clear() {
        kunde_nr.clear();
        Firma.clear();
        Att.clear();
        Adr.clear();
        PostBy.clear();
    };
};

struct knddata {
    QString dato;
    QString toka_nr;
    QString lev;
    QString stk;
    QString vnr;
    QString vtxt;
    void clear() {
        dato.clear();
        toka_nr.clear();
        lev.clear();
        stk.clear();
        vnr.clear();
        vtxt.clear();
    };
};

struct datodata {
    kndstam kunde;
    QString toka_nr;
    QString lev;
    void clear() {
        kunde.clear();
        toka_nr.clear();
        lev.clear();
    };
};

struct stat_knd {
    kndstam kunde;
    QVector<knddata> data;
};

struct stat_dato {
    QString dato;
    QVector<datodata> data;
};

#endif
