#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <iostream>
#include "geometry2d.h"

/* ASCII code for the escape key. */
#define ESCAPE 27

using namespace std;
using namespace geometry2d;

/* The number of our GLUT window */
int window;

const int X_SIZE = 640;
const int Y_SIZE = 480;

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

  	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

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
	glColor3f(1.0, 1.0, 1.0);
}

// Pontos a serem exibidos
vector<Point2D> p;
// Convex Hull de p
vector<Point2D> ch;

void drawPolygon(const vector<Point2D> & poli){
	int n = poli.size();
	if(n == 0) return;

	glBegin(GL_LINE_STRIP);				// start drawing a polygon
	for(int i = 0; i < n; i++)
		glVertex2f( poli[i].getX(), poli[i].getY());		// Top
	glVertex2f( poli[0].getX(), poli[0].getY());
	glEnd();					// we're done with the polygon

	resetColor();
}

void drawPoints(){
	int n = p.size();
	if(n == 0) return;

	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	for(int i=0; i<n; i++)
 		glVertex2f(p[i].getX(), p[i].getY());
 	glEnd();

 	resetColor();
}

/* The main drawing function. */
void DrawGLScene()
{
	 // Setup a 2D projection
 	glMatrixMode (GL_PROJECTION);
 	glLoadIdentity ();
 	glOrtho (0, X_SIZE, Y_SIZE, 0, 0, 1);
 	glDisable(GL_DEPTH_TEST);
 	glMatrixMode (GL_MODELVIEW);
 	glLoadIdentity();
 	//Displacement trick for exact pixelization
 	glTranslatef(0.375, 0.375, 0);

 	// Draw a scene
 	glClearColor(.3, .3, .3, 0);
 	glClear(GL_COLOR_BUFFER_BIT);

	drawPoints();
	drawPolygon(ch);

  	// swap buffers to display, since we're double buffered.
  	glutSwapBuffers();
}

// Algoritmos de convex hull
GrahamScanAlgorithm graham;
DivideAndConquerConvexHullAlgorithm divideAndConquer;

void generateRandomPoint(){
	double noise = 1.0 / (rand() + 1.0);
	p.push_back(Point2D((rand() % X_SIZE) - noise, (rand() % Y_SIZE) - noise));
}

void addNewPoint(int x, int y){
	p.push_back(Point2D(x, y));
}

void runGrahamScan(){
	ch = p;
	graham.convexHull(ch);
}

void runDivideAndConquer(){
	ch = p;
	divideAndConquer.convexHull(ch);
}

void clearAll(){
	p.clear();
	ch.clear();
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y)
{
    /* avoid thrashing this procedure */
    //usleep(100);

	switch(key){
		case 'c':
			clearAll();
			break;
		case 'p':
			generateRandomPoint();
			break;
		case 'g':
			runGrahamScan();
			break;
		case 'd':
			runDivideAndConquer();
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

void onClick(int button, int state, int x, int y){
	//GLUT_DOWN – When mouse button is pressed
	//GLUT_UP – When mouse button is released
	if(state == GLUT_UP)
		return;

	// GLUT_LEFT_BUTTON – when left mouse button click is detected
	// GLUT_RIGHT_BUTTON  - when right mouse button click is detected
	// GLUT_MIDDLE_BUTTON – when middle mouse button click is detected
	switch(button){
		case GLUT_LEFT_BUTTON:
			addNewPoint(x, y);
			break;
		case GLUT_RIGHT_BUTTON:
			//runDivideAndConquer();
			runGrahamScan();
			break;
		case GLUT_MIDDLE_BUTTON:
			clearAll();
			break;
	}
}

int main(int argc, char **argv)
{
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
  	window = glutCreateWindow("Convex Hull Algorithm Tests");

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

	/* Tratar clique do mouse */
	glutMouseFunc(&onClick);

  	/* Initialize our window. */
  	InitGL(X_SIZE, Y_SIZE);

  	/* Start Event Processing Engine */
  	glutMainLoop();

  	return 0;
}
