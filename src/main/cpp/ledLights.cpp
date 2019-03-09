#include <frc/I2C.h>
#include <ledLights.hpp>
#include <string>
#include <array>

using namespace frc;
using namespace std;

LedLights::LedLights() 
{
	uint8_t tx[100];
	tx[0] = 'g';
	tx[1] = 'o';
	tx[2] = 0;

	uint8_t rx[100];
	Wire->Transaction(tx, 3, rx, 0);
}
