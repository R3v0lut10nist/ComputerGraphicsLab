#include<GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h> 
#include<math.h> 
#include<stdio.h>

float a,b,c,d,e,f,g,h,xmax,xmin,ymax,ymin,vxmax,vxmin,vymax,vymin;
float m,i;
int choice;
void plotpolygon(float a,float b,float c,float d,float e,float f,float g,float h)
{
    
    glBegin(GL_POLYGON);
    glVertex3f(a,b,0.0);
    glVertex3f(c,d,0.0);
    glVertex3f(e,f,0.0);
    glVertex3f(g,h,0.0);
    glEnd();
    
}
void plotaxes()
{
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
glVertex2i(-100,0);
glVertex2i(100, 0);
glVertex2i(0,-100);
glVertex2i(0,100);
glEnd();
    
}


void plotviewport(float p,float q,float r,float s)
{
    glBegin(GL_LINES);
glVertex2f(p,q);
glVertex2f(r,q);
glVertex2f(r,q);
glVertex2f(r,s);
glVertex2f(r,s);
glVertex2f(p,s);
glVertex2f(p,s);
glVertex2f(p,q);
glEnd();

    
}



void display(void)
{
glClear(GL_COLOR_BUFFER_BIT); 
glColor3f(1.0,1.0,1.0); 

glPointSize(3.0); 
glBegin(GL_POINTS); 

 for(int i=-2; i<=2 ; i++)// x axis
 {
 glVertex2s(95+i,4+i);
 glVertex2s(95-i,4+i);
 } 
 for(int i=0; i<=2 ; i++)// y axis
 {
 glVertex2s(4+i,95+i);
 glVertex2s(4-i,95+i);
 glVertex2s(4,95-i);
 }

glEnd(); 
    float a1,b1,c1,d1,e1,f1,g1,h1;
float sx=(vxmax-vxmin)/(xmax-xmin);
float sy=(vymax-vymin)/(ymax-ymin);

    a1=a*sx -(sx*xmin) + vxmin;
    b1=b*sy -(sy*ymin) + vymin;
    c1=c*sx -(sx*xmin) + vxmin;
    d1=d*sy -(sy*ymin) + vymin;;
    e1=e*sx -(sx*xmin) + vxmin;
    f1=f*sy -(sy*ymin) + vymin;;
    g1=g*sx -(sx*xmin) + vxmin;
    h1=h*sy -(sy*ymin) + vymin;;
    plotaxes();
    glColor3f(0.0,0.0,1.0);
    plotpolygon(a1,b1,c1,d1,e1,f1,g1,h1);
    float p=vxmin,q=vymin,r=vxmax,s=vymax;
    glColor3f(1.0,0.0,0.0);
    plotviewport(p,q,r,s);



    glFlush();
}

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glOrtho(-100.0, 100.0,-100.0, 100.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    
    printf("Enter the co-ordinates of polygon\n");
    scanf("%f %f %f %f %f %f %f %f",&a,&b,&c,&d,&e,&f,&g,&h);
    
    printf("Enter lower left coordinates and upper right coordinates of window\n");
    
    scanf("%f %f %f %f",&xmin,&ymin,&xmax,&ymax);
printf("Enter lower left coordinates and upper right coordinates of viewport\n");
    
    scanf("%f %f %f %f",&vxmin,&vymin,&vxmax,&vymax);
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (500, 500);
    glutCreateWindow ("Viewport");
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
