#include<dos.h>
#include<conio.h>
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
int point;
int push(int data[], int top, int size){
if(top!=size-1)
{
top++;
data[top]=point;
} else
printf("Overflow\n");
return top;
}
void display(int data[], int top,int size){
int t=1;
if(top!=size-1)
{
while(t<=top)
{
printf("point=%d",data[t]);
t++;
}
}
if(top == 0)
printf("No elements\n");
}
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ESC 1
#ifdef __c
#define __C ...
#else
#define __C
#endif
struct SnakeParts
{

int x;
int y;
}box[50],target;
void snake(int ,int );
void initialize(int,int);
void interrupt (*prev)(__C);
void interrupt our(__C);
void snakeb();
int check();
void Rectangle(int ,int,int,int);
int
stop=0,blocks=4,direction=2,size=10,hit=1,snake_color=14,bk=7,target_color=4;

int stage=1,speed=100,sp=80,sped=60,point=0;
void main()
{
int data[100],ch; int top = 0;
int gd=DETECT,gm,x=100,op,y=100,i=0,j=0;
char msg[50];
while(1)
{
printf("\n\n SNAKE GAME FOR FUN\n");
printf("\n\n1.START THE GAME\n\n2.EXIT\n");
scanf("%d",&ch);
// while(1){
switch(ch)
{
case 1:
initgraph(&gd,&gm,"c:\\turboc3\\bg i");
prev=getvect(9);
setcolor(bk);
rectangle(0,0,639,479);
setfillstyle(SOLID_FILL,bk);
floodfill(250,250,bk);
initialize(x,y);
while (1)
{

switch(direction){

case 0: j-=size;break;
case 1: j+=size;break;
case 2: i+=size;break;
case 3: i-=size;break;

}
setcolor(snake_color);
snake(x+i,y+j);
delay(speed);
setcolor(bk);
snakeb(/*x+i,y+j*/);
setvect(9,our);
if(stop==1){break;}
if(check()){break;}
if(hit==1){
hit=0;
target.x=size+size*random(40);
target.y=size+size*random(35);
setcolor(target_color);
setfillstyle(SOLID_FILL,target_color);
circle(target.x+size/2,target.y+size/2,size/2-1);
floodfill(target.x+size/2,target.y+size/2,target_color);

}
setfillstyle(SOLID_FILL,target_color);
setcolor(2);
circle(target.x+size/2,target.y+size/2,size/2-1);
floodfill(target.x+size/2,target.y+size/2,2);
gotoxy(65,4);
printf("POINT = %3d",point);
}//end of while
getch();
closegraph();
break;
case 2: exit(1);
default:printf("\n INVALID CHOICE ");
}
top = push(data, top, 100);
display(data, top,100);
}
}
void interrupt our(__C){

switch(inportb(0x60)){

case UP: if(direction==1)break;direction=0;break;
case DOWN: if(direction==0)break;direction=1;break;
case RIGHT: if(direction==3)break;direction=2;break;
case LEFT: if(direction==2)break;direction=3;break;
case 15:blocks++;break;
case ESC: stop=1;break;

}
(*prev)();

}
void snake(int x1,int y1)
{

int k=0;

for(k=blocks-1;k>0;k--)
{

box[k].x=box[k-1].x;
box[k].y=box[k-1].y;

}
box[0].x=x1;
box[0].y=y1;
for(k=0;k<blocks;k++){

Rectangle(box[k].x,box[k].y,box[k].x+size,box[k].y+size);

}

}
void snakeb(){
int k;
for(k=0;k<blocks;k++)
{

Rectangle(box[k].x,box[k].y,box[k].x+size,box[k].y+size);

}

}
void initialize(int x,int y)
{

int i;
setcolor(bk);
rectangle(0,0,639,479);
setfillstyle(SOLID_FILL,bk);

floodfill(250,250,bk);
box[0].x=x;
box[0].y=y;
for(i=1;i<blocks;i++)
{

box[i].x=x-size*i;
box[i].y=y;

}

}
int check(){
int i;
char msg[50];
if(!(box[0].x>=0 && box[0].x<=639 && box[0].y>=0 && box[0].y<=479)){

for( i=100;i<700;i+=100){
sound(i);
delay(100);
nosound();
}
sprintf(msg,"GAME OVER");
setcolor(4);
settextstyle(1,HORIZ_DIR,6);
outtextxy(150,200,msg);
delay(3000);
cleardevice();
return 1;

}
for( i=1;i<blocks;i++){

if(box[0].x==box[i].x && box[0].y==box[i].y){
sprintf(msg,"GAME OVER");
setcolor(4);
settextstyle(1,HORIZ_DIR,6);
outtextxy(150,200,msg);
delay(3000);
cleardevice();
return 1;

}

}
if(box[0].x==target.x && box[0].y==target.y){

sound(700);
delay(100);
nosound();
blocks++;
point++;
hit=1;
setcolor(bk);
setfillstyle(SOLID_FILL,bk);
setcolor(bk);
circle(target.x+size/2,target.y+size/2,size/2-1);
floodfill(target.x+size/2,target.y+size/2,bk);

}
if(blocks==10){

stage++;
blocks=4;
sprintf(msg,"STAGE %d CLEARED",stage-1);
setcolor(4);
settextstyle(1,HORIZ_DIR,6);
outtextxy(150,200,msg);
delay(2000);
cleardevice();
initialize(100,100);
speed=100/stage;

}
return 0;

}
void Rectangle(int x1,int y1,int x2,int y2)
{

int i;
for(i=0;i<size/2;i++)

rectangle(x1+i,y1+i,x2-i,y2-i);

}
