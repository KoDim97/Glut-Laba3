#include <cstdlib>
#include <glut.h>
#include "Menu.h"
#include "window.h"

#define COLUMNS 100
#define ROWS 100
#define FPS 30

int position = 0;
int prevPosition = 0;
Menu *root = new Menu("root", 0, 0, {}, NULL);
Menu *currentMenu = root;

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	currentMenu->DrawMenu();
	currentMenu->DrawSelection();
	glutSwapBuffers();
}

void Reshape(int curWidth, int CurHeight)
{
	glViewport(0, 0, (GLsizei)curWidth, (GLsizei)CurHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, COLUMNS, ROWS, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}
void Timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, Timer, 0);
}

void Keyboard(int key, int, int) {
	Menu* temp;
	switch (key)
	{
	case GLUT_KEY_UP:
		if (!currentMenu->GetParent()) {
			break;
		}
		position = prevPosition;
		currentMenu = currentMenu->GetParent();
		currentMenu->selected = currentMenu->GetSubMenu()[position];
		break;
	case GLUT_KEY_DOWN:
		if (currentMenu->selected->GetSubMenu().empty()) {
			break;
		}
		prevPosition = position;
		position = 0;
		currentMenu = currentMenu->selected;
		currentMenu->selected = currentMenu->GetSubMenu()[position];
		break;
	case GLUT_KEY_RIGHT:
		if (position < (currentMenu->GetSubMenu().size() - 1)) {
			position++;
		}
		currentMenu->selected = currentMenu->GetSubMenu()[position];
		break;
	case GLUT_KEY_LEFT:
		if (position > 0) {
			position--;
		}
		currentMenu->selected = currentMenu->GetSubMenu()[position];
		break;
		break;
	default:
		break;
	}
}

void Initialize() {
	glClearColor(1.0, 1.0, 1.0, 1.0);

}
int main(int argc, char ** argv) {
	currentMenu->GetMenu();
	currentMenu->selected = currentMenu->GetSubMenu()[position];
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	Window curWindow(800, 800, 400, 200, "The second glut project");
	curWindow.initilization();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutTimerFunc(0, Timer, 0);
	glutSpecialFunc(Keyboard);
	Initialize();
	glutMainLoop();
	delete root;
	return 0;
}