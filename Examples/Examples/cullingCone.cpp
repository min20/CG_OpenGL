#include <Windows.h>
#include <gl/glut.h>
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void RenderScene()
{
	GLfloat x, y, angle;
	int iPivot = 1;

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_FAN);

	glVertex3f(0.0f, 0.0f, 75.0f);

	for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
	{

		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);

		if ((iPivot % 2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);

		iPivot++;

		glVertex2f(x, y);
	}

	glEnd();


	// Begin a new triangle fan to cover the bottom
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_FAN);

	// Center of fan is at the origin
	glVertex2f(0.0f, 0.0f);
	for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
	{
		// Calculate x and y position of the next vertex
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);

		// Alternate color between red and green
		if ((iPivot % 2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);

		iPivot++;
		glVertex2f(x, y);
	}

	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glShadeModel(GL_FLAT);

	glEnable(GL_CULL_FACE);
}

void ContorolKey(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Triangle");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(ContorolKey);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}