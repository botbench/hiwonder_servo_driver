#include <cactus_rt/rt.h>
#include <array>

#include <SerialPort.h>
#include <JetsonGPIO.h>

using cactus_rt::App;
using cactus_rt::Thread;

namespace hiwonder_servo
{

    class CommsHandlerThread : public Thread
    {
    public:
        CommsHandlerThread(std::string portname, LibSerial::BaudRate rate, cactus_rt::ThreadConfig config);
        ~CommsHandlerThread();

        void setPort(std::string portname);
        void setBaud(LibSerial::BaudRate rate);
        void write(std::array<uint8_t, 20> data);
        std::array<uint8_t, 20> &read();
        void stop();

    private:
        const int RX_CON_PIN = 17;
        const int TX_CON_PIN = 27;

        LibSerial::SerialPort *serialPort;
        std::string portName;
        cactus_rt::mutex mutex_buffer;
        std::array<uint8_t, 20> data_buffer;
        bool runloop;

        void worker_loop();
        inline void setRX();
        inline void setTX();

    protected:
        void Run() final;
    };

} // end namespoace hiwonder_servo