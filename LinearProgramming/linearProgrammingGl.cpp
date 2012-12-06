#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <iostream>
#include "lp2d.h"

/* ASCII code for the escape key. */
#define ESCAPE 27

using namespace std;
using namespace lp2D;

/* The number of our GLUT window */
int window;

const int X_SIZE = 640;
const int Y_SIZE = 480;

const int MAXGL = 1000;
int WINDOW = 50;
int dx = 0, dy = 0;

LinearProgram2D * lp;
double optX = 0.0, optY = 0.0, optZ = 0.0;

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
  	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  	glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  	glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  	glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  	glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

	glEnable( GL_POINT_SMOOTH );
    glPointSize( 3.0 );

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
  	//glBlendFunc(GL_SRC_ALPHA,GL_ONE);

  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();				// Reset The Projection Matrix

  	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window

  	glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
	if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
    	Height=1;

  	glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();

  	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,5000.0f);
  	glMatrixMode(GL_MODELVIEW);
}

void resetColor(){
	glColor3f(0.0, 0.0, 0.0);
}

void drawGrid(){
	glColor4f(0.0, 0.0, 1.0, 0.2);

	glBegin(GL_LINES);
	for(int i = -MAXGL; i<=MAXGL; i++){
		if(i == 0){
			//glColor4f(139.0/255.0, 125.0/255.0, 123.0/255.0, 1.0);
			//glColor4f(0, 1, 1, 1.0);
			glColor4f(0, 1, 0, 2.5);
		}

		glVertex2f((double) -MAXGL, (double) i);
		glVertex2f((double)  MAXGL, (double) i);

		glVertex2f((double) i, (double) -MAXGL);
		glVertex2f((double) i, (double) MAXGL);

		if(i == 0)
			glColor4f(0.0, 0.0, 1.0, 0.2);
	}
	glEnd();

	resetColor();
}

double calcY(double x, double a0, double a1, double b){
	return (b - (a0 * x)) / a1;
}

double calcX(double y, double a0, double a1, double b){
	return (b - (a1 * y)) / a0;
}

void drawLp(){

	glBegin(GL_QUADS);
	int nc = lp->getNumberOfConstraints();
	for(int i = 0; i < nc; i++){
		Constraint2D * c = lp->getConstraint(i);
		double a0 = c->getA(0);
		double a1 = c->getA(1);
		double b = c->getB();

		glColor4f(1.0, 0.0, 0.0, 0.5);

		double x0 = (double) -MAXGL;
		double y0 = calcY(-MAXGL, a0, a1, b);

		double x1 = MAXGL;
		double y1 = calcY(MAXGL, a0, a1, b);

		b += ((c->getType() == GEQ) ? 20 : -20);

		double x2 = (double) -MAXGL;
		double y2 = calcY(-MAXGL, a0, a1, b);

		double x3 = MAXGL;
		double y3 = calcY(MAXGL, a0, a1, b);

		glVertex2f(x0, y0);
		glVertex2f(x1, y1);

		glColor4f(1.0, 0.0, 0.0, 0.0);

		glVertex2f(x3, y3);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_LINES);
	for(int i = 0; i < nc; i++){
		Constraint2D * c = lp->getConstraint(i);
		double a0 = c->getA(0);
		double a1 = c->getA(1);
		double b = c->getB();

		glColor4f(1.0, 1.0, 1.0, 0.7);

		double x0 = (double) -MAXGL;
		double y0 = calcY(-MAXGL, a0, a1, b);

		double x1 = MAXGL;
		double y1 = calcY(MAXGL, a0, a1, b);


		glVertex2f(x0, y0);
		glVertex2f(x1, y1);
	}

	glColor4f(1.0, 1.0, 0.0, 1.0);

	double c0 = lp->getC(0);
	double c1 = lp->getC(1);

	double x0 = (double) -MAXGL;
	double y0 = calcY(-MAXGL, c0, c1, optZ);

	double x1 = MAXGL;
	double y1 = calcY(MAXGL, c0, c1, optZ);

	glVertex2f(x0, y0);
	glVertex2f(x1, y1);
	glEnd();


	resetColor();
}

void drawLine(double p0x, double p0y, double p1x, double p1y){
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2f( p0x, p0y);
		glVertex2f( p1x, p1y);
	glEnd();

	//resetColor();
}

void drawPoint(double x, double y){
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
 		glVertex2f(x, y);
 	glEnd();

 	resetColor();
}

/* The main drawing function. */
void DrawGLScene()
{
	 // Setup a 2D projection
 	glMatrixMode (GL_PROJECTION);
 	glLoadIdentity ();
 	//glOrtho (0, X_SIZE, Y_SIZE, 0, 0, 1);
 	glOrtho (0, WINDOW, WINDOW, 0, 0, 1);
 	glDisable(GL_DEPTH_TEST);
 	glMatrixMode (GL_MODELVIEW);
 	glLoadIdentity();
 	//glTranslatef(200, 200, 0);
 	glTranslatef((WINDOW/2) - optX + dx, (WINDOW/2) + optY + dy, 0);

 	// Draw a scene
 	glClearColor(0.0, 0.0, 0.0, 0);
 	glClear(GL_COLOR_BUFFER_BIT);
	glScalef(1.0f, -1.0f, 1.0f);

	drawLp();
	drawGrid();
	drawPoint(optX, optY);
	//drawPoint(100, 100);
	//drawPoint(0, 0);

  	// swap buffers to display, since we're double buffered.
  	glutSwapBuffers();
}


/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y)
{
    /* avoid thrashing this procedure */
    //usleep(100);

	switch(key){
		case 'o':
			WINDOW += 2;
			break;
		case 'i':
			WINDOW -= 2;
			if(WINDOW <= 0)
				WINDOW = 2;
			break;
	}

    /* If escape is pressed, kill everything. */
    if (key == ESCAPE){
		/* shut down our window */
		glutDestroyWindow(window);

		/* exit the program...normal termination. */
		exit(0);
	}
}

void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_LEFT :
			dx -= 1;
			break;
		case GLUT_KEY_RIGHT :
			dx += 1;
			break;
		case GLUT_KEY_UP :
			dy += 1;
			break;
		case GLUT_KEY_DOWN :
			dy -= 1;
			break;
	}
}

void onClick(int button, int state, int x, int y){
	//GLUT_DOWN – When mouse button is pressed
	//GLUT_UP – When mouse button is released
	if(state == GLUT_UP)
		return;

	switch(button){
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
	}
}

int main(int argc, char **argv)
{
	string inputFile;

	if(argc < 2){
		cout << "Please specify the linear program descriptor file: " << endl;
		cin >> inputFile;
	}
	else{
		inputFile = string(argv[1]);
	}

	lp = readLinearProgram2D(inputFile.c_str());

	if(lp == NULL){
		cout << "Error: impossible to read file '" << inputFile << "'"<< endl;
		return 1;
	}

	solveLinearProgram2D(lp, optX, optY, optZ);

	cout << endl << endl << "------------------ How to Use ------------------ " << endl;
	cout << endl << "Use arrow keys to change camera position" << endl << endl;
	cout << "Use key 'i' to Zoom-In" << endl;
	cout << "Use key 'o' to Zoom-Out" << endl << endl;
	cout << "------------------------------------------------ " << endl;

	srand(time(0));

  	/* Initialize GLUT state - glut will take any command line arguments that pertain to it or
     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */
  	glutInit(&argc, argv);

  	/* Select type of Display mode:
     Double buffer
     RGBA color
     Alpha components supported
     Depth buffer */
  	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

  	/* get a 640 x 480 window */
  	glutInitWindowSize(X_SIZE, Y_SIZE);

  	/* the window starts at the upper left corner of the screen */
  	glutInitWindowPosition(0, 0);

  	/* Open a window */
  	window = glutCreateWindow("Linear Programming 2D");

  	/* Register the function to do all our OpenGL drawing. */
  	glutDisplayFunc(&DrawGLScene);

  	/* Go fullscreen.  This is the soonest we could possibly go fullscreen. */
  	//glutFullScreen();

  	/* Even if there are no events, redraw our gl scene. */
  	glutIdleFunc(&DrawGLScene);

  	/* Register the function called when our window is resized. */
  	glutReshapeFunc(&ReSizeGLScene);

  	/* Register the function called when the keyboard is pressed. */
  	glutKeyboardFunc(&keyPressed);
  	glutSpecialFunc(processSpecialKeys);

	/* Tratar clique do mouse */
	glutMouseFunc(&onClick);

  	/* Initialize our window. */
  	InitGL(X_SIZE, Y_SIZE);

  	/* Start Event Processing Engine */
  	glutMainLoop();

	delete lp;

  	return 0;
}
