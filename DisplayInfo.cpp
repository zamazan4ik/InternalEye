#include "Computer.h"
#include "Util.h"
#include <QTextStream>
#include <QDebug>

Computer::DisplayInfo::DisplayInfo()
{
    _update();
}

void Computer::DisplayInfo::_update()
{
    _getGLXinfo();
//    _getX11info();
}

void Computer::DisplayInfo::update()
{
    _update();
}

void Computer::DisplayInfo::_getGLXinfo()
{
    QByteArray out = getOutputConsole("glxinfo");
    QTextStream stream(&out);
    QString line;
    oglVendor = oglRenderer = oglVersion = "Unknown";
    dri = false;
    while(!stream.atEnd())
    {
        line = stream.readLine();
        if(line.indexOf("OpenGL vendor string") != -1)          oglVendor   = line.split(':').at(1).trimmed();
        else if(line.indexOf("OpenGL renderer string") != -1)   oglRenderer = line.split(':').at(1).trimmed();
        else if(line.indexOf("OpenGL version string") != -1)    oglVersion  = line.split(':').at(1).trimmed();
        else if(line.indexOf("direct rendering: Yes") != -1)    dri = true;
    }
}


//QString displayName, vendor, version,
//        extensions, monitors;
//QSize size;
void Computer::DisplayInfo::_getX11info()
{

}

