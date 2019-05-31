#include "Menu.h"
#include <glut.h>
#include <cmath>

ifstream indata("menu.txt");
int sizeElem = 20;

Menu::Menu(string curName, int curX, int curY, vector <Menu*> curSubMenu, Menu* curParent)
{
	name = curName;
	x = curX;
	y = curY;
	subMenu = curSubMenu;
	parent = curParent;
}


Menu::~Menu()
{
	for (auto &elem: subMenu) {
		delete elem;
	}
}

istream& operator >> (istream& is, Element& el) {
	Element new_el;
	if (is >> ws
		&& getline(is, new_el.label, ' ')
		&& is >> new_el.level >> new_el.x >> new_el.y) {
		el = new_el;
	}
	return is;
}

void Menu::GetMenu() {
	Element curElem;
	Menu *currentParent = this;
	int curLevel = 0;
	while (indata >> curElem) {
		if (curElem.level < curLevel) {
			int diff = curLevel - curElem.level;
			for (int i = 0; i < diff; ++i) {
				currentParent = currentParent->parent;
				--curLevel;
			}
		} else if (curElem.level > curLevel) {
			currentParent = currentParent->subMenu.back();
			++curLevel;
		}
		Menu *newElem = new Menu(curElem.label, curElem.x, curElem.y, {}, currentParent);
		currentParent->subMenu.push_back(newElem);
	}
}

void TextOut(string str, int x, int y)
{
	glRasterPos2i(x, y);
	for (auto &c : str) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
	}
}
void Menu::DrawMenu() {
	for (auto &elem : subMenu) {
		glBegin(GL_LINE_LOOP);
		glLineWidth(5.0);
		glColor3f(0.5, 0.5, 0.5);
		glVertex2f(elem->x, elem->y);
		glVertex2f(elem->x + sizeElem, elem->y);
		glVertex2f(elem->x + sizeElem, elem->y + sizeElem);
		glVertex2f(elem->x, elem->y + sizeElem);
		glEnd();
		TextOut(elem->name, elem->x + sizeElem / 2 - elem->name.size()/2, elem->y + sizeElem / 2);
	}
}
void Menu::DrawSelection() {
	int x = this->selected->x;
	int y = this->selected->y;
	string label = this->selected->name;
	glBegin(GL_LINE_LOOP);
	glLineWidth(5.0);
	glColor3f(1, 0, 0);
	glVertex2f(x, y);
	glVertex2f(x + sizeElem, y);
	glVertex2f(x + sizeElem, y + sizeElem);
	glVertex2f(x, y + sizeElem);
	glEnd();
	TextOut(label, x + sizeElem / 2 - label.size() / 2, y + sizeElem / 2);
}