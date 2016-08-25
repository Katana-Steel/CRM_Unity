/**************************************************************************
    This file: main/browser.cc is part of Helhed Client.

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

#include <QtCore>
#include <QtGui>

/** Opens a web-browser.

    This works in two ways on different systems.
	On a Windows system it locate the ProgramFiles path and
	add the well known path to Internet Explorer.
	On a GNU/Linux system it looks in /usr/bin for a list of
	known web browsers and picks the first it finds.
*/
void OpenBrowser(const QString &url)
{
    QString prog;
    QStringList env;
    int idx;
    QString path;

#if defined(WIN32)
    env = QProcess::systemEnvironment();
    env = env.filter("ProgramFiles=",Qt::CaseInsensitive); // windows doesn't know about case differences.
    for(idx = 0;idx < env.size();idx++) {
        path = env.at(idx);
        if(path.mid(0,3) == QString("Pro")) break;
    }
    idx = path.indexOf('=') + 1;
    path = path.mid(idx);
    prog = QString('"') + path + "\\Internet Explorer\\iexplore.exe" + QString('"');
#elif defined(Q_OS_LINUX)
	path = "/usr/bin/";
	env << "firefox" << "seamonkey" << "iceweasel" << "iceape" << "mozilla";
	QString app;
	for(idx=0;idx<env.size();idx++) {
		if(QFile::exists(path + env.at(idx)))
			break;
	}
    if(idx != env.size())
		prog = path + env.at(idx);
#endif
    QProcess *r = new QProcess;
    r->startDetached(prog +" " +QString('"')+url+QString('"'));
    r->close();
    if(r->waitForStarted()) delete r;
}
