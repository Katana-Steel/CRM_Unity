/**************************************************************************
    This file: include/stat_interf.h is part of Helhed Client.

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
#ifndef __stat_interf_h
#define __stat_interf_h

class QString;
class Conn;
class QWidget;

class StatInterface
{
public:
    virtual ~StatInterface() {};
    virtual int searchDialog()=0;
    virtual void xmlParse()=0;
    virtual QString name()=0;
    virtual void setDialogParent(QWidget *_p)=0;
    virtual void setConn(Conn *_c)=0;
};

Q_DECLARE_INTERFACE(StatInterface,"dk.bhsribe.helhed/stat/1.1")

#endif
