#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include<cstring>
#include<iomanip>
class Account{
	public:
		Account();
		Account(char *,char *,char *);
		Account(const char *,const char *,const char *,double);
		~Account();
		void withdraw(double);
		void deposit(double);
		void setAccountID(char *);
		void setAccountName(char *);
		void setAccountPasswd(char *);
		void setBalance(double);
		char *getAccountID();
		char *getAccountName();
		char *getAccountPasswd();
		double getBalance()const;
		void display();
		friend class Admin;
	private:
		char accountID[20];
		char accountName[20];
		char accountPasswd[20];
		double balance;
};
#endif
