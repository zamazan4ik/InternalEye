#ifndef DATEDIFFERENCE_H
#define DATEDIFFERENCE_H

#include <QDateTime>

class DateDifference
{
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
