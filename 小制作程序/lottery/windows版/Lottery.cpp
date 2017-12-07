#include"Lottery.h"
bool check_num(char *num){
	if(strlen(num)!=16){
		cout<<"卡号非16位"<<endl;
		return false;
	}
	for(int i=0;i<16;i++){
		if(num[i]<48||num[i]>57){
			cout<<"卡号含有非数字字符！"<<endl;
			return false;
		}
	}
	return true;
}
bool check_passwd(char *num,char *passwd){
	cout<<"num"<<num<<endl;
	cout<<"pas"<<passwd<<endl;
	for(int i=0;i<16;i++){
		num[i]+=3;
		if(num[i]>57)
			num[i]-=10;
	}
	cout<<"pas"<<passwd<<endl;
	if(strcmp(num,passwd)){
		cout<<"卡密错误！"<<endl;
		return false;
	}
	return true;
}
void Lottery::Login_first(){//首次登入界面
	account.getData();
	if(!account.Login_true()){
		cout<<"时间错误,请校正时间！"<<endl;
		return;
	}
	cout<<"欢迎来到**时时大乐透彩票**公益娱乐"<<endl<<endl;
	if(account.login_first){
		struct tm *t=localtime(&account.login_time);
		cout<<"上次登入时间:"<<t->tm_year+1990<<'-'<<t->tm_mon+1<<'-'<<t->tm_mday<<' '<<setw(2)<<t->tm_hour<<':'<<t->tm_min<<endl;
	}else{
		cout<<"初玩者可获得100金额，以下为"<<endl<<endl;
		account.query_account();
		account.login_first=true;
	}
	account.login_time=time(0);
	account.saveData();
	Sleep(3000);//移植
	Login_welcome();
}
void Lottery::Login_welcome(){
	char c[2];
	while(1){
		system("CLS");//移植
		cout<<"##################################################################"<<endl;	
		cout<<"#                        1. 下注选号                             #"<<endl;	
		cout<<"#                        2. 选号记录                             #"<<endl;	
		cout<<"#                        3. 近期开奖记录                         #"<<endl;	
		cout<<"#                        4. 往期开奖记录                         #"<<endl;	
		cout<<"#                        5. 查询账户信息                         #"<<endl;	
		cout<<"#                        6. 帮助说明                             #"<<endl;	
		cout<<"#                        7. 充值                                 #"<<endl;	
		cout<<"#                        0. 退出                                 #"<<endl;	
		cout<<"##################################################################"<<endl;	
		cout<<"请输入选项:";
		cin>>c;
		account.updata();
		if(!strcmp(c,"1")){
			system("CLS");//移植
			play();
		}else if(!strcmp(c,"2")){
			system("CLS");//移植
			account.select_history();
		}else if(!strcmp(c,"3")){
			system("CLS");//移植
			account.announce_history(10);
		}else if(!strcmp(c,"4")){
			system("CLS");//移植
			account.announce_history(10000);
		}else if(!strcmp(c,"5")){
			system("CLS");//移植
			account.query_account();
		}else if(!strcmp(c,"6")){
			system("CLS");//移植
			help();
		}else if(!strcmp(c,"7")){
			system("CLS");//移植
			recharge();
		}else if(!strcmp(c,"0")){
			system("CLS");//移植
			quit();
			break;
		}else{
			cout<<"输入错误，请重新输入！"<<endl;
			Sleep(1000);//移植
			continue;
		}
		cin.clear();//清除错误
		cin.ignore(1024,'\n');//清空输入
		cout<<"输入回车键返回"<<endl;
		c[0]=getchar();
	}
}
void Lottery::quit(){//退出
	account.saveData();
	cout<<"##################################################################"<<endl;	
	cout<<"欢迎下次光临！\n";
	Sleep(3000);//移植
}
void Lottery::recharge(){//充值
	cout<<"##################################################################"<<endl;	
	char num[17],passwd[17];
	cout<<"请输入充值卡号:";
	cin>>num;
	if(!check_num(num))
		return;
	cout<<"请输入充值卡密:";
	cin>>passwd;
	if(!check_passwd(num,passwd))
		return;
	account.money+=100;
	account.saveData();
	cout<<"充值100成功！"<<endl;
}
void Lottery::help(){//帮助说明
	cout<<"##################################################################"<<endl;	
	cout<<"                            帮助说明"<<endl;
	ifstream in("help.dat");
	string line;
	while(getline(in,line)){
		cout<<line<<endl;
	}
	in.close();
}
void Lottery::put(char &s){//输入选号
	char c[2];
	cin>>c;
	if(!strcmp(c,"0")||!strcmp(c,"1")||!strcmp(c,"2")||!strcmp(c,"3")||!strcmp(c,"4")||!strcmp(c,"5")||!strcmp(c,"6")||!strcmp(c,"7")||!strcmp(c,"8")||!strcmp(c,"9"))
		s=c[0];
	else{
		cout<<"输入错误！"<<endl;
		cout<<"按回车键返回"<<endl;
		c[0]=getchar();
		c[1]=getchar();
		Login_welcome();
	}
}
void Lottery::play(){//下注选号
	time_t now=time(0);
	struct tm *t=localtime(&now);
	if(t->tm_min%10==9){
		cout<<"距离开奖不足一分钟，暂无法下注，请耐心等待下一轮购买..."<<endl;
		//		return;
	}
	int type;
	char c[3],s[6]="*****",a[6]="*****";
	cout<<"##################################################################"<<endl;	
	cout<<"#                   2.一星    4.二星组选    8.五星               #"<<endl;	
	cout<<"#     1.大小单双    3.二星    6.三星组选    9.五星通选一等       #"<<endl;	
	cout<<"#     0.返回        5.三星    12.任一       10.五星通选二等      #"<<endl;	
	cout<<"#                   7.四星    13.任二       11.五星通选三等      #"<<endl;	
	cout<<"##################################################################"<<endl;	
	cout<<"请输入选项:";
	cin>>c;
	if(!strcmp(c,"1")){
		system("CLS");//移植
		type=0;
		cout<<"##################################################################"<<endl;	
		cout<<"#       1.小       2.大       3.单       4.双       0.返回       #"<<endl;	
		cout<<"##################################################################"<<endl;	
		cout<<"请输入十位状态:";
		cin>>c;
		if(!strcmp(c,"1")||!strcmp(c,"2")||!strcmp(c,"3")||!strcmp(c,"4"))
			s[3]=c[0]-1;
		else if(!strcmp(c,"0"))
			Login_welcome();
		else{
			cout<<"输入错误！"<<endl;
			return;
		}
		system("CLS");//移植
		cout<<"##################################################################"<<endl;	
		cout<<"#       1.小       2.大       3.单       4.双       0.返回       #"<<endl;	
		cout<<"##################################################################"<<endl;	
		cout<<"请输入十位状态:";
		cin>>c;
		if(!strcmp(c,"1")||!strcmp(c,"2")||!strcmp(c,"3")||!strcmp(c,"4"))
			s[4]=c[0]-1;
		else if(!strcmp(c,"0"))
			Login_welcome();
		else{
			cout<<"输入错误！"<<endl;
			return;
		}
	}else if(!strcmp(c,"2")||!strcmp(c,"3")){
		if(!strcmp(c,"2"))
			type=1;	
		else
			type=2;
		system("CLS");//移植
		cout<<"##################################################################"<<endl;	
		cout<<"请输入个位数:";
		put(s[4]);
	}else if(!strcmp(c,"4")){
		type=3;	
		system("CLS");//移植
		cout<<"##################################################################"<<endl;	
		cout<<"请输入十位数:";
		put(s[3]);
		cout<<"##################################################################"<<endl;	
		cout<<"请输入个位数:";
		put(s[4]);
	}else if(!strcmp(c,"5")||!strcmp(c,"6")){
		if(!strcmp(c,"5"))
			type=4;	
		else
			type=5;
		system("CLS");//移植
		cout<<"##################################################################"<<endl;	
		cout<<"请输入百位数:";
		put(s[2]);
		cout<<"##################################################################"<<endl;	
		cout<<"请输入十位数:";
		put(s[3]);
		cout<<"##################################################################"<<endl;	
		cout<<"请输入个位数:";
		put(s[4]);
	}else if(!strcmp(c,"7")){
		type=5;	
		system("CLS");//移植
		cout<<"##################################################################"<<endl;	
		cout<<"请输入千位数:";
		put(s[1]);
		cout<<"##################################################################"<<endl;	
		cout<<"请输入百位数:";
		put(s[2]);
		cout<<"##################################################################"<<endl;	
		cout<<"请输入十位数:";
		put(s[3]);
		cout<<"##################################################################"<<endl;	
		cout<<"请输入个位数:";
		put(s[4]);
	}else if(!strcmp(c,"8")||!strcmp(c,"9")||!strcmp(c,"10")||!strcmp(c,"11")){
		if(!strcmp(c,"8"))
			type=7;
		if(!strcmp(c,"9"))
			type=8;
		if(!strcmp(c,"10"))
			type=9;
		if(!strcmp(c,"11"))
			type=10;
		system("CLS");//移植
		cout<<"##################################################################"<<endl;	
		cout<<"请输入万位数:";
		put(s[0]);
		cout<<"##################################################################"<<endl;	
		cout<<"请输入千位数:";
		put(s[1]);
		cout<<"##################################################################"<<endl;	
		cout<<"请输入百位数:";
		put(s[2]);
		cout<<"##################################################################"<<endl;	
		cout<<"请输入十位数:";
		put(s[3]);
		cout<<"##################################################################"<<endl;	
		cout<<"请输入个位数:";
		put(s[4]);
	}else if(!strcmp(c,"12")){
		type=11;	
		system("CLS");//移植
		cout<<"##################################################################"<<endl;	
		cout<<"#       1.万       2.千       3.百       4.十       5.个        #"<<endl;	
		cout<<"##################################################################"<<endl;	
		cout<<"请选择投注位置:";
		char c[2];
		cin>>c;
		if(!strcmp(c,"1")||!strcmp(c,"2")||!strcmp(c,"3")||!strcmp(c,"4")||!strcmp(c,"5")){
			system("CLS");//移植
			cout<<"##################################################################"<<endl;	
			cout<<"请输入该位置数:";
			put(s[c[0]-49]);
		}else{
			cout<<"输入错误！"<<endl;
			return;
		}
	}else if(!strcmp(c,"13")){
		type=12;	
		system("CLS");//移植
		cout<<"##################################################################"<<endl;	
		cout<<"#       1.万       2.千       3.百       4.十       5.个	        #"<<endl;	
		cout<<"##################################################################"<<endl;	
		cout<<"请选择第一位投注位置:";
		char c[2],ch[2];
		cin>>c;
		if(!strcmp(c,"1")||!strcmp(c,"2")||!strcmp(c,"3")||!strcmp(c,"4")||!strcmp(c,"5")){
			system("CLS");//移植
			cout<<"##################################################################"<<endl;	
			cout<<"请输入该位置数:";
			put(s[c[0]-49]);
		}else{
			cout<<"输入错误！"<<endl;
			return;
		}
		system("CLS");//移植
		cout<<"##################################################################"<<endl;	
		cout<<"#         ";	
		if(strcmp(c,"1"))
			cout<<"1.万         ";
		if(strcmp(c,"2"))
			cout<<"2.千         ";
		if(strcmp(c,"3"))
			cout<<"3.百         ";
		if(strcmp(c,"4"))
			cout<<"4.十         ";
		if(strcmp(c,"5"))
			cout<<"5.个         ";
		cout<<"   #"<<endl;
		cout<<"##################################################################"<<endl;	
		cout<<"请选择第二位投注位置:";
		cin>>ch;
		if(!strcmp(ch,"1")||!strcmp(ch,"2")||!strcmp(ch,"3")||!strcmp(ch,"4")||!strcmp(ch,"5")){
			if(!strcmp(c,ch)){
				cout<<"输入错误！"<<endl;
				return;
			}
			system("CLS");//移植
			cout<<"##################################################################"<<endl;	
			cout<<"请输入该位置数:";
			put(s[ch[0]-49]);
		}else{
			cout<<"输入错误！"<<endl;
			return;
		}
	}else if(!strcmp(c,"0")){
		Login_welcome();
	}else{
		cout<<"输入错误！"<<endl;
		return;
	}
	system("CLS");//移植
	cout<<"##################################################################"<<endl;	
	cout<<"选号完成！"<<endl;
	if(type==0){
		cout<<s[0]<<s[1]<<s[2];
		if(s[3]=='0')
			cout<<"小";
		if(s[3]=='1')
			cout<<"大";
		if(s[3]=='2')
			cout<<"单";
		if(s[3]=='3')
			cout<<"双";
		if(s[4]=='0')
			cout<<"小";
		if(s[4]=='1')
			cout<<"大";
		if(s[4]=='2')
			cout<<"单";
		if(s[4]=='3')
			cout<<"双";
		cout<<endl;
	}else
		cout<<s<<endl;
	cout<<"请输入下注数:";
	int num;
	cin>>num;
	if(num==0){
		cout<<"输入错误！"<<endl;
		return;
	}
	if(num*2>account.money){
		cout<<"余额不足，请充值！"<<endl;
		return;
	}
	now=time(0);
	t=localtime(&now);
	if(t->tm_min%10==9){
		cout<<"距离开奖不足一分钟，暂无法下注，请耐心等待下一轮购买..."<<endl;
		//		return;
	}
	account.money-=num*2;
	account.buy_num+=num;
	Number number(s,a,now,now,num,type);
	account.numbers.insert(account.numbers.begin(),1,number);
	account.saveData();
	system("CLS");//移植
	cout<<"##################################################################"<<endl;	
	cout<<"下注完成！"<<endl;
	cout<<"距离开奖时间还有"<<10-t->tm_min%10<<"分钟"<<endl;
}
