#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include<time.h>
#include<fstream>
#include<sstream>
#include<vector>
#include"Number.h"
#include<iostream>
#include<iomanip>//setw()
#include<Windows.h>
using namespace std;
using std::vector;

class Account{
	public:
	time_t login_time;//����ʱ��
	unsigned int money;//��ҽ�Ǯ
	unsigned int buy_num;//����ע��
	unsigned int win_num;//�н�����
	bool login_first;//�״ε���
	vector<Number> numbers;//��ע����
	public:
	bool Login_true();//�����ж�
	void select_history();//ѡ�ż�¼
	void announce_history(int);//������¼
	void query_account();//��ѯ�˻���Ϣ
	void updata();//���ø��¿�������
	void saveData();//�浵
	void getData();//����
	
};

#endif
