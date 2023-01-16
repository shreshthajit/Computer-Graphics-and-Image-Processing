#include <iostream>
#include <GL/glut.h>
using namespace std;
int r, xc, yc;

void plot(int x, int y)
{
  glBegin(GL_POINTS);
  glVertex2i(x + xc, y + yc);
  glEnd();
}

void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void midPointCircleAlgo()
{
  int x = 0;
  int y = r;
  float decision = 3  - 2*r;
  plot(x, y);
  while (y > x)
  {
    if (decision < 0)
    {
        x++;
        decision += 4 * x + 6;
    }
    else
    {
        y--;
        x++;
        decision += 4 * (x - y) + 10;
    }
      plot(x, y);
      plot(x, -y);
      plot(-x, y);
      plot(-x, -y);
      plot(y, x);
      plot(-y, x);
      plot(y, -x);
      plot(-y, -x);
    }
}

void myDisplay(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);
  glPointSize(1.0);
  midPointCircleAlgo();
  glFlush();
}

int main(int argc, char** argv)
{
    printf("Enter centre and radius of circle\n");
    scanf("%d %d %d",&xc, &yc, &r);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Line Drawing Alogrithms");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
}
