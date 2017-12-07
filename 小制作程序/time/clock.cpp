#include<iostream>
#include<time.h>
using namespace std;
int main(){
	clock_t start=clock();
	//cout<<clock();
	int i=0;
	for(i;(clock()-start)!=1000000;i++){
	}
	//clock_t end=(clock()-start)/CLOCKS_PER_SEC;
	cout<<i<<endl;
	return 0;
}
