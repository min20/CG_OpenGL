#include <Windows.h>
#include <gl/glut.h>
#include <math.h>

void ChangeSize(int w, int h);
void ControlKey(int keyboardInput, int x, int y);
void Initialize();

GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

void RenderScene() {
	GLfloat length = 50.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glShadeModel(GL_SMOOTH);

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(length, length, -length);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-length, length, -length);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-length, -length, -length);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(length, -length, -length);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(length, length, -length);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(length, -length, -length);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(length, -length, length);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(length, length, length);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(length, length, -length);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(length, length, length);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-length, length, length);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-length, length, -length);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-length, -length, length);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-length, -length, -length);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-length, length, -length);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-length, length, length);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-length, -length, length);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(length, -length, length);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(length, -length, -length);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-length, -length, -length);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-length, -length, length);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-length, length, length);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(length, length, length);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(length, -length, length);
	glEnd();
		
	glPopMatrix();
	glutSwapBuffers();
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("hw-3 RainbowBox");

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(ControlKey);
	Initialize();
	glutMainLoop();
}

void ChangeSize(int w, int h) {
	// Perspective
	GLfloat fAspect;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(50.0f, fAspect, 1.0f, 600.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -300.0f);
}

void ControlKey(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		xRot -= 3.0f;
	}
	if (key == GLUT_KEY_DOWN) {
		xRot += 3.0f;
	}
	if (key == GLUT_KEY_LEFT) {
		yRot -= 3.0f;
	}
	if (key == GLUT_KEY_RIGHT) {
		yRot += 3.0f;
	}

	glutPostRedisplay();
}

void Initialize() {
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Hidden surface removal(DepthBuffer를 설정하면서 가려지는 부분을 잘라내기)
	glEnable(GL_DEPTH_TEST);

	// Culling할 방향 설정
	glFrontFace(GL_CW);
	// Culling on
	glEnable(GL_CULL_FACE);
}
