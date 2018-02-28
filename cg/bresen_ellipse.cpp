#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
using namespace std;
int center_x,center_y,smajor,sminor;
#define PI 3.14159265
void init()
{
    glClearColor(1.0,1.0,1.0,1.0);//Sets the color of the window
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);//Sets the size of the plane
}
void plot_point(int x, int y)
{
  glBegin(GL_POINTS);
  glVertex2f(xc+x, yc+y);
  glVertex2f(xc+x, yc-y);
  glVertex2f(xc-x, yc-y);
  glVertex2f(xc-x, yc+y);
  glEnd();
}
void drawCircle()
{
	glClear(GL_COLOR_BUFFER_BIT);
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
  
   glFlush();
}
void Init1()
{
  glClearColor(0.0,1.0,1.0,1);
  glColor3f(0.0,0.0,0.0);
  glOrtho(-1000,1000,-1000,1000,-1.0,1.0);
}
int main()
{
    int argc=0;
    char **argv;
    cout<<"Enter the coordinates of the center and semi major and semi minor axis"<<endl;
    cin>>center_x>>center_y>>smajor>>sminor;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Window");
    init();
    glutDisplayFunc(polEllipse);
    glutMainLoop();
    return 0;
}