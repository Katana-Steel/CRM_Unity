#include "stat_changed_xml.h"
#include <browser.h>

bool
XmlHnd::startElement(const QString &/*namespaceURI*/, const QString &/*localName*/,
                       const QString &qName, const QXmlAttributes &/*attributes*/)
{
    if(qName == QString("res"))  { err = false; map.clear(); }
    curValue.clear();
    return true;
}

bool
XmlHnd::endElement(const QString &/*namespaceURI*/, const QString &/*localName*/,
                       const QString &qName)
{
    if(qName == QString("res"))    { return true; }
    if(qName == QString("error"))  { err = true; }
    if(qName == QString("page"))   { OpenBrowser(curValue); }

    map[qName] = curValue;
    return true;
}

bool
XmlHnd::characters(const QString &str)
{
    curValue += str;
    return true;
}

