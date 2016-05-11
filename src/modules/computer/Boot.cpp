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
 
 
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QString>
#include <QByteArray>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QTextStream>
#include <QDebug>
#include "Util.h"
#include "Computer.h"

#define CBB Computer::Boot

CBB::Boot()
{
}

CBB::Boot(const QString &kernelVersion, const QDateTime &dateStart, const QDateTime &dateEnd) :
          _kernelVersion(kernelVersion), _dateStart(dateStart), _dateEnd(dateEnd), _duringTime(dateStart, dateEnd)
{
}

QString CBB::getKernelVersion() const
{
    return _kernelVersion;
}

QDateTime CBB::getDateStart() const
{
    return _dateStart;
}

QDateTime CBB::getDateEnd() const
{
    return _dateEnd;
}

DateDifference CBB::getDuringTime() const
{
    return _duringTime;
}

QVector<Computer::Boot> CBB::getBoots()
{
    //TODO : Write a _update for Boot
    QByteArray output = getOutputConsole("last -F | grep 'system boot'");
    QTextStream stream(&output);
    QStringList list;
    QString line;
    QVector<Computer::Boot> boots;
    while(!stream.atEnd())
    {
        line = stream.readLine();
        if(line.indexOf("still") != -1 && line.indexOf("running") != -1)    continue;
        line = line.trimmed();
        line.replace("(", "").replace(")", "").replace(" - ", " ").
             replace("  ", " ").replace("  ", " ");
        list = line.split(' ');
        QString kernelVersion;
        QDateTime dateStart, dateEnd;
        kernelVersion = list.at(3);
        QLocale loc(QLocale::English);
        dateStart = loc.toDateTime(QString("%1 %2 %3 %4 %5").arg(list.at(4)).arg(list.at(5)).arg(list.at(6)).
                                   arg(list.at(7)).arg(list.at(8)), "ddd MMM d hh:mm:ss yyyy");
        dateEnd = loc.toDateTime(QString("%1 %2 %3 %4 %5").arg(list.at(9)).arg(list.at(10)).arg(list.at(11)).
                                 arg(list.at(12)).arg(list.at(13)), "ddd MMM d hh:mm:ss yyyy");
        Boot (kernelVersion, dateStart, dateEnd);
        boots.push_back(Boot (kernelVersion, dateStart, dateEnd));
    }
    return boots;
}
