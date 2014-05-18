#include <Windows.h>
#include <gl/glut.h>

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);

	// 그림 그릴 색상을 선택합니다.
	glColor3f(0.5f, 0.7f, 1.0f);
	// 인자는 (x1, y1, x2, y2) 입니다.
	// (x1, y1), (x2, y2)를 두 꼭지점으로 하는 직사각형을 그립니다.
	glRectf(-90.0f, -90.0f, -40.0f, -40.0f);
	
	glColor3f(0.9f, 0.4f, 0.4f);
	glRectf(90.0f, 90.0f, 40.0f, 40.0f);

	glColor3f(0.6f, 0.95f, 0.7f);
	glRectf(-25.0f, -25.0f, 25.0f, 25.0f);

	// DisplayMode가 DOUBLE이기 때문에 버퍼 스왑을 해줍니다.
	glutSwapBuffers();
}

void ChangeWindowSize(GLsizei w, GLsizei h) {
	// glViewport(시작 x좌표, 시작 y좌표, x크기, y크기)
	//glViewport(0, 0, w, h);
	glViewport(0, 0, 300, 300);

	// projection을 담당하는 행렬을 하나 만듭니다.
	glMatrixMode(GL_PROJECTION);
	// glMatrixMode에서 만든 행렬을 단위행렬로 초기화 합니다.
	glLoadIdentity();

	// glOrtho는 View Volume을 (left, right, bottom, top, near, far) 로 설정.
	

	if (w <= h) {
		glOrtho(-150.0f, 150.0f, -150.0f , 150.0f , 1.0f, -1.0f);
	}
	else {
		glOrtho(-150.0f , 150.0f , -150.0f, 150.0f, 1.0f, -1.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	// 행렬 변환 전에 좌표를 재설정(초기화) 합니다.
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, 0.0f);
}

void Initialize() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {
	// 버퍼를 두 개 만듭니다. 컬러 모델은 RGB
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// 새 창을 만들고 이름을 정해요.
	glutCreateWindow("This is a Window Title");

	// 우리가 실제로 그림 그릴 놈(RenderScene)을 실행합니다(callback function)
	glutDisplayFunc(RenderScene);
	// 창 크기가 변경될 경우 모양을 어떻게 바꿀 지 결정합니다.
	// 지금은 ChangeWindowSize를 써요.
	glutReshapeFunc(ChangeWindowSize);

	// 초기화 함수 하나 만들었어요.
	Initialize();
	// 계속 돌아가면서 유지해주고, 이벤트도 받아주는 함수입니다.
	glutMainLoop();

	return 0;
}