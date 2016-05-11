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
 
 
#ifndef DEVICES_H
#define DEVICES_H

#include <QString>
#include <QVector>
#include <QHash>
#include <QVariant>

class Devices
{
private:
    class Sensors
    {
    private:
        class Sensor
        {
        private:
            QString name;
            int temperature;
            virtual void _update();
        public:
            QString getName() const;
            int getTemp() const;
        };

        class DriveSensor : public Sensor
        {
        private:
            void _update();
        };
        class CPUSensor : public Sensor
        {
        private:
            void _update();
        };
        class VideoSensor : public Sensor
        {
        private:
            void _update();
        };
    };
    class Resources
    {

    };
    class InputDevices
    {
    private:
        class InputDevice
        {
        public:
            enum TypeOfInputDevice {KEYBOARD, MOUSE, JOYSTICK, PCSPKR, UNKNOWN};
        private:
            TypeOfInputDevice type;
            QString name, connectedTo;
            int bus, vendor, product, version;
        public:
            InputDevice();
            InputDevice(const QString& name_, const QString& connectedTo_, const int bus_, const int vendor_,
                        const int product_, const int version_, const TypeOfInputDevice type_);
        };
        void _update();

        QVector<InputDevice> devices;
    public:

    };

    class MemoryInfo
    {
        //TODO : Add ENUM interface for MemoryInfo class
    private:
        QString TypeValue;
        static const QVector<QString> nameProperties;
        QHash<QString, QVariant> values;

        void _update();
    public:
        MemoryInfo();
    };
public:
    Devices();
};

#endif // DEVICES_H
