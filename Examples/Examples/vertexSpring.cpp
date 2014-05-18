#include <Windows.h>
#include <gl/glut.h>
#include <math.h>

#define GL_PI 3.141592f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void RenderScene() {
	GLfloat x, y, z, angle;
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f); //(angle)
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	z = -50.0f;

	glColor3f(0.0f, 1.0f, 0.0f);

	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
		// 3.14/0.1 ���� ����Ʈ�� �Ѹ��� �� 3���� 
	{
		x = 60.0f*sin(angle);
		y = 60.0f*cos(angle);
		glVertex3f(x, y, z);
		z += 0.5f;
	}
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

void KeyControl(int keyboardInput, int x, int y) {
	if (keyboardInput == GLUT_KEY_UP) {
		xRot -= 2.0f;
	}
	
	if (keyboardInput == GLUT_KEY_DOWN) {
		xRot += 2.0f;
	}
	
	if (keyboardInput == GLUT_KEY_LEFT) {
		yRot -= 2.0f;
	}
	
	if (keyboardInput == GLUT_KEY_RIGHT) {
		yRot += 2.0f;
	}
	
	glutPostRedisplay();
}

void ChangeWindowSize(GLsizei w, GLsizei h) {
	GLfloat nRange = 100.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	// z�� ���к�ȭ�� ���ܼ� ortho ������ �÷����Ҵ�.
	if (w <= h) {
		glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
	}
	else {
		glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, 0.0f);
}

void Initialize() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {
	// ���۸� �� �� ����ϴ�. �÷� ���� RGB
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// �� â�� ����� �̸��� ���ؿ�.
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);

	glutCreateWindow("Vertex Spring");

	// �츮�� ������ �׸� �׸� ��(RenderScene)�� �����մϴ�(callback function)
	glutDisplayFunc(RenderScene);
	// â ũ�Ⱑ ����� ��� ����� ��� �ٲ� �� �����մϴ�.
	// ������ ChangeWindowSize�� ���.
	glutReshapeFunc(ChangeWindowSize);
	glutSpecialFunc(KeyControl);

	// �ʱ�ȭ �Լ� �ϳ� ��������.
	Initialize();
	// ��� ���ư��鼭 �������ְ�, �̺�Ʈ�� �޾��ִ� �Լ��Դϴ�.
	glutMainLoop();

	return 0;
}