/**************************************************************************
    This file: include/st_data.h is part of Helhed Client.

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
#ifndef __st_data_h
#define __st_data_h

#include "k-j_data.h"
#include "s_data.h"

template <typename T>
class QVector;
class QString;

class TOKAnr {
public:
    QString nr;
    QVector<SData> list;

//    TOKAnr(const QString &_n) : nr(_n) {};
};

class CustNr {
public:
    KData cust;
    QVector<TOKAnr> list;
    void clear() {
        cust.clear();
        list.clear();
    };

//    CustNr(const QString &_n) : nr(_n) {};
};

#endif
