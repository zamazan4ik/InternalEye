#include <QTextStream>
#include "Util.h"
#include "Computer.h"

void Computer::_getEnvVariables()
{
    QByteArray output = getOutputConsole("printenv");
    QTextStream stream(&output);
    QStringList list;
    while(!stream.atEnd())
    {
        list = stream.readLine().split('=');
        env.push_back({list.at(0), list.at(1)});
    }
}
