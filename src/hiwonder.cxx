#include <algorithm>
#include <iostream>

#include <cmath>
#include <iomanip>

#include <chrono>
#include <thread>

#include "hiwonder.h"

// using namespace LibSerial ;
using namespace hiwonder_servo;
// using namespace GPIO;

std::map<enum SERVO_CMD, servoCmd> servoCommands{
	{MOVE_TIME_WRITE, {1, 7, 0}},
	{MOVE_TIME_READ, {2, 3, 7}},
	{MOVE_TIME_WAIT_WRITE, {7, 7}},
	{MOVE_TIME_WAIT_READ, {8, 3, 7}},
	{MOVE_START, {11, 3, 0}},
	{MOVE_STOP, {12, 3, 0}},
	{ID_WRITE, {13, 4, 0}},
	{ID_READ, {14, 3, 4}},
	{ANGLE_OFFSET_ADJUST, {17, 4, 0}},
	{ANGLE_OFFSET_WRITE, {18, 3, 0}},
	{ANGLE_OFFSET_READ, {19, 3, 4}},
	{ANGLE_LIMIT_WRITE, {20, 7, 0}},
	{ANGLE_LIMIT_READ, {21, 3, 7}},
	{VIN_LIMIT_WRITE, {22, 7, 0}},
	{VIN_LIMIT_READ, {23, 3, 7}},
	{TEMP_MAX_LIMIT_WRITE, {24, 4, 0}},
	{TEMP_MAX_LIMIT_READ, {25, 3, 4}},
	{TEMP_READ, {26, 3, 4}},
	{VIN_READ, {27, 3, 5}},
	{POS_READ, {28, 3, 5}},
	{CMD_OR_MOTOR_MODE_WRITE, {29, 7, 0}},
	{CMD_OR_MOTOR_MODE_READ, {30, 3, 7}},
	{LOAD_OR_UNLOAD_WRITE, {31, 4, 0}},
	{LOAD_OR_UNLOAD_READ, {32, 3, 4}},
	{LED_CTRL_WRITE, {33, 4, 0}},
	{LED_CTRL_READ, {34, 3, 4}},
	{LED_ERROR_WRITE, {35, 4, 0}},
	{LED_ERROR_READ, {36, 3, 4}},
};

// Public functions

HiwonderServoController::HiwonderServoController(std::string _portname)
{
	portName = _portname;

	// cactus_rt::ThreadConfig commsHandlerThreadConfig;
	// auto commsHandler = new CommsHandlerThread(portName, LibSerial::BaudRate::BAUD_115200, commsHandlerThreadConfig);

	// serialPort = new SerialPort(portName, BaudRate::BAUD_115200);
	// serialPort->SetSerialPortBlockingStatus(true);
	// serialStream = new SerialStream(portName);
	//
	// This is a fixed rate
	// serialStream->SetBaudRate(BaudRate::BAUD_115200);
	// GPIO::setmode(GPIO::BCM);
	// GPIO::setup(RX_CON_PIN, GPIO::OUT, GPIO::LOW);  // Configure RX_CON as GPIO17 as output
	// GPIO::setup(TX_CON_PIN, GPIO::OUT, GPIO::HIGH); // Configure TX_CON as GPIO27 as output
}

HiwonderServoController::~HiwonderServoController()
{
	std::cout << "Destructor called" << std::endl;
	std::cout.flush();

	// serialPort->Close();
	// serialStream->Close();
	// GPIO::output(RX_CON_PIN, GPIO::HIGH);
	// GPIO::output(TX_CON_PIN, GPIO::LOW);

	// GPIO::cleanup();

	// delete serialPort;
	// delete serialStream;
}

void HiwonderServoController::moveToPos(int busid, double angle, int msec)
{
	angle = std::clamp(angle, 0.0, 240.0);
	msec = std::clamp(msec, 0, 30000);

	std::vector<unsigned char> data;
	buildPacket(data, MOVE_TIME_WRITE, busid);

	// Conmvert angle to a Hiwonder servo position
	unsigned int servoPos = angleToServoPos(angle);
	data[5] = (unsigned char)(servoPos & 0xFF);
	data[6] = (unsigned char)(servoPos >> 8 & 0xFF);

	// Break up the time in msec
	data[7] = (unsigned char)(msec & 0xFF);
	data[8] = (unsigned char)(msec >> 8 & 0xFF);

	data[9] = getCheckSum(data);

	writeBus(data);
}

void HiwonderServoController::moveToPosWait(int busid, double angle, int msec)
{
	angle = std::clamp(angle, 0.0, 240.0);
	msec = std::clamp(msec, 0, 30000);

	std::vector<unsigned char> data;
	buildPacket(data, MOVE_TIME_WAIT_WRITE, busid);

	// Conmvert angle to a Hiwonder servo position
	unsigned int servoPos = angleToServoPos(angle);
	data[5] = (unsigned char)(servoPos & 0xFF);
	data[6] = (unsigned char)(servoPos >> 8 & 0xFF);

	// Break up the time in msec
	data[7] = (unsigned char)(msec & 0xFF);
	data[8] = (unsigned char)(msec >> 8 & 0xFF);

	data[9] = getCheckSum(data);

	writeBus(data);
}

void HiwonderServoController::moveStart(int busid)
{
	std::vector<unsigned char> data;
	buildPacket(data, MOVE_START, busid);

	data[5] = getCheckSum(data);

	writeBus(data);
}

void HiwonderServoController::moveStop(int busid)
{
	std::vector<unsigned char> data;
	buildPacket(data, MOVE_STOP, busid);

	data[5] = getCheckSum(data);

	writeBus(data);
}

double HiwonderServoController::readPos(int busid)
{
	std::vector<unsigned char> data;
	buildPacket(data, POS_READ, busid);
	data[5] = getCheckSum(data);

	writeBus(data);
	std::this_thread::sleep_for(std::chrono::microseconds(340));

	// data.resize(servoCommands[POS_READ].reply_length + 3);
	readRBus(data);

	return 0.0;
}

void HiwonderServoController::setBrake(int busid, bool brake)
{
	std::vector<unsigned char> data;
	buildPacket(data, LOAD_OR_UNLOAD_WRITE, busid);

	data[5] = brake ? 1 : 0;
	data[6] = getCheckSum(data);

	writeBus(data);
}

void HiwonderServoController::setLED(int busid, bool led)
{
	std::vector<unsigned char> data;
	buildPacket(data, LED_CTRL_WRITE, busid);

	data[5] = led ? 1 : 0;
	data[6] = getCheckSum(data);

	writeBus(data);
}

void HiwonderServoController::setRange(int busid, double minangle, double maxangle)
{
	return;
}

// Private functions

// Set the pins for transmission
// void HiwonderServoController::setTX()
// {
// 	// std::cout << "setTX called" << std::endl;
// 	// std::cout.flush();
// 	// GPIO::output(RX_CON_PIN, GPIO::LOW);
// 	// GPIO::output(TX_CON_PIN, GPIO::HIGH);
// }

// Set the pins for reception
// void HiwonderServoController::setRX()
// {
// 	// std::cout << "setRX called" << std::endl;
// 	// std::cout.flush();
// 	// GPIO::output(RX_CON_PIN, GPIO::HIGH);
// 	// GPIO::output(TX_CON_PIN, GPIO::LOW);
// }

// Write to the servo bus
void HiwonderServoController::writeBus(std::vector<unsigned char> &data)
{
	// setTX();
	// std::cout << "TX: ";
	// for (unsigned char & i: data)
	// 	std::cout << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)i << " ";
	// std::cout << std::endl;
	// std::cout.flush();

	// serialStream->write(reinterpret_cast<char *>(data.data()), data.size());
	// serialStream->flush();

	// serialPort->Write(data);
	// serialPort->DrainWriteBuffer();
	return;
}

// Read from the servo bus
void HiwonderServoController::readRBus(std::vector<unsigned char> &data)
{
	// setRX();
	// std::cout << "RX: ";
	// serialStream->read(reinterpret_cast<char *>(data.data()), data.size());
	// for (unsigned char & i: data)
	// 	std::cout << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)i << " ";
	// std::cout << std::endl;
	// std::cout.flush();
}

unsigned int HiwonderServoController::angleToServoPos(double angle)
{
	return (unsigned int)std::clamp(round(angle / 0.24), 0.0, 1000.0);
}

unsigned char HiwonderServoController::getCheckSum(std::vector<unsigned char> &data)
{

	unsigned char checksum = 0;

	if (data.size() < 3)
		return 0;

	for (int i = 2; i < data.size() - 1; i++)
	{
		checksum += data[i];
	}

	return ~checksum;
}

void HiwonderServoController::buildPacket(std::vector<unsigned char> &data, enum SERVO_CMD cmd, int busid)
{
	data.resize(servoCommands[cmd].cmd_length + 3);
	data[0] = SERVO_CMD_HEADER;
	data[1] = SERVO_CMD_HEADER;
	data[2] = (unsigned char)(busid & 0xFF);
	data[3] = servoCommands[cmd].cmd_length;
	data[4] = servoCommands[cmd].cmd;
	return;
}

void foo()
{
	printf("hello world\n");
	printf("MOVE_TIME_WRITE: cmd: %d, length: %d\n", servoCommands[MOVE_TIME_WRITE].cmd, servoCommands[MOVE_TIME_WRITE].cmd_length);
}
