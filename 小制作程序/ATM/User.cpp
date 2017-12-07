#include"User.h"
User::User(){
	account=new Account;
}
User::User(Account &account){
	this->account=new Account;
	*this->account=account;
//	this->account->setAccountID(account->getAccountID());
//	this->account->setAccountName(account->getAccountName());
//	this->account->setAccountPasswd(account->getAccountPasswd());
//	this->account->setBalance(account->getBalance());
}
User::~User(){
	if(account!=NULL){
		delete account;
		account=NULL;
	}
}
char *User::getID(){
	return account->getAccountID();
}
void User::setAccount(Account &account){
	this->account=new Account;
	this->account=&account;
}
void User::fetchMoney(){
	cout<<"###############################################################################"<<endl;
	double balance;
	cout<<"请输入取款金额:";
	cin>>balance;
	if(balance<0){
		cout<<"输入金额非法,请重新输入！"<<endl;
		return;
	}else if(balance>account->getBalance()){
		cout<<"余额不足，请重新输入！"<<endl;
		return;
	}else{
		account->deposit(balance);
		cout<<"取款成功！"<<endl;
		cout<<"当前余额为:"<<account->getBalance()<<endl;
	}
}
void User::storeMoney(){
	cout<<"###############################################################################"<<endl;
	double balance;
	cout<<"请输入存款金额:";
	cin>>balance;
	if(balance<0){
		cout<<"输入金额非法,请重新输入！"<<endl;
		return;
	}else{
		account->withdraw(balance);
		cout<<"存款成功！"<<endl;
		cout<<"当前余额为:"<<account->getBalance()<<endl;
	}
}
void User::query(){
	account->display();
}
void User::change_userPasswd(){
	cout<<"###############################################################################"<<endl;
	char old[20],new1[20],new2[20];
	cout<<"请输入旧密码:";
	cin>>old;
	if(strcmp(account->getAccountPasswd(),old)){
		cout<<"密码错误，请重新输入！"<<endl;
		return;
	}
	cout<<"请输入新密码:";
	cin>>new1;
	cout<<"请再次输入:";
	cin>>new2;
	if(strcmp(new1,new2)){
		cout<<"两次密码输入不一致，请重新输入！"<<endl;
		return;
	}
	account->setAccountPasswd(new1);
	cout<<"密码修改成功！"<<endl;
}
