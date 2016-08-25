/**************************************************************************
    This file: main/log.cc is part of Helhed Client.

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
#include <QtGui>
#include "log.h"

system_log::system_log(QObject *parent, QListWidget *out)
    : QObject(parent),lLog()
{
    output = out;
    time = QTime::currentTime();
}

system_log::~system_log()
{
     QFile file("out.txt");
     if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

     QTextStream out(&file);
     foreach(QString str, lLog) {
         out << str << endl;
     }
     file.close();
}

void
system_log::setList(QListWidget *lst)
{
    output = lst;
    if(output) {
        foreach(QString str, lLog) {
            output->addItem(str);
        }
    }
}

void
system_log::log(QString module, QString message, int level)
{
    time = QTime::currentTime();
    QString line = time.toString("HH:mm:ss.zzz - ");
    switch(level)
    {
        case 0:
        line += "INFO  ";
        break;
        case 1:
        line += "ERROR ";
        break;
    }
    line += "* " + module +" * - " + message;
    lLog.push_back(line);
    if(output)
        output->addItem(line);
}
