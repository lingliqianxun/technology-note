#ifndef _LOTTERY_H_
#define _LOTTERY_H_
#include<Windows.h>
#include"Account.h"

class Lottery{
	Account account;
	public:
	void Login_first();//�״ε������
	void Login_welcome();//��ӭ����
	void play();//��עѡ��
	void recharge();//��ֵ
	void help();//����˵��
	void quit();//�˳�
	void put(char&);//����ѡ��
};

#endif
