#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<graphics.h>
#define xmid 320
#define ymid 240
#define left 20
#define right 620
#define top 40
#define bottom 440

typedef struct point
{
	int x,y;
}point;

int gd=DETECT,gm=DETECT;
int score,lives,count;
double hit_ratio;

void initscreen()
{
	int i;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	rectangle(left,top,right,bottom);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,6);
	outtextxy(xmid-185,ymid-150,"hOw FAsT");
	outtextxy(xmid-70,ymid-50,"caN");
	outtextxy(xmid-185,ymid+50,"YoU tyPe");
	delay(2000);
	closegraph();
	gotoxy(20,8);
	printf("Press the keys displayed on the screen");
	delay(1000);
	gotoxy(20,8);
	for(i=0;i<37;i++)
	{
		delay(200);
		printf("|");
	}
}

void display_lives()
{
	int offset=0,i;
	line(left,bottom-70,right,bottom-70);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	outtextxy(left+55,395,"LIVES:");
	for(i=0;i<lives;i++)
	{
		outtextxy(left+175+offset,395,"\n");
		offset+=25;
	}
}

void putcharacter(point* p,char* c)
{
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	outtextxy(p->x,p->y,c);
}

void wrong_hit()
{
	setcolor(RED);
	settextstyle(3,HORIZ_DIR,10);
	outtextxy(xmid-25,ymid-120,"X");
	setcolor(CYAN);
}


void fastfingers()
{
	point p;
	int temp;
	char c[2],key;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	setcolor(CYAN);
	while(lives!=0)
	{
		clearviewport();
		fflush(stdin);
		rectangle(left,top,right,bottom);
		display_lives();
		do
		{
			p.x=(rand()+left+20)%right-20;
			p.y=(rand()+top+20)%360;
		}while(p.x>=right-20||p.x<=left+20||p.y>=360||p.y<=top+20);
		do
		{
			temp=(rand()+97)%123;
			c[0]=(char)temp;
		}while(temp<97||temp>123);
		c[1]='\0';
		putcharacter(&p,c);
		delay(900);
		if(kbhit())
		{
			key=getch();
			if(key==c[0])
				score+=10;
			else
			{
				wrong_hit();
				lives--;
			}
		}
		count++;
		delay(30);

	}
	hit_ratio=((double)(score/10)/count)*100;
	closegraph();
}

void initgame()
{
	score=count=0;
	hit_ratio=0.0;
	lives=15;
}

int main()
{
	int c;
	char key;
	while(1)
	{
		srand(time(NULL));
		clrscr();
		gotoxy(30,8);
		printf("1)Test your Reflexes");
		gotoxy(30,11);
		printf("2)Quit because you fear");
		gotoxy(30,14);
		printf("Enter choice:");
		scanf("%d",&c);
		if(c==2)
			return 0;
		if(c!=1)
		{
			gotoxy(20,15);
			printf("You dont even qualify for viewing the menu!");
			delay(2000);
			return 0;
		}
		initscreen();
		initgame();
		fastfingers();
		gotoxy(25,8);
		printf("Score: %d Accuracy: %lf %",score,hit_ratio);
		gotoxy(30,10);
		printf("Press c to continue...");
		while(1)
		{
			if(kbhit())
			{
				key=getch();
				if(key=='c')
					break;
			}
		}
	}
}