/**************************************************************************
    This file: main/xml_login_hnd.cc is part of Helhed Client.

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
#include "conn.h"

bool XmlHnd::startElement(const QString &/*namespaceURI*/, const QString &/*localName*/,
                          const QString &qName, const QXmlAttributes &/*attributes*/)
{
    if(qName == QString("res")) return true;
    curValue.clear();
    return true;
}

bool XmlHnd::endElement (const QString &/*namespaceURI*/, const QString &/*localName*/,
                         const QString &qName)
{
    if(qName == QString("res")) return true;
    if(qName == QString("error")) err = true;
    if(qName == QString("cid")) c->setcid(curValue);
    map[qName] = curValue;
    return true;
}

bool XmlHnd::characters(const QString &str)
{
    curValue += str;
    return true;
}
