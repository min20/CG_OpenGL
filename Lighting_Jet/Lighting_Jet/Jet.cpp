#include "stdafx.h"
#include "GLTools.h"

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zDistance = 0.0f;		///ADD

static GLfloat light_elect = 0.0f;

void SetupRC()
{
	GLfloat amb[] = { 0.3f, 0.3f, 0.3f };
	GLfloat diff[] = { 0.7f, 0.7f, 0.7f };
	GLfloat spec[] = { 1.0f, 1.0f, 1.0f };

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);  // 내부 폴리곤 연산 off (backface culling)
	glEnable(GL_LIGHT0);

	glFrontFace(GL_CCW);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void DrawJet()
{
	GLTVector3 vNormal;	// Storeage for calculated surface normal

	glBegin(GL_TRIANGLES);

	//front bottom
	glNormal3f(0.0f, -1.0f, 0.0f);

	glColor3f(0.7f, 0.7f, 0.7f);
	glVertex3f(0.0f, 0.0f, 60.0f);
	glVertex3f(-15.0f, 0.0f, 30.0f);
	glVertex3f(15.0f, 0.0f, 30.0f);
	//주석처리 제거   

	//Right Winng
	{
		GLTVector3 vPoints[3] = { { 15.0f, 0.0f, 30.0f },
		{ 0.0f, 15.0f, 30.0f },
		{ 0.0f, 0.0f, 60.0f } };

		// Calculate the normal for the plane
		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);

		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = { { 0.0f, 0.0f, 60.0f },
		{ 0.0f, 15.0f, 30.0f },
		{ -15.0f, 0.0f, 30.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	// Body of the Plane ////////////////////////
	{
		GLTVector3 vPoints[3] = { { -15.0f, 0.0f, 30.0f },
		{ 0.0f, 15.0f, 30.0f },
		{ 0.0f, 0.0f, -56.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = { { 0.0f, 0.0f, -56.0f },
		{ 0.0f, 15.0f, 30.0f },
		{ 15.0f, 0.0f, 30.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(15.0f, 0.0f, 30.0f);
	glVertex3f(-15.0f, 0.0f, 30.0f);
	glVertex3f(0.0f, 0.0f, -56.0f);

	///////////////////////////////////////////////
	// Left wing
	// Large triangle for bottom of wing
	glColor3f(0.3f, 0.5f, 0.8f);
	{
		GLTVector3 vPoints[3] = { { 0.0f, 2.0f, 27.0f },
		{ -60.0f, 2.0f, -8.0f },
		{ 60.0f, 2.0f, -8.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	{
		GLTVector3 vPoints[3] = { { 60.0f, 2.0f, -8.0f },
		{ 0.0f, 7.0f, -8.0f },
		{ 0.0f, 2.0f, 27.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = { { 60.0f, 2.0f, -8.0f },
		{ -60.0f, 2.0f, -8.0f },
		{ 0.0f, 7.0f, -8.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = { { 0.0f, 2.0f, 27.0f },
		{ 0.0f, 7.0f, -8.0f },
		{ -60.0f, 2.0f, -8.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	// Tail section///////////////////////////////
	// Bottom of back fin
	glNormal3f(0.0f, -1.0f, 0.0f);
	glColor3f(0.8f, 0.2f, 0.2f);
	glVertex3f(-30.0f, -0.50f, -57.0f);
	glVertex3f(30.0f, -0.50f, -57.0f);
	glVertex3f(0.0f, -0.50f, -40.0f);

	{
		GLTVector3 vPoints[3] = { { 0.0f, -0.5f, -40.0f },
		{ 30.0f, -0.5f, -57.0f },
		{ 0.0f, 4.0f, -57.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	{
		GLTVector3 vPoints[3] = { { 0.0f, 4.0f, -57.0f },
		{ -30.0f, -0.5f, -57.0f },
		{ 0.0f, -0.5f, -40.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	{
		GLTVector3 vPoints[3] = { { 30.0f, -0.5f, -57.0f },
		{ -30.0f, -0.5f, -57.0f },
		{ 0.0f, 4.0f, -57.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = { { 0.0f, 0.5f, -40.0f },
		{ 3.0f, 0.5f, -57.0f },
		{ 0.0f, 25.0f, -65.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = { { 0.0f, 25.0f, -65.0f },
		{ -3.0f, 0.5f, -57.0f },
		{ 0.0f, 0.5f, -40.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}

	{
		GLTVector3 vPoints[3] = { { 3.0f, 0.5f, -57.0f },
		{ -3.0f, 0.5f, -57.0f },
		{ 0.0f, 25.0f, -65.0f } };

		gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
		glNormal3fv(vNormal);
		glVertex3fv(vPoints[0]);
		glVertex3fv(vPoints[1]);
		glVertex3fv(vPoints[2]);
	}


	glEnd();
}


// Called to draw scene
void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save the matrix state and do the rotations
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, zDistance);

	DrawJet();
	glRotatef(light_elect, 0.0f, 1.0f, 0.0f);
	GLfloat lightPos[] = { 100.f, 100.0f, 100.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50.0f);

	glPopMatrix();


	light_elect -= 5.0f;

	glutSwapBuffers();

}


/////////////////////////////////////////////////////
// Handle arrow keys
void ContorolKey(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if (key == GLUT_KEY_HOME) //add
		zDistance += 5.0f;

	if (key == GLUT_KEY_END) //add
		zDistance -= 5.0f;

	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h; // Window의 종횡비 계산
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, fAspect, 1.0f, 255.0f); //(FOV,종횡비,near,far)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -150.0f);
}

void TimerFunc(int value) {
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunc, 1);
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Jet");

	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunc, 1);

	glutSpecialFunc(ContorolKey);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}
