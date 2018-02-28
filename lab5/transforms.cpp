#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#define PI 3.14157
using namespace std;
/*Perform basic transformation functions in 2d*/
float p1[3],p2[3],p3[3];
void init()
{
    glClearColor(1.0,1.0,1.0,1.0);//Sets the color of the window
    glOrtho(-1000.0, 1000.0, -1000.0, 1000.0, -1.0, 1.0);//Sets the size of the plane
}
float angle,x,y;
int axis;
void m2mMultiply(float mat1[3][3],float mat2[3][3],float matout[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            matout[i][j]=0;
            for(int k=0;k<3;k++)
            {
                matout[i][j]+=mat1[i][k]*mat2[k][j];
            }
        }
    }
}
void translateMatGen(int x,int y,float mat[3][3])
{
   
    mat[0][0]=1;
    mat[1][1]=1;
    mat[0][1]=0;
    mat[1][0]=0;
    mat[0][2]=x;
    mat[1][2]=y;
    mat[2][0]=0;
    mat[2][1]=0;
    mat[2][2]=1;
}
void rotateMatGen(float theta,float mat[3][3])
{
    mat[0][0]=cos(theta);
    mat[1][1]=cos(theta);
    mat[0][1]=-sin(theta);
    mat[1][0]=sin(theta);
    mat[0][2]=0;
    mat[1][2]=0;
    mat[2][0]=0;
    mat[2][1]=0;
    mat[2][2]=1;
}
void shearMatGen(int x,int y,float mat[3][3])
{
    mat[0][0]=1;
    mat[1][1]=1;
    mat[0][1]=x;
    mat[1][0]=y;
    mat[0][2]=0;
    mat[1][2]=0;
    mat[2][0]=0;
    mat[2][1]=0;
    mat[2][2]=1;
}
void scaleMatGen(int x,int y,float mat[3][3])
{
    mat[0][0]=x;
    mat[1][1]=y;
    mat[0][1]=0;
    mat[1][0]=0;
    mat[0][2]=0;
    mat[1][2]=0;
    mat[2][0]=0;
    mat[2][1]=0;
    mat[2][2]=1;
}
void ReflectMatGenx(float mat[3][3])
{

    mat[0][0]=1;
    mat[1][1]=-1;
    mat[0][1]=0;
    mat[1][0]=0;
    mat[0][2]=0;
    mat[1][2]=0;
    mat[2][0]=0;
    mat[2][1]=0;
    mat[2][2]=1;
}
void ReflectMatGeny(float mat[3][3])
{

    mat[0][0]=-1;
    mat[1][1]=1;
    mat[0][1]=0;
    mat[1][0]=0;
    mat[0][2]=0;
    mat[1][2]=0;
    mat[2][0]=0;
    mat[2][1]=0;
    mat[2][2]=1;
}
void m2vMultiply(float mat1[3][3],float vec[3],float vec2[3])
{
    for(int i=0;i<3;i++)
    {
        vec2[i]=0;
        for(int j=0;j<3;j++)
            vec2[i]+=vec[j]*mat1[i][j];
    }
}

int opNum;
void Operation()
{   
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2s(p1[0],p1[1]);
    glVertex2s(p2[0],p2[1]);
    glVertex2s(p2[0],p2[1]);
    glVertex2s(p3[0],p3[1]);
    glVertex2s(p3[0],p3[1]);
    glVertex2s(p1[0],p1[1]);
    float operateMat[3][3];
    if(opNum==0){
        translateMatGen(x,y,operateMat);
    }
    else if(opNum==1){
        rotateMatGen(angle*PI/180,operateMat);
    }
    else if(opNum==2){
        scaleMatGen(x,y,operateMat);
    }
    else if(opNum==3){
        shearMatGen(x,y,operateMat);
    }
    else if(opNum==4)
    {
        if(axis==0)
            ReflectMatGenx(operateMat);
        else
            ReflectMatGeny(operateMat);
    }
    float pa1[3],pa2[3],pa3[3];
    m2vMultiply(operateMat,p1,pa1);
    m2vMultiply(operateMat,p2,pa2);
    m2vMultiply(operateMat,p3,pa3);
    glColor3f (0.0, 0.0, 0.0);
    glVertex2s(pa1[0],pa1[1]);
    glVertex2s(pa2[0],pa2[1]);
    glVertex2s(pa2[0],pa2[1]);
    glVertex2s(pa3[0],pa3[1]);
    glVertex2s(pa3[0],pa3[1]);
    glVertex2s(pa1[0],pa1[1]);
    glEnd();
    glFlush();
}
int main()
{
    int argc=0;
    char **argv;
    cout<<"Enter the points of the triangle"<<endl;
    cin>>p1[0]>>p1[1]>>p2[0]>>p2[1]>>p3[0]>>p3[1];
    p1[2]=1;
    p2[2]=1;
    p3[2]=1;
    cout<<"Enter the operation to be performed 0 for translation, 1 for rotation, 2 for scale, 3 for shear ,4 for reflection"<<endl;
        cin>>opNum;
    if(opNum==0)
    {
        cout<<"Enter the x and y"<<endl;
        cin>>x>>y;
    }
    else if(opNum==1)
    {
        cout<<"Enter the angle to rotate"<<endl;
        cin>>angle;
    }
    else if(opNum==2)
    {
        cout<<"Enter the scale in x and y"<<endl;
        cin>>x>>y;
    }
    else if(opNum==3)
    {
        cout<<"Enter the shear amount in x and y"<<endl;
        cin>>x>>y;
    }
    //Be careful while shearing as the point will go out of the coordinate system defined
    else if(opNum==4)
    {
        cout<<"Enter the axis about which you want to reflect 0 for x ,1 for y"<<endl;
        cin>>axis;
    }
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Window");
    init();
    glutDisplayFunc(Operation);
    glutMainLoop();

}