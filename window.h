#pragma once
#include <glut.h>
class Window
{
public:
	int width;
	int height;
	int x;
	int y;
	const char* name;
	Window();
	Window(int curWidth, int curHeight, int curX, int curY, const char* curName);
	~Window();
	void initilization();
};


