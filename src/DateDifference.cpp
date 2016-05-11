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
 
 
#include "DateDifference.h"

DateDifference::DateDifference()
{
}

DateDifference::DateDifference(const QDateTime &from, const QDateTime &to)
{
    __initFromSecs(to.toTime_t() - from.toTime_t());
}

DateDifference::DateDifference(int secs_)
{
    __initFromSecs(secs_);
}

void DateDifference::__initFromSecs(int secs_)
{
    if(secs_ >= SecsInWeek)
    {
        weeks = secs_ / SecsInWeek;
        secs_ %= SecsInWeek;
    }
    if(secs_ >= SecsInDay)
    {
        days = secs_ / SecsInDay;
        secs_ %= SecsInDay;
    }
    if(secs_ >= SecsInHour)
    {
        hours = secs_ / SecsInHour;
        secs_ %= SecsInHour;
    }
    if(secs_ >= SecsInMin)
    {
        minutes = secs_ / SecsInMin;
        secs_ = secs_ / SecsInMin;
    }
    secs = secs_;
}

int DateDifference::getWeeks() const
{
    return weeks;
}

int DateDifference::getDays() const
{
    return days;
}

int DateDifference::getHours() const
{
    return hours;
}

int DateDifference::getMins() const
{
    return minutes;
}

int DateDifference::getSecs() const
{
    return secs;
}
