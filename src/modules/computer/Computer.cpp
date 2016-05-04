#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include "Util.h"
#include "Computer.h"

Computer::Computer()
{
    _getEnvVariables();
    //boots       = Boot::getBoots();//TODO : Crash here
    users       = User::getUsers();
    groups      = Group::getGroups();
    modules     = Module::getModules();
    filesystems = FileSystem::getFileSystems();
    languages   = Language::getLanguages();
}

void Computer::_getEnvVariables()
{
    QByteArray output = getOutputConsole("printenv");
    QTextStream stream(&output);
    QStringList list;
    while(!stream.atEnd())
    {
        list = stream.readLine().split('=');
        env.push_back({list[0], list[1]});
    }
}
