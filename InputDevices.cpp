#include <QString>
#include <QByteArray>
#include "Util.h"
#include "Devices.h"

#define DI Devices::InputDevices
#define DII DI::InputDevice

DII::InputDevice()
{
}

DII::InputDevice(const QString &name_, const QString &connectedTo_, const int bus_, const int vendor_,
                 const int product_, const int version_, const DII::TypeOfInputDevice type_) : name(name_),
                 connectedTo(connectedTo_), bus(bus_), vendor(vendor_), product(product_), version(version_),
                 type(type_)
{
}

void DI::_update()
{
    QByteArray arr = getOutputConsole("/proc/bus/input/devices");
    if(arr.isEmpty())
    {
        return;
    }

}


