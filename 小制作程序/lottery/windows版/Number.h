#ifndef _NUMBER_H_
#define _NUMBER_H_
#include<time.h>
#include<cstring>
#include<stdlib.h>

enum play_type {LSDS,ONE,TWO,TWO_GROUP,THREE,THREE_GROUP,FOUR,
					FIVE,FIVE_ONE,FIVE_TWO,FIVE_THREE,ANY_ONE,ANY_TWO};
class Number{
	public:
	char select_num[6];//ѡ��
	char announce_num[6];//������
	time_t select_time;//ѡ��ʱ��
	time_t announce_time;//����ʱ��
	int num;//��ע��
	int type;//�淨
	public:
	Number();
	Number(char[],char[],time_t,time_t,int,int);
	Number(const Number &);
	bool is_win();//�н��ж�	
};

#endif
