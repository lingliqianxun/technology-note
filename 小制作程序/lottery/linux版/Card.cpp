#include<iostream>
#include<stdlib.h>
#include<cstring>
using namespace std;

int main(int argc,char *argv[]){
	if(argc<2){
		cout<<"无卡号！"<<endl;
		exit(1);
	}
	if(strlen(argv[1])!=16){
		cout<<"卡号非16位"<<endl;
		exit(1);
	}
	for(int i=0;i<16;i++){
		if(argv[1][i]<48||argv[1][i]>57){
			cout<<"卡号含有非数字字符！"<<endl;
			exit(1);
		}
		argv[1][i]+=3;
		if(argv[1][i]>57)
			argv[1][i]-=10;
	}
	cout<<"卡密:"<<argv[1]<<endl;
	return 0;
}
