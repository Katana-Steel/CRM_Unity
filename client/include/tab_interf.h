/**************************************************************************
    This file: include/tab_interf.h is part of Helhed Client.

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
#ifndef __tab_interf_h
#define __tab_interf_h

class Conn;
class KData;
#include <QWidget>
/** The Tab Interface
 *
 * this defines the plugin interface used to
 * add extra tab to the main window with a
 * function of its' own
 */
class TabInterface : public QWidget
{
public:
    /** the destructor */
    virtual ~TabInterface() {};
    /** the name.
     *
     * returns a static string with the name of the plugin.
     */
    virtual QString name()=0;
    /** AccessLevel function.
     *
     * Tells the minimum hard-coded user level needed to use
     * the plugin.
     *
     * Usually implemented like this:
     *
     * {
     *     return n;
     * }
     *
     * where n is an integer from 1-10.
     */
    virtual int minUserAccess()=0;
    /** GUI Setup
     *
     * This is the function that setup all the graphics and is
     * called just after it has been attached to the tabWidget
     * of the main window.
     */
    virtual void LoadInterface()=0;
    /** set Http Connection.
     *
     * Sets the Http Connection object of the application to the
     * plugin for communication with the server.
     * If the plugin doesn't work need to communicate with the
     * server then an empty implementation is okay.
     */
    virtual void setConn(Conn *_c)=0;
    /** set Customer Data.
     *
     * Sets the current Customer for the plugin to work with or
     * upon depending on the plugins purpose.
     * If the plugin doesn't work with customer then an empty
     * implementation is okay.
     * This will be called each time the user selects the tab of
     * the plugin, and just before Shown() is called.
     */
    virtual void setKData(KData *_kd)=0;
    /** Server response handler.
     *
     * The plugin's handler function for server response.
     * And all communication with the client happens using XML.
     */
    virtual void ParseXML()=0;
    /** Shown.
     *
     * This is call each time the user selects the tab of the plugin.
     */
    virtual void Shown()=0;

//signals:
//    void Log(QString mod,QString message,int lvl=0);
};

Q_DECLARE_INTERFACE(TabInterface,"dk.bhsribe.helhed/tabs/1.2")

#endif
