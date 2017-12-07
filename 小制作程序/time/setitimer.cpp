#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>
#include<sys/time.h>
static int count=0;
void printMes(int){
	printf("%d\n",++count);
}
int main(){
	int res=0;
	struct itimerval tick;
	signal(SIGALRM,printMes);
	memset(&tick,0,sizeof(tick));
	tick.it_value.tv_sec=1;
	tick.it_value.tv_usec=0;
	tick.it_interval.tv_sec=1;
	tick.it_interval.tv_usec=0;
	if(setitimer(ITIMER_REAL,&tick,NULL)<0){
		printf("error\n");
	}
	while(1){
		pause();
	}
	return 0;
}
