#include <gl/glut.h>
#include <windows.h>
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	//glEnable(GL_LIGHTING);
}

void TimerFunc(int value) {
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunc, 1);
}

void RenderScene() {
	static GLfloat fElect1 = 0.0f;
	static GLfloat fElect2 = 0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glColor3ub(255, 0, 0);
	// 태양
	glutSolidSphere(10.0f, 15, 15);

	// 위성 1
	glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(90.0f, 0.0f, 0.0f);
	glRotatef(-fElect1, 0.0f, 1.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect2, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 30.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(3.0f, 15, 15);
	glPopMatrix();

	// 행성 1
	// viewing transformation 저장 (1)
	glPushMatrix();
	// y축 방향으로 fElect1 각만큼 회전
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	// 변환된 x축으로 90만큼 이동
	glTranslatef(90.0f, 0.0f, 0.0f);
	glColor3ub(255, 255, 0);
	// 원 그리기
	glutSolidSphere(6.0f, 15, 15);
	// STACK에 저장된 (1) 의 상태로 변환행렬 재설정
	glPopMatrix();

	// 행성 2
	glPushMatrix();
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(-70.0f, 0.0f, 0.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();

	// 행성 3
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 60.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();

	// 회전각 증가
	fElect1 += 3.3f;
	fElect2 += 10.0f;

	if (fElect1 > 360.0f) {
		fElect1 = 0.0f;
	}

	if (fElect2 > 360.0f) {
		fElect2 = 0.0f;
	}

	glutSwapBuffers();
}

void ChangeSize(int w, int h) {
	GLfloat nRange = 120.0f;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange*2.0f, nRange*2.0f);
	}
	else {
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("hw-4 Atom");

	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunc, 1);

	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}