#include <Windows.h>
#include <gl/glut.h>

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);

	// �׸� �׸� ������ �����մϴ�.
	glColor3f(0.5f, 0.7f, 1.0f);
	// ���ڴ� (x1, y1, x2, y2) �Դϴ�.
	// (x1, y1), (x2, y2)�� �� ���������� �ϴ� ���簢���� �׸��ϴ�.
	glRectf(-90.0f, -90.0f, -40.0f, -40.0f);
	
	glColor3f(0.9f, 0.4f, 0.4f);
	glRectf(90.0f, 90.0f, 40.0f, 40.0f);

	glColor3f(0.6f, 0.95f, 0.7f);
	glRectf(-25.0f, -25.0f, 25.0f, 25.0f);

	// DisplayMode�� DOUBLE�̱� ������ ���� ������ ���ݴϴ�.
	glutSwapBuffers();
}

void ChangeWindowSize(GLsizei w, GLsizei h) {
	// glViewport(���� x��ǥ, ���� y��ǥ, xũ��, yũ��)
	//glViewport(0, 0, w, h);
	glViewport(0, 0, 300, 300);

	// projection�� ����ϴ� ����� �ϳ� ����ϴ�.
	glMatrixMode(GL_PROJECTION);
	// glMatrixMode���� ���� ����� ������ķ� �ʱ�ȭ �մϴ�.
	glLoadIdentity();

	// glOrtho�� View Volume�� (left, right, bottom, top, near, far) �� ����.
	

	if (w <= h) {
		glOrtho(-150.0f, 150.0f, -150.0f , 150.0f , 1.0f, -1.0f);
	}
	else {
		glOrtho(-150.0f , 150.0f , -150.0f, 150.0f, 1.0f, -1.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	// ��� ��ȯ ���� ��ǥ�� �缳��(�ʱ�ȭ) �մϴ�.
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, 0.0f);
}

void Initialize() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {
	// ���۸� �� �� ����ϴ�. �÷� ���� RGB
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// �� â�� ����� �̸��� ���ؿ�.
	glutCreateWindow("This is a Window Title");

	// �츮�� ������ �׸� �׸� ��(RenderScene)�� �����մϴ�(callback function)
	glutDisplayFunc(RenderScene);
	// â ũ�Ⱑ ����� ��� ����� ��� �ٲ� �� �����մϴ�.
	// ������ ChangeWindowSize�� ���.
	glutReshapeFunc(ChangeWindowSize);

	// �ʱ�ȭ �Լ� �ϳ� ��������.
	Initialize();
	// ��� ���ư��鼭 �������ְ�, �̺�Ʈ�� �޾��ִ� �Լ��Դϴ�.
	glutMainLoop();

	return 0;
}