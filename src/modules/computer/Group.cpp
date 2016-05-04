#include <QTextStream>
#include "Computer.h"
#include "Util.h"

#define CG Computer::Group

CG::Group()
{
}

CG::Group(const QString& name, const int id, const QStringList& members) :
          _name(name), _id(id), _members(members)
{
}

QVector<Computer::Group> CG::getGroups()
{
    QByteArray out = getOutputConsole("cat /etc/group");
    QTextStream stream(&out);
    QStringList line;
    QVector<Group> groups;
    while(!stream.atEnd())
    {
        line = stream.readLine().split(':');
        QString     name    = line[0];
        int         id      = line[2].toInt();
        QStringList members = line[3].split(',');
        groups.push_back(Group(name, id, members));
    }
    return groups;
}
