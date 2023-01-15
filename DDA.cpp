#include<cstdlib>
#include<cstdio>
#include<gl/glut.h>
#include<cmath>

float xStart, xEnd, yStart, yEnd;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // multiply the current matrix by identity matrix
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int Round(float a)
{
	if (a - (int)a >= 0.5)
		return (int)a + 1;
	return int(a);
}

void swapPoints()
{
	float temp = xStart;
	xStart = xEnd;
	xEnd = temp;
	temp = yStart;
	yStart = yEnd;
	yEnd = temp;
}

void plotPoint(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void display(void)
{
	float m = (yEnd - yStart) / (xEnd - xStart);

	if (abs(m) < 1 && xStart > xEnd)
	{
		swapPoints();
	}

	float x = xStart, y = yStart;
	plotPoint(x, y);

	if (abs(m) < 1)
	{
		while (x <= xEnd - 1)
		{
			x = x + 1;
			y = y + m;

			plotPoint(x, Round(y));
		}
		plotPoint(xEnd, yEnd);
	}
	else if (abs(m) > 1)
	{
		if (yStart > yEnd)
		{
			swapPoints();
		}
		x = xStart, y = yStart;
		m = 1 / m;
		while (y <= yEnd - 1)
		{
			x = x + m;
			y = y + 1;

			plotPoint(Round(x), (y));

		}
		plotPoint(xEnd, yEnd);
	}
	glFlush();

}

int main(int argc, char** argv)
{
	printf_s("Input xStart,yStart,xEnd,yEnd:\n");
	scanf_s("%f %f %f %f", &xStart, &yStart, &xEnd, &yEnd);

	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);//sets the width and height of the window in pixels
	glutInitWindowPosition(10, 10);//sets the position of the window in pixels from top left corner 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//creates a single frame buffer of RGB color capacity.
	glutCreateWindow("DDA Line Algorithm");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
