/**************************************************************************
    This file: main/xml_sale_hnd.cc is part of Helhed Client.

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
SaleHnd::startElement(const QString&,const QString&,const QString &qName,const QXmlAttributes&)
{
    if(qName == QString("res")) { l = false; success = false; err = false; map.clear(); return true; }
    if(qName == QString("toka")) { l = false; success = false; err = false; map.clear(); return true; }
    if(qName == QString("mail_list")) { l = false; success = false; err = false; map.clear(); return true; }
    if(qName == QString("tmp_list")) { l = false; success = false; err = false; map.clear(); return true; }
    if(qName == QString("tmp")) { sd = new SData; sd->clear(); }
    if(qName == QString("sag")) { sd = new SData; sd->type = SData::S; }
    if(qName == QString("holso")) { sd = new SData; sd->type = SData::H; }
    if(qName == QString("salg")) { sd = new SData; sd->type = SData::S; }
    if(qName == QString("byt")) { sd = new SData; sd->type = SData::H; }
    if(qName == QString("int_msg")) { curValue.clear(); cs = false; return true; }
    if(qName == QString("bemark")) { curValue.clear(); cs = false; return true; }
    if(qName == QString("error")) err = true;
    if(qName == QString("success")) success = true;
    if(qName.mid(0,4) == QString("lev_")) l = true;
    if(qName == QString("lev_by")) { curValue.clear(); cs = false; return true; }
    if(cs) curValue.clear();
    else curValue += "<" +qName +">";
    return true;
}

bool
SaleHnd::characters(const QString &str)
{
    curValue += str;
    return true;
}


bool
SaleHnd::endElement(const QString&,const QString&,const QString &qName)
{
    QLocale dk(QLocale::Danish);
    if(qName == QString("res")) {
        parent->showGlist(sl);
        return true;
    }
    if(qName == QString("toka")) {
        parent->addNewOrder(sl);
        return true;
    }
    if(qName == QString("mail_list")) {
        parent->showMailList(ml);
        return true;
    }
    if(qName == QString("tmp_list")) {
        parent->showTempList(sl);
        return true;
    }
    if(qName == QString("mail")) ml.push_back(curValue);

    if(qName == QString("ttitle")) sd->vtxt = curValue;
    if(qName == QString("tid")) sd->sid = curValue.toInt();
    if(qName == QString("tmp")) { sl.push_back(sd); return true; }

    if(qName == QString("nr")) sd->vnr = curValue;
    if(qName == QString("txt")) sd->vtxt = curValue;
    if(qName == QString("pris")) sd->stk_p = dk.toString(curValue.toFloat(),'f',2);
    if(qName == QString("stk")) sd->stk = dk.toString(curValue.toFloat(),'f',2);
    if(qName == QString("rab")) sd->rab = dk.toString(curValue.toFloat(),'f',2);
    if(qName == QString("sag") || qName == QString("holso")) { sl.push_back(sd); return true; }
    if(qName == QString("salg") || qName == QString("byt")) { sl.push_back(sd); return true; }
    if(qName == QString("int_msg")) { cs = true; }
    if(qName == QString("bemark")) { cs = true; }
    if(qName == QString("lev_by")) { cs = true; }
    if(cs) map[qName] = curValue;
    else {
        if(qName == QString("br")) curValue += "<br>";
        else curValue += "</" + qName + ">";
    }
    return true;
}

void
SaleHnd::clearSL()
{
   // emit parent->log("main/xml_sale_hnd.cc","SaleHnd::clearSL");
    if(!sl.empty()) {
        int size = sl.size();
        for(int i=0;i<size;i++)
        {
            SData *j = sl[0];
            sl.pop_front();
            delete j;
        }
    }
}

void
SaleHnd::clearML()
{
   // emit parent->log("main/xml_sale_hnd.cc","SaleHnd::clearML");
    if(!ml.empty()) {
        ml.clear();
    }
}
