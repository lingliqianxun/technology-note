//#井字棋双人游戏#
//2014年07月24日
//By绫里千寻
#include<iostream>
#include<stdlib.h>//system("clear")清屏
using namespace std;
int full(char s[3][3]){//判断棋盘是否下满
	int c=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(s[i][j]!='-'){
				c++;
			}
		}
	}
	if(c==9){
		return 1;
	}else{
		return 0;
	}
}
int win(int time,char s[3][3]){//判断是否获胜
	if(s[0][0]==s[0][1]&&s[0][1]==s[0][2]&&s[0][2]!='-'||
	   s[1][0]==s[1][1]&&s[1][1]==s[1][2]&&s[1][2]!='-'||
	   s[2][0]==s[2][1]&&s[2][1]==s[2][2]&&s[2][2]!='-'||

	   s[0][0]==s[1][0]&&s[1][0]==s[2][0]&&s[2][0]!='-'||
	   s[0][1]==s[1][1]&&s[1][1]==s[2][1]&&s[2][1]!='-'||
	   s[0][2]==s[1][2]&&s[1][2]==s[2][2]&&s[2][2]!='-'||

	   s[0][0]==s[1][1]&&s[1][1]==s[2][2]&&s[2][2]!='-'||
	   s[0][2]==s[1][1]&&s[1][1]==s[2][0]&&s[2][0]!='-'){
		if(time%2==1){
		cout<<"Player1 Win!"<<endl;
		}else{
		cout<<"Player2 Win!"<<endl;
		}
		return 1;
	}
	if(full(s)){
		cout<<"平局！"<<endl;
		return 1;
	}else{
		return 0;
	}
}
int exist(int time,char c){//判断棋位是否存在棋子
	if(c=='x'||c=='o'){
		cout<<"棋子已存在，请重新输入！"<<endl;
		return 0;
	}
	return 1;
}
void print(char s[3][3]){//打印棋盘
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<<s[i][j];
		}
		cout<<endl;
	}
}
int view(int time,int h,int v,char s[3][3]){//操作棋盘
	char c=s[h-1][v-1];
	if(exist(time,c)){
		if(time%2==1){
			s[h-1][v-1]='o';
		}else{
			s[h-1][v-1]='x';
		}
		print(s);
	if(win(time,s)){
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				s[i][j]='-';
			}
			cout<<endl;
		}
		cout<<"井棋"<<endl;
		print(s);
		return 2;
	}	
	return 1;
	}else{
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				cout<<s[i][j];
			}
			cout<<endl;
		}
		return 0;
	}
}
int main(){
	system("clear");//刷新棋盘
	cout<<"井棋"<<endl;
	char s[3][3]={	{'-','-','-'},
					{'-','-','-'},
					{'-','-','-'}};
	int time=1,h,v,p;
	print(s);
	while(time){
		if(time%2==1){
			cout<<"Player1(0退出):"<<endl;
		}else{
			cout<<"Player2(0退出):"<<endl;
		}
		cout<<"请输入行(1~3):";
		cin>>h;
		if(h<0||h>3){
			cout<<"输入错误，请重新输入！"<<endl;
			cout<<h;
			continue;
		}else if(h==0){
			break;
		}
		cout<<"请输入列(1~3):";
		cin>>v;
		if(v<0||v>3){
			cout<<"输入错误，请重新输入！"<<endl;
			continue;
		}else if(v==0){
			break;
		}
		system("clear");//刷新棋盘
		p=view(time,h,v,s);
		if(p==1){
		time++;
		}else if(p==2){
		time =1;
		}
	}
	return 0;
}
