#include <QHash>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>
#include "Computer.h"

#define CM Computer::MemoryInfo

const QVector<QString> CM::nameProperties =
{
    "MemTotal","MemFree","MemAvailable","Buffers","Cached","SwapCached","Active","Inactive",
    "Active(anon)","Inactive(anon)","Active(file)","Inactive(file)","Unevictable","Mlocked","SwapTotal",
    "SwapFree","Dirty","Writeback","AnonPages","Mapped","Shmem","Slab","SReclaimable","SUnreclaim",
    "KernelStack","PageTables","NFS_Unstable","Bounce","WritebackTmp","CommitLimit","Committed_AS",
    "VmallocTotal","VmallocUsed","VmallocChunk","HardwareCorrupted","AnonHugePages","CmaTotal","CmaFree",
    "HugePages_Total","HugePages_Free","HugePages_Rsvd","HugePages_Surp","Hugepagesize","DirectMap4k","DirectMap2M"
};

CM::MemoryInfo()
{
//    int total, used, free, cached;
//    double ratio;
    _update();
}

void Computer::MemoryInfo::_update()
{
    std::ifstream in("/proc/meminfo");
    if(in.is_open())
    {
        QStringList splittedBuffer;
        std::string inputStr;
        while(std::getline(in, inputStr) && inputStr != "")
        {
            splittedBuffer = QString(inputStr.c_str()).split(':');
            for(auto& x : splittedBuffer)
            {
                x = x.trimmed();
            }
            splittedBuffer[1].chop(3);
            const QString& property = splittedBuffer[0];
            int val = splittedBuffer[1].toInt();
            values.insert(property, val);
        }
    }
    in.close();

}
