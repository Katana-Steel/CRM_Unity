#include <QtCore>
#include <QtGui>
#include "tab_infiles_fh.h"

//! The main part of the thread.
/*!
    This is called when the start() slot is called.

    This opens and read the file one line at a time and
    feed the line to the parseLine function and emit the
    tick(int) signal.
*/
void
FileHandler::run()
{
    if(!file->open(QIODevice::ReadOnly)) return;

    QTextStream ts(file);
    QString line;
    for(;;) {
        line = ts.readLine();
        if(line.isNull()) break;
        curByte += line.size();
        parseLine(line);
        emit tick(curByte);
    }
    emit tick(file->size());
    curByte = 0;
}

//! a setup function.
/*!
    This function is provided to save overhead so only
    one point to this object is needed. Instead of
    creating this object every time we need to parse a
    file for data.

    It sets the next file to read and how to read it. It
    expects the file not to have been opened.
*/
void
FileHandler::setFile(QFile *input, const fileOptions &fo)
{
    file = input;
    fOpt = fo;
}

//! the parser.
/*!
    This parser handles atm 3 file types each formatted in
    up to 2 ways.

    The fists way is from the OpenVMS system known as DC4.
    Where "Cases" and "Custommers" can come from in the form
    of a print out written to a file.

    The second way is in the format of a CSV file with a pre
    defined layout.(1 dataset per row and 1 field per column)
*/
void
FileHandler::parseLine(const QString &l)
{
    Case *cc;
    KData *kk;
    QString rest;
    bool ok;
    int idx;
    switch(fOpt.dbp) {
    case Sager:
        cc = new Case;
        switch(fOpt.ft) {
        case DC4:
            if(l.mid(0,1) != QString(" ")){ delete cc; return; }
            cc->cnr = l.mid(0,15).trimmed();
            cc->ctxt = l.mid(15,50).trimmed();
            cc->cval = l.mid(67,12).trimmed();
            emit tick(cc);
            break;
        case CSV:
            idx = l.indexOf(';');
            if(idx > 0) {
             cc->cnr = l.mid(0,idx).trimmed();
             rest = l.mid(idx+1);
             idx = rest.indexOf(';');
             if(idx > 0) {
              cc->ctxt = rest.mid(0,idx).trimmed();
              rest = rest.mid(idx+1);
              idx = rest.indexOf(';');
              if(idx < 0) {
               cc->cval = rest.mid(0).trimmed();
              } else {
               cc->cval = rest.mid(0,idx).trimmed();
              }
              cc->cval = QString::number(cc->cval.toFloat(&ok));
              if(ok) emit tick(cc);
              else delete cc;
             }
            }
        default:
            break;
        }
        break;
    case Vare:
        cc = new Case;
        switch(fOpt.ft) {
        case CSV:
            idx = l.indexOf(';');
            if(idx > 0) {
             cc->cnr = l.mid(0,idx).trimmed();
             rest = l.mid(idx+1);
             idx = rest.indexOf(';');
             if(idx > 0) {
              cc->ctxt = rest.mid(0,idx).trimmed();
              rest = rest.mid(idx+1);
              idx = rest.indexOf(';');
              if(idx < 0) {
               cc->cval = rest.mid(0).trimmed();
              } else {
               cc->cval = rest.mid(0,idx).trimmed();
              }
              cc->cval.toFloat(&ok);
              if(ok) emit tick(cc);
              else delete cc;
             }
            }
        default:
            break;
        }
        break;
    case Kunder:
        kk = new KData;
        kk->clear();
        switch(fOpt.ft) {
        case DC4:
            rest = l.mid(0);
            if(rest.mid(0,1) == QString("\x0c")) rest = rest.remove(0,1);
            if(rest.size() < 137){ delete kk; return; }
            kk->knr  = rest.mid(0,10).trimmed();
            kk->navn = rest.mid(11,37).trimmed();
            kk->att  = rest.mid(49,49).trimmed();
            kk->adr  = rest.mid(99,29).trimmed();
            kk->post = rest.mid(129,4).trimmed();
            kk->by   = rest.mid(135).trimmed();
            kk->land = QString("Danmark");
            break;
        case CSV:
            rest = l;
            for(int i=0;i<11;i++) {
                idx = rest.indexOf(';');
                if(idx > 0) {
                    switch(i) {
                    case 0:
                        kk->knr = rest.mid(0,idx).trimmed();
                        break;
                    case 1:
                        kk->navn = rest.mid(0,idx).trimmed();
                        break;
                    case 2:
                        kk->att = rest.mid(0,idx).trimmed();
                        break;
                    case 3:
                        kk->adr = rest.mid(0,idx).trimmed();
                        break;
                    case 4:
                        kk->post = rest.mid(0,idx).trimmed();
                        break;
                    case 5:
                        kk->by = rest.mid(0,idx).trimmed();
                        break;
                    case 6:
                        kk->land = rest.mid(0,idx).trimmed();
                        break;
                    case 7:
                        kk->ean_se = rest.mid(0,idx).trimmed();
                        break;
                    case 8:
                        kk->tlf = rest.mid(0,idx).trimmed();
                        break;
                    case 9:
                        kk->fax = rest.mid(0,idx).trimmed();
                        break;
                    case 10:
                        kk->mobil = rest.mid(0,idx).trimmed();
                        break;
                    }
                }
                rest = rest.mid(idx+1);
            }
            rest = QString(""); // make rest a shortcut to empty
            bool navn;
            kk->knr.toInt(&ok);
            navn = ((kk->navn != rest) || (kk->att != rest));
            if((kk->knr != rest) && navn && (kk->adr != rest) &&
               (kk->post != rest) && (kk->by != rest) && (kk->land != rest) &&
                ok) emit tick(kk);
            else delete kk;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}
