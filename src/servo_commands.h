#ifndef __SERVO_COMMANDS_H__
#define __SERVO_COMMANDS_H__

#include <map>

namespace hiwonder_servo
{
    const unsigned char SERVO_CMD_HEADER = 0x55;

    enum SERVO_CMD 
    {
        MOVE_TIME_WRITE,
        MOVE_TIME_READ,
        MOVE_TIME_WAIT_WRITE,
        MOVE_TIME_WAIT_READ,
        MOVE_START,
        MOVE_STOP,
        ID_WRITE,
        ID_READ,
        ANGLE_OFFSET_ADJUST,
        ANGLE_OFFSET_WRITE,
        ANGLE_OFFSET_READ,
        ANGLE_LIMIT_WRITE,
        ANGLE_LIMIT_READ,
        VIN_LIMIT_WRITE,
        VIN_LIMIT_READ,
        TEMP_MAX_LIMIT_WRITE,
        TEMP_MAX_LIMIT_READ,
        TEMP_READ,
        VIN_READ,
        POS_READ,
        CMD_OR_MOTOR_MODE_WRITE,
        CMD_OR_MOTOR_MODE_READ,
        LOAD_OR_UNLOAD_WRITE,
        LOAD_OR_UNLOAD_READ,
        LED_CTRL_WRITE,
        LED_CTRL_READ,
        LED_ERROR_WRITE,
        LED_ERROR_READ
    };

    class servoCmd {
        public: 
            unsigned char cmd;
            unsigned char cmd_length;
            unsigned char reply_length;
    };
}

#endif // __SERVO_COMMANDS_H__