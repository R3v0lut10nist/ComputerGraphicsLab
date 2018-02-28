#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#define pi 3.14157
using namespace std;
void init(){
  glClearColor(1.0,1.0,1.0,1.0);
  //glClearDepth(160.0f);
  glOrtho(-200.0, 200.0, -200.0,200.0, -150, 150);
  //glEnable(GL_DEPTH_TEST);
}
float p1[8][4]={{-80,-80,-40 ,1},{-80,80,-40,1},{80,80,-40,1},{80,-80,-40,1},
                {-80,-80,-120,1},{-80,80,-120,1},{80,80,-120,1},{80,-80,-120,1}};
/*
  Camera at Origin
  
    5__________6
   /|         /|
  / |        / |
1/_ |_______/2 |
 |  |       |  |  
 | 4|_______|__|7
 |  /       |  /
 | /        | /
 |/_________|/
 0          3

*/
float z;
int axis,opnum;
void m2mmultiply(float mat1[4][4],float mat2[4][4],float matout[4][4])
{
  for(int i=0;i<4;i++){    
    for(int j=0;j<4;j++){
      matout[i][j]=0;
      for(int k=0;k<4;k++){
	matout[i][j]+=mat1[i][k]*mat2[k][j];
      }
    }
  }
}

void m2vmultiply(float mat1[4][4],float vec[4],float vec2[4])
{
  for(int i=0;i<4;i++){
    vec2[i]=0;
    for(int j=0;j<4;j++){
      vec2[i]+=vec[j]*mat1[i][j];
    }
  }
}
void translatematgen(float mat[4][4],float x,float y,float z)
{
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      if(i==j)
	mat[i][j]=1;
      else
	mat[i][j]=0;
    }
  }
  mat[0][3]=x;
  mat[1][3]=y;
  mat[2][3]=z;
}
void perspectiveMatrix(float mat[4][4],float d)
{
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      if(i==j)
	mat[i][j]=1;
      else
	mat[i][j]=0;
    }
  }
  mat[3][3]=0;
  mat[3][2]=-1/d;
}
void draw(float a[8][4],float pl)//Display the Figure
{
  glBegin(GL_QUADS);
 
  glColor3f (0.5, 0.1+pl/5, 0.3+pl/5);
  glVertex2f(a[7][0]/a[7][3],a[7][1]/a[7][3]);
  glVertex2f(a[6][0]/a[6][3],a[6][1]/a[6][3]);
  glVertex2f(a[5][0]/a[5][3],a[5][1]/a[5][3]);
  glVertex2f(a[4][0]/a[4][3],a[4][1]/a[4][3]);

  
  glColor3f (0.2+pl/5, 0.6, 0.2+pl/5);
  glVertex2f(a[1][0]/a[1][3],a[1][1]/a[1][3]);
  glVertex2f(a[5][0]/a[5][3],a[5][1]/a[5][3]);
  glVertex2f(a[6][0]/a[6][3],a[6][1]/a[6][3]);
  glVertex2f(a[2][0]/a[2][3],a[2][1]/a[2][3]);
  
  glColor3f (0.8, 0.1+pl/5, 0.5);       
  glVertex2f(a[0][0]/a[0][3],a[0][1]/a[0][3]);
  glVertex2f(a[1][0]/a[1][3],a[1][1]/a[1][3]);
  glVertex2f(a[5][0]/a[5][3],a[5][1]/a[5][3]);
  glVertex2f(a[4][0]/a[4][3],a[4][1]/a[4][3]);
  
  
  
  glColor3f (0.7, 0.3+pl/5, 0.1+pl/5);
  glVertex2f(a[6][0]/a[6][3],a[6][1]/a[6][3]);
  glVertex2f(a[7][0]/a[7][3],a[7][1]/a[7][3]);  
  glVertex2f(a[3][0]/a[3][3],a[3][1]/a[3][3]);
  glVertex2f(a[2][0]/a[2][3],a[2][1]/a[2][3]);

  glColor3f (0.2, 0.4, 0.1+pl/5);
  glVertex2f(a[0][0]/a[0][3],a[0][1]/a[0][3]);
  glVertex2f(a[3][0]/a[3][3],a[3][1]/a[3][3]);
  glVertex2f(a[7][0]/a[7][3],a[7][1]/a[7][3]);
  glVertex2f(a[4][0]/a[4][3],a[4][1]/a[4][3]);
  glColor3f (0, 0, 0);
  glVertex2f(a[0][0]/a[0][3],a[0][1]/a[0][3]);
  glVertex2f(a[1][0]/a[1][3],a[1][1]/a[1][3]);
  glVertex2f(a[2][0]/a[2][3],a[2][1]/a[2][3]);
  glVertex2f(a[3][0]/a[3][3],a[3][1]/a[3][3]);
  
  glEnd();
}
void operation(){
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  //draw(p1,0);
  float operatemat[4][4];
  perspectiveMatrix(operatemat,-z);
  float p2[8][4];
  float tmat[4][4];
  translatematgen(tmat,200,200,-160);
  float opmat[4][4];
  m2mmultiply(operatemat,tmat,opmat);
  
  for(int i=0;i<8;i++)
    m2vmultiply(opmat,p1[i],p2[i]);
  for(int i=0;i<8;i++)
    {  for(int j=0;j<4;j++)
	cout<<p2[i][j]<<" ";
      cout<<endl;
    }
  
  draw(p2,.5);
  glEnd();
  glFlush();
}
int main(int argc, char**argv)
{
  cout<<"enter the z coordinate of the plane on which you want to project the cube"<<endl;
  cin>>z;
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH |GLUT_SINGLE);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Window");
  init();
  glutDisplayFunc(operation);
  glutMainLoop();
  return 0;
}
