#include <windows.h>
#include <iostream>
#include <algorithm>
#include <GL/glut.h>
#include <stdio.h>
#include <cmath>
#include <bits/stdc++.h>
#include <vector>
#include <unistd.h>
using namespace std;

vector<int> xs;
vector<int> ys;
int n;

void floodfill(float dr, float dg, float db, int x, int y){

  float pixels[3];

  glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,&pixels[0]);

  float r,g,b;
  r = pixels[0];
  g = pixels[1];
  b = pixels[2];

  if(r==1.0f && g==1.0f && b==1.0f){

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x,y);
    glEnd();
    glFlush();

    floodfill(dr,dg,db,x+1,y);
    floodfill(dr,dg,db,x,y+1);
    floodfill(dr,dg,db,x-1,y);
    floodfill(dr,dg,db,x,y-1);
  }

  return;
}

void fillpolygon(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINES);

  for(int i=0;i<n;i++){
    glVertex2d(xs[i%(n)],ys[i%(n)]);
    glVertex2d(xs[(i+1)%(n)],ys[(i+1)%(n)]);
  }

  glEnd();
  glFlush();

  int xmin = *min_element(xs.begin(),xs.end());
  int ymin = *min_element(ys.begin(),ys.end());

  float dr=1.0f,dg=1.0f,db=1.0f;

  floodfill(dr,dg,db,xmin + 10,ymin + 5);

  glEnd();

  glFlush();
}

int main(int argc, char **argv)
{
  cout<<"Enter number of points: ";
  cin>>n;
  cout<<"Enter coordinates in anti-clockwise direction: ";
  for(int i=0;i<n;i++){
    int x,y;
    cin>>x>>y;
    xs.push_back(x);
    ys.push_back(y);
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Polygon ");
  glClearColor(1.0,1.0,1.0,0);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(0 , 640 , 0 , 480);

  glutDisplayFunc(fillpolygon);

  glutMainLoop();
  return 0;
}
