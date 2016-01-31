#include <fstream>
#include <string>
#include <QDebug>
#include "Computer.h"

#define CL Computer::LoadInfo

CL::LoadInfo()
{
    _update();
}

double CL::getLoad1() const
{
    return load1;
}

double CL::getLoad5() const
{
    return load5;
}

double CL::getLoad15() const
{
    return load15;
}

int CL::getWorkEnt() const
{
    return workEntities;
}

int CL::getAllEnt() const
{
    return allEntities;
}

int CL::getMostRunPID() const
{
    return mostRunPID;
}

void CL::_update()
{
    std::ifstream in("/proc/loadavg");
    if(!in.is_open())
    {
        return;
    }
    in >> load1 >> load5 >> load15;
    in >> workEntities;
    in.get();
    in >> allEntities >> mostRunPID;
}
