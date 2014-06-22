#include <gl/glut.h>
#include <windows.h>
#include <math.h>

#define GL_PI 3.1415f

void SetupRC() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	//glEnable(GL_LIGHTING);

	//ambientLight, diffuseLight, sepcularLight를 위한 값을 설정한다.
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat spotDir[] = { 0.0f, 0.0f, -1.0f };

	glEnable(GL_LIGHTING);

	//light 설정
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 360.0f);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void TimerFunc(int value) {
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunc, 1);
}

void RenderScene() {
	static GLfloat fElect1 = 0.0f;
	static GLfloat fElect2 = 0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 태양
	glPushMatrix();
	// 태양에 빛 주려고 위치 변경.
	// ( lightPos[] == { 0.0f, 0.0f, 0.0f, 1.0f } )
	glTranslatef(0.0f, 0.0f, -40.0f);
	glColor3ub(255, 255, 0);
	glutSolidSphere(20.0f, 15, 15);
	glPopMatrix();

	// 위성 1
	glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(90.0f, 0.0f, 0.0f);
	glRotatef(-fElect1, 0.0f, 1.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect2, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 30.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();

	// 행성 1
	// viewing transformation 저장 (1)
	glPushMatrix();
	// y축 방향으로 fElect1 각만큼 회전
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	// 변환된 x축으로 90만큼 이동
	glTranslatef(90.0f, 0.0f, 0.0f);
	glColor3ub(0, 0, 255);
	// 구 그리기
	glutSolidSphere(10.0f, 15, 15);
	// STACK에 저장된 (1) 의 상태로 변환행렬 재설정
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
	// Perspective
	GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat fAspect;

	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40.0f, fAspect, 1.0f, 600.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -300.0f);
	
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	
	glutInitWindowPosition(0, 0);
	glutCreateWindow("hw-5 Atom with Light");

	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunc, 1);

	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}