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
 
 
#include <QHash>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>
#include "Devices.h"

#define DM Devices::MemoryInfo

const QVector<QString> DM::nameProperties =
{
    "MemTotal","MemFree","MemAvailable","Buffers","Cached","SwapCached","Active","Inactive",
    "Active(anon)","Inactive(anon)","Active(file)","Inactive(file)","Unevictable","Mlocked","SwapTotal",
    "SwapFree","Dirty","Writeback","AnonPages","Mapped","Shmem","Slab","SReclaimable","SUnreclaim",
    "KernelStack","PageTables","NFS_Unstable","Bounce","WritebackTmp","CommitLimit","Committed_AS",
    "VmallocTotal","VmallocUsed","VmallocChunk","HardwareCorrupted","AnonHugePages","CmaTotal","CmaFree",
    "HugePages_Total","HugePages_Free","HugePages_Rsvd","HugePages_Surp","Hugepagesize","DirectMap4k","DirectMap2M"
};

DM::MemoryInfo()
{
//    int total, used, free, cached;
//    double ratio;
    _update();
}

void DM::_update()
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
