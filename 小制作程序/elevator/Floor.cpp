#include"Elevator.cpp"
using std::vector;
class Floor{
	public:
		Floor(){getData();}
		void getData();
		void saveData();
		void run();
		void up();
		void down();
		void stop();
		void out_view();
		void in_view();
		void out_wait();
		void in_wait();
		void login();
		static int t,f,in;
		vector<Elevator> elevators;
};
int Floor::t=0;
int Floor::f=1;
int Floor::in=0;
void t_wait(int){//电梯门定时开门时间
	Floor::t++;
}
void out_flush(int){//用户电梯外等待
	Floor f;
	f.f=Floor::f;
	f.out_view();
//	sleep(1);
}
void Floor::run(){
	while(elevators[1].getF()==2){
		sleep(1);
		if(elevators[0].getFD()){
			up();
		}else{
			down();
		}
	}
	stop();
}
void Floor::stop(){
	sleep(1);
	elevators[1].setF(0);
	saveData();
	struct itimerval tick={{1,0},{1,0}};
	setitimer(ITIMER_REAL,&tick,NULL);
	signal(SIGALRM,t_wait);
	t=0;
	char c;
	while(elevators[1].getF()==0&&t<8){
		if(in){
			in_view();
			c=getchar();
			getData();
			if(c=='c'){
				if(elevators[0].getFU()>10){
					cout<<"超载"<<endl;			
				}else{
					elevators[1].setF(1);
					saveData();
					in_wait();
				}
			}
			if(c=='o'){
				if(elevators[1].getF()==0&&t<8){
					in=0;
					elevators[0].setFU(elevators[0].getFU()-1);
					saveData();
				}else{
					elevators[1].setF(1);
					saveData();
					in_view();
					printf("门已关闭！\n");
					sleep(1);
					printf("\033[3;1H\033[K");
					in_wait();
				}
			}
		}else{
			out_view();
			c=getchar();
			getData();
			if(c=='i'){
				if(elevators[1].getF()==0&&t<8){
					in=1;
					elevators[0].setFU(elevators[0].getFU()+1);
					saveData();
				}else{
					elevators[1].setF(1);
					saveData();
					out_view();
					printf("门已关闭！\n");
					sleep(1);
					printf("\033[3;1H\033[K");
					out_wait();
				}
			}
			if(c=='q'){
				printf("\033[2J");
				cout<<"欢迎下次光临！"<<endl;
				exit(1);
			}
		}
	}
	elevators[1].setF(1);
	saveData();
	if(in){
		in_view();
		in_wait();
	}else{
		out_view();
		out_wait();
	}
	cout<<"close()"<<endl;
}
void Floor::in_wait(){
	in_view();
	char c[2];
	while(elevators[1].getF()!=2){
		printf("\033[3;1H输入要去的楼层:\033[K");
		getData();
		c[0]=getchar();
		if(c[0]=='p'){
			elevators[1].setF(0);
			saveData();
			stop();
		}
		if(c[0]=='-'){
			c[1]=getchar();
			if(c[1]=='1'&&f!=0){
				elevators[3].setF(1);
				elevators[1].setF(2);
				if(0<f)
					elevators[0].setFD(0);
				else
					elevators[0].setFD(1);
			}
			if(c[1]=='2'&&f!=-1){
				elevators[2].setF(1);
				elevators[1].setF(2);
				if(-1<f)
					elevators[0].setFD(0);
				else
					elevators[0].setFD(1);
			}
		}
		if(c[0]=='1'){
			c[1]=getchar();
			if(c[1]=='0'&&f!=10){
				elevators[13].setF(1);
				elevators[1].setF(2);
				if(10<f)
					elevators[0].setFD(0);
				else
					elevators[0].setFD(1);
			}
			if(c[1]=='1'&&f!=11){
				elevators[14].setF(1);
				elevators[1].setF(2);
				if(11<f)
					elevators[0].setFD(0);
				else
					elevators[0].setFD(1);
			}
			if(c[1]=='2'&&f!=12){
				elevators[15].setF(1);
				elevators[1].setF(2);
				if(12<f)
					elevators[0].setFD(0);
				else
					elevators[0].setFD(1);
			}else if(f!=1&&c[1]=='\n'){
				elevators[4].setF(1);
				elevators[1].setF(2);
				if(1<f)
					elevators[0].setFD(0);
				else
					elevators[0].setFD(1);
			}
		}
		if(c[0]>=50&&c[0]<=57){
			if(f!=c[0]-48){
				elevators[c[0]-45].setF(1);
				elevators[1].setF(2);
				if(c[0]-48<f)
					elevators[0].setFD(0);
				else
					elevators[0].setFD(1);
			}
		}
		saveData();
	}
	in_view();
	run();
	cout<<"in_wait"<<endl;
	exit(1);
}
void Floor::out_wait(){
	char c;
	struct itimerval tick={{1,0},{1,0}};
	setitimer(ITIMER_REAL,&tick,NULL);
	signal(SIGALRM,out_flush);
	while(elevators[0].getF()!=f||elevators[1].getF()==1){
		c=getchar();
		getData();
		if(c=='q'){
			cout<<"欢迎下次光临！"<<endl;
			break;
		}
		if(c=='u'&&f!=12){
			elevators[f+3].setFU(1);
			saveData();
			if(f!=elevators[0].getF()){
				elevators[1].setF(2);
				if(elevators[0].getF()>f)
					elevators[0].setFD(0);
				else
					elevators[0].setFD(1);
				saveData();
				run();
			}
			if(elevators[0].getF()==f)
				stop();
		}
		if(c=='d'&&f!=-1){
			elevators[f+3].setFD(1);
			saveData();
			if(f!=elevators[0].getF()){
				elevators[1].setF(2);
				if(elevators[0].getF()>f)
					elevators[0].setFD(0);
				else
					elevators[0].setFD(1);
				saveData();
				run();
			}
			if(elevators[0].getF()==f)
				stop();
		}
		printf("\033[3;1H\033[K");
	}
	stop();
}
void Floor::up(){//单向问题
	if(in){
		in_view();
		if(elevators[f+4].getF()||elevators[f+4].getFU()||elevators[f+4].getFD()){
			elevators[f+4].setF(0);
			elevators[f+4].setFU(0);
			elevators[f+4].setFD(0);//多余单向
			elevators[1].setF(3);
			elevators[0].setF(f+1);
			f+=1;
		}else{
			elevators[0].setF(f+1);
			f+=1;
		}
		in_view();
	}else{
		out_view();
		int F=elevators[0].getF();
		if(elevators[F+4].getF()||elevators[F+4].getFU()||elevators[F+4].getFD()){
			elevators[F+4].setF(0);
			elevators[F+4].setFU(0);
			elevators[F+4].setFD(0);//多余单向
			elevators[1].setF(3);
			elevators[0].setF(F+1);
		}else{
			elevators[0].setF(F+1);
		}
		out_view();
	}
	saveData();
}
void Floor::down(){
	if(in){
		in_view();
		if(elevators[f+2].getF()||elevators[f+2].getFD()||elevators[f+4].getFU()){
			elevators[f+2].setF(0);
			elevators[f+2].setFD(0);
			elevators[f+2].setFU(0);//多余单向
			elevators[1].setF(3);
			elevators[0].setF(f-1);
			f-=1;
		}else{
			elevators[0].setF(f-1);
			f-=1;
		}
		in_view();
	}else{
		out_view();
		int F=elevators[0].getF();
		if(elevators[F+2].getF()||elevators[F+2].getFD()||elevators[F+4].getFU()){
			elevators[F+2].setF(0);
			elevators[F+2].setFD(0);
			elevators[F+2].setFU(0);//多余单向
			elevators[1].setF(3);
			elevators[0].setF(F-1);
		}else{
			elevators[0].setF(F-1);
		}
		out_view();
	}
	saveData();
}
void Floor::in_view(){
	printf("\033[1;1H\033[K楼层:");
	if(elevators[0].getF()==-1)
		printf("\033[42mB2\033[0m ");
	else if(elevators[2].getF())
		printf("\033[41mB2\033[0m ");
	else
		printf("B2 ");

	if(elevators[0].getF()==0)
		printf("\033[42mB1\033[0m ");
	else if(elevators[3].getF())
		printf("\033[41mB1\033[0m ");
	else
		printf("B1 ");

	for(int i=1;i<13;i++){
		if(elevators[0].getF()==i)
			printf("\033[42m%d\033[0m ",i);
		else if(elevators[i+3].getF())
			printf("\033[41m%d\033[0m ",i);
		else
			printf("%d ",i);
	}
	printf("\033[2;1H\033[K电梯门状态:");
	if(elevators[1].getF()==0)
		printf("\033[47m \033[0m  \033[47m \033[m");
	else
		printf(" \033[47m  \033[0m ");
	printf("\033[3;1H\033[K");
	fflush(stdout);
}
void Floor::out_view(){
	if(f==-1)
		printf("\033[1;1H\033[K当前楼层:B2");
	else if(f==0)
		printf("\033[1;1H\033[K当前楼层:B1");
	else
		printf("\033[1;1H\033[K当前楼层:%d",f);

	if(elevators[f+3].getFU()&&f!=12)
		printf(" 按钮:\033[41mU\033[0m ");
	else
		printf(" 按钮:U ");
	if(elevators[f+3].getFD()&&f!=-1)
		printf(" 按钮:\033[41mD\033[0m");
	else
		printf(" 按钮:D");

	printf("\033[2;1H\033[K电梯门状态:");
	if(elevators[1].getF()==0&&elevators[0].getF()==f)
		printf("\033[47m \033[0m  \033[47m \033[m");
	else
		printf(" \033[47m  \033[0m ");
	
	if(elevators[0].getF()==0)
		printf(" 电梯所在楼层:B1");
	else if(elevators[0].getF()==-1)
		printf(" 电梯所在楼层:B2");
	else
		printf(" 电梯所在楼层:%d",elevators[0].getF());
	printf("\033[3;1H");
	fflush(stdout);
}
void Floor::getData(){
	elevators.clear();
	ifstream in("elevator.dat");
	string line;
	while(getline(in,line)){
		istringstream is(line);
		int F,FU,FD;
		is>>F>>FU>>FD;
		Elevator e(F,FU,FD);
		elevators.push_back(e);
	}
	in.close();
}
void Floor::saveData(){
	ofstream out("elevator.dat");
	vector<Elevator>::iterator p=elevators.begin();
	for(p;p!=elevators.end();p++){
		out<<p->getF()<<' '<<p->getFU()<<' '<<p->getFD()<<endl;
	}
	out.close();
}
