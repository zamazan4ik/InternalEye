//#include "hardinfo.h"
//#include "computer.h"

//MemoryInfo *
//computer_get_memory(void)
//{
//    MemoryInfo *mi;
//    FILE *procmem;
//    gchar buffer[128];

//    procmem = fopen("/proc/meminfo", "r");
//    if (!procmem)
//	return NULL;
//    mi = g_new0(MemoryInfo, 1);

//    while (fgets(buffer, 128, procmem)) {
//	gchar **tmp = g_strsplit(buffer, ":", 2);

//	tmp[0] = g_strstrip(tmp[0]);
//	tmp[1] = g_strstrip(tmp[1]);

//	get_int("MemTotal", mi->total);
//	get_int("MemFree", mi->free);
//	get_int("Cached", mi->cached);

//	g_strfreev(tmp);
//    }
//    fclose(procmem);

//    mi->used = mi->total - mi->free;

//    mi->total  /= 1000;
//    mi->cached /= 1000;
//    mi->used   /= 1000;
//    mi->free   /= 1000;

//    mi->used -= mi->cached;
//    mi->ratio = 1 - (gdouble) mi->used / mi->total;

//    return mi;
//}

#include <QHash>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include "Computer.h"

#define CM Computer::MemoryInfo

const QHash<QString, std::function<void(CM&, int)> > CM::transform =
{
    {"MemTotal", &CM::_setTotal},
    {"MemFree" , &CM::_setFree},
    {"Cached"  , &CM::_setCached}
};

CM::MemoryInfo()
{
//    int total, used, free, cached;
//    double ratio;
}

void CM::_setCached(int value)
{
    cached = value;
}

void CM::_setFree(int value)
{
    free = value;
}

void CM::_setTotal(int value)
{
    total = value;
}

void Computer::MemoryInfo::_update()
{
    QFile file("/proc/meminfo");
    if(file.exists() && file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QStringList splittedBuffer;
        while(!stream.atEnd())
        {
            splittedBuffer =  QString(stream.readLine()).split(':');
            for(auto& x : splittedBuffer)
            {
                x = x.trimmed();
            }
            splittedBuffer[1].chop(2);
            const QString& property = splittedBuffer[0];
            int val = splittedBuffer[1].toInt();
            transform[property](*this, val);
        }
    }
    file.close();
    used = total - free;

    total  /= 1000;
    cached /= 1000;
    used   /= 1000;
    free   /= 1000;

    used -= cached;
    ratio = 1 - (double) used / total;
}
