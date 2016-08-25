/**************************************************************************
    This file: main/main.cc is part of Helhed Client.

    Helhed Client is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Helhed Client is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helhed Client.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2008, 2009, 2010 René Kjellerup aka Katana Steel
**************************************************************************/
/*! \file main.cc
    \brief helhed -- Helheds program start fil.

\verbatim
 ********************************************************
 * Forfatter: René Kjellerup                            *
 *                                                      *
 * Formål: Den bruges til at sætte det umiddelbare      *
 *         miljø op, såsom at læse konfigurations filen *
 *         og lave forbindelses objektet til serveren.  *
 *                                                      *
 * Brugervejledning:                                    *
 *   helhed [-path <sti>] [-win | -nix]                 *
 *     -path <sti>:                                     *
 *         bruges til at fortælle hvor iexplorer ligger *
 *     -win: bruges til at sætte looket til Windows(XP) *
 *     -nix: bruges til at sætte looket til Unix CDE    *
 *                                                      *
 ******************************************************** \endverbatim
 */
#include <QtCore>
#include <QtGui>
#include <cstring>
#include "mwin.h"
#include "login.h"
#include "conn.h"
#include "config.h"
#include "browser.h"

/*! \mainpage

  Class relations expressed via an inline dot graph:

  \dotfile mainpage.dot

  Note that the classes in the above graph are clickable
  (in the HTML output).
 */


Config *cfg; //!< objectet der holder konfigurations filens data

//! Is serv > cli version number wise.
bool compareVersion(QString serv, QString cli);

int
main (int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon i("helhed.png");
    a.setWindowIcon(i);
    QStyle *st = 0;
    QString path("");
    // er der parameter ved program start?
    if(argc > 1)
    {
        if(argv[1] != 0 && std::strncmp("-style",argv[1],6) == 0) st = a.style();
        int i = 1;
        if(std::strncmp("-path",argv[1],5) == 0) {
            path = argv[2];
            i += 2;
        }
#ifdef WIN32
        // skal vi bruge Windows(XP) looket?
        if(argv[i] != 0 && std::strncmp("-win",argv[i],4) == 0) st = new QWindowsXPStyle;
#endif
        // skal vi bruge Unix CDE looket?
        if(argv[i] != 0 && std::strncmp("-nix",argv[i],4) == 0) st = new QCDEStyle;

    }
    // er der ikke blevet tildelt et look, brug standard looket
    cfg = new Config("config.xml"); // indlæs konfigurations filen
    QString fz = cfg->dfontsz();
    bool ok;

    QFont fn("Andale Mono");
    fz.toInt(&ok);
    if(ok)
        fn.setPixelSize(fz.toInt());
    else
        fn.setPixelSize(12);
    a.setFont(fn);
    if(st==0) {
        st = cfg->getStyleHint();
    }

    a.setPalette(st->standardPalette()); // tildel programmet farve der matcher looket
    a.setStyle(st); // tildel programmet det ønskede look
    Conn *c = cfg->getConn();  // lav og hent server forbindelse objectet
    Login *l = new Login(c); // lav login vinduet
    MWin *w;
    if(l->exec() == QDialog::Accepted) // blev loginet godkendt?
    {
        QString serv = l->servVersion();
        w = new MWin(c);   // lav hovde program vinduet
        delete l;
        QString newVerTxt = "Der er en ny version af\n\"Helhed\" tilgængelig.\nVil du åbne hjemmesiden "
                            "hvor\ndu kan download den nye udgave?\n\n(hvis du vælger \"Yes\" bliver "
                            "programmet lukket nu).";
        if( compareVersion(serv, w->version()) )
            if(QMessageBox::Yes == QMessageBox::information(0,"Helhed",newVerTxt,QMessageBox::Yes,QMessageBox::No)) {
                OpenBrowser("http://"+ cfg->webserver() +"/helhed/app/install.htm");
                delete w;
                delete cfg;
                return 0;
            }
            w->showMaximized();
            int ret = a.exec();  // gå ind i programmets hovde løkke
//            while(c->hasPendingRequests()) {;}
// vent 4 extra sekunder for at sikre os at http requests'ne er færdig behandlet
#ifdef WIN32
                sleep sl(4);
#else
                sleep(4);
#endif
        delete w;
        c->disconnect();
        delete cfg;
        return ret;
    } else {   // ellers luk programmet ordenligt ned
        delete l;
        c->disconnect();
        delete cfg;
        return 0;
    }
}

bool compareVersion(QString serv, QString cli)
{
        int sMaj, sMin, sRel;
        int cMaj, cMin, cRel;
        QStringList strl = serv.split('.');
        sMaj = strl.at(0).toInt();
        sMin = strl.at(1).toInt();
        sRel = strl.at(2).toInt();

        strl = cli.split('.');
        cMaj = strl.at(0).toInt();
        cMin = strl.at(1).toInt();
        cRel = strl.at(2).toInt();
        return (((sMaj == cMaj) && (sMin == cMin) && (sRel > cRel)) || ((sMaj == cMaj) && (sMin > cMin)) || (sMaj > cMaj));
}
