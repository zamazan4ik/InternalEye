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
 
 
#include <QTextStream>
#include "Computer.h"
#include "Util.h"

#define CG Computer::Group

CG::Group()
{
}

CG::Group(const QString& name, const int id, const QStringList& members) :
          _name(name), _id(id), _members(members)
{
}

QVector<Computer::Group> CG::getGroups()
{
    QByteArray out = getOutputConsole("cat /etc/group");
    QTextStream stream(&out);
    QStringList line;
    QVector<Group> groups;
    while(!stream.atEnd())
    {
        line = stream.readLine().split(':');
        QString     name    = line[0];
        int         id      = line[2].toInt();
        QStringList members = line[3].split(',');
        groups.push_back(Group(name, id, members));
    }
    return groups;
}
