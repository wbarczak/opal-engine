#include <bitset>
#include "Window.hpp"

#include "RayCore.hpp"

void Window::init(int32_t width, int32_t height, const char* name)
{
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(width, height, name);
	SetWindowState(FLAG_WINDOW_RESIZABLE);
}

void Window::close() { CloseWindow(); }
bool Window::shouldClose() { return WindowShouldClose(); }
int32_t Window::getWidth() { return GetScreenWidth(); }
int32_t Window::getHeight() { return GetScreenHeight(); }