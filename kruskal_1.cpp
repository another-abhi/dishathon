#include<GL/glut.h>
#include<math.h>
#include<iostream>
#include<unistd.h>

using namespace std;
int xi,yi,xf,yf,i;
int mat[10][10];
int dist[10][10];
int tmp,tmp2;
int a,b;
int count=0;

struct node
{
	int x,y;
	int data;
	int pred;
	int w;
	int lcount;
}N[10];
int node_count=0;
	
struct edge
{
	int n1;
	int n2;
	int weight;
	int process;
};
edge E[50];
int edge_count=0;
int weight[50];
int weight_count;

struct subset
{
	int parent;
	int rank;
};
int find (struct subset subsets[],int i)
{
	if(subsets[i].parent != i)
	{
		subsets[i].parent = find(subsets,subsets[i].parent);
	}
	return subsets[i].parent;
}
void Union(struct subset subsets[],int x,int y)
{
	int xroot=find(subsets,x);
	int yroot=find(subsets,y);

	if(subsets[xroot].rank <subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if(subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent=xroot;
	else
	{
		subsets[yroot].parent=xroot;
		subsets[xroot].rank++;
	}
}
void putPixel(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
void printChar(int x,int y,char c)
{
	glColor3f(1,0,0);
 	glRasterPos2f(x,y);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,c);
	glFlush();
}
void circle(int xCenter,int yCenter)
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
void line(int x0,int y0,int x1,int y1)
{
	glColor3f(1,0,0);
	glBegin(GL_LINES);
		glVertex2i(x0,y0);
		glVertex2i(x1,y1);
	glEnd();
	glFlush();
}
void line2(int x0,int y0,int x1,int y1)
{
	glLineWidth(4.0);
	glColor3f(1,1,1);
	glBegin(GL_LINES);
		glVertex2i(x0,y0);
		glVertex2i(x1,y1);
	glEnd();
	glFlush();
}
void insertionSort(int arr[], int n)
{
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1;
 
       /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}

void printArray(int arr[], int n)
{
   int i;
   for (i=0; i < n; i++)
       printf("%d ", arr[i]);
   printf("\n");
}

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

void kruskal()
{
	cout<<"\nEnters logic.";
	int start=0,node_1,node_2;
	int e=0,k=0;
	
	struct subset *subsets =
        (struct subset*) malloc( node_count * sizeof(struct subset) );
 
    // Create V subsets with single elements
    for (int v = 0; v < node_count; v++)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    cout<<"\n Subsets created are: ";
     for (int v = 0; v < node_count; v++)
    {
      	 cout<< subsets[v].parent;
         cout<< " " << subsets[v].rank;
         cout<<"\n";
    }

 
    // Number of edges to be taken is equal to V-1
    while (e < (node_count - 1))
    {
        // Step 2: Pick the smallest edge. And increment 
        // the index for next iteration
        start=weight[k];
		for(i=0;i<edge_count;i++)
		{
			if(start==E[i].weight && E[i].process==0)
			{
				node_1=E[i].n1;
				node_2=E[i].n2;
				break;
			}
		}

 
        int x = find(subsets, node_1);
        int y = find(subsets, node_2);
 
        // If including this edge does't cause cycle,
        // include it in result and increment the index 
        // of result for next edge
        if (x != y)
        {
            e++;
            Union(subsets, x, y);
            glLineWidth(4.0);
            line2(N[node_1].x,N[node_1].y,N[node_2].x,N[node_2].y);
        }
        // Else discard the next_edge
        E[i].process=1;
        k++;
    }	
	
}

void initialize()
{
	
/*-------------------------------------------*/
	  printArray(weight,weight_count);
	  insertionSort(weight,weight_count);
	  printArray(weight,weight_count);
//*------------------------------------------*/

	  kruskal();
}

void mouse(int btn,int state,int x,int y)
{
	y=500-y;
	if(btn == GLUT_RIGHT_BUTTON && state ==GLUT_DOWN)
	{
		circle(x,y);
		N[node_count].data=node_count;
		N[node_count].x=x;
		N[node_count].y=y;
		printChar(x-10,y-10,65+node_count);
		node_count++;
		glFlush();
	}
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		xi=x;
		yi=y;
		for(i=0;i<node_count;i++)
		{
			if((abs(xi-N[i].x)<=30) && (abs(yi-N[i].y)<=30))
			{
				xi=N[i].x;
				yi=N[i].y;
				tmp=i;
				break;
			}
		}
	}
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		xf=x;
		yf=y;
		for(i=0;i<node_count;i++)
		{
			if((abs(xf-N[i].x)<=30)&&(abs(yf-N[i].y)<=30))
			{
				xf=N[i].x;
				yf=N[i].y;
				line(xi,yi,xf,yf);
				tmp2=i;
				glFlush();
				cout<<"\nEnter edge distance"<<tmp<<"-"<<i<<":";
				cin>>E[edge_count].weight;
				weight[weight_count]=E[edge_count].weight;
				weight_count++;
				E[edge_count].n1=tmp;
				E[edge_count].n2=tmp2;
				E[edge_count].process=0;
				a=(xf+xi)/2;
				b=(yf+yi)/2;
				printChar(a,b,E[edge_count].weight+48);
				edge_count++;
				glFlush();
				N[tmp].lcount++;
				break;
			}
		}
	}

	if(i==node_count)
	{
		cout<<"\nEnter kruskal program.\n";
		initialize();

	}
}

void keyboard(unsigned char key,int x,int y)
{

	cout<<"\n key pressed is "<<key;
	switch(key)
	{
		case 'e':exit(1);
			 break;
		case 'k':initialize();
				break;
		case 'n':cout<<"\n invlaid n ";
				break;
		default: cout<<"\n invalid default";
				break;
	}	
	
}


int main(int argc,char** argv)
{
		for(i=0;i<10;i++)
		{
			N[i].lcount=0;
		}
		glutInit(&argc,argv);
		glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
		glutInitWindowSize(600,500);
		glutInitWindowPosition(100,200);
		glutCreateWindow("Kruskal");
		glutDisplayFunc(display);
		glutMouseFunc(mouse);
		glutKeyboardFunc(keyboard);
		glutMainLoop();
		return 0;
}
