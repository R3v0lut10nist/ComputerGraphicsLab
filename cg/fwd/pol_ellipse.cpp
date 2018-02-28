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
int round_off(float x)
{
    int c=x;
    if(x-c>0.5)
        return c+1;
    else 
        return c;

}
void polEllipse()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);//Color of the vertices
    int x=center_x;
    int y=center_y+sminor;
    glBegin(GL_POINTS); 
    glVertex2s(x,y);
    glVertex2s(2*center_x-x,y);
    glVertex2s(2*center_x-x,2*center_y-y);
    glVertex2s(x,2*center_y-y);
    while(sminor*sminor*(x-center_x)<smajor*smajor*y-center_y)
    {
        y=center_y+round_off((sminor/(smajor*1.0))*sqrt(smajor*smajor-(x-center_x)*(x-center_x)));
        glVertex2s(2*center_x-x,y);
        glVertex2s(x,y);
        glVertex2s(2*center_x-x,2*center_y-y);
        glVertex2s(x,2*center_y-y);
        x++;
    }
    while(y>=center_y)
    {
        x=center_x+round_off((smajor/(sminor*1.0))*sqrt(sminor*sminor-(y-center_y)*(y-center_y)));
        glVertex2s(2*center_x-x,y);
        glVertex2s(x,y);
        glVertex2s(2*center_x-x,2*center_y-y);
        glVertex2s(x,2*center_y-y);
        y--;
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
    glutDisplayFunc(polEllipse);
    glutMainLoop();
    return 0;
}