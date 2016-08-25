#ifndef __tab_infiles_data_h
#define __tab_infiles_data_h

//! the part of the database to update.
enum DBPart {
        Sager,  //!< the Cases.
        Kunder, //!< the Custommers.
        Vare    //!< the Grosseries.
    };
//! the file type.
enum FType {
        CSV, //!< a CSV file (as saved from MS Excel).
        DC4  //!< a Pring file from OpenVMS/DC4.
    };

//! the chossen file options.
struct fileOptions {
    DBPart dbp;
    FType ft;
};

//! a case or a grossery.
struct Case {
    QString cnr;
    QString ctxt;
    QString cval;
};

#endif
