//#推箱子&编辑器#
//2014年10月08日
//By绫里千寻
#include<cstdio>
#include<termios.h>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
static int s[22][66];//高22,宽33*2
static int x,y;//玩家坐标
static int num=1;//关卡
static int flag=1;//结束标志
#include"pushBox.cpp"

int main(){
	init();//初始化
	printf("\33[?25l");
	int ch;
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
		if(ch=='q')//退出
			flag=0;
		if(ch=='r')//重新本关卡
			getData();
	}
	printf("\033[?25h");
	tcsetattr(0,0,&save);
	printf("\033[2J");//清屏
	printf("\033[1;1H");
	return 0;
}
