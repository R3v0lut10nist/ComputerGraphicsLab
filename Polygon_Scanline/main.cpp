#include <windows.h>
#include <iostream>
#include <algorithm>
#include <GL/glut.h>
#include <stdio.h>
#include <cmath>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

vector<int> xs;
vector<int> ys;
int n;


int round_value(float v)
{
  return int(floor(v + 0.5));
}

void bresenhamX(int dx, int dy, int X0, int Y0, int X1, int Y1)
{
    int i, j, k;

    i = 2 * dy - dx;
    j = 2 * dy;
    k = 2 * (dy - dx);
    if (!(X0 < X1)) {
        int xtemp=X0;
        X0=X1;
        X1=xtemp;

        int ytemp=Y0;
        Y0=Y1;
        Y1=ytemp;
    }
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    glVertex2d(X0,Y0);
    while (X0 < X1) {
        if (i < 0)
            i += j;
        else {
            if (Y0 < Y1)
                ++Y0;
            else
                --Y0;
            i += k;
        }
        ++X0;
        glVertex2d(round_value(X0), round_value(Y0));

    }

}

void bresenhamY(int dx, int dy, int X0, int Y0, int X1, int Y1)
{
    int i, j, k;

    i = 2 * dx - dy;
    j = 2 * dx;
    k = 2 * (dx - dy);
    if (!(Y0 < Y1)) {
        int xtemp=X0;
        X0=X1;
        X1=xtemp;

        int ytemp=Y0;
        Y0=Y1;
        Y1=ytemp;
    }
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    glVertex2d(X0,Y0);
    while (Y0 < Y1) {
        if (i < 0)
            i += j;
        else {
            if (X0 > X1)
                --X0;
            else
                ++X0;
            i += k;
        }
        ++Y0;
        glVertex2d(round_value(X0), round_value(Y0));
    }
}

void bresenham(int X0, int Y0, int X1, int Y1)
{
    int dx = abs(X1 - X0);
    int dy = abs(Y1 - Y0);

    if (dx >= dy)
        bresenhamX(dx, dy, X0, Y0, X1, Y1);
    else
        bresenhamY(dx, dy, X0, Y0, X1, Y1);
}


void fillpolygon(void)
{
  glBegin(GL_POINTS);

  for(int i=0;i<n;i++){
    bresenham(xs[i%(n)],ys[i%(n)],xs[(i+1)%(n)],ys[(i+1)%(n)]);
  }

  int ymin = *min_element(ys.begin(),ys.end());
  int ymax = *max_element(ys.begin(),ys.end());

  glColor3f(1.0,0.0,0.0);
  //okay till here
  for(int i=ymin+1;i<ymax;i++){
    vector<int> px;

    for(int j=0;j<n;j++){
      if( i >= ys[j%n] && i < ys[(j+1)%n] ){
        px.push_back(int( (float(xs[(j+1)%n] - xs[j%n])/float(ys[(j+1)%n] - ys[j%n]))*(i-ys[j%n]) + xs[j%n] ) );
      }

      if(i < ys[j%n] && i >= ys[(j+1)%n]){
        px.push_back(int( (float(xs[(j)%n] - xs[(j+1)%n])/float(ys[(j)%n] - ys[(j+1)%n]))*(i-ys[(j+1)%n]) + xs[(j+1)%n] ) );
      }
    }

    sort(px.begin(),px.end());

    for(int j=0;j<px.size();j+=2){
      for(int k=px[j];k<px[j+1];k++){
        glVertex2d(k,i);
      }
    }

  }

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
