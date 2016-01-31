#include <QProcess>
#include <QString>
#include <QStringList>
#include <QString>
#include <QByteArray>
#include <QDateTime>
#include <QTextStream>
#include "Computer.h"

#define CB Computer::BootInfo

CB::BootInfo()
{

}

void CB::_update()
{
    //TODO : Write a _update for BootInfo
    QProcess proc;
    proc.start("/bin/sh", QStringList() << "-c" << "last | grep 'system boot'");
    proc.waitForFinished(-1);
    QByteArray output = proc.readAll();
    QTextStream stream(&output);
    QString line;
    while(!stream.atEnd())
    {
        line = stream.readLine();
    }
}

QDateTime CB::getDateOfBoot() const
{
    return dateOfBoot;
}

QString CB::getKernelVersion() const
{
    return kernelVersion;
}

