#include"Admin.h"
Admin::Admin(){
//	strcpy(adminName,"admin");
//	strcpy(adminPasswd,"admin");
	getData();
}
Admin::Admin(const char *name,const char *passwd){
	strcpy(adminName,name);
	strcpy(adminPasswd,passwd);
	getData();
}
Admin::~Admin(){}
void Admin::setName(char *name){
	strcpy(adminName,name);
}
void Admin::setPasswd(char *passwd){
	strcpy(adminPasswd,passwd);
}
char *Admin::getName(){
	return adminName;
}
char *Admin::getPasswd(){
	return adminPasswd;
}
void Admin::query_all(){
	if(!accounts.size()){
		cout<<"###############################################################################"<<endl;
		cout<<"目前没有用户，请添加！"<<endl;
	}else{
		vector<Account>::iterator p=accounts.begin();
		for(p;p!=accounts.end();p++)
			p->display();
	}
}
void Admin::query_one(){
	if(!accounts.size()){
		cout<<"###############################################################################"<<endl;
		cout<<"目前没有用户，请添加！"<<endl;
	}else{
		cout<<"###############################################################################"<<endl;
		cout<<"请输入要查询的用户ID:";
		char id[20];
		cin>>id;
		if(!isID(id)){
			cout<<"该用户不存在！"<<endl;
		}else{
			vector<Account>::iterator p=accounts.begin();
			for(p;p!=accounts.end();p++){
				if(!strcmp(p->getAccountID(),id)){
					p->display();
				}
			}
		}
	}
}
void Admin::add_account(){
	cout<<"###############################################################################"<<endl;
	char id[20],name[20],passwd[20];
	double balance;
	cout<<"输入用户ID:";
	cin>>id;
	if(isID(id)){
		cout<<"用户已存在，请重新添加！"<<endl;
	}else{
		cout<<"输入用户名:";
		cin>>name;
		cout<<"输入用户密码:";
		cin>>passwd;
		cout<<"输入余额:";
		cin>>balance;
		if(balance<0){
			cout<<"输入金额错误，请重新添加！"<<endl;
		}else{
			Account account(id,name,passwd,balance);
			accounts.push_back(account);
			saveData();
			cout<<"添加用户成功！"<<endl;
		}
	}
}
void Admin::remove_account(){
	if(!accounts.size()){
		cout<<"###############################################################################"<<endl;
		cout<<"目前没有用户，请添加！"<<endl;
	}else{
		cout<<"###############################################################################"<<endl;
		cout<<"请输入要删除的用户ID:";
		char id[20];
		cin>>id;
		if(!isID(id)){
			cout<<"该用户不存在！"<<endl;
		}else{
			vector<Account>::iterator p=accounts.begin();
			for(p;p!=accounts.end();p++){
				if(!strcmp(p->getAccountID(),id)){
					accounts.erase(p);
					p--;//由于删除了一个元素后accounts.end()也减1，下次循环p++越界，因此要减1
					//break();//或添加break直接退出
				}
			}
			saveData();
			cout<<"删除用户成功！"<<endl;
		}
	}
}
void Admin::change_account(){
	if(!accounts.size()){
		cout<<"###############################################################################"<<endl;
		cout<<"目前没有用户，请添加！"<<endl;
	}else{
		cout<<"###############################################################################"<<endl;
		cout<<"请输入要修改的用户ID:";
		char id[20],name[20],passwd[20];
		double balance;
		cin>>id;
		if(!isID(id)){
			cout<<"该用户不存在！"<<endl;
		}else{
			vector<Account>::iterator p=accounts.begin();
			for(p;p!=accounts.end();p++){
				if(!strcmp(p->getAccountID(),id)){
					p->display();
					break;
				}
			}
			cout<<"输入新用户名:";
			cin>>name;
			cout<<"输入新用户密码:";
			cin>>passwd;
			cout<<"输入新余额:";
			cin>>balance;
			if(balance<0){
				cout<<"输入金额错误，请重新修改！"<<endl;
			}else{
				p->setAccountName(name);
				p->setAccountPasswd(passwd);
				p->setBalance(balance);
				saveData();
				cout<<"修改用户成功！"<<endl;
			}
		}
	}
}
void Admin::getData(){
	ifstream in("data.txt");
	string line;
	while(getline(in,line)){
		istringstream is(line);
		char ID[20],name[20],passwd[20];
		double balance;
		is>>ID>>name>>passwd>>balance;
		if(!strcmp(ID,"admin")){
			strcpy(adminName,name);
			strcpy(adminPasswd,passwd);
		}
		Account account(ID,name,passwd,balance);
	//	Account account(strcat(ID,""),strcat(name,""),strcat(passwd,""),balance);
		accounts.push_back(account);
	}
	in.close();
}
void Admin::saveData(){
	ofstream out("data.txt",ios::out|ios::trunc);
	vector<Account>::iterator p=accounts.begin();
	for(p;p!=accounts.end();p++){
		if(!strcmp(p->getAccountID(),"admin")){
			setName(p->getAccountName());
			setPasswd(p->getAccountPasswd());
		}
		out<<p->getAccountID()<<' '<<p->getAccountName()<<' '<<p->getAccountPasswd()<<' '<<p->getBalance()<<endl;
	}
	out.close();
}
bool Admin::isID(char *ID){
	vector<Account>::iterator p=accounts.begin();
	for(p;p!=accounts.end();p++){
		if(!strcmp(p->getAccountID(),ID))
			return true;
	}
	return false;
}
bool Admin::isName(char *name){
	vector<Account>::iterator p=accounts.begin();
	for(p;p!=accounts.end();p++){
		if(!strcmp(p->getAccountName(),name))
			return true;
	}
	return false;
}
bool Admin::check_account(char *name,char *passwd,User &user){
	vector<Account>::iterator p=accounts.begin();
	for(p;p!=accounts.end();p++){
		if(!strcmp(p->getAccountName(),name)&&!strcmp(p->getAccountPasswd(),passwd)){
			user.setAccount(*p);
			return true;
		}
	}
	return false;
}
void Admin::transfer(int sure,const char *id_u){
	cout<<"###############################################################################"<<endl;
	cout<<"请输入对方ID:";
	char id1[20],id2[20];
	cin>>id1;
	if(!isID(id1)){
		cout<<"不存在该用户，请重新操作！"<<endl;
		return;
	}   
	if(!strcmp(id1,id_u)){
		cout<<"该ID为本用户，请重新操作！"<<endl;
	}
	cout<<"请再输入一遍:";
	cin>>id2;
	if(strcmp(id1,id2)){
		cout<<"两次输入不一致，请重新操作！"<<endl;
		return;
	}   
	vector<Account>::iterator p=accounts.begin();
	for(p;p!=accounts.end();p++){
		if(!strcmp(p->getAccountID(),id1)){
			break;
		}
	}
	vector<Account>::iterator p_u=accounts.begin();
	for(p_u;p_u!=accounts.end();p_u++){
		if(!strcmp(p_u->getAccountID(),id_u)){
			break;
		}
	}
	cout<<"对方信息:"<<*p->getAccountName()<<"*"<<endl;
	double balance;
	cout<<"请输入转(存)入金额:";
	cin>>balance;
	if(balance<0){
		cout<<"输入错误，请重新操作！"<<endl;
		return;
	}   
	if(sure){
		if(balance>p_u->getBalance()){
			cout<<"余额不足，请重新操作！"<<endl;
			return;
		}else{
			p_u->deposit(balance);
			cout<<"转账成功！"<<endl;
			cout<<"当前余额:"<<p_u->getBalance()<<endl;
		}
	}else
		cout<<"存入成功！"<<endl;
	p->withdraw(balance);
	saveData();
}
