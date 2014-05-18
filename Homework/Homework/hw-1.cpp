#include <Windows.h>
#include <gl/glut.h>

#define NUM_POINTS 3
#define NUM_PARAMETERS 4

GLfloat points[NUM_POINTS][NUM_PARAMETERS] = {
	//{x, y, xstep, ystep5}
	{ -90.0f, -90.0f, 1.3f, 1.0f },
	{ 40.0f, 40.0f, -0.5f, 0.4f },
	{ -25.0f, -25.0f, -0.5f, -1.8f }
};
GLsizei rsize = 50.0f;

GLfloat window_width;
GLfloat window_height;

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);

	// �׸� �׸� ������ �����մϴ�.
	glColor3f(0.5f, 0.7f, 1.0f);
	// glRectf�� ���ڴ� (x1, y1, x2, y2) �Դϴ�.
	// (x1, y1), (x2, y2)�� �� ���������� �ϴ� ���簢���� �׸��ϴ�.
	glRectf(points[0][0], points[0][1], points[0][0] + rsize, points[0][1] + rsize);

	glColor3f(0.9f, 0.4f, 0.4f);
	glRectf(points[0][0] + 10.0f, points[0][1] + 10.0f, points[0][0] + 10.0f + (rsize - 20.0f), points[0][1] + 10.0f + (rsize - 20.0f));
	glRectf(points[1][0], points[1][1], points[1][0] + rsize, points[1][1] + rsize);
	
	glColor3f(0.6f, 0.95f, 0.7f);
	glRectf(points[1][0] + 10.0f, points[1][1] + 10.0f, points[1][0] + 10.0f + (rsize - 20.0f), points[1][1] + 10.0f + (rsize - 20.0f));
	glRectf(points[2][0], points[2][1], points[2][0] + rsize, points[2][1] + rsize);


	// DisplayMode�� DOUBLE�̱� ������ ���� ������ ���ݴϴ�.
	glutSwapBuffers();
}

void TimerFunction(int value) {
	int idxPoints;
	for (idxPoints = 0; idxPoints < NUM_POINTS; idxPoints++) {
		if (points[idxPoints][0] > window_width - rsize ||
			points[idxPoints][0] < -window_width) {
			points[idxPoints][2] = -points[idxPoints][2];
		}
		if (points[idxPoints][0] > window_width - rsize) {
			points[idxPoints][0] = window_width - rsize - 1;
		}
		points[idxPoints][0] += points[idxPoints][2];

		if (points[idxPoints][1] > window_height - rsize ||
			points[idxPoints][1] < -window_height)
			points[idxPoints][3] = -points[idxPoints][3];
		if (points[idxPoints][1] > window_height - rsize)
			points[idxPoints][1] = window_height - rsize - 1;
		points[idxPoints][1] += points[idxPoints][3];
	}

	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}

void ChangeWindowSize(GLsizei w, GLsizei h) {
	// glViewport(���� x��ǥ, ���� y��ǥ, xũ��, yũ��)
	glViewport(0, 0, w, h);
	//glViewport(0, 0, 300, 300);

	// projection�� ����ϴ� ����� �ϳ� ����ϴ�.
	glMatrixMode(GL_PROJECTION);
	// glMatrixMode���� ���� ����� ������ķ� �ʱ�ȭ �մϴ�.
	glLoadIdentity();

	// glOrtho�� View Volume�� (left, right, bottom, top, near, far) �� ����.


	if (w <= h) {
		window_width = 100.0f;
		window_height = 100.0f * h / w;
		glOrtho(-window_width, window_width, -window_height, window_height, -1.0f, 1.0f);
		//glOrtho(-150.0f, 150.0f, -150.0f, 150.0f, 1.0f, -1.0f);
	}
	else {
		window_width = 100.0f * w / h;
		window_height = 100.0f;
		glOrtho(-window_width, window_width, -window_height, window_height, -1.0f, 1.0f);		//glOrtho(-150.0f, 150.0f, -150.0f, 150.0f, 1.0f, -1.0f);
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
	glutCreateWindow("hw-1-01 ����");

	// �츮�� ������ �׸� �׸� ��(RenderScene)�� �����մϴ�(callback function)
	glutDisplayFunc(RenderScene);
	// â ũ�Ⱑ ����� ��� ����� ��� �ٲ� �� �����մϴ�.
	// ������ ChangeWindowSize�� ���.
	glutReshapeFunc(ChangeWindowSize);
	glutTimerFunc(1000, TimerFunction, 1);

	// �ʱ�ȭ �Լ� �ϳ� ��������.
	Initialize();
	// ��� ���ư��鼭 �������ְ�, �̺�Ʈ�� �޾��ִ� �Լ��Դϴ�.
	glutMainLoop();

	return 0;
}