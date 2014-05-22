#include <gl/glut.h>
#include <windows.h>
#include <math.h>

#define GL_PI 3.1415f


static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;


void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(33, TimerFunc, 1);
}


void RenderScene()
{
	static GLfloat fElect1 = 0.0f;
	static GLfloat fElect2 = 0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -100.0f);  // z 축으로 -100만큼 이동

	glColor3ub(255, 0,0);
	glutSolidSphere(10.0f,15,15);
	glPushMatrix();						// viewing transformation 저장 (1) 
										// (1) - z축으로 -100만큼 이동		
	
	GLfloat position = 90.0f;
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(position,0.0f, 0.0f);      // 변환된 x축으로 90만큼 이동
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect2, 0.0f, 1.0f, 0.0f); // y축 방향으로 fElect1 각만큼 회전
	glTranslatef(0.0f, 0.0f, -20.0f);
	glColor3ub(255, 255, 255);
	glutSolidSphere(3.0f, 15, 15);
	glPopMatrix();						// STACK에 저장된 (1) 의 상태로 변환행렬 재설정
	
	glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(position, 0.0f, 0.0f);
	glColor3ub(255,255,0);
	glutSolidSphere(6.0f,15,15);        // 원 그리기
	glPopMatrix();
										// (1) - z축으로 -100만큼 이동		

	// 두번째 원자 그리기
	glPushMatrix();						// viewing transformation 저장 (1) 				
	glRotatef(45.0f, 0.0f,0.0f, 1.0f);  
	glRotatef(fElect1, 0.0f,1.0f,0.0f);
	glTranslatef(-70.0f, 0.0f,0.0f);
	glutSolidSphere(6.0f,15,15);
	glPopMatrix();						// STACK에 저장된 (1) 의 상태로 변환행렬 재설정
										// (1) - z축으로 -100만큼 이동		


	glPushMatrix();                     // viewing transformation 저장 (1) 	
	glRotatef(90.0f,0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);// 변환된 z축으로 90만큼 이동
	glTranslatef(0.0f, 0.0f, 60.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();						// STACK에 저장된 (1) 의 상태로 변환행렬 재설정
										// (1) - z축으로 -100만큼 이동		


	fElect1 += 3.0f;					// 회전각 증가
	if(fElect1 > 360.0f)
		fElect1 = 0.0f;

	fElect2 += 10.0f;
	if (fElect2 > 360.0f)
		fElect2 = 0.0f;

	glutSwapBuffers(); 
	
}



void ContorolKey(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	glutPostRedisplay();
}


void ChangeSize(int w, int h)
{
	GLfloat nRange = 120.0f;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2.0f, nRange*2.0f);  //add
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);  //add


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512,512);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Atom");

	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33,TimerFunc,1 );
	glutSpecialFunc(ContorolKey);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}

