#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;



void display ( )   // Create The Display Function
{

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gluLookAt(0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,-1.0 ,0.0 ,1.0 ,0.0);


    glBegin(GL_QUADS); 

        glColor3f(0.813205,0.813205,0.813205);
        glVertex3f(-0.389662380802125,0.9152038469432,  -1.12528215173346); // top left corner

        glColor3f(0.309385,0.309385,0.309385);
        glVertex3f(0.433401472883409,0.2288002674917,  -0.923754348668237); // top right corner

        glColor3f(0.288292,0.288292,0.288292);
        glVertex3f(0.441173907261717,-0.124431126115,  -0.915317251508196);// bottom right corner

        glColor3f(0.74028,0.74028,0.74028);
        glVertex3f(-0.8657135983495,-0.317680965994535,  -1.09611219327051); // bottom left corner


    glEnd();
    GLfloat zbuffer[640][480];

    glReadPixels(0,0,640,480,GL_DEPTH_COMPONENT,GL_FLOAT, zbuffer);
    

    cout<<"Depth1:"<<zbuffer[0][0]<<endl;
    cout<<"Depth2:"<<zbuffer[639][470]<<endl;

    glFlush();
    glBegin(GL_QUADS); 

        glColor3f(0.75,0.84205,0.445);
        glVertex3f(-0.662380802125,0.38469432,  -1.12528215173346); // top left corner

        glColor3f(0.364385,0.525385,0.309385);
        glVertex3f(0.433401472883409,0.28002674917,  -0.923754348668237); // top right corner

        glColor3f(0.288292,0.288292,0.288292);
        glVertex3f(0.441173907261717,-0.431126115,  -0.915317251508196);// bottom right corner

        glColor3f(0.774028,0.77573828,0.74028);
        glVertex3f(-0.33495,-0.217680965994535,  -1.09611219327051); // bottom left corner


    glEnd();

    

    glReadPixels(0,0,480,320,GL_DEPTH_COMPONENT,GL_FLOAT, zbuffer);
    

    cout<<"Depth1:"<<zbuffer[0][0]<<endl;
    cout<<"Depth2:"<<zbuffer[479][318]<<endl;

    glFlush();

    glutSwapBuffers ( );
}

void reshape ( int w, int h )   // Create The Reshape Function (the viewport)
{
    glViewport(0 ,0 ,(GLsizei)w,( GLsizei)h);
    glMatrixMode (GL_PROJECTION );
    glLoadIdentity ( );
    gluPerspective(48.6f, (GLfloat) 640 / 480, 0.01f, 1000.0f);
    glMatrixMode (GL_MODELVIEW) ;
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
  switch ( key ) {
    case 27:        // When Escape Is Pressed...
      exit ( 0 );   // Exit The Program
      break;        // Ready For Next Case
    default:        // Now Wrap It Up
      break;
  }
}

void mouse(int button, int state, int x, int y) {

        float mx = x ;
        float my = y ;
//      ox = (mx/320-1.0);
//      oy = -(my/240 -1.0);
        switch(button){
            case GLUT_LEFT_BUTTON:
                if(state==GLUT_DOWN){
                    printf("%f,",mx);
                    printf("%f\n",my);
                }
                break;
        }
}

int main ( int argc, char** argv )   
{
    glutInit( &argc, argv ); 
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow( "My Window" ); 
    glutReshapeFunc( reshape ) ;
    glutDisplayFunc( display );  // Matching Earlier Functions To Their Counterparts
    glutKeyboardFunc( keyboard );
    glutMouseFunc(mouse);
    glutMainLoop();          // Initialize The Main Loop


  return 0;
}
