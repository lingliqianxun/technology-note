#ifndef _USER_H_
#define _USER_H_
#include"Account.h"
class User{
	public:
		User();
		User(Account &);
		~User();
		char *getID();
		void setAccount(Account &);
		void fetchMoney();
		void storeMoney();
		void query();
		void change_userPasswd();
	private:
		Account *account;
};
#endif
