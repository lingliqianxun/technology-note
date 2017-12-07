//ATM银行系统
//制作结束08-22-2014
//By绫里千寻
#include"Account.h"
#include"User.h"
#include"Admin.h"
#include"ATM.h"
#include<iostream>
#include<vector>
using namespace std;
#include"Account.cpp"
#include"Admin.cpp"
#include"User.cpp"
#include"ATM.cpp"
int main(){
//	Admin admin("admin","admin");
	Admin admin;
	ATM atm(admin);
	atm.mainMenu();
//	Account a("001","lisa","123",900);
//	User user(a);
//	user.query();
	return 0;
}
