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
float p1[8][4]={{-80,-80,80 ,1},{-80,80,80,1},{80,80,80,1},{80,-80,80,1},
                {-80,-80,-80,1},{-80,80,-80,1},{80,80,-80,1},{80,-80,-80,1}};
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

float pp[4];
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
void orthogonalMatrix(float mat[4][4])
{
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      if(i==j)
	mat[i][j]=1;
      else
	mat[i][j]=0;
    }
  }
  mat[2][2]=0;
}
void orthMatrix(float mat[4][4])
{
  

  
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
void rotatematgen(float theta,float mat[4][4],float x,float y,float z){
  double sine=sin(theta);
  double cosine=cos(theta);
  float dc[4];
  float mod=sqrt(x*x+y*y+z*z);
  if(mod!=0){
    
    dc[0]=x/mod;
    dc[1]=y/mod;
    dc[2]=z/mod;
    dc[3]=0;
  
    for(int i=0;i<4;i++)
      for(int j=0;j<4;j++)
	if(i==j)
	  mat[i][j]=((1-cosine)*dc[i]*dc[j])+cosine;
	else
	  mat[i][j]=(1-cosine)*dc[i]*dc[j];
    float A[3][3];
    
    A[0][0]=0;
    A[0][1]=-dc[2]*sine;
    A[0][2]=dc[1]*sine;
    A[1][0]=dc[2]*sine;
    A[1][1]=0;
    A[1][2]=-dc[0]*sine;
    A[2][0]=-dc[1]*sine;
    A[2][1]=dc[0]*sine;
    A[2][2]=0;
    for(int i=0;i<3;i++)
      for(int j=0;j<3;j++){
	mat[i][j]=mat[i][j]+A[i][j];
	if(i==3 || j==3)
	  mat[i][j]=0;
      }
    mat[3][3]=1;
  }

  else{
    for(int i=0;i<4;i++)
      for(int j=0;j<4;j++)
	if(i==j)
	  mat[i][j]=1;
	else
	  mat[i][j]=0;
  }
  
      
  
}
void intersectingLine(float l[6],float p1[4],float p2[4]){
  l[0]=p1[1]*p2[2]-p2[1]*p1[2];
  l[1]=p1[2]*p2[0]-p2[2]*p1[0];
  l[2]=p1[0]*p2[1]-p2[0]*p1[1];
  if((p1[0]*p2[1]-p2[0]*p1[1])==0)
    l[3]=0;
  else
    l[3]=(p1[3]*p2[1]-p2[3]*p1[1])/(p1[0]*p2[1]-p2[0]*p1[1]);
  if((p1[1]*p2[0]-p2[1]*p1[0])==0)
    l[4]=0;
  else
    l[4]=(p1[3]*p2[0]-p2[3]*p1[0])/(p1[1]*p2[0]-p2[1]*p1[0]);
  l[5]=0;
}

void operation(){
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  //draw(p1,0);
  float operatemat[4][4];
  float line[6];
  float orthoPlane[4];
  for (int i=0;i<4;i++)
    orthoPlane[i]=0;
  
  orthoPlane[2]=1;
  intersectingLine(line,orthoPlane,pp);
  //for(int i=0;i<6;i++)
  //  cout<<line[i]<<" ";
  //cout<<endl;
  orthogonalMatrix(operatemat);
  float p2[8][4];
  float tmat[4][4];
  float rmat[4][4];
  
  translatematgen(tmat,-line[3],-line[4],line[5]);
  float angle=pp[2]/sqrt(pp[0]*pp[0]+pp[1]*pp[1]+pp[2]*pp[2]);
  angle=acos(angle);
  rotatematgen(angle,rmat,line[0],line[1],line[2]);
  float opmat[4][4];
  m2mmultiply(rmat,tmat,opmat);
  m2mmultiply(operatemat,opmat,tmat);
  rotatematgen(-angle,rmat,line[0],line[1],line[2]);
  m2mmultiply(tmat,rmat,opmat);
  translatematgen(tmat,line[3],line[4],line[5]);
  m2mmultiply(tmat,rmat,operatemat);
  /*for(int i=0;i<4;i++){
    for(int j=0;j<4;j++)
      cout<<tmat[i][j]<<" ";
    cout<<endl;
    }*/
  for(int i=0;i<8;i++)
    m2vmultiply(operatemat,p1[i],p2[i]);
  draw(p2,.5);
  glEnd();
  glFlush();
}
int main(int argc, char**argv)
{
  cout<<"enter the values of a,b,c and d for the plane ax+by+cz=d on which you want to project orthographically"<<endl;
  for(int i=0;i<4;i++)
    cin>>pp[i];
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB |GLUT_SINGLE);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Window");
  init();
  glutDisplayFunc(operation);
  glutMainLoop();
  return 0;
}
