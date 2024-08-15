#include <cactus_rt/rt.h>
#include <chrono>

#include "comms_handler.h"

using namespace LibSerial;
using namespace hiwonder_servo;
using namespace GPIO;

CommsHandlerThread::CommsHandlerThread(std::string portname, BaudRate rate, cactus_rt::ThreadConfig config)
    : Thread("CommandHandlerThread", config)
{
    return;
}

void CommsHandlerThread::Run()
{
    while (!this->StopRequested())
    {
    }
}

void CommsHandlerThread::setPort(std::string portname)
{
}

void CommsHandlerThread::setBaud(BaudRate rate)
{
}

void CommsHandlerThread::write(std::array<uint8_t, 20> data)
{
    // Copy the data into our buffer, so we own it.
    std::copy_n(data_buffer.begin(), data_buffer.size(), data.begin());
    return;
}

std::array<uint8_t, 20> &CommsHandlerThread::read()
{
    return data_buffer;
}

void CommsHandlerThread::stop()
{
    runloop = false;
}

void CommsHandlerThread::worker_loop()
{
    while (runloop)
    {
    }
    return;
}

// Set the pins for transmission
void CommsHandlerThread::setTX()
{
    // std::cout << "setTX called" << std::endl;
    // std::cout.flush();
    GPIO::output(RX_CON_PIN, GPIO::LOW);
    GPIO::output(TX_CON_PIN, GPIO::HIGH);
}

// Set the pins for reception
void CommsHandlerThread::setRX()
{
    // std::cout << "setRX called" << std::endl;
    // std::cout.flush();
    GPIO::output(RX_CON_PIN, GPIO::HIGH);
    GPIO::output(TX_CON_PIN, GPIO::LOW);
}
