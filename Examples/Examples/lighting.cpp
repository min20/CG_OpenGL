#include <Windows.h>
#include <gl/glut.h>

float xRot = 0.0f;
float yRot = 0.0f;

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// xRot 도(angle) 만큼 x축 방향으로 회전한다
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	// yRot 도(angle) 만큼 y축 방향으로 회전한다
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-25.0f, 0.0f, -30.0f);
	glVertex3f(0.0f, 25.0f, -30.0f);
	glVertex3f(25.0f, 0.0f, -30.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(25.0f, 25.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);
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

	// 기본 Shading 정책 결정. 각각 도형별로 바꿀 수도 있습니다.
	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);


	// 앞면(보일 면) 설정
	glFrontFace(GL_CW);
	// 뒷면(안 보일 면) 설정
	//glEnable(GL_CULL_FACE);
	// 가리는 물체 안 보이게 함
	glEnable(GL_DEPTH_TEST);

	// 빛 성분들
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	// 물체의 반사율
	GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glEnable(GL_LIGHTING);

	// 빛의 설정.
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glEnable(GL_LIGHT0);

	// 이제부터 빛이 물건 색상에 영향을 줄건데
	glEnable(GL_COLOR_MATERIAL);
	// GL_FRONT = 앞면에만, Ambient와 Diffuse를 적용함
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// GL_FRONT = 앞면에만, 물체 반사율을 materialSpecual로 적용할거임.
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	// GL_SHININESS = specular 광의 n제곱 얼마로 할건지 결정
	glMateriali(GL_FRONT, GL_SHININESS, 256);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Example_lighting");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeWindowSize);

	Initialize();
	// glutSpecialFunc 는 glutMainLoop 전에 들어가야 합니다!!
	glutSpecialFunc(KeyControl);

	glutMainLoop();

	return 0;
}