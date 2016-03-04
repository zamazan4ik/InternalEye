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
