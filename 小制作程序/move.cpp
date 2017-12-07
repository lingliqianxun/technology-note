#include<iostream>
#include<cstdio>
#include<termios.h>
using namespace std;
static int x=10,y=5;
void print(){
	printf("\33[%d;%dH\33[47m  \33[0m",y,x);
}
void up(){
	printf("\33[%d;%dH\33[0m  ",y,x);
	y-=1;
	print();
}
void down(){
	printf("\33[%d;%dH\33[0m  ",y,x);
	y+=1;
	print();
}
void right(){
	printf("\33[%d;%dH\33[0m  ",y,x);
	x+=2;
	print();
}
void left(){
	printf("\33[%d;%dH\33[0m  ",y,x);
	x-=2;
	print();
}
int main(){
	printf("\33[2J");//清屏
	printf("\33[?25l");
	print();
	int ch,flag=1;
	struct termios save,raw;
	tcgetattr(0,&save);//保存屏显
	cfmakeraw(&raw);
	tcsetattr(0,0,&raw);
	while(flag){
		ch=getchar();
		if(ch=='\33'){
			ch=getchar();
			if(ch=='['){
				ch=getchar();
				switch(ch){
					case 'A':
						up();break;
					case 'B':
						down();break;
					case 'C':
						right();break;
					case 'D':
						left();break;
				}
			}
		}
		if(ch=='q')
			flag=0;
	}
	printf("\033[?25h");
	tcsetattr(0,0,&save);
	printf("\033[2J");//清屏
	printf("\033[1;1H");
	return 0;
}
