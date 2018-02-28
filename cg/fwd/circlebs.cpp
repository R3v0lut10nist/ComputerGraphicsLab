#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
using namespace std;
int center_x,center_y,radius;

void init()
{
    glClearColor(1.0,1.0,1.0,1.0);//Sets the color of the window
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);//Sets the size of the plane
}
void BresenhamCircle()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);//Color of the vertices
    int x=center_x;
    int y=center_y+radius;
    int p=2*(x+1-center_x)*(x+1-center_x)+2*(y-center_y)*(y-center_y)+1-2*(y-center_y)-2*radius*radius;
    glBegin(GL_POINTS); 
    glVertex2s(x,y);
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
    while((y-center_y)>=(x-center_x))
    {
        if(p>0)
        {   
            
            p+=4*x-4*center_x+6-4*(y-center_y-1);
            y--;
        }
        else
            p+=4*x-4*center_x+6;
        x++;
        x2=center_x+y-center_y;
        y2=center_y+x-center_x;
        //Plot all the points using the 8 fold symmetry of circle
        glVertex2s(2*center_x-x,y);
        glVertex2s(x,y);
        glVertex2s(2*center_x-x,2*center_y-y);
        glVertex2s(x,2*center_y-y);
        glVertex2s(2*center_x-x2,y2);
        glVertex2s(x2,y2);
        glVertex2s(2*center_x-x2,2*center_y-y2);
        glVertex2s(x2,2*center_y-y2);
    }
    glEnd();
    glFlush();

}
int main()
{
    int argc=0;
    char **argv;
    cin>>center_x>>center_y>>radius;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Window");
    init();
    glutDisplayFunc(BresenhamCircle);
    glutMainLoop();
    return 0;
}