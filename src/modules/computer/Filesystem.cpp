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
 
 
#include "Computer.h"
#include "Util.h"
#include <QTextStream>
#include <sys/vfs.h>

Computer::FileSystem::FileSystem()
{
}

Computer::FileSystem::FileSystem(const QString& filesystem, const QString& device, const QString& mountPoint,
                                 const QStringList& mountFlags, const double size, const double used, const double available) :
                                 _filesystem(filesystem), _device(device), _mountPoint(mountPoint), _mountFlags(mountFlags),
                                 _size(size), _used(used), _available(available)
{
}

QVector<Computer::FileSystem> Computer::FileSystem::getFileSystems()
{
    QByteArray out = getOutputConsole("cat /etc/mtab");
    QTextStream stream(&out);
    QVector<FileSystem> filesystems;
    QStringList line;
    struct statfs sfs;
    while(!stream.atEnd())
    {
        line = stream.readLine().split(' ');
        QString device = line[0], mountPoint = line[1], filesystem = line[2];
        QStringList mountFlags = line[3].split(',');
        double size = 0.0, used = 0.0, available = 0.0;
        if(!statfs(mountPoint.toStdString().c_str(), &sfs))
        {
            size = static_cast<double>(sfs.f_bsize * sfs.f_blocks);
            available = static_cast<double>(sfs.f_bsize * sfs.f_bavail);
            used = size - available;
        }
        filesystems.push_back(FileSystem(filesystem, device, mountPoint, mountFlags, size, used, available));
    }
    return filesystems;
}

