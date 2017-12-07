#ifndef _LOTTERY_H_
#define _LOTTERY_H_
#include<Windows.h>
#include"Account.h"

class Lottery{
	Account account;
	public:
	void Login_first();//首次登入界面
	void Login_welcome();//欢迎界面
	void play();//下注选号
	void recharge();//充值
	void help();//帮助说明
	void quit();//退出
	void put(char&);//输入选号
};

#endif
