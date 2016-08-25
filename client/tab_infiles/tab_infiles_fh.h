#ifndef __tab_infiles_fh_h
#define __tab_infiles_fh_h
#include <QThread>
#include "tab_infiles_data.h"
#include "k-j_data.h"

class QFile;
class QListWidget;

//! Handles the way files are read.
/*!
    This creates a new thread and reads a file
    according to the fileOptions structure and
    emits two signals. One containing the data
    read and one with the number of bytes read
    from file.
*/
class FileHandler : public QThread
{
    Q_OBJECT
    QFile *file; //!< the current file to read.
    int curByte; //!< the number of bytes read this far.
    fileOptions fOpt; //!< how to read the file.
    void parseLine(const QString &l);
public:
    FileHandler() : curByte(0) {};
    void run();
    void setFile(QFile *input, const fileOptions &fo);

signals:
    void tick(int); //!< emits the number of bytes read.
    void tick(Case*); //!< emits the data from a line if successfully aquired.
    void tick(KData*); //!< emits the data from a line if successfully aquired.
};

#endif
