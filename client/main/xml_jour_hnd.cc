/**************************************************************************
    This file: main/xml_jour_hnd.cc is part of Helhed Client.

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

bool JourHnd::startElement(const QString &, const QString &,
                          const QString &qName, const QXmlAttributes &)
{
    if(qName == QString("res")) { nid = 0; mail = false; success = false; err = false; map.clear(); return true; }
    if(qName == QString("cus")) { kd = new KData; }
    if(qName == QString("jour")) { jd = new JData; jd->lev = JData::IACT; }
    if(qName == QString("ant")) { k = true; /* err = true; map["error"] = "tjek errorLog.xml"; */ }
    if(qName == QString("br")) { curValue += " "; return true; }
    if(qName == QString("nota_text")) { curValue.clear(); cl = false; return true; }
    if(qName == QString("mail_list")) {
        jd = 0; kd = 0; nid = 0; mail = true; success = false; err = false; map.clear(); return true;
    }

    if(cl) curValue.clear();
    else curValue += "<"+qName+">";

    return true;
}

bool JourHnd::characters(const QString &str)
{
    curValue += parent->svr_tr(str);
    return true;
}

bool
JourHnd::endElement (const QString &, const QString &,
                     const QString &qName)
{
    if(qName == QString("res"))
    {
        if(k) { parent->showKList(kl); clearKL(); }
        parent->dispJD();
        j=false;
        k=false;
        return true;
    }
    if(qName == QString("error")) err = true;
    if(qName == QString("success")) success = true;
    if(qName == QString("cus"))
    {
        if(k) { kl.push_back(kd); }
        else { parent->setCustomer(*kd); delete kd; }
        return true;
    }

    if(qName == QString("mail_list")) {
        mail = false;
        parent->showMailList(ml,false);
        return true;
    }
    if(qName == QString("nid") && mail) nid = curValue.toInt();
    if(qName == QString("mail") && mail) ml.push_back(curValue);

    if(kd) {
     if(qName == QString("kid")) kd->kid = curValue.toInt();
     if(qName == QString("knr")) kd->knr = curValue;
     if(qName == QString("navn")) kd->navn = curValue;
     if(qName == QString("att")) kd->att = curValue;
     if(qName == QString("adr")) kd->adr = curValue;
     if(qName == QString("post")) kd->post = curValue;
     if(qName == QString("by")) kd->by = curValue;
     if(qName == QString("email")) kd->email.push_back(curValue);
     if(qName == QString("tlf")) kd->tlf = curValue;
     if(qName == QString("fax")) kd->fax = curValue;
     if(qName == QString("mobil")) kd->mobil = curValue;
     if(qName == QString("nota")) kd->nota = curValue;
     if(qName == QString("kdato")) kd->dato = curValue;
     if(qName == QString("land")) kd->land = curValue;
     if(qName == QString("ean_se")) kd->ean_se = curValue;
    }
    if(jd) {
     if(qName == QString("jour")) { parent->addJournal(jd); jd=0; return true; }
     if(qName == QString("notat")) jd->nid = curValue.toInt();
     if(qName == QString("sid")) jd->sid = curValue;
     if(qName == QString("til")) { jd->type = JData::T; jd->nr = curValue; }
     if(qName == QString("ord")) { jd->type = JData::O; jd->nr = curValue; }
     if(qName == QString("kon")) { jd->type = JData::K; jd->nr = curValue; }
     if(qName == QString("arb")) { jd->type = JData::A; jd->nr = curValue; }
     if(qName == QString("slg")) { jd->type = JData::S; jd->nr = curValue; }
     if(qName == QString("del")) { jd->type = JData::X; jd->nr = curValue; }
     if(qName == QString("mail")) { jd->type = JData::M; jd->nr = curValue; }
     if(qName == QString("dato")) jd->dato = curValue;
     if(qName == QString("status")) { if(curValue == QString("A")) jd->status = JData::ACT; else jd->status = JData::IACT; }
     if(qName == QString("lev")) { if(curValue == QString("A")) jd->lev = JData::ACT; else jd->lev = JData::IACT; }
     if(qName == QString("luk")) { jd->luk = curValue.toInt(); if(jd->luk == 1) jd->luk = 100; }
     if(qName == QString("titel")) { jd->type = JData::NONE; jd->nr = curValue; }
     if(qName == QString("nota_text")) { jd->nota_text= curValue;  cl = true; }
    }
    if(qName == QString("page")) {
        OpenBrowser(curValue);
    }
    if(!cl) {
        if(qName != QString("br")) curValue += "</"+qName+">";
        else  curValue += "<"+qName+">";
        return true;
    }

    map[qName] = curValue;
    return true;
}

void
JourHnd::clearKL()
{
   // emit parent->log("main/xml_jour_hnd.cc","JourHnd::clearKL");
    if(!kl.empty()) {
        int size = kl.size();
        for(int i=0;i<size;i++)
        {
            KData *j = kl[0];
            kl.pop_front();
            delete j;
        }
    }
}

void
JourHnd::clearML()
{
  //  emit parent->log("main/xml_jour_hnd.cc","JourHnd::clearML");
    if(!ml.empty()) {
        ml.clear();
    }
}
