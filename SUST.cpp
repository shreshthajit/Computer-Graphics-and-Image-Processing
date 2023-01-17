 #include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);	// Set display window colour to white

	glMatrixMode(GL_PROJECTION);		// Set projection parameters
	gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

void drawShapes(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear display window

	//Set colour to black
	glColor3f(0.0, 0.0, 0.0);
	//Adjust the point size
	glPointSize(5.0);

	//Set colour to red
	glColor3f(1.0, 0.0, 0.0);

	// Draw an outlined triangle
	glBegin(GL_LINES);

	//Draw s
		glVertex2i(0, 0);
		glVertex2i(40, 40);

		glVertex2i(0,40);
		glVertex2i(40,40);

		glVertex2i(0,40);
		glVertex2i(40,80);

    //draw u
        glVertex2i(60, 0);
		glVertex2i(60, 80);

		glVertex2i(60,0);
		glVertex2i(100,0);

		glVertex2i(100,0);
		glVertex2i(100,80);


		//draw S
        glVertex2i(120, 0);
		glVertex2i(160, 0);

		glVertex2i(160,0);
		glVertex2i(160,40);

		glVertex2i(120,40);
		glVertex2i(160,40);

		glVertex2i(120,40);
		glVertex2i(120,80);

		glVertex2i(120,80);
		glVertex2i(160,80);

		//draw T
		glVertex2i(220,0);
		glVertex2i(220,80);

		glVertex2i(200,80);
		glVertex2i(240,80);






		//glVertex2d()

	//	glVertex2i(200, 400);
		//glVertex2i(200,0);



	glEnd();

	glFlush();	// Process all OpenGL routines
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);						// Initalise GLUT
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);	// Set display mode

	glutInitWindowPosition(50, 100);				// Set window position
	glutInitWindowSize(400, 300);					// Set window size
	glutCreateWindow("An Example OpenGL Program");	// Create display window

	init();							// Execute initialisation procedure
	glutDisplayFunc(drawShapes);		// Send graphics to display window
	glutMainLoop();					// Display everything and wait

	return 0;
}
