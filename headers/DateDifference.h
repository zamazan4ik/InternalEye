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
 
 
#ifndef DATEDIFFERENCE_H
#define DATEDIFFERENCE_H

#include <QDateTime>

class DateDifference
{
    //TODO : Rewrite this class
private:
    static const int SecsInMin = 60, SecsInHour = 3600,
                     SecsInDay = 24 * SecsInHour, SecsInWeek = 7 * SecsInDay;

    int weeks, years, days, hours, minutes, secs;

    void __initFromSecs(int secs_);
public:
    DateDifference();
    DateDifference(int secs_);
    DateDifference(const QDateTime& from, const QDateTime& to);

    //Getters
    int getWeeks() const;
    int getDays() const;
    int getHours() const;
    int getMins() const;
    int getSecs() const;
};

#endif // DATEDIFFERENCE_H
