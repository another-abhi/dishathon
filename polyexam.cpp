/*TITLE   : SUTHERLAND HODGEMAN POLYGON CLIPPING ALGORITHM 
  AUTHOR  : RACHNA RAMESH
  ROLL NO : 246

 INPUT : The polygon to clip
*/

#include <iostream>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <GL/gl.h>

using namespace std;

const int x_max = 600;
const int y_max = 400;
const int x_min = 100;
const int y_min = 100;


int xc[100], yc[100],xLine[100], yLine[100], radius = 10, mouseX, mouseY, mouseLX, mouseLY, slope = 2, color[3], parent[10];
int pointsDrawn = 0, xLineNew[20], yLineNew[20], polygonSize = 0;

int sign(int x)                         //to determine the sign, used in line's function
{
	return((x > 0) ? 1 : ((x < 0) ? -1 : 0));
}


void line(int x2, int y2, int x3, int y3,int col)
{
	if(col == 0)
  		glColor3f(1.0, 1.0, 1.0 );
	else
		glColor3f(0.8, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2i(x2,y2);
		glVertex2i(x3,y3);
	glEnd();
	glFlush();
}
void drawCircleLine()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 1.0, 1.0);
	line( x_min, y_min, x_max, y_min,  0 );
  	line( x_max, y_min, x_max, y_max,  0 );
  	line( x_min, y_max, x_max, y_max,  0 );
  	line( x_min, y_min, x_min, y_max,  0 );
	for(int i = 0; i < pointsDrawn && pointsDrawn > 1; i+=1)
	{
		
		//glColor3f(0.8, 0, 0);
		line(xLine[i], yLine[i], xLine[(i+1)%pointsDrawn], yLine[(i+1)%pointsDrawn],  1);
	}
}

int xIntersect(int x1, int y1, int x2, int y2, int xi, int yi, int xj, int yj)
{
	int num = ((x1*y2 - y1*x2) * (xi-xj)) - ((x1-x2) * (xi*yj - yi*xj));
	int den = ((x1-x2) * (yi-yj)) - ((y1-y2) * (xi-xj));
	cout<<num<<" "<<den<<endl;
    	return num/den;
}

int yIntersect(int x1, int y1, int x2, int y2, int xi, int yi, int xj, int yj)
{
	int num = ((x1*y2 - y1*x2) * (yi-yj)) - ((y1-y2) * (xi*yj - yi*xj));
	int den = ((x1-x2) * (yi-yj)) - ((y1-y2) * (xi-xj));
	cout<<num<<" "<<den<<endl;
	return num/den;
}

void checkBothInside(int xj, int yj)
{
	//cout << "Completely Inside";
	xLineNew[polygonSize] = xj;
	yLineNew[polygonSize] = yj;
	polygonSize++;
}

void checkFirstOutside(int x1, int y1, int x2, int y2, int xi, int yi, int xj, int yj)
{
	xLineNew[polygonSize] = xIntersect(x1, y1, x2, y2, xi, yi, xj, yj );
	yLineNew[polygonSize] = yIntersect(x1, y1, x2, y2, xi, yi, xj, yj );
	polygonSize++;

	xLineNew[polygonSize] = xj;
	yLineNew[polygonSize] = yj;
	polygonSize++;
}

void checkSecondOutside(int x1, int y1, int x2, int y2, int xi, int yi, int xj, int yj)
{
	xLineNew[polygonSize] = xIntersect(x1, y1, x2, y2, xi, yi, xj, yj );
	yLineNew[polygonSize] = yIntersect(x1, y1, x2, y2, xi, yi, xj, yj );
	polygonSize++;
}

void polygonClip(int x1, int y1, int x2, int y2)
{
	 polygonSize = 0;
	//cout << "\nPointsDrawn : " << pointsDrawn;
	for(int i = 0; i < pointsDrawn; i++)
	{
		int j = (i+1)%pointsDrawn;
		int xi = xLine[i], yi = yLine[i];
		int xj = xLine[j], yj = yLine[j];

		int positioni = ((x2-x1) * (yi-y1)) - ((y2-y1) * (xi - x1));
		int positionj = ((x2-x1) * (yj-y1)) - ((y2-y1) * (xj-x1));

		if(positioni < 0 && positionj < 0)
			checkBothInside(xj, yj);
		else if(positioni >= 0 && positionj < 0)
			checkFirstOutside(x1, y1, x2, y2, xi, yi, xj, yj);
		else if(positioni < 0 && positionj >= 0)
			checkSecondOutside(x1, y1, x2, y2, xi, yi, xj, yj);
			//do nothing
	}
	pointsDrawn = polygonSize;
	for(int i = 0; i < polygonSize; i++)
	{
		xLine[i] = xLineNew[i];
		yLine[i] = yLineNew[i];
	}
	drawCircleLine();
}

void sutherHodge()
{
	cout << "\nIn sutherHodge";
	polygonClip( x_min, y_min, x_min, y_max);
  	polygonClip( x_min, y_max, x_max, y_max);
  	polygonClip( x_max, y_max, x_max, y_min);
  	polygonClip( x_max, y_min, x_min, y_min);
	//drawCircleLine();
}

void mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)              //if a left-click occured
	{
		xLine[pointsDrawn] = mouseLX = x;
		yLine[pointsDrawn] = mouseLY = 500 - y;
		pointsDrawn++;
		xLine[pointsDrawn] = xLine[0];
		yLine[pointsDrawn] = yLine[0];
	}
	drawCircleLine();
}

void keyboardPress(unsigned char key, int x, int y)
{
		xLine[pointsDrawn] = xLine[0];
		yLine[pointsDrawn] = yLine[0];
		pointsDrawn++;
	switch(key)
	{
		case  's' : sutherHodge();           //if 's' character id pressed, then start line clipping
			break;
		default : cout << "\nUnknown Key " << endl;
	}
	//drawCircleLine();
}

void init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Polygon Clipping");
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0);
	glColor3f(1.0, 1.0, 1.0);
	gluOrtho2D(0, 800, 0, 500);
	//initAdjMatrix();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	init();
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboardPress);
	glutDisplayFunc(drawCircleLine);
	glutMainLoop();
	return 0;
}
/*   ------------END OF PROGRAM---------- */

