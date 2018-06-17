#include<GL/glut.h>
#include<math.h>
#include<iostream>
#include<unistd.h>
#define WHITE 1
#define GREY 2
#define BLACK 3 
using namespace std;
int xi,yi,xf,yf,i;
int mat[10][10];
int dist[10][10];
int tmp,tmp2;
int count=0;
int a,b;
int heap[10];
int count2;
struct node
{
	int x,y;
	int data;
	int pred;
	int w;
	int lcount;
}ob[10];

void swap(int a[],int x,int y)
{
	int tmp;
	tmp=a[x];
	a[x]=a[y];
	a[y]=tmp;
}
void heapify(int a[],int n,int i)
{
	int small=i;
	int l=2*i+1;
	int r=l+1;
	if(l<n && ob[a[l]].w<ob[a[small]].w)
		small=l;
	if(r<n && ob[a[r]].w<ob[a[small]].w)
		small=r;
	if(small != i)
	{
		swap(a,i,small);
		heapify(a,n,small);
	}
}
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

void circle(int xCenter,int yCenter)		//Circle
{
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
//////////////////////////////////////////////	Line

void line(int x0, int y0, int x1, int y1)  
 {  
	glColor3f(1,0,0);
  	glBegin(GL_LINES);
		glVertex2i(x0,y0);
		glVertex2i(x1,y1);
	glEnd();
	glFlush(); 
 }  
 void line2(int x0, int y0, int x1, int y1)  
 {  
	glColor3f(0,0,0);
  	glBegin(GL_LINES);
		glVertex2i(x0,y0);
		glVertex2i(x1,y1);
	glEnd();
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
void initialize()
{
	for(i=0;i<count;i++)
	{
		ob[i].w=100;
		ob[i].pred=-1;
	}
	ob[0].w=0;
}
void relax(int u,int v,int w)
{
	if(ob[v].w>ob[u].w+w)
	{
		ob[v].w=ob[u].w+w;
		ob[v].pred=u;
	}

}

void bfs()
{
	int u;
	count2=count;
	for(i=0;i<count;i++)
		heap[i]=i;

	initialize();
	for(i=count/2-1;i>=0;i--)
	{
		heapify(heap,count,i);
	}
	while(count2>0)
	{
		u=heap[0];
		for(i=0;i<ob[u].lcount;i++)
			relax(u,mat[u][i],dist[u][i]);
		heap[0]=heap[count2-1];
		count2--;
		heapify(heap,count2,0);
	}
	for(i=count-1;i>0;i--)
		line2(ob[i].x,ob[i].y,ob[ob[i].pred].x,ob[ob[i].pred].y);
}
/////////////////////////////////////	Mouse Function
void mouse(int btn,int state,int x,int y)
{
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
				line(xi,yi,xf,yf);
				glFlush();
				cout<<"\nEnter edge distance "<<tmp<<" - "<<i<<" : ";
				cin>>dist[tmp][ob[tmp].lcount];
				mat[tmp][ob[tmp].lcount]=i;
				a=(xf+xi)/2;
				b=(yf+yi)/2;
				printChar(a,b,dist[tmp][ob[tmp].lcount]+48);
				glFlush();
				ob[tmp].lcount++;
				break;
			}
		
		}
		if(i==count)
			bfs();
		
		
	}
	
}

int main(int argc,char** argv)
{
	for(i=0;i<10;i++)
	{
		ob[i].lcount=0;
	}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(600,500);
	glutInitWindowPosition(100,200);
	glutCreateWindow("Algorithm");
		glutDisplayFunc(display);
		glutMouseFunc(mouse);

	glutMainLoop();
	return 0;
}