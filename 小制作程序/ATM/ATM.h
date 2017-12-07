#ifndef _ATM_H_
#define _ATM_H_
#include"Admin.h"
#include"User.h"
#include"Account.h"
#include<cstdlib>
#include<cstdio>
#include<iostream>
using namespace std;
class ATM{
	public:
		ATM();
		ATM(Admin &);
		~ATM();
		void mainMenu();
		void adminMenu();
		void userMenu();
		void adminLogin();
		void userLogin();
		void wait();//按任意键返回
	private:
		Admin *admin;
		User *user;
};
#endif
