// PacMan_Project.cpp : Defines the entry point for the console application.
// Christopher Gonzalez
// 4/11/16

#include "stdafx.h"
#include "glut.h"
#include <gl\GL.h>
#include <math.h>

//window size
#define WIDTH 720
#define HEIGHT 480

#define PI 3.1417		//appox. value of pi
#define INC 0.003		//how much theta increases by when circles are made
#define radius 9		//button circle radius
#define PacManRadius 25 //PacMan body radius
#define pelletRadius 4  //pellet radius
#define angle PI/2		//circle definition

//translation and rotation variables
static int spin = 0;
static GLfloat deltaX = 0.0;
static GLfloat deltaY = 0.0;
static GLfloat deltaZ = 0.001;

//PacMan variables
static float mouthSize = 0.6; //size of PacMan's mouth

//pellet variables
const int numPellets = 8; //total number of pellets
const int deltaPellet = 50; //distance between two pellets

struct pellets
{
	int positionX; //x position of pellet
	int positionY; //y position of pellet
	GLbyte pelletOn; //whether the pellet is on the screen or not
};

//pellet segments
pellets pelletHoriSegment1[numPellets];
pellets pelletHoriSegment2[numPellets];
pellets pelletHoriSegment3[numPellets];
pellets pelletVertSegment1[numPellets];
pellets pelletVertSegment2[numPellets];

//other variables
static int index = -1;

//functions
int menuIndex(int x, int y);								 //controls each arrow of the button
void init();												 //initializes window
void display();												 //displays objects on screen
void initializePellets();									 //initializes the pellet lcoations
void drawPellet(int pRadius, int pelletX, int pelletY);		 //draws pellets
void drawPacMan();											 //draws PacMan
void drawMaze();											 //draws out the maze
void drawLeftMazePart();									 //draws left part of maze
void drawMiddleMazePart();									 //draws middle part of maze
void drawRightMazePart();									 //draws right part of maze
void drawButton();											 //draws a button
void reDrawPellets(pellets pelletArray[]);					 //redraws pellets if pellet is on
void handleButton(int button, int state, int x, int y);		 //button handler

/* Objective: Enables the arrows on the button to be controlled independently
*			  and control different actions
*  Parameters: int x
*			   int y
*  Return: int
*/
int menuIndex(int x, int y)
{
	//up arrow
	if (x >= 50 && x <= 60 && y >= 5 && y <= 45)
	{
		return 1;
	}

	//down arrow
	if (x >= 50 && x <= 60 && y >= 66 && y <= 96)
	{
		return 2;
	}

	//left arrow
	if (x >= 9 && x <= 39 && y >= 45 && y <= 60)
	{
		return 3;
	}

	//right arrow
	if (x >= 66 && x <= 96 && y >= 45 && y <= 60)
	{
		return 4;
	}

	return 5;
}

/* Objective: A simple PacMan program that features eatable pellets and very basic collision detection
*  Parameters: N/A
*  Return: N/A
*/
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(WIDTH/2, HEIGHT/2);

	glutCreateWindow("PacMan Project");

	glutDisplayFunc(display);
	glutMouseFunc(handleButton); //mouse handler

	init();
	glutMainLoop();

	return;
}

/* Objective: Initializes the window
*  Parameters:
*  Return:
*/
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluOrtho2D(0, WIDTH, HEIGHT, 0);

	return;
}

/* Objective: Displays an image of PacMan, pellets, and a button
*  Parameters: N/A
*  Return: N/A
*/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	initializePellets();
	drawPacMan();
	drawMaze();
	drawButton();

	glutSwapBuffers();


	return;
}

/* Objective: Draws the initial location of the pellets on the screen
*  Parameters: N/A
*  Return: N/A
*/
void initializePellets()
{
	int i;

	//filling in horizontal pellet segment 1
	for (i = 0; i < numPellets; i ++)
	{
		pelletHoriSegment1[i].positionX = (i * (deltaPellet + 30)) + 110;
		pelletHoriSegment1[i].positionY = 105;
		pelletHoriSegment1[i].pelletOn = 0;
	}

	//filling in horizontal pellet segment 2
	for (i = 0; i < numPellets; i ++)
	{
		pelletHoriSegment2[i].positionX = (i * (deltaPellet + 10)) + 200;
		pelletHoriSegment2[i].positionY = 240;
		pelletHoriSegment2[i].pelletOn = 0;
	}

	//filling in horizontal pellet segment 3
	for (i = 0; i < numPellets; i ++)
	{
		pelletHoriSegment3[i].positionX = (i * (deltaPellet + 30)) + 110;
		pelletHoriSegment3[i].positionY = 375;
		pelletHoriSegment3[i].pelletOn = 0;
	}

	//filling in vertical pellet segment 1
	for (i = 0; i < numPellets; i ++)
	{
		pelletVertSegment1[i].positionX = 270;
		pelletVertSegment1[i].positionY = (i * (deltaPellet + 18)) + 35;
		if (i == 1 || i == 3 || i == 5 || i == 7) //turn off every other pellet
		{
			pelletVertSegment1[i].pelletOn = 1;
		} else {
			pelletVertSegment1[i].pelletOn = 0;
		}
	}

	//filling in vertical pellet segment 2
	for (i = 0; i < numPellets; i ++)
	{
		pelletVertSegment2[i].positionX = 475;
		pelletVertSegment2[i].positionY = (i * (deltaPellet + 18)) + 35;
		if (i == 1 || i == 3 || i == 5 || i == 7) //turn off every other pellet
		{
			pelletVertSegment2[i].pelletOn = 1;
		} else {
			pelletVertSegment2[i].pelletOn = 0;
		}
	}

	//drawing pellet segment 1
	for (i = 0; i < numPellets; i ++)
	{
		drawPellet(pelletRadius, pelletHoriSegment1[i].positionX, pelletHoriSegment1[i].positionY);
	}

	//drawing pellet segment 1
	for (i = 0; i < numPellets; i ++)
	{
		drawPellet(pelletRadius, pelletHoriSegment2[i].positionX, pelletHoriSegment2[i].positionY);
	}

	//drawing pellet segment 1
	for (i = 0; i < numPellets; i ++)
	{
		drawPellet(pelletRadius, pelletHoriSegment3[i].positionX, pelletHoriSegment3[i].positionY);
	}

	//filling in vertical pellet segment 1
	for (i = 0; i < numPellets; i ++)
	{
		if (pelletVertSegment1[i].pelletOn == 0)
		{
			drawPellet(pelletRadius, pelletVertSegment1[i].positionX, pelletVertSegment1[i].positionY);
		}
	}

	//filling in vertical pellet segment 2
	for (i = 0; i < numPellets; i ++)
	{
		if (pelletVertSegment2[i].pelletOn == 0)
		{
			drawPellet(pelletRadius, pelletVertSegment2[i].positionX, pelletVertSegment2[i].positionY);
		}
	}

	return;
}

/* Objective: Draws a pellet at an X and Y coordinate
*  Parameters: int pRadius
*			   int pelletX
*			   int pelletY
*  Return: N/A
*/
void drawPellet(int pRadius, int pelletX, int pelletY)
{
	float theta;

	glBegin(GL_POLYGON);
		for (theta = 0.0; theta <= 2 * PI; theta += INC)
		{
			glColor4f(0.95, 0.95, 0.95, 0);
			glVertex2f(pelletX + pRadius * cos(theta), pelletY + pRadius * sin(theta));
		}
	glEnd();

	return;
}

/* Objective: Draws Pac Man as a yellow circle with his mouth as a black circle
*  Parameters: N/A
*  Return: N/A
*/
void drawPacMan()
{
	float theta;

	//PacMan Body
	glBegin(GL_POLYGON);
		for (theta = 0.0; theta <= 2 * PI; theta += INC)
		{
			glColor4f(1.0, 1.0, 0.3, 0);
			glVertex2f(100 + PacManRadius * cos(theta), 240 + PacManRadius * sin(theta));
		}
	glEnd();

	//PacMan Mouth
	glBegin(GL_POLYGON);
		glColor4f(0.0, 0.0, 0.0, 0.0);
		glVertex2f(100, 240);
		for (theta = -mouthSize; theta <= mouthSize; theta += INC)
		{
			glColor4f(0.0, 0.0, 0.0, 0.0);
			glVertex2f(100 + (PacManRadius + 1) * cos(theta), 240 + (PacManRadius + 1) * sin(theta));
		}
	glEnd();

	glFlush();
}

/* Objective: Draws a square button with four arrows inside and a circle in the center
*  Parameters: N/A
*  Return: N/A
*/
void drawButton()
{
	//corner box border
	glBegin(GL_POLYGON);
		glColor4f(0, 1, 1, 0);
		glVertex3i(110, 0, 0);
		glVertex3i(110, 110, 0);
		glVertex3i(0, 110, 0);
		glVertex3i(0, 0, 0);
	glEnd();

	//corner box
	glBegin(GL_POLYGON);
		glColor4f(1, 1, 1, 0);
		glVertex3i(105, 5, 0);
		glVertex3i(105, 105, 0);
		glVertex3i(5, 105, 0);
		glVertex3i(5, 5, 0);
	glEnd();

	//up & down arrow line
	glBegin(GL_POLYGON);
		glColor4f(1, 0.5, 0, 1);
		glVertex3i(60, 25, 0);
		glVertex3i(60, 85, 0);
		glVertex3i(50, 85, 0);
		glVertex3i(50, 25, 0);
	glEnd();

	//up arrow
	glBegin(GL_POLYGON);
		glColor4f(1, 0.5, 0, 1);
		glVertex3i(55, 5, 0);
		glVertex3i(65, 25, 0);
		glVertex3i(45, 25, 0);
	glEnd();

	//down arrow
	glBegin(GL_POLYGON);
		glColor4f(1, 0.5, 0, 1);
		glVertex3i(55, 105, 0);
		glVertex3i(65, 85, 0);
		glVertex3i(45, 85, 0);
	glEnd();

	//left & right arrow line
	glBegin(GL_POLYGON);
		glColor4f(1, 0.5, 0, 1);
		glVertex3i(85, 60, 0);
		glVertex3i(85, 50, 0);
		glVertex3i(25, 50, 0);
		glVertex3i(25, 60, 0);
	glEnd();

	//left arrow
	glBegin(GL_POLYGON);
		glColor4f(1, 0.5, 0, 1);
		glVertex3i(25, 45, 0);
		glVertex3i(5, 55, 0);
		glVertex3i(25, 65, 0);
	glEnd();

	//right arrow
	glBegin(GL_POLYGON);
		glColor4f(1, 0.5, 0, 1);
		glVertex3i(85, 45, 0);
		glVertex3i(105, 55, 0);
		glVertex3i(85, 65, 0);
	glEnd();

	//circle
	float t;
	glBegin(GL_POLYGON);
		for (t = 0.0; t <= 2 * PI; t += INC)
		{
			glColor4f(0, 0.2, 0.4, 1);
			glVertex2f(55 + radius * cos(t), 55 + radius * sin(t));
		}
	glEnd();

	glFlush();
}

/* Objective: Draws the maze onto the screen by drawing separate parts of the maze
*  Parameters: N/A
*  Return: N/A
*/
void drawMaze()
{
	/*maze color is dark blue*/
	drawLeftMazePart();
	drawMiddleMazePart();
	drawRightMazePart();

	glFlush();
}

/* Objective: Draws the left part of the maze onto the screen
*  Parameters: N/A
*  Return: N/A
*/
void drawLeftMazePart()
{
	
	/* -code format-
	* box position
	* inner line
	* outer line
	*/

	//top left "box"
	glBegin(GL_LINE_STRIP); //inner line
		glColor4f(0, 0, 1, 0);
		glVertex2f(0, 50);
		glVertex2f(210, 50);
		glVertex2f(210, 0);
	glEnd();
	glBegin(GL_LINE_STRIP); //outer line
		glColor4f(0, 0, 1, 0);
		glVertex2f(0, 70);
		glVertex2f(230, 70);
		glVertex2f(230, 0);
	glEnd();

	//upper-middle left "box"
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(0, 180);
		glVertex2f(210, 180);
		glVertex2f(210, 160);
		glVertex2f(0, 160);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(0, 200);
		glVertex2f(230, 200);
		glVertex2f(230, 140);
		glVertex2f(0, 140);
	glEnd();

	//lower-middle left "box"
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(0, 300);
		glVertex2f(210, 300);
		glVertex2f(210, 320);
		glVertex2f(0, 320);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(0, 280);
		glVertex2f(230, 280);
		glVertex2f(230, 340);
		glVertex2f(0, 340);
	glEnd();

	//bottom left "box"
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(0, 430);
		glVertex2f(210, 430);
		glVertex2f(210, 480);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(0, 410);
		glVertex2f(230, 410);
		glVertex2f(230, 480);
	glEnd();

	return;
}

/* Objective: Draws the middle part of the maze onto the screen
*  Parameters: N/A
*  Return: N/A
*/
void drawMiddleMazePart()
{
	
	/* -code format-
	* box position
	* inner line
	* outer line
	*/

	//top middle "box"
	glBegin(GL_LINE_STRIP); //inner line
		glColor4f(0, 0, 1, 0);
		glVertex2f(330, 0);
		glVertex2f(330, 50);
		glVertex2f(420, 50);
		glVertex2f(420, 0);
	glEnd();
	glBegin(GL_LINE_STRIP); //outer line
		glColor4f(0, 0, 1, 0);
		glVertex2f(310, 0);
		glVertex2f(310, 70);
		glVertex2f(440, 70);
		glVertex2f(440, 0);
	glEnd();

	//upper-middle middle "box"
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(330, 160);
		glVertex2f(330, 180);
		glVertex2f(420, 180);
		glVertex2f(420, 160);
		glVertex2f(330, 160);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(310, 140);
		glVertex2f(310, 200);
		glVertex2f(440, 200);
		glVertex2f(440, 140);
		glVertex2f(310, 140);
	glEnd();

	//lower-middle middle "box"
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(330, 300);
		glVertex2f(330, 320);
		glVertex2f(420, 320);
		glVertex2f(420, 300);
		glVertex2f(330, 300);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(310, 280);
		glVertex2f(310, 340);
		glVertex2f(440, 340);
		glVertex2f(440, 280);
		glVertex2f(310, 280);
	glEnd();

	//bottom middle "box"
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(330, 480);
		glVertex2f(330, 430);
		glVertex2f(420, 430);
		glVertex2f(420, 480);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(310, 480);
		glVertex2f(310, 410);
		glVertex2f(440, 410);
		glVertex2f(440, 480);
	glEnd();

	return;
}

/* Objective: Draws the right part of the maze onto the screen
*  Parameters: N/A
*  Return: N/A
*/
void drawRightMazePart()
{
	
	/* -code format-
	* box position
	* inner line
	* outer line
	*/

	//top right "box"
	glBegin(GL_LINE_STRIP); //inner line
		glColor4f(0, 0, 1, 0);
		glVertex2f(720, 50);
		glVertex2f(530, 50);
		glVertex2f(530, 0);
	glEnd();
	glBegin(GL_LINE_STRIP); //outer line
		glColor4f(0, 0, 1, 0);
		glVertex2f(720, 70);
		glVertex2f(510, 70);
		glVertex2f(510, 0);
	glEnd();

	//upper-middle right "box"
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(720, 180);
		glVertex2f(530, 180);
		glVertex2f(530, 160);
		glVertex2f(720, 160);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(720, 200);
		glVertex2f(510, 200);
		glVertex2f(510, 140);
		glVertex2f(720, 140);
	glEnd();

	//lower-middle right "box"
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(720, 280);
		glVertex2f(510, 280);
		glVertex2f(510, 340);
		glVertex2f(720, 340);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(720, 300);
		glVertex2f(530, 300);
		glVertex2f(530, 320);
		glVertex2f(720, 320);
	glEnd();

	//bottom right "box"
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(720, 410);
		glVertex2f(510, 410);
		glVertex2f(510, 480);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glColor4f(0, 0, 1, 0);
		glVertex2f(720, 430);
		glVertex2f(530, 430);
		glVertex2f(530, 480);
	glEnd();

	return;
}

/* Objective: Moves PacMan around the screen and updates the pellets on screen
*  Parameters: N/A
*  Return: N/A
*/
void translatePacBuddy()
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	//moves PacMan up and down
	if (index == 1 && deltaY >= -210 && ((deltaX >= 160 && deltaX <= 200) || (deltaX >= 360 && deltaX <= 390)))
	{
		deltaY -= .5; //up
		spin = -90;
	}

	if (index == 2 && deltaY <= 210 && ((deltaX >= 160 && deltaX <= 200) || (deltaX >= 360 && deltaX <= 390)))
	{
		deltaY += .5; //down
		spin = 90;
	}

	//moves PacMan left and right
	if (index == 3 && deltaX >= -70 && ((deltaY >= -16 && deltaY <= 16) || (deltaY >= 130 && deltaY <= 150) || (deltaY <= -130 && deltaY >= -150)))
	{
		deltaX -= .5; //left
		spin = 180;
	}

	if (index == 4 && deltaX <= 590 && ((deltaY >= -16 && deltaY <= 16) || (deltaY >= 130 && deltaY <= 150) || (deltaY <= -130 && deltaY >= -150)))
	{
		deltaX += .5; //right
		spin = 0;
	}

	//Actual PacMan translate
	glPushMatrix();
		glTranslatef(100 + deltaX, 240 + deltaY, 0);
		glRotatef(spin, 0, 0, 1);
		glTranslatef(-100, -240, 0);
		drawPacMan();
	glPopMatrix();

	/*pellet controls (on/off switches)*/
	//horiztonal pellet segment 1
	for (i = 0; i < numPellets; i ++)
	{
		if((deltaX >= (-20 + (i * (deltaPellet + 35))) && deltaX <= (20 + (i * (deltaPellet + 35)))) && (deltaY <= -130 && deltaY >= -150))
			pelletHoriSegment1[i].pelletOn = 1;
	}
	//horiztonal pellet segment 2
	for (i = 0; i < numPellets; i ++)
	{
		if((deltaX >= (100 + (i * (deltaPellet + 10))) && deltaX <= (105 + (i * (deltaPellet + 10))) ) && (deltaY <= 60 && deltaY >= -60))
			pelletHoriSegment2[i].pelletOn = 1;
	}
	//horiztonal pellet segment 3
	for (i = 0; i < numPellets; i ++)
	{
		if((deltaX >= (-20 + (i * (deltaPellet + 35))) && deltaX <= (20 + (i * (deltaPellet + 35)))) && (deltaY >= 130 && deltaY <= 150))
			pelletHoriSegment3[i].pelletOn = 1;
	}
	//vertical pellet segment 1
	for (i = 0; i < numPellets; i ++)
	{
		if((deltaX >= 160 && deltaX <= 200) && (deltaY >= (-220 + (i * (deltaPellet + 18))) && deltaY <= (-200 + (i * (deltaPellet + 18)))))
			pelletVertSegment1[i].pelletOn = 1;
	}
	//vertical pellet segment 2
	for (i = 0; i < numPellets; i ++)
	{
		if((deltaX >= 360 && deltaX <= 390) && (deltaY >= (-220 + (i * (deltaPellet + 18))) && deltaY <= (-200 + (i * (deltaPellet + 18)))))
			pelletVertSegment2[i].pelletOn = 1;
	}

	/*redraw pellets if switch is still on*/
	reDrawPellets(pelletHoriSegment1);
	reDrawPellets(pelletHoriSegment2);
	reDrawPellets(pelletHoriSegment3);
	reDrawPellets(pelletVertSegment1);
	reDrawPellets(pelletVertSegment2);

	drawMaze();
	drawButton();

	glutSwapBuffers();

	//conrols the speed of the mouth
	if (mouthSize > 0.05)
	{
		mouthSize -= 0.04;
	} else {
		mouthSize = 0.6;
	}

	return;
}

/* Objective: Redraws the pellets if they weren't eaten already
*  Parameters: pellets pelletArray[]
*  Return: N/A
*/
void reDrawPellets(pellets pelletArray[])
{
	int i;

	for (i = 0; i < numPellets; i ++)
	{
		if (pelletArray[i].pelletOn == 0)
		{
			drawPellet(pelletRadius, pelletArray[i].positionX, pelletArray[i].positionY);
		}
	}
}

/* Objective: Determines if the mouse was pressed down, which direction on the
*			  button was pressed and translates PacMan in the direction chosen
*  Parameters: int button
*			   int state
*			   int x
*			   int y
*  Return: N/A
*/
void handleButton(int button, int state, int x, int y)
{
	index = menuIndex(x,y);

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN && (index == 1 || index == 2 || index == 3 || index == 4))
		{
			glutIdleFunc(translatePacBuddy);
		}

		if (state == GLUT_UP)
		{
			glutIdleFunc(NULL);
		}
	}

	return;
}