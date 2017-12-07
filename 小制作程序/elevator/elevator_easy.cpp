#include<iostream>
#include<fstream>
using namespace std;
void write(const char *name,int f){
	int v;
	ifstream fin(name,ios::in);
	fin>>v;
	if(v<f){
		for(v;v<f;v++){
			cout<<"目前电梯在楼层"<<v<<"..."<<endl;
			sleep(1);
		}
	}else{
		for(v;v>f;v--){
			cout<<"目前电梯在楼层"<<v<<"..."<<endl;
			sleep(1);
		}
	}
	ofstream fout(name,ios::out|ios::trunc);
	fout<<f;
	fout.close();
}
void read(const char *name ,int &v){
	ifstream fin(name,ios::in);
	fin>>v;
	fin.close();
}
int main(){
	int f=1,v;
	cout<<"欢迎光临杰普大厦！"<<endl;
	cout<<"您目前处于楼层"<<f<<endl;
	cout<<"正在帮您呼叫电梯..."<<endl;
	sleep(2);
	while(1){
		read("a.txt",v);
		if(v==f){
			cout<<"目前电梯在本层"<<f<<"，请入电梯！"<<endl;
			cout<<"请输入要去的楼层：";
			cin>>f;
			sleep(2);
			write("a.txt",f);
			cout<<"已到达楼层"<<f<<",欢迎下次光临！"<<endl;
		}
		else
			cout<<"目前电梯在楼层"<<v<<"，请等待..."<<endl;
		write("a.txt",f);
		sleep(2);
	}

	return 0;
}
