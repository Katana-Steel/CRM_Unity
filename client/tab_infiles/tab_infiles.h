#ifndef __tab_infiles_h
#define __tab_infiles_h
#include "tab_interf.h"
#include "ui_tab_infile.h"
#include "tab_infiles_data.h"
#include "s_data.h"
#include "k-j_data.h"
#include <QVector>

class QXmlSimpleReader;
class XmlHnd;
class Stat;
class QFile;
class FileHandler;
class QDialog;
class QTableWidget;
class QFontMetrics;
class QLocale;
class KData;

//! The main part of the LVO plugin.
/*!
    This implements the Tab Interface from Helhed and
    adds an interface to handle data file uploads and
    editing prices of all the existing items for sale
    in the database. (both cases and machines)
    And the ability to quickly insert a few new items.
*/
class tabInFiles : public TabInterface, private Ui::fDlg
{
    Q_OBJECT
    Q_INTERFACES(TabInterface)
    Conn *c; //!< access to the http communication used by the Client.
    QXmlSimpleReader *xml; //!< the XML parser.
    XmlHnd *hnd; //!< the XML handler.
    Stat *status; //!< the popup status dialog.
    QString pFile; //!< the file name \& path of the current file.
    QFile *input; //!< the file to read data from.
    FileHandler *fh; //!< the file parser and handler.
    bool ready; //!< are we reading a file atm?
    QVector<Case*> caList; //!< the Case buffer.
    QVector<KData*> kdList; //!< the KData buffer.
    QFontMetrics *fmx;
    QLocale *dk; //!< an object used in conjunction with float conversion.
    QString mod;
public:
    tabInFiles();
    ~tabInFiles();
    QString name();
    int minUserAccess();
    void LoadInterface();
    void setConn(Conn *_c);
    void setKData(KData *) {};
    void ParseXML();
    void Shown();
private slots:
    void addGross();
    void OpenFile();
    void resetReady();
    void startParse();
    void addCase(Case *str);
    void addCust(KData *str);
    void searchGross();
    void multiUpdate();
    void multiDelete();
    void valueUpdate(QTableWidgetItem *twi);
private:
    QString convertToDk(const QString &str);
    void showGList(QVector<SData> &sdata);
    void setupSystem0Dlg(QDialog *win);
    void setupSystem1Dlg(QDialog *win);
    void setupSystem2Dlg(QDialog *win);
    void runSystem0();
    void runSystem1();
    void runSystem2();
signals:
    void Log(QString mod,QString message,int lvl=0);
};

#endif
