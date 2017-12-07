//#模拟城市#
//2014年10月11日
//By绫里千寻
#include<cstdio>
#include<termios.h>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
static int s[30][100];//高30,宽50*2
static int x,y;//编辑坐标
static int e=4;//编辑标志
static int flag=1;//结束标志
static int quit=1;//退出与否
static int money=50000;//金钱
static int business=0;//商业数
static int farm=0;//田地数
static int house=0;//住宅数
static int road=0;//马路数
static int num;
static int num_b;

void print(){//打印地图
	int h,w;
	for(h=1;h<30;h++){
		for(w=1;w<100;w++){
			switch(s[h][w]){
				case 0:
					printf("\33[%d;%dH\33[40m  \33[0m",h,w);//未开发
					break;
				case 1:
					printf("\33[%d;%dH\33[41m╠╗\33[0m",h,w);//商业
					break;
				case 2:
					printf("\33[%d;%dH\33[42m≡ \33[0m",h,w);//田地
					break;
				case 3:
					printf("\33[%d;%dH\33[43m╤╕\33[0m",h,w);//住宅
					break;
				case 4:
					printf("\33[%d;%dH  ",h,w);//马路
					break;
			}
			w++;
		}
	}
	switch(e){//打印编辑位置
		case 0:
			printf("\33[%d;%dH\33[40m↓ \33[0m",y,x);
			break;
		case 1:
			printf("\33[%d;%dH\33[41m↓ \33[0m",y,x);
			break;
		case 2:
			printf("\33[%d;%dH\33[42m↓ \33[0m",y,x);
			break;
		case 3:
			printf("\33[%d;%dH\33[43m↓ \33[0m",y,x);
			break;
		case 4:
			printf("\33[%d;%dH↓ ",y,x);
			break;
	}
}
void flush(){//刷新信息
	//加钱
	money+=business*100+farm*100+road*40-house*100;
	//显示
	int people=house*100;
	int worker=business*50+farm*50+road*25;
	printf("\33[30;1H\33[K信息:\t金钱:%d\t工作人数/总人口:%d/%d",money,worker,people);
	printf("\33[31;1H\33[K数量:\t商业数:%d/%d\t田地数:%d\t住宅数:%d\t马路数:%d",business,farm/2,farm,house,road);
	printf("\33[32;1H\33[K造价:\t商业(20000)\t田地(5000)\t住宅(10000)\t马路(3000)");
	printf("\33[33;1H\33[K操作:\t【1】商业\t【2】田地\t【3】住宅\t【4】马路");
	printf("\33[34;1H\33[K\t【↑ 】上移\t【↓ 】下移\t【← 】左移\t【→ 】右移");
	printf("\33[35;1H\33[K\t【0】未开发(拆除)\t\t【空格】放置\t【Q】退出");
	//判断成功&失败
	if(money>10000000){
		while(quit){
			printf("\33[14;30H恭喜您已经成为大富翁,是否继续游戏[Y/N]！\n");
			char ch;
			ch=getchar();
			if(ch=='y'){
				quit=0;
				break;
			}
			if(ch=='n'){
				flag=0;
				quit=0;
			}
		}
		
	}else if(money<0){
		while(quit){
			printf("\33[14;35H抱歉,您已破产,是否继续游戏[Y/N]！\n");
			char ch;
			ch=getchar();
			if(ch=='y'){
				quit=0;
				break;
			}
			if(ch=='n'){
				flag=0;
				quit=0;
			}
		}
	}
}
void put(){//放置
	if(s[y][x]!=0&&e!=0){
		printf("\33[14;40H已存在建筑,请拆除后建设！\n");
		sleep(1);
		return;
	}
	if(e==0){//未开发(拆除)
		if(s[y][x]==1){
			business--;
			money+=5*400;
		}
		if(s[y][x]==2){
			if(business>(farm-1)/2){
				printf("\33[14;40H田地供应不足,无法拆除！\n");
				sleep(1);
				return;
			}
			farm--;
			money+=5*100;
		}
		if(s[y][x]==3){
			if(business*50+farm*50+road*25>house*100-100){
				printf("\33[14;40H人数供应不足,无法拆除！\n");
				sleep(1);
				return;
			}
			house--;
			money+=5*200;
		}
		if(s[y][x]==4){
			road--;
			money+=5*60;
		}
	}
	//金钱是否足够
	int build_money=0;
	if(e==1)build_money=50*400;
	if(e==2)build_money=50*100;
	if(e==3)build_money=50*200;
	if(e==4)build_money=50*60;
	if(build_money>money&&e!=0){
		printf("\33[14;45H金钱不足！\n");
		sleep(1);
		return;
	}
	//人数是否足够
	if(e==1||e==2||e==4){
		int people;
		if(e==1)people=50;
		if(e==2)people=50;
		if(e==4)people=25;
		if(business*50+farm*50+road*25+people>house*100){
			printf("\33[14;40H人数不足,请先建设住宅！\n");
			sleep(1);
			return;
		}
	}
	//建设商业,田地是否足够
	if(e==1){
		if(business+1>farm/2){
			printf("\33[14;40H田地数不足,请先建设田地！\n");
			sleep(1);
			return;
		}
		business++;
		printf("\33[14;45H-20000\n");
		usleep(300000);
	}
	if(e==2){
		farm++;
		printf("\33[14;45H-5000\n");
		usleep(300000);
	}
	if(e==3){
		house++;
		printf("\33[14;45H-10000\n");
		usleep(300000);
	}
	if(e==4){
		road++;
		printf("\33[14;45H-3000\n");
		usleep(300000);
	}
	//修改数据
	s[y][x-1]=e;
	s[y][x]=e;
	money-=build_money;
	flush();
}
void init(){//初始化
	printf("\33[2J");//清屏
	int h,w;
	for(h=1;h<30;h++){
		for(w=1;w<100;w++){
			s[h][w]=0;
			w++;
		}
	}
	x=1;
	y=1;
	print();
	flush();
}
void up(){
	if(y-1<0)
		return;
	y-=1;
	flush();
}
void down(){
	if(y+1>29)
		return;
	y+=1;
	flush();
}
void right(){
	if(x+2>100)
		return;
	x+=2;
	flush();
}
void left(){
	if(x-2<0)
		return;
	x-=2;
	flush();
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
		if(ch=='y')//Y退出
			quit=0;
		if(ch=='n')//N不退出
			quit=1;
		if(ch=='0')//未开发(拆除)
			e=0;
		if(ch=='1')//商业
			e=1;
		if(ch=='2')//田地
			e=2;
		if(ch=='3')//住宅
			e=3;
		if(ch=='4')//马路
			e=4;
		if(ch==32)//空格涂写
			put();
		print(ch);
	}
	printf("\033[?25h");
	tcsetattr(0,0,&save);
	printf("\033[2J");//清屏
	printf("\033[1;1H");
	return 0;
}
/*保存/读取功能
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
*/
