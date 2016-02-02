#include <QProcess>
#include <QString>
#include <QByteArray>
#include <QStringList>
#include "Util.h"


QByteArray getOutputConsole(const QString& arg)
{
    QProcess process;
    process.start("/bin/sh", QStringList() << "-c" << arg);
    process.waitForFinished();
    QByteArray array = process.readAll();
    if(array.isEmpty())
    {
        return "Unknown";
    }
    return array;
}

QString getLineOfString(const QString &str, int number)
{
    QStringList list = str.split('\n');
    if(number >= list.size())
    {
        return "Error";
    }
    return list[number];
}
