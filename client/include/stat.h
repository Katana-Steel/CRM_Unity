/**************************************************************************
    This file: include/stat.h is part of Helhed Client.

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

    Copyright 2008, 2009 René Kjellerup aka Katana Steel
**************************************************************************/
#ifndef __stat_h
#define __stat_h

#include <QDialog>

//! The common status dialog.
/*!
    All this does is to display a simple dialog which
    can be blocking (the most common way), or just
    informational. The dialog can only be closed
    programatically. And must be by another thread if
    used blocking.
    the most common use is:
    in header: \code
    Stat *statdlg;
    \endcode
    in constructor: \code
    statdlg = 0;
    \endcode
    in the calling function: \code
// initiate a new thread to make a job the main thread need to wait for
// ie. a http request.
    conn->Command();
    statdlg = new Stat("type message here");
    statdlg->place();
    statdlg->exec();
    delete statdlg;
    statdlg = 0;
    \endcode
    in the job complete function: \code
    if(statdlg) statdlg->accept(); \endcode

*/
class Stat : public QDialog
{
    Q_OBJECT
public:
    Stat(const QString &msg, QWidget *parent=0);
    void place();
};

#endif
