// First_OpenGL_Project.cpp : Defines the entry point for the console application.
// Christopher Gonzalez
// 3/17/16

#include "stdafx.h"
#include <glut.h>
#include <GL/gl.h>

//general GL functions
void display();
void init();
//functions used to create the sword
void createBlade();
void createGuard();
void createHilt();

//variables that establish the window size
const int width = 720;
const int height = 480;

void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("First_OpenGL_Project");
	glutDisplayFunc(display);
	init();
	glutMainLoop();

	return;
}

/* Objective: Displays an image to the screen
*  Parameters: N/A
*  Return: N/A
*/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	createBlade();
	createGuard();
	createHilt();

	glFlush();

	return;
}

/* Objective: 
*  Parameters: N/A
*  Return: N/A
*/
void init()
{
	glClearColor(1.0,1.0,1.0,1.0); //white background
	glColor3f(0.0,0.0,0.0); //sets fill color to black

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-9.0,11.0,-9.0,11.0);

	return;
}

/* Objective: Creates the blade of the sword using primitives and color
*  Parameters: N/A
*  Return: N/A
*/
void createBlade()
{
	//little triangle on tip of blade
	glBegin(GL_POLYGON);
		glColor3f(0.5,0.1,0.05); //red
		glVertex2f(-5,3);
		glVertex2f(-8,9);
		glVertex2f(-8,5);
	glEnd();

	//body of the blade as a rectangle
	glBegin(GL_POLYGON);
		glColor3f(0.5,0.1,0.05); //red
		glVertex2f(5,0);
		glVertex2f(5,-2);
		glColor3f(0,0,0); //black
		glVertex2f(-8,1);
		glColor3f(0.5,0.1,0.05); //red
		glVertex2f(-8,5);
	glEnd();

	return;
}

/* Objective: Creates the guard of the sword using primitives and color
*  Parameters: N/A
*  Return: N/A
*/
void createGuard()
{
	//top part of the '3D' guard as a rectangle
	glBegin(GL_POLYGON);
		glColor3f(0.42,0.39,0.39); //light gray
		glVertex2f(6,2.5);
		glVertex2f(7,-.5);
		glVertex2f(6,-.5);
		glVertex2f(5,2.5);
	glEnd();

	//bottom part of the '3D' guard as a triangle
	glBegin(GL_POLYGON);
		glColor3f(0.23,0.21,0.21); //dark gray
		glVertex2f(6,-2.2);
		glVertex2f(5,-4.5);
		glVertex2f(7,-2.2);
	glEnd();

	//middle part of '3D' guard as a trapezoid
	glBegin(GL_POLYGON);
		glColor3f(0.42,0.39,0.39); //light gray
		glVertex2f(5,2.5);
		glColor3f(0.25,0.23,0.23); //gray
		glVertex2f(6,-.5);
		glVertex2f(6,-2.2);
		glVertex2f(5,-4.5);
	glEnd();

	return;
}

/* Objective: Creates the hilt of the sword using primitives and color
*  Parameters: N/A
*  Return: N/A
*/
void createHilt()
{
	//top part of hilt as a rectangle
	glBegin(GL_POLYGON);
		glColor3f(0.38,0.35,0.35); //light gray
		glVertex2f(7,-.5);
		glVertex2f(10,-1.5);
		glVertex2f(9,-1.5);
		glVertex2f(6,-.5);
	glEnd();

	//middle part of hilt as a rectangle
	glBegin(GL_POLYGON);
		glColor3f(0.25,0.23,0.23); //gray
		glVertex2f(6,-.5);
		glVertex2f(9,-1.5);
		glVertex2f(9,-3.2);
		glVertex2f(6,-2.2);
	glEnd();

	//end of hilt as a square
	glBegin(GL_POLYGON);
		glColor3f(0.23,0.21,0.21); //dark gray
		glVertex2f(9,-1.5);
		glVertex2f(10,-1.5);
		glVertex2f(10,-3.2);
		glVertex2f(9,-3.2);
	glEnd();

	return;
}