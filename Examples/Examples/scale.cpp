#include <Windows.h>
#include <gl/glut.h>

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);

	glScalef(1.5f, 1.5f, 0.0f);
	glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.7f, 1.0f);
	glVertex2f(-50.0f, 5.0f);

	glColor3f(0.9f, 0.4f, 0.4f);
	glVertex2f(0.0f, 80.0f);

	glColor3f(0.6f, 0.95f, 0.7f);
	glVertex2f(50.0f, 5.0f);
	glEnd();

	glScalef(0.5f, 0.5f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.7f, 1.0f);
	glVertex2f(-50.0f, -5.0f);

	glColor3f(0.9f, 0.4f, 0.4f);
	glVertex2f(0.0f, -80.0f);

	glColor3f(0.6f, 0.95f, 0.7f);
	glVertex2f(50.0f, -5.0f);
	glEnd();

	glutSwapBuffers();
}

void ChangeWindowSize(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		glOrtho(-100.0f, 100.0f, -100.0f * h / w, 100.0f * h / w, 1.0f, -1.0f);
	}
	else {
		glOrtho(-100.0f * w / h, 100.0f * w / h, -100.0f, 100.0f, 1.0f, -1.0f);
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
	glutCreateWindow("Example_scale");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeWindowSize);

	Initialize();
	glutMainLoop();

	return 0;
}