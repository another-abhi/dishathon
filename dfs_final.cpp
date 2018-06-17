#include<GL/glut.h>
#include<math.h>
#include<iostream>
#include<unistd.h>
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
	int lcount;	//no of links from the current node
}ob[10];
int mat[10][10];
int tmp,tmp2;
int count=0;
struct Color
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

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
//////////////////////////////////////////////	bound filling
Color getPixelColor(int x,int y)
{
	Color color;
	glReadPixels(x,y,1,1,GL_RGBA,GL_FLOAT,&color);
	return color;
}
void setPixelColor(int x,int y,Color fill)
{
	glColor3f(fill.r,fill.g,fill.b);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
void areaFill(int x,int y,Color boundary,Color fill)
{		
	Color color;
	color=getPixelColor(x,y);
	if((color.r!=boundary.r && color.g!=boundary.g && color.b!=boundary.b)&&(color.r!=fill.r && color.g!=fill.b && color.b!=fill.b))
	{
		setPixelColor(x,y,fill);
		areaFill(x+1,y,boundary,fill);
		areaFill(x-1,y,boundary,fill);
		areaFill(x,y+1,boundary,fill);
		areaFill(x,y-1,boundary,fill);
	}
}

void circle(int xCenter,int yCenter)		//Circle
{
	glPointSize(4.0f);
	int x,y,r,p;
	glColor3f(1,1,0);
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
//	Line

 
void line(int x0, int y0, int x1, int y1)  
{  
	glColor3f(1,0,0);
  	int dx = abs (x1 - x0);  
  	int dy = abs (y1 - y0);  
  	int x, y;  
  	if (dx >= dy)  
  	{  
   		int d = 2*dy-dx;  
   		int ds = 2*dy;  
   		int dt = 2*(dy-dx);  
       		if (x0 < x1)   
       		{  
           		x = x0;  
            		y = y0;  
       		}  
       		else  
       		{   
       	     		x = x1;  
             		y = y1;  
             		x1 = x0;  
             		y1 = y0;  
        	}  
       		putPixel (x, y);  
   		while (x < x1)  
   		{  
        		if (d < 0)  
        		d += ds;  
        		else 
			{  
             			if (y < y1) 
				{  
              				y++;  
              				d += dt;  
             			}   
             			else 
				{  
              				y--;  
  					d += dt;  
             			}  
            		}  
   			x++;  
        		putPixel (x, y);  
       		}  
       }  
       else {   
             int d = 2*dx-dy;  
             int ds = 2*dx;  
             int dt = 2*(dx-dy);  
             if (y0 < y1) {  
             x = x0;  
             y = y0;  
             }  
             else {   
             x = x1;  
             y = y1;  
             y1 = y0;  
             x1 = x0;  
             }  
            putPixel (x, y);   
        while (y < y1)  
        {  
              if (d < 0)  
                 d += ds;  
              else {  
                      if (x > x1){  
                      x--;  
                      d += dt;  
                   } else {  
                      x++;  
                      d += dt;  
                   }  
              }  
              y++;  
              putPixel (x, y);  
        }  
       } 
glFlush(); 
}
void changecolor(int num)
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
/////////////////////////////////////	Display Function
void display()
{
	glClearColor(0,1,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,600,500);
	gluOrtho2D(0,600,0,500); 
	
	glFlush();
}
void visit(int u)
{
	int j;
	Color grey={0.4,0.4,0.4};
	Color white={1,1,1};
	Color black={0,0,0};
	Color bg={1,1,0};
	ob[u].color=GREY;
	//areaFill(ob[u].x,ob[u].y,bg,grey);
	glColor3f(0.4,0.4,0.4);
	changecolor(u);
	printChar(ob[u].x-10,ob[u].y-10,65+u);
	sleep(1);
	for(j=0;j<ob[u].lcount;j++)
	{
		if(ob[mat[u][j]].color==WHITE)
		{
			visit(mat[u][j]);
		}
	}
	ob[u].color=BLACK;
	//areaFill(ob[u].x,ob[u].y,bg,black);
	glColor3f(0,0,0);
	changecolor(u);
	printChar(ob[u].x-10,ob[u].y-10,65+u);
	sleep(1);

}
void dfs()
{
	int u;
	Color grey={0.4,0.4,0.4};
	Color white={1,1,1};
	Color black={0,0,0};
	Color bg={1,1,0};
	for(i=0;i<count;i++)
	{	
		ob[i].color=WHITE;
		//areaFill(ob[i].x,ob[i].y,bg,white);
		glColor3f(1,1,1);
		changecolor(i);
		printChar(ob[i].x-10,ob[i].y-10,65+i);
	}
	sleep(2);
	for(i=0;i<count && ob[i].color==WHITE;i++)
		visit(i);
}
/////////////////////////////////////	Mouse Function
void mouse(int btn,int state,int x,int y)
{
	Color boundary={1,1,0};
	Color fill={0,1,1};
	y=500-y;
	if(btn==GLUT_RIGHT_BUTTON  && state==GLUT_DOWN)
	{
		circle(x,y);
		ob[count].data=count;
		ob[count].x=x;
		ob[count].y=y;
		printChar(x-10,y-10,65+count);
		count++;
		glFlush();
	}

	if(btn==GLUT_LEFT_BUTTON  && state==GLUT_DOWN)
	{
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
	}
	if(btn==GLUT_LEFT_BUTTON  && state==GLUT_UP)
	{
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
		if(i==count)
			dfs();
		line(xi,yi,xf,yf);
		circle(xi,yi);
		circle(xf,yf);
		areaFill(xi,yi,boundary,fill);
		areaFill(xf,yf,boundary,fill);
		
		printChar(ob[tmp].x-10,ob[tmp].y-10,65+ob[tmp].data);
		printChar(ob[tmp2].x-10,ob[tmp2].y-10,65+ob[tmp2].data);
		glFlush();
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
	glutCreateWindow("DFS");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);

	glutMainLoop();
	return 0;
}
