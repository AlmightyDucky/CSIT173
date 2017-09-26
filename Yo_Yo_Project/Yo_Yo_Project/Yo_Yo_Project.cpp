// Yo_Yo_Project.cpp : Defines the entry point for the console application.
// Christopher Gonzalez
// 4/7/15

#include "stdafx.h"
#include <glut.h>
#include <gl\GL.h>
#include <math.h>

//functions
void init(); //initializes window
void displayImageFirst(); //first image to appear on the screen
void drawString(); //draws the string attached to the yo-yo
void drawYoYo(); //draws the yo-yo
void drawStar(); //draws the star on yo-yo
void drawButton(); //draws the blue button
void moveYoYo(); //moves the yo-yo up and down while spinning it
void handleButton(int button, int state, int x, int y); //controls the button and its functions

//width and height of the window
const int WIDTH = 1080;
const int HEIGHT = 720;

//static variables
static float PI = 3.14159;  //five decimal approxiate value of PI
static float radius = 75;   //radius used to define the size of a circle
static float INC = (PI/30); //angle measure for circle
//translation & rotation variables
static GLfloat spin = 0.0;
static GLfloat deltaX = 0.0;
static GLfloat deltaY = 0.0;
static GLfloat deltaZ = .001;

/* Objective: Displays a yo-yo and allows the user to click a button to move it down and up repeatedly
*  Paramaters: N/A
*  Return: N/A
*/
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	//double buffer, rgb color, multisample, 16 bit depth
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	//centers the window on the middle of the screen
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1080) / 2, 
		(glutGet(GLUT_SCREEN_HEIGHT) - 720) / 2);

	glutCreateWindow("Yo-Yo Project");

	glutDisplayFunc(displayImageFirst);
	glutMouseFunc(handleButton);

	init();
	glutMainLoop();

	return;
}

/* Objective: Initalizes the window's background color and clipping box
*  Parameters: N/A
*  Return: N/A
*/
void init()
{
	glClearColor(0.0,0.0,0.0,0.0); //clear color: black, alpa: 0
	glColor3f(1.0,1.0,1.0); //fill color: white

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluOrtho2D(0, WIDTH, HEIGHT, 0);

	return;
}

/* Objective: Displays the initial image to the screen
*  Parameters: N/A
*  Return: N/A
*/
void displayImageFirst()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawString();
	drawYoYo();
	drawButton();

	glutSwapBuffers();

	glFlush();

	return;
}

/* Objective: Draws the string of the yo-yo which grows/shrinks while the yoyo moves
*  Parameters: N/A
*  Return: N/A
*/
void drawString()
{
	glBegin(GL_LINES);
		glColor3f(0.79,.90,0.96); //very light blue/practically white color
		glVertex2f(560, 0);
		//moves second vertex to make it appear that it is shrinking/growing
		glVertex2f(560, 280 + deltaY);
	glEnd();

	return;
}

/* Objective: Draws a yo-yo from Kirby
*  Parameters: N/A
*  Return: N/A
*/
void drawYoYo()
{
	float theta;

	//back of yo-yo
	glBegin(GL_POLYGON);
		for (theta = 0.0; theta <= 2 * PI; theta += INC)
		{
			glColor3f(0.55, 0.0, 0.01); //dark red
			glVertex2f(540 + (radius + 5) * cos(theta), 280 + (radius + 5) * sin(theta));
		}
	glEnd();

	//front of yo-yo
	glBegin(GL_POLYGON);
		for (theta = 0.0; theta <= 2 * PI; theta += INC)
		{
			glColor3f(0.92, 0.0, 0.0); //red
			glVertex2f(540 + radius * cos(theta), 280 + radius * sin(theta));
		}
	glEnd();

	//slight shading behind yellow circle in middle
	glBegin(GL_POLYGON);
		for (theta = 0.0; theta <= 2 * PI; theta += INC)
		{
			glColor3f(0.83, 0.0, 0.0); //red
			glVertex2f(540 + (radius - 20) * cos(theta), 280 + (radius - 20) * sin(theta));
		}
	glEnd();

	//circle in the middle of the front of the yo-yo
	glBegin(GL_POLYGON);
		for (theta = 0.0; theta <= 2 * PI; theta += INC)
		{
			glColor3f(0.99, 0.92, 0.39); //light yellow
			glVertex2f(540 + (radius - 25) * cos(theta), 280 + (radius - 25) * sin(theta));
		}
	glEnd();

	drawStar(); //draws the star on the yo-yo

	return;
}

/* Objective: Draws the star design on the middle of the yo-yo
*  Parameters: N/A
*  Return: N/A
*/
void drawStar()
{
	//middle pentagon
	glBegin(GL_POLYGON);
		glColor3f(0.99, 0.98, 0.84); //very light yellow
		glVertex2f(520, 255);
		glVertex2f(560, 255);
		glVertex2f(570, 295);
		glVertex2f(540, 315);
		glVertex2f(510, 295);
	glEnd();

	/*color carries over to the rest of the polygons*/

	//top triangle
	glBegin(GL_POLYGON);
		glVertex2f(520, 255);
		glVertex2f(540, 235);
		glVertex2f(560, 255);
	glEnd();

	//right triangle
	glBegin(GL_POLYGON);
		glVertex2f(560, 255);
		glVertex2f(585, 265);
		glVertex2f(570, 295);
	glEnd();

	//bottom right triangle
	glBegin(GL_POLYGON);
		glVertex2f(570, 295);
		glVertex2f(568, 318);
		glVertex2f(540, 315);
	glEnd();

	//bottom left triangle
	glBegin(GL_POLYGON);
		glVertex2f(540, 315);
		glVertex2f(512, 318);
		glVertex2f(510, 295);
	glEnd();

	//left triangle
	glBegin(GL_POLYGON);
		glVertex2f(510, 295);
		glVertex2f(495, 265);
		glVertex2f(520, 255);
	glEnd();

	return;
}

/* Objective: Draws the button
*  Parameters: N/A
*  Return: N/A
*/
void drawButton()
{
	float theta;

	//gray circle on bottom of button
	glBegin(GL_POLYGON);
		for (theta = 0.0; theta <= 2 * PI; theta += INC)
		{
			glColor3f(0.25, 0.25, 0.33); //dark bluish gray
			glVertex2f(100 + (radius - 10) * cos(theta), 110 + (radius - 10) * sin(theta));
		}
	glEnd();

	//gray circle on bottom of button
	glBegin(GL_POLYGON);
		for (theta = 0.0; theta <= 2 * PI; theta += INC)
		{
			glColor3f(0.4, 0.4, 0.4); //gray
			glVertex2f(100 + (radius - 10) * cos(theta), 105 + (radius - 10) * sin(theta));
		}
	glEnd();

	//dark blue circle in middle of button
	glBegin(GL_POLYGON);
		for (theta = 0.0; theta <= 2 * PI; theta += INC)
		{
			glColor3f(0.0, 0.0, 0.8); //dark blue
			glVertex2f(100 + (radius - 20) * cos(theta), 110 + (radius - 20) * sin(theta));
		}
	glEnd();

	//blue circle ontop of button
	glBegin(GL_POLYGON);
		for (theta = 0.0; theta <= 2 * PI; theta += INC)
		{
			glColor3f(0.0, 0.3, 0.8); //blue
			glVertex2f(100 + (radius - 20) * cos(theta), 100 + (radius - 20) * sin(theta));
		}
	glEnd();

	return;
}

/* Objective: Handles how the button works
*  Parameters: N/A
*  Return: N/A
*/
void handleButton(int button, int state, int x, int y)
{
	static int index = -1;

	if (button == GLUT_LEFT_BUTTON)
	{
		//click range (mostly) limited to the blue part of button
	 if (x >= 43 && x <= 155 && y >= 45 && y < 160)
	 {
		 if (state == GLUT_DOWN)
		 {
			 glutIdleFunc(moveYoYo);
		 }
		 if (state == GLUT_UP)
		 {
			 glutIdleFunc(NULL);
		 }
	 }
	}
}

/* Objective: Translates the yo-yo up and down while spinning it
*  Parameters: N/A
*  Return: N/A
*/
void moveYoYo()
{
	static int goingUp = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (goingUp == 1)
	{
		deltaY -= 5; //moves up
		if (deltaY <= -180)
		{
			goingUp = 0;
		}
	}

	if (goingUp == 0)
	{
		deltaY += 5; //moves down
		if (deltaY >= 350)
		{
			goingUp = 1;
		}
	}

	spin -= 7; //speed of spin

	if (spin < 360)
	{
		spin += 360;
	}
	
	glPushMatrix();
		drawString(); //draw string last to prevent it from moving like the yoyo
		glTranslatef(540 + deltaX, 280 + deltaY, 0.0);
		if (goingUp == 1)
		{
			glRotatef(-spin, 0.0, 0.0, 1.0); //spins yoyo clockwise
		} else if (goingUp == 0)
		{
			glRotatef(spin, 0.0, 0.0, 1.0); //spins yoyo counterclockwise
		}
		glTranslatef(-540, -280, 0.0);
		drawYoYo(); //draw yoyo first to translate and spin it
	glPopMatrix();

	drawButton();
	glutSwapBuffers();
}