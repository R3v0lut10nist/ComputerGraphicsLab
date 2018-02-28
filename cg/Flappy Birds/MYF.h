#include<graphics.h>
#include<fstream>
#include<stdio.h>
#include<iostream>
#include <sys/ioctl.h>
#include <termios.h>

using namespace std;

bool kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}
using namespace std;

void gotoxy(int x,int y)    
{
    printf("%c[%d;%df",0x1B,y,x);
}

void clrscr(void)
{
    system("clear");
}

void loadingg()
{
	int gd=DETECT, gm;
	initgraph(&gd,&gm,NULL);
	char gyu[]={"LOADING"};
	for(int i=0;i<7;i++)
	{
	clrscr();
	setcolor(3);
	setbkcolor(4);
	arc(320,240,0,50*i+60,100);
	sleep(500);
	gotoxy(38,16);
	for(int j=0;j<i+1;j++)
	cout<<gyu[j];
	sleep(200);
	}
	getch();
}