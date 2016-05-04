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

