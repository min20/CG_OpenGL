#include <Windows.h>
#include <gl/glut.h>

float xRot = 0.0f;
float yRot = 0.0f;

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// xRot ��(angle) ��ŭ x�� �������� ȸ���Ѵ�
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	// yRot ��(angle) ��ŭ y�� �������� ȸ���Ѵ�
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

	// �⺻ Shading ��å ����. ���� �������� �ٲ� ���� �ֽ��ϴ�.
	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);


	// �ո�(���� ��) ����
	glFrontFace(GL_CW);
	// �޸�(�� ���� ��) ����
	//glEnable(GL_CULL_FACE);
	// ������ ��ü �� ���̰� ��
	glEnable(GL_DEPTH_TEST);

	// �� ���е�
	GLfloat ambientLight [] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight [] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat specularLight [] = { 0.5f, 0.5f, 0.5f, 1.0f };
	// ��ü�� �ݻ���
	GLfloat materialSpecular [] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glEnable(GL_LIGHTING);

	// ���� ����.
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glEnable(GL_LIGHT0);

	// �������� ���� ���� ���� ������ �ٰǵ�
	glEnable(GL_COLOR_MATERIAL);
	// GL_FRONT = �ո鿡��, Ambient�� Diffuse�� ������
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// GL_FRONT = �ո鿡��, ��ü �ݻ����� materialSpecual�� �����Ұ���.
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	// GL_SHININESS = specular ���� n���� �󸶷� �Ұ��� ����
	glMateriali(GL_FRONT, GL_SHININESS, 256);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Example_lighting");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeWindowSize);

	Initialize();
	// glutSpecialFunc �� glutMainLoop ���� ���� �մϴ�!!
	glutSpecialFunc(KeyControl);

	glutMainLoop();

	return 0;
}