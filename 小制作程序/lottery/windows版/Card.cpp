#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<Windows.h>
using namespace std;

int main(){
	cout<<"����:";
	char s[17];
	cin>>s;
	if(strlen(s)!=16){
		cout<<"���ŷ�16λ"<<endl;
		exit(1);
	}
	for(int i=0;i<16;i++){
		if(*(s+i)<48||*(s+i)>57){
			cout<<"���ź��з������ַ���"<<endl;
			exit(1);
		}
		*(s+i)+=3;
		if(*(s+i)>57)
			*(s+i)-=10;
	}
	cout<<"����:"<<s<<endl;
	Sleep(60000);
	return 0;
}
