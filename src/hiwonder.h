#ifndef __HIWONDER_H__
#define __HIWONDER_H__

#include <SerialStream.h>
#include <SerialPort.h>
#include <string>

#include "servo_commands.h"
#include "comms_handler.h"
namespace hiwonder_servo
{
    class HiwonderServoController
    {
    public:
        HiwonderServoController(std::string _portname);
        ~HiwonderServoController();

        void moveToPos(int busid, double angle, int msec);
        void moveToPosWait(int busid, double angle, int msec);
        void moveStart(int busid);
        void moveStop(int busid);

        double readPos(int busid);

        void setBrake(int busid, bool brake);

        void setLED(int busid, bool led);
        void setRange(int busid, double minangle, double maxangle);

    private:
        // LibSerial::SerialStream *serialStream;
        LibSerial::SerialPort *serialPort;
        std::string portName;

        // void setTX();
        // void setRX();

        void writeBus(LibSerial::DataBuffer &data);
        void readRBus(LibSerial::DataBuffer &data);

        unsigned int angleToServoPos(double angle);
        unsigned char getCheckSum(LibSerial::DataBuffer &data);

        void buildPacket(LibSerial::DataBuffer &data, enum SERVO_CMD cmd, int busid);

    }; // end class HiwonderServoController
} // end namespace hiwonder_servo
void foo();

#endif // __HIWONDER_H__
