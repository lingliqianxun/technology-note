#include"Account.h"

bool Account::Login_true(){//登入判断
	time_t now_time=time(0);
	return now_time<login_time?false:true;
}
void Account::select_history(){//选号记录
	cout<<"选号记录:"<<endl;
	if(numbers.empty()){
		cout<<"\t暂无选号记录！"<<endl;
		return;
	}
	vector<Number>::iterator p=numbers.begin();
	struct tm *t;
	for(p;p!=numbers.end();p++){
		cout<<"玩法:";
		switch(p->type){
			case 0:cout<<"大小单双";break;
			case 1:cout<<"一星";break;
			case 2:cout<<"二星";break;
			case 3:cout<<"二星组选";break;
			case 4:cout<<"三星";break;
			case 5:cout<<"三星组选";break;
			case 6:cout<<"四星";break;
			case 7:cout<<"五星";break;
			case 8:cout<<"五星通选一等";break;
			case 9:cout<<"五星通选二等";break;
			case 10:cout<<"五星通选三等";break;
			case 11:cout<<"任一";break;
			case 12:cout<<"任二";break;
		}
		cout<<"\t中奖与否:";
		if(p->is_win())
			cout<<"是";
		else
			cout<<"否";
		cout<<"\t下注数:"<<p->num<<"\t"<<"下注金额:"<<p->num*2<<endl;
		cout<<"选  号:";
		if(p->type==0){
			cout<<"***";
			if(p->select_num[3]=='0')
				cout<<"小";
			if(p->select_num[3]=='1')
				cout<<"大";
			if(p->select_num[3]=='2')
				cout<<"单";
			if(p->select_num[3]=='3')
				cout<<"双";
			if(p->select_num[4]=='0')
				cout<<"小";
			if(p->select_num[4]=='1')
				cout<<"大";
			if(p->select_num[4]=='2')
				cout<<"单";
			if(p->select_num[4]=='3')
				cout<<"双";
		}else
			cout<<p->select_num;
		t=localtime(&p->select_time);
		cout<<"\t选号时间:"<<t->tm_year+1990<<'-'<<t->tm_mon+1<<'-'<<t->tm_mday<<' '<<setw(2)<<t->tm_hour<<':'<<t->tm_min<<endl;
		cout<<"开奖号:";
		if(strcmp(p->announce_num,"*****")){
			cout<<p->announce_num;
		}else	
			cout<<"未开奖";
		t=localtime(&p->announce_time);
		cout<<"\t开奖时间:";
		if(strcmp(p->announce_num,"*****"))
			cout<<t->tm_year+1990<<'-'<<t->tm_mon+1<<'-'<<t->tm_mday<<' '<<setw(2)<<t->tm_hour<<':'<<t->tm_min<<endl;
		else
			cout<<"未开奖"<<endl;
		cout<<"------------------------------------------------------------------"<<endl;
	}
}
void Account::announce_history(int mount){//开奖记录
	cout<<"往期开奖记录:"<<endl;
	if(numbers.empty()){
		cout<<"\t暂无开奖信息！"<<endl;
		return;
	}
	vector<Number>::iterator p=numbers.begin();
	struct tm *t;
	int n=1;
	for(p;p!=numbers.end();p++){
		if(!strcmp(p->announce_num,"*****"))
			continue;
		t=localtime(&p->announce_time);
		cout<<setw(3);
		cout.fill('0');
		cout<<n++<<'.'<<"开奖时间:"<<t->tm_year+1990<<'-'<<t->tm_mon+1<<'-'<<t->tm_mday<<' '<<setw(2)<<t->tm_hour<<':'<<t->tm_min;
		cout<<"\t开奖号:"<<p->announce_num<<endl;
		cout<<"------------------------------------------------------------------"<<endl;
		if(n>mount)break;
	}
}
void Account::query_account(){//查询账户信息
	int pro=0;
	if(buy_num!=0)
		pro=(double)win_num/(double)buy_num*10000;//只保留4位
	cout<<"账户信息:"<<endl;
	cout<<"余额:"<<money<<"\t中奖概率:"<<(double)pro/(double)100<<"%"<<endl;
	cout<<"下注数:"<<buy_num<<"\t中奖数:"<<win_num<<endl;
}
void Account::updata(){//内置更新开奖数据
	getData();
	vector<Number>::iterator p=numbers.begin();
	struct tm *t;
	time_t tt,now,pre=0;
	for(p;p!=numbers.end();p++){
		if(!strcmp(p->announce_num,"*****")){
			t=localtime(&p->announce_time);
			t->tm_min=(t->tm_min/10+1)*10;
			if(t->tm_min==60){
				t->tm_min=0;
				t->tm_hour+=1;
			}
			if(t->tm_hour==24){
				t->tm_hour=0;
				t->tm_mday+=1;
			}//继续添加天、月、年
			t->tm_sec=0;//清除秒
			tt=mktime(t);
			if(p!=numbers.begin()&&tt==pre){
				strcpy(p->announce_num,(p-1)->announce_num);
			}else{
				now=time(0);
				if(now>=tt){
					p->announce_num[0]=rand()%10+48;
					p->announce_num[1]=rand()%10+48;
					p->announce_num[2]=rand()%10+48;
					p->announce_num[3]=rand()%10+48;
					p->announce_num[4]=rand()%10+48;
				}
			}
			p->announce_time=tt;
			pre=tt;//保存前一个
			if(p->is_win()){
				win_num++;
				switch(p->type){
					case 0:
						money+=p->num*4;break;
					case 1:
						money+=p->num*11;break;
					case 2:
						money+=p->num*116;break;
					case 3:
						money+=p->num*58;break;
					case 4:
						money+=p->num*1160;break;
					case 5:
						money+=p->num*190;break;
					case 6:
						money+=p->num*10000;break;
					case 7:
						money+=p->num*116000;break;
					case 8:
						money+=p->num*20000;break;
					case 9:
						money+=p->num*200;break;
					case 10:
						money+=p->num*30;break;
					case 11:
						money+=p->num*11;break;
					case 12:
						money+=p->num*116;break;
				}
			}
		}
	}
	saveData();
}
void Account::saveData(){//存档
	ofstream out("lottery.dat",ios::out|ios::trunc);
	out<<login_time<<' '<<money<<' '<<buy_num<<' '<<win_num<<' '<<login_first<<endl;
	vector<Number>::iterator p=numbers.begin();
	for(p;p!=numbers.end();p++){
		out<<p->select_num<<' '<<p->announce_num<<' '<<p->select_time<<' '<<p->announce_time<<' '<<p->num<<' '<<p->type<<endl;
	}
	out.close();
}
void Account::getData(){//读档
	ifstream in("lottery.dat");
	string line;
	getline(in,line);
	istringstream is(line);
	is>>login_time>>money>>buy_num>>win_num>>login_first;
	numbers.clear();
	while(getline(in,line)){
		istringstream is(line);
		char select_num[6],announce_num[6];
		time_t select_time,announce_time;
		int num,type;
		is>>select_num>>announce_num>>select_time>>announce_time>>num>>type;
		Number number(select_num,announce_num,select_time,announce_time,num,type);
		numbers.push_back(number);
	}
	in.close();
}
