#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

#define DEG2RAD 3.14/180
using namespace std;
typedef struct
{
float x;
float y;
}CIRCLE;

CIRCLE circle;
float r1,r2;
int xc,yc;
void plot_point(int x, int y)
{
  glBegin(GL_POINTS);
  glVertex2f(xc+x, yc+y);
  glVertex2f(xc+x, yc-y);
  glVertex2f(xc-x, yc-y);
  glVertex2f(xc-x, yc+y);
}
void drawCircle()
{
	glClear(GL_COLOR_BUFFER_BIT);
   
 glColor3f (0.0, 0.0, 0.0);//Color of the vertices
  
  int x=0,y=r1,a=r1,b=r2;
  int sigma,a2=a*a,b2=b*b,fb2=4*b*b,fa2=4*a*a;
  for (x = 0, y = b, sigma = 2*b2+a2*(1-2*b); b2*x <= a2*y; x++)
    {
        plot_point(x,y);
        if (sigma >= 0)
        {
            sigma += fa2 * (1 - y);
            y--;
        }
        sigma += b2 * ((4 * x) + 6);
    }

    for (x = a, y = 0, sigma = 2*a2+b2*(1-2*a); a2*y <= b2*x; y++)
    {
       plot_point(x,y);
        if (sigma >= 0)
        {
            sigma += fb2 * (1 - x);
            x--;
        }
        sigma += a2 * ((4 * y) + 6);
    }
  glEnd();
   glFlush();
}

void init()
{
    glClearColor(1.0,1.0,1.0,1.0);//Sets the color of the window
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);//Sets the size of the plane
}


int main(int argc, char **argv)
{

cin >> r1 >> r2>>xc>>yc;
	glutInit(&argc,argv);
 
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowPosition(20,0);
  glutInitWindowSize(800,800);

  glutCreateWindow("Ellipse");

  init();
	
	glutDisplayFunc(drawCircle);

  glutMainLoop();
  return 0;
}
