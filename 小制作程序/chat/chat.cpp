/*
双人聊天(服务器联机)
2014年08月25日
By绫里千寻
配置文件(chat.dat):用户数，p1输入状态，p2输入状态，文字
	p输入状态:0(未输入)，1(已输入)，3(已下线)
*/
#include<iostream>
#include<fstream>
#include<cstring>
#include<stdlib.h>
#include<time.h>
using namespace std;
static int p;
void getData(int select,char *c){
	char num[2],p1[2],p2[2],s[256];
	ifstream in("chat.dat");
	in>>num>>p1>>p2>>s;
	in.close();
	switch(select){
		case 1:
			strcpy(c,num);break;
		case 2:
			strcpy(c,p1);break;
		case 3:
			strcpy(c,p2);break;
		case 4:
			strcpy(c,s);break;
		default:
			break;
	}
}
void saveData(int select,const char *c=NULL){
	char num[2],p1[2],p2[2],s[256],t[256];
	ifstream in("chat.dat");
	in>>num>>p1>>p2>>s;
	in.close();
	//time
	time_t rawtime;
	time(&rawtime);
	struct tm * timeinfo;
	timeinfo=localtime(&rawtime);
	strftime(t,256,"(%X-%m/%d/%Y):",timeinfo);
	switch(select){
		case 1:
			num[0]+=1;break;
		case -1:
			num[0]-=1;break;
		case 2:
			strcpy(p1,c);break;
		case 3:
			strcpy(p2,c);break;
		case 4:
			strcpy(s,strcat(t,c));break;
		default:
			break;
	}
	ofstream out("chat.dat");
	out<<num<<' '<<p1<<' '<<p2<<' '<<s;
	out.close();
}
void chat();
void login();
void wait(){chat();}
void chat(){
	if(p==1){
		saveData(3,"0");
		printf("\033[K请输入文字(q退出):");
		char num[2],p2[2],c[256];
		cin>>c;
		if(strcmp(c,"q")==0){
			cout<<"欢迎下次使用！"<<endl;
			getData(1,num);//单独退出
			if(strcmp(num,"2")==0)
				saveData(2,"3");
			saveData(-1);
			exit(1);
		}
		saveData(4,c);
		saveData(2,"1");
		getData(3,p2);
		while(strcmp(p2,"1")!=0){
			printf("等待对方输入...\n");
			fflush(stdout);
			printf("\033[1A");
			getData(3,p2);
			if(strcmp(p2,"3")==0){
				printf("\033[K对方已下线，正重新登入...\n");
				saveData(-1);
				saveData(3,"0");
				login();
			}
			sleep(1);
		}
		getData(4,c);
		printf("\033[K对方%s\n",c);
	}
	if(p==2){
		char p1[2],c[256];
		while(strcmp(p1,"1")!=0){
			printf("等待对方输入...\n");
			fflush(stdout);
			printf("\033[1A");
			getData(2,p1);
			if(strcmp(p1,"3")==0){
				printf("\033[K对方已下线，正重新登入...\n");
				saveData(-1);
				saveData(2,"0");
				login();
			}
			sleep(1);
		}
		saveData(2,"0");
		getData(4,c);
		printf("\033[K对方%s\n",c);
		cout<<"请输入文字(q退出):";
		cin>>c;
		if(strcmp(c,"q")==0){
			cout<<"欢迎下次使用！"<<endl;
			saveData(-1);
			saveData(3,"3");
			exit(1);
		}
		saveData(4,c);
		saveData(3,"1");
	}
	wait();
}
void login(){
	int time=0;
	char num[2];
	getData(1,num);
	while(strcmp(num,"2")==0){
		printf("\033[K用户已满，请等待...\n");
		printf("\033[1A");
		getData(1,num);
		sleep(1);
		if(time++>15){
			printf("\033[K连接超时，请重新登入！\n");
			exit(1);
		}
	}
	cout<<"登入成功！"<<endl;
	saveData(1);
	getData(1,num);
	if(!strcmp(num,"1"))p=1;
	if(!strcmp(num,"2"))p=2;
	getData(1,num);
	cout<<"当前用户数:"<<num<<endl;
	while(strcmp(num,"1")==0){
		printf("\033[K等待其他用户登入...\n");
		printf("\033[1A");
		getData(1,num);
		sleep(1);
		if(time++>15){
			printf("\033[K连接超时，请重新登入！\n");
			saveData(-1);
			exit(1);
		}
	}
	chat();
}
int main(){
	login();
	return 0;
}
