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

Computer::Users::Users()
{
    update();
}

QVector<Computer::Users::User> Computer::Users::_getUsers()
{
    QByteArray out = getOutputConsole("cat /etc/passwd");
    QTextStream stream(&out);
    QStringList line;
    QVector<User> users;
    while(!stream.atEnd())
    {
        line = stream.readLine().split(':');
        QString name = line[0], firstName, secondName, address, workPhone, homePhone,
                workDir = line[5], shell = line[6];
        int id = line[2].toInt(), groupID = line[3].toInt();

        QStringList addInfo = line[4].split(',');
        int size = addInfo.size();

        secondName  = addInfo[0];
        firstName   = size >= 2 ? addInfo[1] : "";
        address     = size >= 3 ? addInfo[2] : "";
        workPhone   = size >= 4 ? addInfo[3] : "";
        homePhone   = size >= 5 ? addInfo[4] : "";

        users.push_back({name, firstName, secondName, address, workPhone,
                             homePhone, workDir, shell, id, groupID});
    }
    return users;
}

void Computer::Users::update()
{
    users = _getUsers();
}

QVector<Computer::Users::User> Computer::Users::getUsers()
{
    return users;
}
