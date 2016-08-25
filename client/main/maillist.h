/**************************************************************************
    This file: main/maillist.h is part of Helhed Client.

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
#ifndef __maillist_h
#define __maillist_h 1
#include <QDialog>
#include <QString>

class QLineEdit;
class QTableWidget;
class QTableWidgetItem;

class MailList : public QDialog
{
    Q_OBJECT
public:
    MailList(QTableWidget *t, QLineEdit *out=0, QWidget *parent=0);
    QString res(void);
public slots:
    void insertMail(QTableWidgetItem *twi);
private:
    QLineEdit *lineout;
};

#endif
