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
#include <QLocale>
#include "DateDifference.h"
#include "Util.h"
#include "Computer.h"

#define CB Computer::BootInfo

CB::BootInfo()
{
    _update();
}

void CB::_update()
{
    //TODO : Write a _update for BootInfo
    QByteArray output = getOutputConsole("last -F | grep 'system boot'");
    QTextStream stream(&output);
    QStringList list;
    QString line;
    while(!stream.atEnd())
    {
        line = stream.readLine();

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
}
