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
void bsEllipse()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);//Color of the vertices
    int x=center_x;
    int y=center_y+sminor;
    glBegin(GL_POINTS);
    int smn2=sminor*sminor;
    int smj2=smajor*smajor; 
    int p=smn2+round_off(smj2/(4.0))-sminor*smj2;
    glVertex2s(2*center_x-x,y);
    glVertex2s(x,y);
    glVertex2s(2*center_x-x,2*center_y-y);
    glVertex2s(x,2*center_y-y);
    while(smn2*(x-center_x)<=smj2*(y-center_y))
    {
        if(p>0)
        {    
            p+=smn2*(2*(x-center_x))-smj2*2*(y-center_y-1);
            y--;
        }
        else
            p+=smn2*(2*(x-center_x));
        x++;
        glVertex2s(2*center_x-x,y);
        glVertex2s(x,y);
        glVertex2s(2*center_x-x,2*center_y-y);
        glVertex2s(x,2*center_y-y);       
    }
    p=smj2*(y-1-center_y)*(y-1-center_y)+smn2*(x-center_x)*(x-center_x)-smn2*(x-center_x)+round_off(smn2/4.0)-smj2*smn2;
    while(y-center_y>=0)
    {
        if(p<=0)
        {
            p+=2*smn2*(x+1-center_x)-smj2*(2*(y-center_y)-3);
            x++;
        }
        else
            p-=(2*(y-center_y)-3)*smj2; 
        y--;
        glVertex2s(2*center_x-x,y);
        glVertex2s(x,y);
        glVertex2s(2*center_x-x,2*center_y-y);
        glVertex2s(x,2*center_y-y);      
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
    glutDisplayFunc(bsEllipse);
    glutMainLoop();
    return 0;
}