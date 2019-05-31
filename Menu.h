#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdarg>

using namespace std;

struct Element{
	string label;
	int level;
	int x;
	int y;
};

void TextOut(string str, int x, int y);

class Menu
{
public:
	Menu(string curName, int curX, int curY, vector <Menu*> curSubMenu, Menu *curParent);
	~Menu();
	void GetMenu(); 
	void DrawMenu();
	void DrawSelection();
	vector <Menu*> GetSubMenu() { return subMenu; };
	Menu* GetParent() { return parent; };
	Menu* selected;
private:
	Menu* parent;
	string name;
	int x;
	int y;
	vector <Menu*> subMenu;
};