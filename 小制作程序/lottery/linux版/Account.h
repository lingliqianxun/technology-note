#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include<time.h>
#include<fstream>
#include<sstream>
#include<vector>
#include"Number.h"
#include<iostream>
#include<iomanip>//setw()
using namespace std;
using std::vector;

class Account{
	public:
	time_t login_time;//登入时间
	unsigned int money;//玩家金钱
	unsigned int buy_num;//购买注数
	unsigned int win_num;//中奖次数
	bool login_first;//首次登入
	vector<Number> numbers;//下注号组
	public:
	bool Login_true();//登入判断
	void select_history();//选号记录
	void announce_history(int);//开奖记录
	void query_account();//查询账户信息
	void updata();//内置更新开奖数据
	void saveData();//存档
	void getData();//读档
	
};

#endif
