#include<graphics.h>
#include<fstream.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<iostream.h>

void loadingg()
{
	int gd=DETECT, gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI\\");
	char gyu[]={"LOADING"};
	for(int i=0;i<7;i++)
	{
		clrscr();
		setcolor(3);
		setbkcolor(4);
		arc(320,240,0,50*i+60,100);
		delay(10);
		gotoxy(38,16);
		for(int j=0;j<i+1;j++)
			cout<<gyu[j];
		delay(200);
	}
	getch();
}

int i,j,score;
void gen();
struct pill
{
	int x[2],y[2];
}flap[3];
void bak()
{
	for(int i=0;i<16;i++)
	{
		int n=0;
		switch(random(2))
		{
		case 0:n=14;break;
		case 1:n=15;break;
		}
		setfillstyle(7,n);
		bar3d(i*40,370-(i%5)*10,i*40+40,380,0,0);
	}
}
void rec(int o)
{
	randomize();
	flap[o].x[0]=660;
	flap[o].x[1]=660;
	do{
	flap[o].y[0]=random(280)+100;
	flap[o].y[1]=random(280)+100;
	}while(flap[o].y[1]-flap[o].y[0]!=60 || flap[o].y[0]<120 || flap[o].y[1]>=370);
}
int end()
{
	int h=0;
	for(int e=0;e<3;e++)
	{
	if(i>flap[e].x[0]-10 && i<flap[e].x[0]+30)
	if(j<=flap[e].y[0]+10 || j>=flap[e].y[1]-10)
	h++;
	}
	if(h>0)
	return 1;
	else
	return 0;
}
void game()
{
	setbkcolor(7);
	i=320;
	j=240;
	score=0;
	int kt;
	for(int s=0;s<3;s++)
	{
	rec(s);
	flap[s].x[0]=660+s*220;
	flap[s].x[1]=660+s*220;
	}
	while(kt!=27 &&j>=110 && j<=370 && end()==0)
	{
		cleardevice();
		ofstream oyt("temp.txt");
		oyt<<score;
		oyt.close();
		char a[5];
		ifstream ot("temp.txt");
		ot>>a;
		ot.close();
		setcolor(1);
		outtextxy(50,50,"Score:");
		outtextxy(580,50,a);
		outtextxy(300,420,"FLAPPY BIRDS");
		bak();
		line(0,100,640,100);
		line(0,380,640,380);
		setcolor(9);
		circle(i,j,10);
		setcolor(8);
		circle(i+5,j+2,2);
		if(j%20)
			line(i-20,j-8,i-5,j);
		else
			line(i-20,j,i-5,j);
		line(i+10,j+2,i+15,j);
		line(i+10,j-2,i+15,j);
		for(int u=0;u<3;u++)
		{
			if(flap[u].x[0]==0)
				{rec(u);}
			if(flap[u].x[0]+40==i)
				score++;
			if(flap[u].x[0]<620)
			{
				setcolor(2);
				// setfillstyle(1,2);
				bar3d(flap[u].x[0],100,flap[u].x[0]+20,flap[u].y[0],0,8);
				bar3d(flap[u].x[1],flap[u].y[1],flap[u].x[1]+20,380,0,8);
				// setfillstyle(1,0);
				setcolor(2);
				rectangle(flap[u].x[0]+5,110,flap[u].x[0]+15,flap[u].y[0]-10);
				rectangle(flap[u].x[1]+5,flap[u].y[1]+10,flap[u].x[1]+15,370);
			}
			for(int wb=0;wb<2;wb++)
				flap[u].x[wb]-=10;
		}
		delay(100);
		if(kbhit())
		{
			kt=getch();
			j-=20;
		}
		else
			j+=10;
	}
	gen();
}
void gen()
{
	cleardevice();
	for(int u=0;u<3;u++)
	if(flap[u].x[0]<620)
	{
	setcolor(2);
	// setfillstyle(7,2);
	bar3d(flap[u].x[0],100,flap[u].x[0]+20,flap[u].y[0],0,0);
	bar3d(flap[u].x[1],flap[u].y[1],flap[u].x[1]+20,380,0,0);
	setcolor(3);
	rectangle(flap[u].x[0]+5,110,flap[u].x[0]+15,flap[u].y[0]-10);
	rectangle(flap[u].x[1]+5,flap[u].y[1]+10,flap[u].x[1]+15,370);
	}
	line(0,100,640,100);
	line(0,380,640,380);
	// setfillstyle(1,15);
	setcolor(9);
	circle(i,j,10);
	setcolor(8);
	circle(i+5,j+2,2);
	int style= 4;
	setcolor(4);
	rectangle(230,192,410,288);
	floodfill(250,200,4);
	// settextstyle(style,HORIZ_DIR,2);
	ofstream oyt("temp.txt");
	oyt<<score;
	oyt.close();
	char a[5];
	ifstream ot("temp.txt");
	ot>>a;
	ot.close();
	setcolor(4);
	outtextxy(300,230,a);
	switch(score/10)
	{
	case 0:outtextxy(260,200,"BETTER LUCK");
	       break;
	case 1:outtextxy(280,200,"BRONZE");
	       break;
	case 2:outtextxy(280,200,"SILVER");
	       break;
	case 3:outtextxy(280,200,"GOLD");
	       break;
	default:outtextxy(280,200,"PLATINUM");
	}
	getch();
	style=0;
	outtextxy(200,400,"PRESS Y TO PLAY AGAIN");
	// settextstyle(style,HORIZ_DIR,0);
	char x;
	cin>>x;
	if(x=='Y' || x=='y')
	game();
	else
	{
	closegraph();

	exit(1);
	}
}
int main()
{
	clrscr();
	cout<<"\t\t\t\tFLAPPY BIRDS \n\n\n\n\n\n\n\n\t\t\tPress Any Key To Continue";
	getch();
	loadingg();
	getch();
	game();
	return 0;
}