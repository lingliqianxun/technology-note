#include"Account.h"
Account::Account(){}
Account::Account(char *ID,char *name,char *passwd){
	strcpy(accountID,ID);
	strcpy(accountName,name);
	strcpy(accountPasswd,passwd);
	balance=0;
}
Account::Account(const char *ID,const char *name,const char *passwd,double balance){
	strcpy(accountID,ID);
	strcpy(accountName,name);
	strcpy(accountPasswd,passwd);
	this->balance=balance;
}
Account::~Account(){}
void Account::withdraw(double balance){
	this->balance+=balance;
}
void Account::deposit(double balance){
	this->balance-=balance;
}
void Account::setAccountID(char *ID){
	strcpy(accountID,ID);
}
void Account::setAccountName(char *name){
	strcpy(accountName,name);
}
void Account::setAccountPasswd(char *passwd){
	strcpy(accountPasswd,passwd);
}
void Account::setBalance(double balance){
	this->balance=balance;
}
char *Account::getAccountID(){
	return accountID;
}
char *Account::getAccountName(){
	return accountName;
}
char *Account::getAccountPasswd(){
	return accountPasswd;
}
double Account::getBalance()const{
	return balance;
}
//Account *Account::getAccount(){}
void Account::Account::display(){
	cout<<"###############################################################################"<<endl;
	cout<<"#用户ID:"<<left<<setw(20)<<accountID<<"用户名:"<<setw(20)<<accountName<<"余额:"<<setw(18)<<balance<<"#"<<endl;
	cout<<"###############################################################################"<<endl;
	cout<<endl;
}
