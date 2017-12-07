#ifndef _NUMBER_H_
#define _NUMBER_H_
#include<time.h>
#include<cstring>
#include<stdlib.h>

enum play_type {LSDS,ONE,TWO,TWO_GROUP,THREE,THREE_GROUP,FOUR,
					FIVE,FIVE_ONE,FIVE_TWO,FIVE_THREE,ANY_ONE,ANY_TWO};
class Number{
	public:
	char select_num[6];//选号
	char announce_num[6];//开奖号
	time_t select_time;//选号时间
	time_t announce_time;//开奖时间
	int num;//下注数
	int type;//玩法
	public:
	Number();
	Number(char[],char[],time_t,time_t,int,int);
	Number(const Number &);
	bool is_win();//中奖判断	
};

#endif
