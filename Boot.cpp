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

#define CBB Computer::BootInfo::Boot

CBB::Boot()
{
}

CBB::Boot(const QString &kernelVersion_, const QDateTime &dateStart_, const QDateTime &dateEnd_) :
          kernelVersion(kernelVersion_), dateStart(dateStart_), dateEnd(dateEnd_), duringTime(dateStart_, dateEnd_)
{
}

QString CBB::getKernelVersion() const
{
    return kernelVersion;
}

QDateTime CBB::getDateStart() const
{
    return dateStart;
}

QDateTime CBB::getDateEnd() const
{
    return dateEnd;
}

DateDifference CBB::getDuringTime() const
{
    return duringTime;
}
