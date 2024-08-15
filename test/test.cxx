#include <signal.h>

#include "hiwonder.h"

using namespace hiwonder_servo;

HiwonderServoController *bus;

void handle_sigint(int a)
{
	printf("Caught ctrl-c\n");
	delete bus;
	exit;
}

int main()
{
	try
	{
		bus = new HiwonderServoController("/dev/ttyTHS0");

		signal(SIGINT, handle_sigint);
		// bus->moveToPos(3, 120, 500);
		bus->readPos(3);
		// bus.setLED(3, true);
		// bus.moveToPosWait(1, 180, 10);
		// bus.moveStart(3);
		// bus.moveStop(5);
		// bus.setBrake(10, true);
		// bus.setLED(20, false);
	}
	catch (const std::runtime_error &e)
	{
		printf("Error: %s\n", e.what());
	}

	delete bus;
	// foo();
}
