#include<cstdio>
#include<termios.h>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
static int s[22][66];//高22,宽33*2
static int x,y;//编辑坐标
static int num=1;//关卡
static int num_b=1;//备份关卡
static int e=0;//编辑标志
static int flag=1;//结束标志

void print(){//打印
	int h,w;
	for(h=1;h<22;h++){
		for(w=1;w<=66;w++){
			switch(s[h][w]){
				case 0:
					printf("\33[%d;%dH\33[40m  \33[0m",h,w);
					break;
				case 1:
					printf("\33[%d;%dH\33[41m[]\33[0m",h,w);
					break;
				case 2:
					printf("\33[%d;%dH\33[42m[]\33[0m",h,w);
					break;
				case 3:
					printf("\33[%d;%dH\33[43m  \33[0m",h,w);
					break;
				case 7:
					printf("\33[%d;%dH\33[47m  \33[0m",h,w);
					break;
				case 8:
					printf("\33[%d;%dH  ",h,w);
					break;
			}
			w++;
		}
	}
	printf("\33[%d;%dH\33[47m  \33[0m",y,x);//打印编辑位置
	printf("\33[22;1H当前关卡:%d 【Q】退出 【B】上一关卡 【N】下一关卡 【空格】涂写",num);
	printf("\033[23;1H【0】墙【1】箱子【2】箱子&箱子地【3】箱子地【7】人物【8】空地");
}
void getData(){//获取地图
	x=33;
	y=10;
	char filename[16];
	sprintf(filename,"map/map%d.dat",num);
	ifstream in(filename);
	//出错判断
	if(in==NULL){
		printf("\33[10;30H\033[31m无关卡！\33[0m\n");
		num=num_b;
		sleep(1);
		print();
		return;
	}
	string line;
	int h=0,w;
	while(getline(in,line)){
		w=0;
		while(*(line.data()+w)){
			s[h][w]=*(line.data()+w)-48;
			w++;
		}
		h++;
	}
	in.close();
	print();
}
void saveData(){//保存地图
	char filename[16];
	sprintf(filename,"map/map%d.dat",num);
	ofstream out(filename);
	int h,w;
	for(h=0;h<22;h++){
		for(w=0;w<66;w++){
			out<<s[h][w];
		}
		out<<endl;
	}
	printf("\33[10;30H\033[31m保存成功！\33[0m\n");
	out.close();
	sleep(1);
	print();
}
void init(){//初始化
	printf("\33[2J");//清屏
	int h,w;
	for(h=1;h<22;h++){
		for(w=1;w<=66;w++){
			printf("\33[%d;%dH\33[47m  \33[0m",h,w);//设置背景为白色
			w++;
		}
	}
	getData();
}
void up(){
	if(y-1<0)
		return;
	y-=1;
	print();
}
void down(){
	if(y+1>21)
		return;
	y+=1;
	print();
}
void right(){
	if(x+2>66)
		return;
	x+=2;
	print();
}
void left(){
	if(x-2<0)
		return;
	x-=2;
	print();
}
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
		if(ch=='s')//保存关卡
			saveData();
		if(ch=='b'){//加载上一关卡
			num_b=num;
			num--;
			getData();
		}
		if(ch=='n'){//加载下一关卡
			num_b=num;
			num++;
			getData();
		}
		if(ch=='0')//墙
			e=0;
		if(ch=='1')//箱子
			e=1;
		if(ch=='2')//箱子+箱子地
			e=2;
		if(ch=='3')//箱子地
			e=3;
		if(ch=='7')//人物
			e=7;
		if(ch=='8')//地
			e=8;
		if(ch==32){//空格涂写
			s[y][x-1]=e;
			s[y][x]=e;
		}
	}
	printf("\033[?25h");
	tcsetattr(0,0,&save);
	printf("\033[2J");//清屏
	printf("\033[1;1H");
	return 0;
}
