#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
using namespace std;
int center_x,center_y,radius;
#define PI 3.14159265
void init()
{
    glClearColor(1.0,1.0,1.0,1.0);//Sets the color of the window
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);//Sets the size of the plane
}
int round_off(float x)
{
    int c=x;
    if(x-c>0.5)
        return c+1;
    else 
        return c;

}
void PolCircle()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);//Color of the vertices
    int x=center_x;
    int y=center_y+radius;
    glBegin(GL_POINTS); 
    
    while((x-center_x)<(y-center_y))
    {
        y=round_off(sqrt(radius*radius-x*x));
        //Plot all the points using the 8 fold symmetry of circle
        int x2=center_x+y-center_y;
        int y2=center_y+x-center_x;
        glVertex2s(2*center_x-x,y);
        glVertex2s(x,y);
        glVertex2s(2*center_x-x,2*center_y-y);
        glVertex2s(x,2*center_y-y);
        glVertex2s(2*center_x-x2,y2);
        glVertex2s(x2,y2);
        glVertex2s(2*center_x-x2,2*center_y-y2);
        glVertex2s(x2,2*center_y-y2);
        x++;
    }
    glEnd();
    glFlush();

}
int main()
{
    int argc=0;
    char **argv;
    cout<<"Enter the coordinates of the center and radius"<<endl;
    cin>>center_x>>center_y>>radius;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Window");
    init();
    glutDisplayFunc(PolCircle);
    glutMainLoop();
    return 0;
}