#include "Window.h"


Window::Window()
{
	width = 600;
	height = 600;
	x = 200;
	y = 100;
	name = "My proggram";
}
Window::Window(int curWidth = 600, int curHeight = 600, int curX = 200, int curY = 100, const char* curName = "My programm")
{
	width = curWidth;
	height = curHeight;
	x = curX;
	y = curY;
	name = curName;
}


Window::~Window()
{
}

void Window::initilization()
{
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x, y);
	glutCreateWindow(name);
}
