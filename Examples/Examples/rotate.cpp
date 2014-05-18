#include <Windows.h>
#include <gl/glut.h>

float xRot = 0.0f;
float yRot = 0.0f;

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.7f, 1.0f);
	glVertex2f(-50.0f, 5.0f);

	glColor3f(0.9f, 0.4f, 0.4f);
	glVertex2f(0.0f, 80.0f);

	glColor3f(0.6f, 0.95f, 0.7f);
	glVertex2f(50.0f, 5.0f);
	glEnd();

	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.7f, 1.0f);
	glVertex2f(-50.0f, -5.0f);

	glColor3f(0.9f, 0.4f, 0.4f);
	glVertex2f(0.0f, -80.0f);

	glColor3f(0.6f, 0.95f, 0.7f);
	glVertex2f(50.0f, -5.0f);
	glEnd();
	glLoadIdentity();

	glutSwapBuffers();
}

void KeyControl(int keyboardInput, int x, int y) {
	if (keyboardInput == GLUT_KEY_UP) {
		xRot -= 2.0f;
	}
	else if (keyboardInput == GLUT_KEY_DOWN) {
		xRot += 2.0f;
	}
	else if (keyboardInput == GLUT_KEY_LEFT) {
		yRot -= 2.0f;
	}
	else if (keyboardInput == GLUT_KEY_RIGHT) {
		yRot += 2.0f;
	}
	else {
		// DO NOTHING
	}

	glutPostRedisplay();
}

void ChangeWindowSize(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// z축 성분변화도 생겨서 ortho 범위를 늘려놓았다.
	if (w <= h) {
		glOrtho(-100.0f, 100.0f, -100.0f * h / w, 100.0f * h / w, 100.0f, -100.0f);
	}
	else {
		glOrtho(-100.0f * w / h, 100.0f * w / h, -100.0f, 100.0f, 100.0f, -100.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, 0.0f);
}

void Initialize() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// 기본 Shading 정책 결정. 각각 도형별로 바꿈다.
	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Example_rotate");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeWindowSize);

	Initialize();
	// glutSpecialFunc 는 glutMainLoop 전에 들어가야 합니다!!
	glutSpecialFunc(KeyControl);

	glutMainLoop();

	return 0;
}