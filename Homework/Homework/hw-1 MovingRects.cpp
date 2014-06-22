#include <Windows.h>
#include <gl/glut.h>

#define NUM_POINTS 3
#define NUM_PARAMETERS 4

GLfloat points[NUM_POINTS][NUM_PARAMETERS] = {
	//{x, y, xstep, ystep5}
	{ -90.0f, -90.0f, 1.3f, 1.0f },
	{ 40.0f, 40.0f, -0.5f, 0.4f },
	{ -25.0f, -25.0f, -0.5f, -1.8f }
};
GLsizei rsize = 50.0f;

GLfloat window_width;
GLfloat window_height;

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);

	// 그림 그릴 색상을 선택합니다.
	glColor3f(0.5f, 0.7f, 1.0f);
	// glRectf의 인자는 (x1, y1, x2, y2) 입니다.
	// (x1, y1), (x2, y2)를 두 꼭지점으로 하는 직사각형을 그립니다.
	glRectf(points[0][0], points[0][1], points[0][0] + rsize, points[0][1] + rsize);

	glColor3f(0.9f, 0.4f, 0.4f);
	glRectf(points[0][0] + 10.0f, points[0][1] + 10.0f, points[0][0] + 10.0f + (rsize - 20.0f), points[0][1] + 10.0f + (rsize - 20.0f));
	glRectf(points[1][0], points[1][1], points[1][0] + rsize, points[1][1] + rsize);

	glColor3f(0.6f, 0.95f, 0.7f);
	glRectf(points[1][0] + 10.0f, points[1][1] + 10.0f, points[1][0] + 10.0f + (rsize - 20.0f), points[1][1] + 10.0f + (rsize - 20.0f));
	glRectf(points[2][0], points[2][1], points[2][0] + rsize, points[2][1] + rsize);


	// DisplayMode가 DOUBLE이기 때문에 버퍼 스왑을 해줍니다.
	glutSwapBuffers();
}

void TimerFunction(int value) {
	int idxPoints;
	for (idxPoints = 0; idxPoints < NUM_POINTS; idxPoints++) {
		if (points[idxPoints][0] > window_width - rsize ||
			points[idxPoints][0] < -window_width) {
			points[idxPoints][2] = -points[idxPoints][2];
		}
		if (points[idxPoints][0] > window_width - rsize) {
			points[idxPoints][0] = window_width - rsize - 1;
		}
		points[idxPoints][0] += points[idxPoints][2];

		if (points[idxPoints][1] > window_height - rsize ||
			points[idxPoints][1] < -window_height)
			points[idxPoints][3] = -points[idxPoints][3];
		if (points[idxPoints][1] > window_height - rsize)
			points[idxPoints][1] = window_height - rsize - 1;
		points[idxPoints][1] += points[idxPoints][3];
	}

	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}

void ChangeWindowSize(GLsizei w, GLsizei h) {
	// glViewport(시작 x좌표, 시작 y좌표, x크기, y크기)
	glViewport(0, 0, w, h);
	//glViewport(0, 0, 300, 300);

	// projection을 담당하는 행렬을 하나 만듭니다.
	glMatrixMode(GL_PROJECTION);
	// glMatrixMode에서 만든 행렬을 단위행렬로 초기화 합니다.
	glLoadIdentity();

	// glOrtho는 View Volume을 (left, right, bottom, top, near, far) 로 설정.


	if (w <= h) {
		window_width = 100.0f;
		window_height = 100.0f * h / w;
		glOrtho(-window_width, window_width, -window_height, window_height, -1.0f, 1.0f);
		//glOrtho(-150.0f, 150.0f, -150.0f, 150.0f, 1.0f, -1.0f);
	}
	else {
		window_width = 100.0f * w / h;
		window_height = 100.0f;
		glOrtho(-window_width, window_width, -window_height, window_height, -1.0f, 1.0f);		//glOrtho(-150.0f, 150.0f, -150.0f, 150.0f, 1.0f, -1.0f);
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
	glutCreateWindow("hw-1 MovingRects");

	// 우리가 실제로 그림 그릴 놈(RenderScene)을 실행합니다(callback function)
	glutDisplayFunc(RenderScene);
	// 창 크기가 변경될 경우 모양을 어떻게 바꿀 지 결정합니다.
	// 지금은 ChangeWindowSize를 써요.
	glutReshapeFunc(ChangeWindowSize);
	glutTimerFunc(1000, TimerFunction, 1);

	// 초기화 함수 하나 만들었어요.
	Initialize();
	// 계속 돌아가면서 유지해주고, 이벤트도 받아주는 함수입니다.
	glutMainLoop();

	return 0;
}