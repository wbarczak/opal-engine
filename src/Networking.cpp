#include <cstdint>
#include "Networking.hpp"

static bool s_IsBigEndian = false;

void Networking::detectEndian()
{
	uint16_t x = 1;
	uint8_t* y = reinterpret_cast<uint8_t*>(&x);
	s_IsBigEndian = *y ^ 1;
}

bool Networking::isBigEndian() { return s_IsBigEndian; }