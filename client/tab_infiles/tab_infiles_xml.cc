#include "tab_infiles_xml.h"

inline QString lstr(const char *str) { return QString::fromLocal8Bit(str); }

//! the open tag has been encountered.
/*!
    Does we know the tag, and does we need to set someting
    up to parse this tag properly.

    This clears the value of curValue.
*/
bool
XmlHnd::startElement(const QString &/*namespaceURI*/, const QString &/*localName*/,
                          const QString &qName, const QXmlAttributes &/*attributes*/)
{
    if(qName == QString("res"))   { map.clear(); err=false; success=false; SDList.clear(); }
    if(qName == QString("sag"))   { curSD.clear(); curSD.type = SData::S; }
    if(qName == QString("holso")) { curSD.clear(); curSD.type = SData::H; }
    curValue.clear();
    return true;
}

//! the close tag has been encountered.
/*!
    Does we know the tag then take the appropriate action.
    Else just add the tag to the tag/value map so the main
    program can get the value through getValue() if needed.
*/
bool
XmlHnd::endElement (const QString &/*namespaceURI*/, const QString &/*localName*/,
                         const QString &qName)
{
    if(qName == QString("res"))     return true;
    if(qName == QString("error"))   err = true;
    if(qName == QString("success")) success = true;
    if(qName == QString("sag"))     SDList.push_back(curSD);
    if(qName == QString("holso"))   SDList.push_back(curSD);
    if(qName == QString("id"))      curSD.sid   = curValue.toInt();
    if(qName == QString("nr"))      curSD.vnr   = curValue;
    if(qName == QString("txt"))     curSD.vtxt  = curValue;
    if(qName == QString("pris"))    curSD.stk_p = curValue;
    if(qName == QString("sort"))   curSD.rab   = curValue;

    map[qName] = curValue;
    return true;
}

//! adds the data to curValue.
/*!
    This appends the data of the current tag to the
    curValue member.
*/
bool
XmlHnd::characters(const QString &str)
{
    curValue += lstr(str.toStdString().c_str());
    return true;
}

//! Get the SData buffer.
/*!
    Checks if there is a list to return and returns
    it through the passed sdata variable and exits
    true, otherwise it exits false.
*/
bool
XmlHnd::getSDList(QVector<SData> &sdata)
{
    if(SDList.empty()) return false;
    sdata = SDList;
    return true;
}
