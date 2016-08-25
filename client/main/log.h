/**************************************************************************
    This file: main/log.h is part of Helhed Client.

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
#ifndef __log_h
#define __log_h 1

#include <QObject>
#include <QStringList>
#include <QTime>
class QListWidget;

class system_log : public QObject
{
    Q_OBJECT
    QListWidget *output;
    QStringList lLog;
    QTime time;
public:
    system_log(QObject *parent=0, QListWidget *out=0);
    ~system_log();

    void setList(QListWidget *lst);
public slots:

    void log(QString module, QString messages, int level=0);
};

#endif
