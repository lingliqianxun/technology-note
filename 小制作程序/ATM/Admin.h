#ifndef _ADMIN_H_
#define _ADMIN_H_
#include"Account.h"
#include"User.h"
#include<cstring>
#include<fstream>
#include<sstream>
#include<vector>
#include<termios.h>
using std::vector;
class Admin{
	public:
		Admin();
		Admin(const char *,const char *);
		~Admin();
		void setName(char *);
		void setPasswd(char *);
		char *getName();
		char *getPasswd();
		void query_all();
		void query_one();
		void add_account();
		void remove_account();
		void change_account();
		void getData();
		void saveData();
		bool isID(char *);//判断用户ID是否存在
		bool isName(char *);//判断用户名是否存在
		bool check_account(char *,char *,User &);//校对用户名与密码
		void transfer(int,const char *id="");//无卡存款与转账
	private:
		char adminName[20];
		char adminPasswd[20];
		vector<Account> accounts;
};
#endif
