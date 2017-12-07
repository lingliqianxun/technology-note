#include"Lottery.h"
bool check_num(char *num){
	if(strlen(num)!=16){
		cout<<"���ŷ�16λ"<<endl;
		return false;
	}
	for(int i=0;i<16;i++){
		if(num[i]<48||num[i]>57){
			cout<<"���ź��з������ַ���"<<endl;
			return false;
		}
	}
	return true;
}
bool check_passwd(char *num,char *passwd){
	cout<<"num"<<num<<endl;
	cout<<"pas"<<passwd<<endl;
	for(int i=0;i<16;i++){
		num[i]+=3;
		if(num[i]>57)
			num[i]-=10;
	}
	cout<<"pas"<<passwd<<endl;
	if(strcmp(num,passwd)){
		cout<<"���ܴ���"<<endl;
		return false;
	}
	return true;
}
void Lottery::Login_first(){//�״ε������
	account.getData();
	if(!account.Login_true()){
		cout<<"ʱ�����,��У��ʱ�䣡"<<endl;
		return;
	}
	cout<<"��ӭ����**ʱʱ����͸��Ʊ**��������"<<endl<<endl;
	if(account.login_first){
		struct tm *t=localtime(&account.login_time);
		cout<<"�ϴε���ʱ��:"<<t->tm_year+1990<<'-'<<t->tm_mon+1<<'-'<<t->tm_mday<<' '<<setw(2)<<t->tm_hour<<':'<<t->tm_min<<endl;
	}else{
		cout<<"�����߿ɻ��100������Ϊ"<<endl<<endl;
		account.query_account();
		account.login_first=true;
	}
	account.login_time=time(0);
	account.saveData();
	Sleep(3000);//��ֲ
	Login_welcome();
}
void Lottery::Login_welcome(){
	char c[2];
	while(1){
		system("CLS");//��ֲ
		cout<<"##################################################################"<<endl;	
		cout<<"#                        1. ��עѡ��                             #"<<endl;	
		cout<<"#                        2. ѡ�ż�¼                             #"<<endl;	
		cout<<"#                        3. ���ڿ�����¼                         #"<<endl;	
		cout<<"#                        4. ���ڿ�����¼                         #"<<endl;	
		cout<<"#                        5. ��ѯ�˻���Ϣ                         #"<<endl;	
		cout<<"#                        6. ����˵��                             #"<<endl;	
		cout<<"#                        7. ��ֵ                                 #"<<endl;	
		cout<<"#                        0. �˳�                                 #"<<endl;	
		cout<<"##################################################################"<<endl;	
		cout<<"������ѡ��:";
		cin>>c;
		account.updata();
		if(!strcmp(c,"1")){
			system("CLS");//��ֲ
			play();
		}else if(!strcmp(c,"2")){
			system("CLS");//��ֲ
			account.select_history();
		}else if(!strcmp(c,"3")){
			system("CLS");//��ֲ
			account.announce_history(10);
		}else if(!strcmp(c,"4")){
			system("CLS");//��ֲ
			account.announce_history(10000);
		}else if(!strcmp(c,"5")){
			system("CLS");//��ֲ
			account.query_account();
		}else if(!strcmp(c,"6")){
			system("CLS");//��ֲ
			help();
		}else if(!strcmp(c,"7")){
			system("CLS");//��ֲ
			recharge();
		}else if(!strcmp(c,"0")){
			system("CLS");//��ֲ
			quit();
			break;
		}else{
			cout<<"����������������룡"<<endl;
			Sleep(1000);//��ֲ
			continue;
		}
		cin.clear();//�������
		cin.ignore(1024,'\n');//�������
		cout<<"����س�������"<<endl;
		c[0]=getchar();
	}
}
void Lottery::quit(){//�˳�
	account.saveData();
	cout<<"##################################################################"<<endl;	
	cout<<"��ӭ�´ι��٣�\n";
	Sleep(3000);//��ֲ
}
void Lottery::recharge(){//��ֵ
	cout<<"##################################################################"<<endl;	
	char num[17],passwd[17];
	cout<<"�������ֵ����:";
	cin>>num;
	if(!check_num(num))
		return;
	cout<<"�������ֵ����:";
	cin>>passwd;
	if(!check_passwd(num,passwd))
		return;
	account.money+=100;
	account.saveData();
	cout<<"��ֵ100�ɹ���"<<endl;
}
void Lottery::help(){//����˵��
	cout<<"##################################################################"<<endl;	
	cout<<"                            ����˵��"<<endl;
	ifstream in("help.dat");
	string line;
	while(getline(in,line)){
		cout<<line<<endl;
	}
	in.close();
}
void Lottery::put(char &s){//����ѡ��
	char c[2];
	cin>>c;
	if(!strcmp(c,"0")||!strcmp(c,"1")||!strcmp(c,"2")||!strcmp(c,"3")||!strcmp(c,"4")||!strcmp(c,"5")||!strcmp(c,"6")||!strcmp(c,"7")||!strcmp(c,"8")||!strcmp(c,"9"))
		s=c[0];
	else{
		cout<<"�������"<<endl;
		cout<<"���س�������"<<endl;
		c[0]=getchar();
		c[1]=getchar();
		Login_welcome();
	}
}
void Lottery::play(){//��עѡ��
	time_t now=time(0);
	struct tm *t=localtime(&now);
	if(t->tm_min%10==9){
		cout<<"���뿪������һ���ӣ����޷���ע�������ĵȴ���һ�ֹ���..."<<endl;
		//		return;
	}
	int type;
	char c[3],s[6]="*****",a[6]="*****";
	cout<<"##################################################################"<<endl;	
	cout<<"#                   2.һ��    4.������ѡ    8.����               #"<<endl;	
	cout<<"#     1.��С��˫    3.����    6.������ѡ    9.����ͨѡһ��       #"<<endl;	
	cout<<"#     0.����        5.����    12.��һ       10.����ͨѡ����      #"<<endl;	
	cout<<"#                   7.����    13.�ζ�       11.����ͨѡ����      #"<<endl;	
	cout<<"##################################################################"<<endl;	
	cout<<"������ѡ��:";
	cin>>c;
	if(!strcmp(c,"1")){
		system("CLS");//��ֲ
		type=0;
		cout<<"##################################################################"<<endl;	
		cout<<"#       1.С       2.��       3.��       4.˫       0.����       #"<<endl;	
		cout<<"##################################################################"<<endl;	
		cout<<"������ʮλ״̬:";
		cin>>c;
		if(!strcmp(c,"1")||!strcmp(c,"2")||!strcmp(c,"3")||!strcmp(c,"4"))
			s[3]=c[0]-1;
		else if(!strcmp(c,"0"))
			Login_welcome();
		else{
			cout<<"�������"<<endl;
			return;
		}
		system("CLS");//��ֲ
		cout<<"##################################################################"<<endl;	
		cout<<"#       1.С       2.��       3.��       4.˫       0.����       #"<<endl;	
		cout<<"##################################################################"<<endl;	
		cout<<"������ʮλ״̬:";
		cin>>c;
		if(!strcmp(c,"1")||!strcmp(c,"2")||!strcmp(c,"3")||!strcmp(c,"4"))
			s[4]=c[0]-1;
		else if(!strcmp(c,"0"))
			Login_welcome();
		else{
			cout<<"�������"<<endl;
			return;
		}
	}else if(!strcmp(c,"2")||!strcmp(c,"3")){
		if(!strcmp(c,"2"))
			type=1;	
		else
			type=2;
		system("CLS");//��ֲ
		cout<<"##################################################################"<<endl;	
		cout<<"�������λ��:";
		put(s[4]);
	}else if(!strcmp(c,"4")){
		type=3;	
		system("CLS");//��ֲ
		cout<<"##################################################################"<<endl;	
		cout<<"������ʮλ��:";
		put(s[3]);
		cout<<"##################################################################"<<endl;	
		cout<<"�������λ��:";
		put(s[4]);
	}else if(!strcmp(c,"5")||!strcmp(c,"6")){
		if(!strcmp(c,"5"))
			type=4;	
		else
			type=5;
		system("CLS");//��ֲ
		cout<<"##################################################################"<<endl;	
		cout<<"�������λ��:";
		put(s[2]);
		cout<<"##################################################################"<<endl;	
		cout<<"������ʮλ��:";
		put(s[3]);
		cout<<"##################################################################"<<endl;	
		cout<<"�������λ��:";
		put(s[4]);
	}else if(!strcmp(c,"7")){
		type=5;	
		system("CLS");//��ֲ
		cout<<"##################################################################"<<endl;	
		cout<<"������ǧλ��:";
		put(s[1]);
		cout<<"##################################################################"<<endl;	
		cout<<"�������λ��:";
		put(s[2]);
		cout<<"##################################################################"<<endl;	
		cout<<"������ʮλ��:";
		put(s[3]);
		cout<<"##################################################################"<<endl;	
		cout<<"�������λ��:";
		put(s[4]);
	}else if(!strcmp(c,"8")||!strcmp(c,"9")||!strcmp(c,"10")||!strcmp(c,"11")){
		if(!strcmp(c,"8"))
			type=7;
		if(!strcmp(c,"9"))
			type=8;
		if(!strcmp(c,"10"))
			type=9;
		if(!strcmp(c,"11"))
			type=10;
		system("CLS");//��ֲ
		cout<<"##################################################################"<<endl;	
		cout<<"��������λ��:";
		put(s[0]);
		cout<<"##################################################################"<<endl;	
		cout<<"������ǧλ��:";
		put(s[1]);
		cout<<"##################################################################"<<endl;	
		cout<<"�������λ��:";
		put(s[2]);
		cout<<"##################################################################"<<endl;	
		cout<<"������ʮλ��:";
		put(s[3]);
		cout<<"##################################################################"<<endl;	
		cout<<"�������λ��:";
		put(s[4]);
	}else if(!strcmp(c,"12")){
		type=11;	
		system("CLS");//��ֲ
		cout<<"##################################################################"<<endl;	
		cout<<"#       1.��       2.ǧ       3.��       4.ʮ       5.��        #"<<endl;	
		cout<<"##################################################################"<<endl;	
		cout<<"��ѡ��Ͷעλ��:";
		char c[2];
		cin>>c;
		if(!strcmp(c,"1")||!strcmp(c,"2")||!strcmp(c,"3")||!strcmp(c,"4")||!strcmp(c,"5")){
			system("CLS");//��ֲ
			cout<<"##################################################################"<<endl;	
			cout<<"�������λ����:";
			put(s[c[0]-49]);
		}else{
			cout<<"�������"<<endl;
			return;
		}
	}else if(!strcmp(c,"13")){
		type=12;	
		system("CLS");//��ֲ
		cout<<"##################################################################"<<endl;	
		cout<<"#       1.��       2.ǧ       3.��       4.ʮ       5.��	        #"<<endl;	
		cout<<"##################################################################"<<endl;	
		cout<<"��ѡ���һλͶעλ��:";
		char c[2],ch[2];
		cin>>c;
		if(!strcmp(c,"1")||!strcmp(c,"2")||!strcmp(c,"3")||!strcmp(c,"4")||!strcmp(c,"5")){
			system("CLS");//��ֲ
			cout<<"##################################################################"<<endl;	
			cout<<"�������λ����:";
			put(s[c[0]-49]);
		}else{
			cout<<"�������"<<endl;
			return;
		}
		system("CLS");//��ֲ
		cout<<"##################################################################"<<endl;	
		cout<<"#         ";	
		if(strcmp(c,"1"))
			cout<<"1.��         ";
		if(strcmp(c,"2"))
			cout<<"2.ǧ         ";
		if(strcmp(c,"3"))
			cout<<"3.��         ";
		if(strcmp(c,"4"))
			cout<<"4.ʮ         ";
		if(strcmp(c,"5"))
			cout<<"5.��         ";
		cout<<"   #"<<endl;
		cout<<"##################################################################"<<endl;	
		cout<<"��ѡ��ڶ�λͶעλ��:";
		cin>>ch;
		if(!strcmp(ch,"1")||!strcmp(ch,"2")||!strcmp(ch,"3")||!strcmp(ch,"4")||!strcmp(ch,"5")){
			if(!strcmp(c,ch)){
				cout<<"�������"<<endl;
				return;
			}
			system("CLS");//��ֲ
			cout<<"##################################################################"<<endl;	
			cout<<"�������λ����:";
			put(s[ch[0]-49]);
		}else{
			cout<<"�������"<<endl;
			return;
		}
	}else if(!strcmp(c,"0")){
		Login_welcome();
	}else{
		cout<<"�������"<<endl;
		return;
	}
	system("CLS");//��ֲ
	cout<<"##################################################################"<<endl;	
	cout<<"ѡ����ɣ�"<<endl;
	if(type==0){
		cout<<s[0]<<s[1]<<s[2];
		if(s[3]=='0')
			cout<<"С";
		if(s[3]=='1')
			cout<<"��";
		if(s[3]=='2')
			cout<<"��";
		if(s[3]=='3')
			cout<<"˫";
		if(s[4]=='0')
			cout<<"С";
		if(s[4]=='1')
			cout<<"��";
		if(s[4]=='2')
			cout<<"��";
		if(s[4]=='3')
			cout<<"˫";
		cout<<endl;
	}else
		cout<<s<<endl;
	cout<<"��������ע��:";
	int num;
	cin>>num;
	if(num==0){
		cout<<"�������"<<endl;
		return;
	}
	if(num*2>account.money){
		cout<<"���㣬���ֵ��"<<endl;
		return;
	}
	now=time(0);
	t=localtime(&now);
	if(t->tm_min%10==9){
		cout<<"���뿪������һ���ӣ����޷���ע�������ĵȴ���һ�ֹ���..."<<endl;
		//		return;
	}
	account.money-=num*2;
	account.buy_num+=num;
	Number number(s,a,now,now,num,type);
	account.numbers.insert(account.numbers.begin(),1,number);
	account.saveData();
	system("CLS");//��ֲ
	cout<<"##################################################################"<<endl;	
	cout<<"��ע��ɣ�"<<endl;
	cout<<"���뿪��ʱ�仹��"<<10-t->tm_min%10<<"����"<<endl;
}
