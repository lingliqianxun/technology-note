/*
猜拳游戏(服务器联机)
2014年08月24日
By绫里千寻
配置文件(guess.txt):用户数，p1猜测，p2猜测
目前Bug:满时等待时对方正退出
*/
#include<iostream>
#include<fstream>
#include<termios.h>
#include<stdlib.h>
using namespace std;
static int p;//区别玩家登入先后
void saveData(int select,int c=0){//保存数据
	ifstream in("guess.txt");
	int num,p1,p2;
	in>>num>>p1>>p2;
	in.close();
	ofstream out("guess.dat");
	switch(select){
		case 1:
			num++;break;
		case -1:
			num--;break;
		case 2:
			p1=c;break;
		case 3:
			p2=c;break;
		default:
			break;
	}
	out<<num<<' '<<p1<<' '<<p2;
	out.close();
}
int getData(int select){//获取数据
	ifstream in("guess.dat");
	int num,p1,p2;
	in>>num>>p1>>p2;
	in.close();
	switch(select){
		case 1:
			return num;
		case 2:
			return p1;
		case 3:
			return p2;
		default:
			break;
	}
}
void compare(int n1,int n2){
	saveData(-1);
//	if(p==2)sleep(1);
	if(n1==n2)
		printf("\033[2;1H\033[K\033[1;1H平局！\033[K");
	else if(n1==n2-1||n1==n2+2){
		if(p==1)
			printf("\033[2;1H\033[K\033[1;1H本轮获得胜利！\033[K");
		else
			printf("\033[2;1H\033[K\033[1;1H本轮被打败！\033[K");
	}else{
		if(p==2)
			printf("\033[2;1H\033[K\033[1;1H本轮获得胜利！\033[K");
		else
			printf("\033[2;1H\033[K\033[1;1H本轮被打败！\033[K");
	}
	if(getData(1)==0){
		saveData(2,0);
		saveData(3,0);
	}
//	fflush(stdout);
//	sleep(1);//延迟，防止时间差
	cout<<"\033[2;1H\033[K按任意键返回...";
	char ch;
	printf("\033[?25l");
	struct termios save,raw;
	tcgetattr(0,&save);
	cfmakeraw(&raw);
	tcsetattr(0,0,&raw);
	while(1){
		ch=getchar();
		if(ch!='\n')//ascii中\n为10
			break;
	}
	tcsetattr(0,0,&save);
	printf("\033[?25h");
}
void menu();//前向声明
void login(){//登入
	if(getData(1)==0){
		saveData(2,0);
		saveData(3,0);
	}
	int time=0;
	printf("\033[2J");
	printf("\033[?25l");
	struct termios save,raw;
	tcgetattr(0,&save);//取终端属性
	cfmakeraw(&raw);
	tcsetattr(0,0,&raw);
	while(getData(1)==2){
		printf("\033[1;1H当前登入用户已满，请稍后重新登入！\033[K");
		printf("\033[2;1H");
		tcsetattr(0,0,&save);
		printf("\033[?25h");
		exit(1);
	}
//	printf("\033[1;1H\033[K登入成功！\033[2;1H");
	saveData(1);
	if(getData(1)==1)p=1;
	if(getData(1)==2)p=2;
	time=0;
	while(getData(1)==1){
		printf("\033[1;1H等待其他用户上线中\033[K");
		fflush(stdout);
		if(getData(1)==2)break;sleep(1);
		printf(".");fflush(stdout);sleep(1);
		if(getData(1)==2)break;sleep(1);
		printf(".");fflush(stdout);sleep(1);
		if(getData(1)==2)break;sleep(1);
		printf(".");fflush(stdout);sleep(1);
		if(getData(1)==2)break;sleep(1);
		if(++time>5){
			printf("\033[1;1H\033[K连接超时，请重新登入！\033[2;1H");
			tcsetattr(0,0,&save);
			printf("\033[?25h");
			saveData(-1);
			exit(1);
		}
	}
	tcsetattr(0,0,&save);
	printf("\033[?25h");
	menu();
}
void menu(){
	while(p==1){
		printf("\033[1;1H\033[K1.石头 2.剪刀 3.布 q.退出\033[2;1H\033[K请选择游戏选项:");
		char c;
		cin>>c;
		if(c=='1'||c=='2'||c=='3'){
			saveData(2,c-48);
			break;
		}
		if(c=='q'){
			saveData(-1);
			exit(1);
		}
		continue;
	}
	if(p==2){
		printf("\033[?25l");
		struct termios save,raw;
		tcgetattr(0,&save);//取终端属性
		cfmakeraw(&raw);
		tcsetattr(0,0,&raw);
		while(getData(2)==0){
			printf("\033[2;1H\033[K\033[1;1H已有用户在线，等待对方输入\033[K");
			fflush(stdout);
			if(getData(2)!=0)break;sleep(1);
			printf(".");fflush(stdout);sleep(1);
			if(getData(2)!=0)break;sleep(1);
			printf(".");fflush(stdout);sleep(1);
			if(getData(2)!=0)break;sleep(1);
			printf(".");fflush(stdout);sleep(1);
			if(getData(2)!=0)break;sleep(1);
			if(getData(1)==1){
				printf("\033[1;1H\033[K\033[1;1H对方已下线，正重新连接...\033[K");
				fflush(stdout);
				saveData(-1);
				sleep(2);
				tcsetattr(0,0,&save);
				printf("\033[?25h");
				login();
			}
		}
		tcsetattr(0,0,&save);
		printf("\033[?25h");

		while(p==2){//内嵌
			printf("\033[1;1H\033[K1.石头 2.剪刀 3.布 q.退出\033[2;1H\033[K请选择游戏选项:");
			char c;
			cin>>c;
			if(c=='1'||c=='2'||c=='3'){
				saveData(3,c-48);
				break;
			}
			if(c=='q'){
				saveData(-1);
				exit(1);
			}
			continue;
		}

	}
	if(p==1){
		printf("\033[?25l");
		struct termios save,raw;
		tcgetattr(0,&save);//取终端属性
		cfmakeraw(&raw);
		tcsetattr(0,0,&raw);
		while(getData(3)==0){
			printf("\033[2;1H\033[K\033[1;1H等待对方输入\033[K");
			fflush(stdout);
			if(getData(3)!=0)break;sleep(1);
			printf(".");fflush(stdout);sleep(1);
			if(getData(3)!=0)break;sleep(1);
			printf(".");fflush(stdout);sleep(1);
			if(getData(3)!=0)break;sleep(1);
			printf(".");fflush(stdout);sleep(1);
			if(getData(3)!=0)break;sleep(1);
			if(getData(1)==1){
				printf("\033[1;1H\033[K\033[1;1H对方已下线，正重新连接...\033[K");
				fflush(stdout);
				saveData(-1);
				sleep(2);
				tcsetattr(0,0,&save);
				printf("\033[?25h");
				login();
			}
		}
		tcsetattr(0,0,&save);
		printf("\033[?25h");
	}
	compare(getData(2),getData(3));
	login();
}
int main(){
	login();
	return 0;
}
