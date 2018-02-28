#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include <list>
using namespace std;
#define ROUND(a) ((int)(a + 0.5))

struct _line
{
	int x1, y1;
	int x2, y2;
};

int xmax, xmin, ymax, ymin;

void clip(_line &a)
{
	int p[4], q[4], i, dx, dy, flag = 1;
	double u1 = 0, u2 = 1, temp;
	dx = a.x2 - a.x1;
	dy = a.y2 - a.y1;
	p[0] = -dx; q[0] = a.x1 - xmin;
	p[1] = dx; q[1] = xmax - a.x1;
	p[2] = -dy; q[2] = a.y1 - ymin;
	p[3] = dy; q[3] = ymax - a.y1;

	if (p[0] == 0 && p[3] == 0) //Point Clipping
	{
		if (a.x1 >= xmin && a.x1 <= xmax && a.y1 >= ymin && a.y1 <= ymax)
			;
		else
			return;
	}

	if (p[0] == 0)
		if (q[0] * q[1] <= 0)
			return; //for Parallel lines
	if (p[2] == 0)
		if (q[2] * q[3] <= 0)
			return;

	for (i = 0; i<4; i++)
	{
		if (p[i]<0 && flag)
		{
			temp = (double)q[i] / (double)p[i];
			if (temp>u2)
				flag = 0;
			else
				if (temp>u1)
					u1 = temp;
		}
		else
			if (p[i]>0 && flag)
			{
				temp = (double)q[i] / (double)p[i];
				if (temp<u1)
					flag = 0;
				else
					if (temp<u2)
						u2 = temp;
			}
	}
	if (u1 >= u2 || flag == 0)
		return;
	temp = a.x1;
	i = a.y1;
	a.x1 = temp + u1*dx;
	a.x2 = temp + u2*dx;
	a.y1 = i + u1*dy;
	a.y2 = i + u2*dy;

}
_line a[100];
int n;
int flag = 0;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	int i;
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2d(xmin, ymin);
	glVertex2d(xmin, ymax);
	glVertex2d(xmax, ymax);
	glVertex2d(xmax, ymin);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	if(flag==1)
	for (i = 0; i < n; i++)
	{
		glBegin(GL_LINES);
		glVertex2d(a[i].x1, a[i].y1);
		glVertex2d(a[i].x2, a[i].y2);
		glEnd();
	}
	if (flag == 0)
	{
		for (int j = 0; j < n; j++)
			clip(a[j]);
		for (i = 0; i < n; i++)
		{
			glBegin(GL_LINES);
			glVertex2d(a[i].x1, a[i].y1);
			glVertex2d(a[i].x2, a[i].y2);
			glEnd();
		}
		glFlush();
		return;
	}




	glFlush();
	/*
	for (i = 0; i<n; i++)
		clip(a[i]);
	for (i = 0; i < n; i++)
	{
		glBegin(GL_LINES);
		glVertex2d(a[i].x1, a[i].y1);
		glVertex2d(a[i].x2, a[i].y2);
		glEnd();
	}*/
}
int main(int argc,char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Many Amaze Very GL WOW");
	cout << "Enter the window coordinates : \n";
	cout << "Lower Left Corner : ";
	cin >> xmin >> ymin;

	cout << "Upper Right Corner : ";
	cin >> xmax >> ymax;

	cout << "How many lines do you want to draw : ";
	cin >> n;

	int i;
	cout << "Enter Coordinates : \n";
	for (i = 0; i<n; i++)
	{
		cout << "line " << i + 1 << " : ";
		cout << "Enter coordinates of Ist Vertex" << endl;
		cout << "x1 =";
		cin >> a[i].x1;
		cout << "y1 =";
		cin >> a[i].y1;

		cout << "Enter coordinates of IInd Vertex" << endl;
		cout << "x2 ="; cin >> a[i].x2;
		cout << "y2 ="; cin >> a[i].y2;
	}
	glutDisplayFunc(display);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-320, 320, -240, 240);
	glutMainLoop();

	return 0;
}
