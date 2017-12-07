#include<iostream>
#include<sys/time.h>
using namespace std;
int main(){
	timeval timer={1,0};
	select(0,NULL,NULL,NULL,&timer);
	cout<<"aaaaaa"<<endl;
	return 0;
}
