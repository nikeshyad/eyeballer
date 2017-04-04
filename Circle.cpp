#include "Circle.h" 

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#define _USE_MATH_DEFINES
#include <cmath>


Circle::Circle() {
	x = 0;
	y = 0;
	radius = 10;
}

Circle::Circle(int xcoord, int ycoord, int r) {
	x = xcoord;
	y = ycoord;
	radius = r;
}

void Circle::draw() {
	glColor3f(0., 255., 0.);
  	const int NUM_DIVS = 50;
  	glBegin(GL_TRIANGLE_FAN);
   	glVertex2d(x, y);
    for ( int i = 0; i < NUM_DIVS; ++i )
    	glVertex2d(x + radius*cos(i*2*M_PI/(NUM_DIVS-1)),
        	y + radius*sin(i*2*M_PI/(NUM_DIVS-1)));
  	glEnd();
}

int Circle::getRadius() {
	return radius;
}

int Circle::getX() {
	return x;
}

int Circle::getY() {
	return y;
}
