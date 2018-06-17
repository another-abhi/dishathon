#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <unistd.h>
#include <queue>
#define WHITE 1
#define GREY 2
#define BLACK 3 
using namespace std;
int xi,yi,xf,yf,i;

struct node
{
	int x,y;
	int data;
	int color;
	int pred;
	int lcount;
}ob[10]; 


int mat[10][10];
int tmp,tmp2;
int count=0;
struct Color
{
	float r;
	float g;
	float b;
};
Color grey={0.4,0.4,0.4};
Color white={1,1,1};
Color black={0,0,0};
Color bg={1,1,0};

void putPixel(int x,int y)		//putPixel
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();	
}

void printChar(int x,int y,char c)			//Print character
{
	glColor3f(1,0,0);
	glRasterPos2f(x,y);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,c);
	glFlush();
}
//////////////////////////////////////////////	Area filling

void circleFillColor(int xCenter, int yCenter, int x, int y, Color fillColor) 
{
	int yUp, yDown, limit, i;
	glColor3f(fillColor.r, fillColor.g, fillColor.b);
	glBegin(GL_POINTS);
		limit = xCenter + x; yUp = yCenter + y; yDown = yCenter - y;
		for( i = xCenter-x+1; i < limit; i++ )
		{
			glVertex2i(i, yUp);
			glVertex2i(i, yDown);
		}
		limit = xCenter + y; yUp = yCenter + x;	yDown = yCenter - x;
		for( i = xCenter-y+1; i < limit; i++ )
		{
			glVertex2i(i, yUp);
			glVertex2i(i, yDown);
		}
	glEnd();
}
/////////////////////////////////////////////////////
void circle(int xCenter,int yCenter)		//Circle
{
	//cout<<"\nEnter circle";
	int x,y,r,p;
	glColor3f(1,1,0);
	glPointSize(4.0f);	
	r=30;
	p=1-r;
	x=0;
	y=r;
	while(x<=y)
	{
		putPixel(xCenter+x,yCenter+y);
		putPixel(xCenter+y,yCenter+x);
		putPixel(xCenter-x,yCenter+y);
		putPixel(xCenter+y,yCenter-x);
		putPixel(xCenter-x,yCenter-y);
		putPixel(xCenter-y,yCenter-x);
		putPixel(xCenter+x,yCenter-y);
	 	putPixel(xCenter-y,yCenter+x);
		if(p<0)
			p=p+2*x+3;
		else
		{
			p=p+2*(x-y)+5;
			y=y-1;
		}
		x++;
	}
	glFlush();
}
//////////////////////////////////////////////	Line

void line(int x0, int y0, int x1, int y1)  
  {  
	cout<<"\nEnter line";
	glColor3f(1,0,0);
	glLineWidth(4.0f);
  	glBegin(GL_LINES);
  		glVertex2i(x0,y0);
  		glVertex2i(x1,y1);
  	glEnd();
	glFlush(); 
}  
void changecolor(int num,Color fillColor)
{	
	cout<<"\n Enters change color";
	int xCenter,yCenter;
	cout<<ob[num].x;
	cout<<ob[num].y;
	xCenter=ob[num].x;
	yCenter=ob[num].y;
	int x,y,r,p;
	r=30;
	p=1-r;
	x=0;
	y=r;
	circleFillColor(xCenter, yCenter, x, y, fillColor);
	while(x<=y)
	{
		putPixel(xCenter+x,yCenter+y);
		putPixel(xCenter+y,yCenter+x);
		putPixel(xCenter-x,yCenter+y);
		putPixel(xCenter+y,yCenter-x);
		putPixel(xCenter-x,yCenter-y);
		putPixel(xCenter-y,yCenter-x);
		putPixel(xCenter+x,yCenter-y);
	 	putPixel(xCenter-y,yCenter+x);
		if(p<0)
			p=p+2*x+3;
		else
		{
			p=p+2*(x-y)+5;
			y=y-1;
		}
		x++;
		circleFillColor(xCenter, yCenter, x, y, fillColor);
	}
	glFlush();
}
/////////////////////////////////////	Display Function
void display()
{
	glClearColor(0.5,1,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	glViewport(0,0,600,500);
	gluOrtho2D(0,600,0,500); 
	glFlush();
}
void bfs()
{
	cout<<"Enters bfs";
	int u;
	queue<int> nodeQueue;
	for(i=1;i<count;i++)
	{		
		cout<<"\n enters bfs lopp";
		ob[i].color=WHITE;
		changecolor(i,white);
		printChar(ob[i].x-10,ob[i].y-10,65+i);
	}
	ob[0].color=GREY;
	changecolor(0,grey);
	printChar(ob[0].x-10,ob[0].y-10,65);
	nodeQueue.push(0);
	sleep(2);
	while( !nodeQueue.empty() )
	{
		u= nodeQueue.front(); 
		nodeQueue.pop();
		for(i=0;i<ob[u].lcount;i++)
		{
			if(ob[mat[u][i]].color==WHITE)
			{
			ob[mat[u][i]].color=GREY;
			changecolor(mat[u][i],grey);
			printChar(ob[mat[u][i]].x-10,ob[mat[u][i]].y-10,65+mat[u][i]);
			sleep(1);
			nodeQueue.push(mat[u][i]);
			
			}
		}
	ob[u].color=BLACK;
	changecolor(u,black);
	printChar(ob[u].x-10,ob[u].y-10,65+u);
	sleep(1);
	}
}
/////////////////////////////////////	Mouse Function
void mouse(int btn,int state,int x,int y)
{
	Color boundary={1,1,0};
	Color fill={0,1,1};
	y=500-y;
	if(btn==GLUT_RIGHT_BUTTON  && state==GLUT_DOWN)
	{
		cout<<"\n Enters right button down";
		circle(x,y);
		ob[count].data=count;
		ob[count].x=x;
		ob[count].y=y;
		printChar(x-10,y-10,65+count);
		cout<<"\n count is"<<count;
		cout<<"node is"<<char(65+count)<<" \n ";
		count++;
		glFlush();
	}

	if(btn==GLUT_LEFT_BUTTON  && state==GLUT_DOWN)
	{
		cout<<"\nEnters left button down";
		xi=x;
		yi=y;
		for(i=0;i<count;i++)
		{
			if((abs(xi-ob[i].x)<=30)&&(abs(yi-ob[i].y)<=30))
			{
				xi=ob[i].x;
				yi=ob[i].y;
				tmp=i;
				break;
			}
		
		}
		cout<<"\nstart here is "<<char(65+i);	
	}
	if(btn==GLUT_LEFT_BUTTON  && state==GLUT_UP)
	{	
		cout<<"\nenters left button up";
		xf=x;
		yf=y;
		for(i=0;i<count;i++)
		{
			if((abs(xf-ob[i].x)<=30)&&(abs(yf-ob[i].y)<=30))
			{
				xf=ob[i].x;
				yf=ob[i].y;
				mat[tmp][ob[tmp].lcount]=i;
				ob[tmp].lcount++;
				tmp2=i;
				break;
			}
		}	
		cout<<"\nend here is "<<char(65+i) <<"\t  i "<< i;	
		if(i==count)
		{
			bfs();
		}
		cout<<"\n count is : "<<count;
		line(xi,yi,xf,yf);
		glFlush();
	}
}
////////////////////////////////////////////////keyboard funtion
void keyboard(unsigned char key,int x,int y)
{	
	cout<<"\n key pressed is "<<key;
	switch(key)
	{
		case 'e':exit(1);
			 	break;
		case 'b':bfs();
				cout<<"\n Enter bfs ";
				break;
		default: cout<<"\n invalid default";
				break;
	}		
}
int main(int argc,char** argv)
{
	for(i=0;i<10;i++)
		ob[i].lcount=0;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(600,500);
	glutInitWindowPosition(100,200);
	glutCreateWindow("BFS");
		glutDisplayFunc(display);
		glutMouseFunc(mouse);
		glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}
