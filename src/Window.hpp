#pragma once

#include <cstdint>
#include "Core.hpp"

namespace Window
{
	void init(int32_t width, int32_t height, const char* name);
	void close();
	bool shouldClose();
	int32_t getWidth();
	int32_t getHeight();
}