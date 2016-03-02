#include "Computer.h"
#include "Util.h"
#include <QTextStream>

Computer::Module::Module()
{
}

Computer::Module::Module(const QString& name, const QStringList& author, const QString& description, const QString& license,
                         const QStringList& depends, const QString& versionMagic, const QString& path, const QStringList& usedBy,
                         const double size) : _name(name), _author(author), _description(description), _license(license),
                         _depends(depends), _versionMagic(versionMagic), _path(path), _usedBy(usedBy), _size(size)
{
}

QVector<Computer::Module> Computer::Module::getModules()
{
    QByteArray out = getOutputConsole("lsmod");
    QTextStream stream(&out);
    QStringList line;
    QVector<Module> modules;
    stream.readLine();//erase first line
    while(!stream.atEnd())
    {
        line = stream.readLine().split(" ", QString::SkipEmptyParts);
        QString name        = line[0];
        QStringList usedBy  = line.size() >= 4 ? line[3].split(',') : QStringList();
        double size         = line[1].toInt() / 1024.0;

        QByteArray modinfo = getOutputConsole("modinfo " + name);
        QTextStream streamMod(&modinfo);
        QStringList modLine, author, depends;
        QString description, license, versionMagic, path;
        while(!streamMod.atEnd())
        {
            modLine = streamMod.readLine().split(':');
            if(modLine.size() != 2) continue;
            QString first = modLine[0], second = modLine[1].trimmed();
            if     (first == "author")      author.push_back(second);
            else if(first == "description") description = second;
            else if(first == "license")     license = second;
            else if(first == "depends")     depends.push_back(second);
            else if(first == "vermagic")    versionMagic = second;
            else if(first == "filename")    path = second;
        }
        modules.push_back(Module(name, author, description, license, depends,
                                 versionMagic, path, usedBy, size));
    }
    return modules;
}
