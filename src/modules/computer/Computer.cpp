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
 
 
#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include "Util.h"
#include "Computer.h"

Computer::Computer()
{
    modules.push_back(new OperatingSystem);
    modules.push_back(new Modules);
    modules.push_back(new Boots);
    modules.push_back(new Languages);
    modules.push_back(new FileSystems);
    modules.push_back(new DisplayInfo);
    modules.push_back(new EnvVariables);
    modules.push_back(new DevTools);
    modules.push_back(new Groups);
    modules.push_back(new Users);
}

Computer::~Computer()
{
    for(AbstractModule* x : modules)
    {
        delete x;
    }
}
