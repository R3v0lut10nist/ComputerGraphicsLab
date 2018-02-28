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
    glOrtho(-1000.0, 1000.0, -1000.0, 1000.0, -1.0, 1.0);//Sets the size of the plane
}
int round_off(float x)
{
    int c=x;
    if(x-c>0.5)
        return c+1;
    else 
        return c;

}
void ParametricEllipse()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);//Color of the vertices
    int x,y;
    glBegin(GL_POINTS); 
    double angle=90;
    while(angle>0)
    {
        x=center_x+round_off(smajor*cos((angle*PI)/180.0));
        y=center_y+round_off(sminor*sin((angle*PI)/180.0));
        int x2=center_x+y-center_y;
        int y2=center_y+x-center_x;
        //Plot all the points using the 8 fold symmetry of circle
        glVertex2s(2*center_x-x,y);
        glVertex2s(x,y);
        glVertex2s(2*center_x-x,2*center_y-y);
        glVertex2s(x,2*center_y-y);
        angle-=0.1;
    }
    glEnd();
    glFlush();

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
    glutDisplayFunc(ParametricEllipse);
    glutMainLoop();
    return 0;
}