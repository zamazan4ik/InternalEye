/***************************************************************************
 *   Copyright (C) 2016 by Zaitsev Alexander                               *
 *   zamazan4ik@tut.by	                                                   *
 *                                                                         *
 *   This file is part of InternalEye.                                     *
 *                                                                         *
 *   InternalEye is free software: you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   InternalEye is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with InternalEye.  If not, see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/
 
 
#include "Computer.h"
#include "Util.h"
#include <QTextStream>

Computer::DisplayInfo::DisplayInfo()
{
    _update();
}

void Computer::DisplayInfo::_update()
{
    _getGLXinfo();
    _getX11info();
}

void Computer::DisplayInfo::update()
{
    _update();
}

void Computer::DisplayInfo::_getGLXinfo()
{
    QByteArray out = getOutputConsole("glxinfo");
    QTextStream stream(&out);
    QString line;
    oglVendor = oglRenderer = oglVersion = "Unknown";
    dri = false;
    while(!stream.atEnd())
    {
        line = stream.readLine();
        if(line.indexOf("OpenGL vendor string") != -1)          oglVendor   = line.split(':').at(1).trimmed();
        else if(line.indexOf("OpenGL renderer string") != -1)   oglRenderer = line.split(':').at(1).trimmed();
        else if(line.indexOf("OpenGL version string") != -1)    oglVersion  = line.split(':').at(1).trimmed();
        else if(line.indexOf("direct rendering: Yes") != -1)    dri = true;
    }
}


//QString displayName, monitors;
//QSize size;
void Computer::DisplayInfo::_getX11info()
{
    QByteArray out = getOutputConsole("xdpyinfo");
    QTextStream stream(&out);
    QString line;
    while(!stream.atEnd())
    {
        line = stream.readLine();
        if(line.indexOf("number of extensions") != -1)
        {
            int count = line.split(':')[1].trimmed().toInt();
            for(int i = 0; !stream.atEnd() && i < count; ++i)
            {
                line = stream.readLine();
                extensions.push_back(line.trimmed());
            }
        }
        else if(line.indexOf("vendor string") != -1)    vendor = line.split(':')[1].trimmed();
        else if(line.indexOf("X.Org version") != -1 ||
                line.indexOf("XFree86 version") != -1)    version = line.split(':')[1].trimmed();
    }
}


