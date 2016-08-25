/**************************************************************************
    This file: include/s_data.h is part of Helhed Client.

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
#ifndef __s_data_h
#define __s_data_h

#include <QTableWidgetItem>

class SData {
public:
    enum _t { N, H, S };
    int sid;
    _t type;
    QString vtxt;
    QString vnr;
    QString stk_p;
    QString stk;
    QString rab;
    void clear() {
        sid=0;
        type=N;
        vtxt.clear();
        vnr.clear();
        stk_p.clear();
        stk.clear();
    };
};

/** SDataListItem
 * 
 * this is a table widget item that 
 * can store sales data while still
 * offering the same interface.
 */
class SDataListItem : public QTableWidgetItem
{
    SData _data;
public:
    SDataListItem(int type= Type);
    SDataListItem(const QString &text,int type= Type);
    ~SDataListItem();
    void setData(int role, const QVariant &value);
    void setData(const SData &data);
    SData data();
    QVariant data(int role);
};

#endif
