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
 
 
#include <fstream>
#include <string>
#include <QDebug>
#include "Computer.h"

#define CL Computer::LoadInfo

CL::LoadInfo()
{
    _update();
}

double CL::getLoad1() const
{
    return load1;
}

double CL::getLoad5() const
{
    return load5;
}

double CL::getLoad15() const
{
    return load15;
}

int CL::getWorkEnt() const
{
    return workEntities;
}

int CL::getAllEnt() const
{
    return allEntities;
}

int CL::getMostRunPID() const
{
    return mostRunPID;
}

void CL::update()
{
    _update();
}

void CL::_update()
{
    std::ifstream in("/proc/loadavg");
    if(!in.is_open())
    {
        return;
    }
    in >> load1 >> load5 >> load15;
    in >> workEntities;
    in.get();
    in >> allEntities >> mostRunPID;
}
