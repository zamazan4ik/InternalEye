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
