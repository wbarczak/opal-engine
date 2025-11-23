#include <cstdint>
#include "Game.hpp"
#include "Core.hpp"

int32_t main(int32_t argc, char** argv)
{
	Game::init();
	Game::loop();
	Game::cleanup();
}