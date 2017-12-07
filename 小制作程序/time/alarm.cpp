#include<iostream>
using namespace std;
#include<signal.h>
#include<unistd.h>
void sigalarm(int){
	cout<<"Hello world\n";
}
int main(){
	sigset(SIGALRM,sigalarm);
	alarm(2);
	cout<<"aa";
	while(1);
//	pause();
	return 0;
}
