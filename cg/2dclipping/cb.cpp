// #include<GL/glut.h>

// void init(void)
// {
// glClearColor(0,0,0,0);
// }

// void DrawCube(void)
// {

//     glMatrixMode(GL_MODELVIEW);
//     // clear the drawing buffer.
//     glClear(GL_COLOR_BUFFER_BIT);
//     glLoadIdentity();
//     glTranslatef(0.0,0.0,-10.5);
//     glRotatef(0.0,1.0,0.0,0.0);
//     // rotation about Y axis
//     glRotatef(0.0,0.0,1.0,0.0);
//     // rotation about Z axis
//     glRotatef(0.01,0.0,0.0,1.0);
//     glBegin(GL_QUADS);        // Draw The Cube Using quads
//     glColor3f(0.0f,1.0f,0.0f);    // Color Blue
//     glVertex3i( 100, 100,-100);    // Top Right Of The Quad (Top)
//     glVertex3i(-100, 100,-100);    // Top Left Of The Quad (Top)
//     glVertex3i(-100, 100, 100);    // Bottom Left Of The Quad (Top)
//     glVertex3i( 100, 100, 100);    // Bottom Right Of The Quad (Top)
//     glColor3f(1.0f,0.5f,0.0f);    // Color Orange
//     glVertex3i( 100,-100, 100);    // Top Right Of The Quad (Bottom)
//     glVertex3i(-100,-100, 100);    // Top Left Of The Quad (Bottom)
//     glVertex3i(-100,-100,-100);    // Bottom Left Of The Quad (Bottom)
//     glVertex3i( 100,-100,-100);    // Bottom Right Of The Quad (Bottom)
//     glColor3f(1.0f,0.0f,0.0f);    // Color Red    
//     glVertex3i( 100, 100, 100);    // Top Right Of The Quad (Front)
//     glVertex3i(-100, 100, 100);    // Top Left Of The Quad (Front)
//     glVertex3i(-100,-100, 100);    // Bottom Left Of The Quad (Front)
//     glVertex3i( 100,-100, 100);    // Bottom Right Of The Quad (Front)
//     glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
//     glVertex3i( 100,-100,-100);    // Top Right Of The Quad (Back)
//     glVertex3i(-100,-100,-100);    // Top Left Of The Quad (Back)
//     glVertex3i(-100, 100,-100);    // Bottom Left Of The Quad (Back)
//     glVertex3i( 100, 100,-100);    // Bottom Right Of The Quad (Back)
//     glColor3f(0.0f,0.0f,1.0f);    // Color Blue
//     glVertex3i(-100, 100, 100);    // Top Right Of The Quad (Left)
//     glVertex3i(-100, 100,-100);    // Top Left Of The Quad (Left)
//     glVertex3i(-100,-100,-100);    // Bottom Left Of The Quad (Left)
//     glVertex3i(-100,-100, 100);    // Bottom Right Of The Quad (Left)
//     glColor3f(1.0f,0.0f,1.0f);    // Color Violet
//     glVertex3i( 100, 100,-100);    // Top Right Of The Quad (Right)
//     glVertex3i( 100, 100, 100);    // Top Left Of The Quad (Right)
//     glVertex3i( 100,-100, 100);    // Bottom Left Of The Quad (Right)
//     glVertex3i( 100,-100,-100);    // Bottom Right Of The Quad (Right)
//   glEnd();            // End Drawing The Cube
// glFlush();
// }



// int main(int argc, char** argv){

//     glutInit(&argc, argv);
//     //we initizlilze the glut. functions
//     glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
//     glutInitWindowPosition(100, 100);
//     glutCreateWindow(argv[0]);
//     init();
//     glutDisplayFunc(DrawCube);
//     glutMainLoop();
//     return 0;
// }

#include <GL/glut.h>
 GLfloat xRotated, yRotated, zRotated;

 int x1=-80,x2=0,y3=-80,y2=0;
float u1=0,u2=1;
int xmin=-50,ymin=-50,xmax=50,ymax=50;
double p[4],q[4];  // changed from int to double thats it
void init(void)
{
glClearColor(0,0,0,0);
 
}

void clip(int x1,int y1,int x2,int y2)
{
    int dx=x2-x1,dy=y2-y1,i;
    double t;
    p[0]=-dx;q[0]=x1-xmin;
    p[1]=dx;q[1]=xmax-x1;
    p[2]=-dy;q[2]=y1-ymin;
    p[3]=dy;q[3]=ymax-y1;

    for(i=0;i<4;i++)
    {
        if(p[i]==0 && q[i]<0)
            return;
        if(p[i]<0)
        {
            t=(q[i])/(p[i]);  // This calculation was returning a zero because both q and p were int
            if(t>u1 && t<u2)
                {u1=t;}
        }
        else if(p[i]>0)
        {
            t=(q[i])/(p[i]);  // This calculation was returning a zero because both q and p were int
            if(t>u1 && t<u2)
                {u2=t;}
        }
    }
    if(u1<u2)
    {
        x1=x1+u1*(x2-x1);
        y1=y1+u1*(y2-y1);
        x2=x1+u2*(x2-x1);
        y2=y1+u2*(y2-y1);
    glColor3f(0.0,1.0,0.0);
        glBegin(GL_LINES);
            glVertex2i(x1,y1);
            glVertex2i(x2,y2);
        glEnd();
        glFlush();
    }
}


void DrawCube(void)
{

     glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
        glTranslatef(0.0,0.0,-10.5);
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
  glBegin(GL_LINE_LOOP);        // Draw The Cube Using quads
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
      glEnd();            // End Drawing The Cube
glFlush();
  glBegin(GL_LINES); 
    glColor3f(0.0f,1.0f,0.0f);    // Color Violet
    glVertex3f( -2.0f,-2.0f, -2.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(2.0f,2.0f, 2.0f);
glEnd();            // End Drawing The Cube
glFlush();




  glBegin(GL_LINE_LOOP); 
    glColor3f(0.0f,0.0f,1.0f);    // Color Orange
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
      glEnd();            // End Drawing The Cube
glFlush();
  glBegin(GL_LINE_LOOP); 
    glColor3f(0.0f,0.0f,1.0f);    // Color Red    
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
      glEnd();            // End Drawing The Cube
glFlush();
  glBegin(GL_LINE_LOOP); 
    glColor3f(0.0f,0.0f,1.0f);    // Color Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
      glEnd();            // End Drawing The Cube
glFlush();
  glBegin(GL_LINE_LOOP); 
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
      glEnd();            // End Drawing The Cube
glFlush();
  glBegin(GL_LINE_LOOP); 
    glColor3f(0.0f,0.0f,1.0f);    // Color Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
  glEnd();            // End Drawing The Cube
glFlush();
}


void reshape(int x, int y)
{
    yRotated += 3;
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
     
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void myKey(unsigned char key,int x,int y)
{
glClear(GL_COLOR_BUFFER_BIT);
    if(key=='c')
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
             glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
        glTranslatef(0.0,0.0,-10.5);
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
  glBegin(GL_LINE_LOOP);        // Draw The Cube Using quads
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
      glEnd();            // End Drawing The Cube
glFlush();
  glBegin(GL_LINES); 
    glColor3f(0.0f,1.0f,0.0f);    // Color Violet
    glVertex3f( -1.0f,-1.0f, -1.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(1.0f,1.0f, 1.0f);
glEnd();            // End Drawing The Cube
glFlush();




  glBegin(GL_LINE_LOOP); 
    glColor3f(0.0f,0.0f,1.0f);    // Color Orange
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
      glEnd();            // End Drawing The Cube
glFlush();
  glBegin(GL_LINE_LOOP); 
    glColor3f(0.0f,0.0f,1.0f);    // Color Red    
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
      glEnd();            // End Drawing The Cube
glFlush();
  glBegin(GL_LINE_LOOP); 
    glColor3f(0.0f,0.0f,1.0f);    // Color Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
      glEnd();            // End Drawing The Cube
glFlush();
  glBegin(GL_LINE_LOOP); 
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
      glEnd();            // End Drawing The Cube
glFlush();
  glBegin(GL_LINE_LOOP); 
    glColor3f(0.0f,0.0f,1.0f);    // Color Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
  glEnd();            // End Drawing The Cube
glFlush();
    }


}

int main(int argc, char** argv){

glutInit(&argc, argv);
//we initizlilze the glut. functions
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(100, 100);
glutCreateWindow(argv[0]);
init();
glutDisplayFunc(DrawCube);
glutReshapeFunc(reshape);
glutKeyboardFunc(myKey);
//Set the function for the animation.
// glutIdleFunc(animation);
glutMainLoop();
return 0;
}
