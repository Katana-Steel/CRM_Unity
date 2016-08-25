/**************************************************************************
    This file: main/xml_stat_hnd.cc is part of Helhed Client.

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
#include "xml_c_handle.h"
#include "mwin.h"


bool
StatHnd::characters(const QString &str)
{
    curValue += str;
    return true;
}

bool
StatHnd::startElement(const QString &, const QString &,const QString &qName, const QXmlAttributes &)
{
    if(QString("res") == qName) { err = false; success = false; map.clear(); }
    curValue.clear();
    return true;
}

bool
StatHnd::endElement(const QString &, const QString &,const QString &qName)
{
    if(QString("error") == qName) err = true;
    if(QString("success") == qName) success = true;
    if(QString("page") == qName) {
        OpenBrowser(curValue);
    }
    if(QString("res") == qName) {
        return true;
    }
    map[qName] = curValue;
    return true;
}
