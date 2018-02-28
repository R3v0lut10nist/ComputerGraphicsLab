/*Perform basic transformations in 3d*/
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#define pi 3.14157
using namespace std;
void init(){
  glClearColor(1.0,1.0,1.0,1.0);
  glClearDepth(160.0f);
  glOrtho(-400.0, 400.0, -400.0, 400.0, -200.0, 200.0);
  glEnable(GL_DEPTH_TEST);
}
float p1[8][4]={{0,0,0 ,1},{0,80,0,1},{80,80,0,1},{80,0,0,1},
                    {0,0,-80,1},{0,80,-80,1},{80,80,-80,1},{80,0,-80,1}};
/*  5__________6
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
float angle,x,y,z,sxz,sxy,syx,syz,szy,szx;
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
void rotatematgen(float theta,float mat[4][4]){
  double sine=sin(theta);
  double cosine=cos(theta);
  float dc[4];
  float mod=sqrt(x*x+y*y+z*z);
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
void scalematgen(float mat[4][4],float x,float y,float z)
{
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      if(i==j)
	mat[i][j]=1;
      else
	mat[i][j]=0;
    }
  }
  mat[0][0]=x;
  mat[1][1]=y;
  mat[2][2]=z;
}
void shearmatgen(float mat[4][4]){
  for(int i=0;i<3;i++)
    mat[i][i]=1;
  mat[0][1]=sxy;
  mat[0][2]=sxz;
  mat[1][0]=syx;
  mat[1][2]=syz;
  mat[2][0]=szx;
  mat[2][1]=szy;
  for(int i=0;i<3;i++){
    mat[i][3]=0;
    mat[3][i]=0;
  }
  mat[3][3]=1;
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
void reflectmatgen(float mat1[4][4])
{
  //Find reflection of a point with the y-z plane acting as the mirror
  for(int i=0;i<4;i++)
    for(int j=0;j<4;j++){
      if(i==j)
	mat1[i][j]=1;
      else
	mat1[i][j]=0;
    }
  mat1[0][0]=-1;
}
void draw(float a[8][4],float pl)//Display the Figure
{
  glBegin(GL_QUADS);
  
  glColor3f (0.1+pl/5, 0.4, 0.7);
  glVertex3s(a[0][0],a[0][1],a[0][2]);
  glVertex3s(a[1][0],a[1][1],a[1][2]);
  glVertex3s(a[2][0],a[2][1],a[2][2]);
  glVertex3s(a[3][0],a[3][1],a[3][2]);
  
  glColor3f (0.8, 0.1+pl/5, 0.5);       
  glVertex3s(a[0][0],a[0][1],a[0][2]);
  glVertex3s(a[1][0],a[1][1],a[1][2]);
  glVertex3s(a[5][0],a[5][1],a[5][2]);
  glVertex3s(a[4][0],a[4][1],a[4][2]);

  glColor3f (0.2, 0.4, 0.1+pl/5);
  glVertex3s(a[0][0],a[0][1],a[0][2]);
  glVertex3s(a[3][0],a[3][1],a[3][2]);
  glVertex3s(a[7][0],a[7][1],a[7][2]);
  glVertex3s(a[4][0],a[4][1],a[4][2]);

  glColor3f (0.5, 0.1+pl/5, 0.3+pl/5);
  glVertex3s(a[7][0],a[7][1],a[7][2]);
  glVertex3s(a[6][0],a[6][1],a[6][2]);
  glVertex3s(a[5][0],a[5][1],a[5][2]);
  glVertex3s(a[4][0],a[4][1],a[4][2]);

  glColor3f (0.2+pl/5, 0.6, 0.2+pl/5);
  glVertex3s(a[1][0],a[1][1],a[1][2]);
  glVertex3s(a[5][0],a[5][1],a[5][2]);
  glVertex3s(a[6][0],a[6][1],a[6][2]);
  glVertex3s(a[2][0],a[2][1],a[2][2]);
  
  glColor3f (0.7, 0.3+pl/5, 0.1+pl/5);
  glVertex3s(a[6][0],a[6][1],a[6][2]);
  glVertex3s(a[7][0],a[7][1],a[7][2]);  
  glVertex3s(a[3][0],a[3][1],a[3][2]);
  glVertex3s(a[2][0],a[2][1],a[2][2]);
  
  glEnd();
}
void operation(){
  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
   draw(p1,0);
  float operatemat[4][4];
  if(opnum==0)
    translatematgen(operatemat,x,y,z);
  else if(opnum==1)
    {
      float tMat[4][4],aMat[4][4],rMat[4][4];
      translatematgen(tMat,0,-sxy,-sxz);
      rotatematgen(angle*pi/180,rMat);
      m2mmultiply(rMat,tMat,aMat);
      translatematgen(tMat,0,sxy,sxz);
      m2mmultiply(tMat,aMat,operatemat);
    }
    else if(opnum==2)
      scalematgen(operatemat,x,y,z);
  else if(opnum==3)
    shearmatgen(operatemat);
  else if(opnum==4)
    //reflect about y-z plane
    reflectmatgen(operatemat);
  float p2[8][4];
  for(int i=0;i<8;i++)
    m2vmultiply(operatemat,p1[i],p2[i]);
  draw(p2,.5);
  glEnd();
  glFlush();
}
int main(int argc, char**argv)
{
  cout<<"enter the operation to be performed 0 for translation, 1 for rotation, 2 for scale, 3 for shear ,4 for reflection"<<endl;
  cin>>opnum;
  if(opnum==0){
    cout<<"enter the x and y and z"<<endl;
    cin>>x>>y>>z;
  }
  else if(opnum==1){
    cout<<"enter the x, y and z directions of the line about which you want to rotate"<<endl;
    cin>>x>>y>>z;
    cout<<"Enter the y and z intercepts on y-z plane"<<endl;
    cin>>sxy>>sxz;
    cout<<"enter the angle to rotate"<<endl;
    cin>>angle;
  }
  else if(opnum==2){
    cout<<"enter the scale in x, y and z"<<endl;
    cin>>x>>y>>z;
  }
  else if(opnum==3){
    cout<<"enter the shear amount in x(sxy sxz) ,y(syx syz) and z(szx szy)"<<endl;
    cin>>sxy>>sxz>>syx>>syz>>szx>>szy;
  }
  //be careful while shearing as the point will go out of the coordinate system defined
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB| GLUT_DEPTH | GLUT_SINGLE);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Window");
  init();
  glutDisplayFunc(operation);
  glutMainLoop();
  return 0;
}
