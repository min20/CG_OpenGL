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
		// 3.14/0.1 개의 포인트를 뿌린다 총 3바퀴 
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

	// z축 성분변화도 생겨서 ortho 범위를 늘려놓았다.
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
	// 버퍼를 두 개 만듭니다. 컬러 모델은 RGB
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// 새 창을 만들고 이름을 정해요.
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);

	glutCreateWindow("Vertex Spring");

	// 우리가 실제로 그림 그릴 놈(RenderScene)을 실행합니다(callback function)
	glutDisplayFunc(RenderScene);
	// 창 크기가 변경될 경우 모양을 어떻게 바꿀 지 결정합니다.
	// 지금은 ChangeWindowSize를 써요.
	glutReshapeFunc(ChangeWindowSize);
	glutSpecialFunc(KeyControl);

	// 초기화 함수 하나 만들었어요.
	Initialize();
	// 계속 돌아가면서 유지해주고, 이벤트도 받아주는 함수입니다.
	glutMainLoop();

	return 0;
}