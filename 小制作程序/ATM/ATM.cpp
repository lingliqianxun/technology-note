#include"ATM.h"
ATM::ATM(){}
ATM::ATM(Admin &admin){
	this->admin=new Admin;
	*this->admin=admin;
	user=new User;
}
ATM::~ATM(){
	if(admin!=NULL){
		delete admin;
		admin=NULL;
	}
	if(user!=NULL){
		delete user;
		user=NULL;
	}
}
void ATM::mainMenu(){
	while(1){
		system("clear");
		cout<<"###############################################################################"<<endl;
		cout<<"#                            $1.管理员登入                                    #"<<endl;
		cout<<"#                                                                             #"<<endl;
		cout<<"#                            $2. 用户登入                                     #"<<endl;
		cout<<"#                                                                             #"<<endl;
		cout<<"#                            $3. 无卡存款                                     #"<<endl;
		cout<<"#                                                                             #"<<endl;
		cout<<"#                            $0. 退    出                                     #"<<endl;
		cout<<"###############################################################################"<<endl;
		char i;
		cout<<"请输入要执行的操作:";
		cin>>i;
		switch(i){
			case '1':
				adminLogin();
				//adminMenu();//用于测试
			case '2':
				userLogin();
				break;
			case '3':
				system("clear");
				admin->transfer(0);
				wait();
				break;
			case '0':
				cout<<"欢迎下次光临！"<<endl;
				exit(1);
			default:
				cout<<"输入错误，请重新输入！"<<endl;
				sleep(2);
				break;
		}
	}
}
void ATM::adminLogin(){
	system("clear");
	cout<<"###############################################################################"<<endl;
	char name[20],passwd[20];
	cout<<"请输入管理员名:";
	cin>>name;
	if(strcmp(admin->getName(),name)){
		cout<<"管理员不存在，请重新登入！"<<endl;
		wait();
		mainMenu();
	}
	cout<<"请输入密码:";
	//cin>>passwd;
	struct termios save,raw;//隐藏密码
	tcgetattr(0,&save);
	cfmakeraw(&raw);
	tcsetattr(0,0,&raw);
	char a=getchar();//获取换行流\n
	for(int i=0;passwd[i]!='\n';i++){
		passwd[i]=getchar();
		if(passwd[i]=='\r'){//回车13
			passwd[i]='\0';
			break;
		}
		cout<<'*';
	}
	tcsetattr(0,0,&save);
	cout<<endl;

	if(strcmp(admin->getPasswd(),passwd)){
		cout<<"密码错误，请重新登入！"<<endl;
		wait();
		mainMenu();
	}
	adminMenu();
}
void ATM::userLogin(){
	system("clear");
	cout<<"###############################################################################"<<endl;
	char name[20],passwd[20];
	cout<<"请输入用户名:";
	cin>>name;
	if(!admin->isName(name)){
		cout<<"用户不存在，请重新登入！"<<endl;
		wait();
		mainMenu();
	}
	cout<<"请输入密码:";
	//cin>>passwd;
	struct termios save,raw;//隐藏密码
	tcgetattr(0,&save);
	cfmakeraw(&raw);
	tcsetattr(0,0,&raw);
	char a=getchar();//获取换行流\n
	for(int i=0;passwd[i]!='\n';i++){
		passwd[i]=getchar();
		if(passwd[i]=='\r'){//回车13
			passwd[i]='\0';
			break;
		}
		cout<<'*';
	}
	tcsetattr(0,0,&save);
	cout<<endl;

	if(!admin->check_account(name,passwd,*user)){
		cout<<"密码错误，请重新登入！"<<endl;
		wait();
		mainMenu();
	}
	userMenu();
}
void ATM::adminMenu(){
	while(1){
		system("clear");
		cout<<"###############################################################################"<<endl;
		cout<<"#                            $1.查 询 所 有 用 户                             #"<<endl;
		cout<<"#                                                                             #"<<endl;
		cout<<"#                            $2.  查  询  用  户                              #"<<endl;
		cout<<"#                                                                             #"<<endl;
		cout<<"#                            $3.  添  加  用  户                              #"<<endl;
		cout<<"#                                                                             #"<<endl;
		cout<<"#                            $4.  删  除  用  户                              #"<<endl;
		cout<<"#                                                                             #"<<endl;
		cout<<"#                            $5.  修  改  用  户                              #"<<endl;
		cout<<"#                                                                             #"<<endl;
		cout<<"#                            $0.    返    回                                  #"<<endl;
		cout<<"###############################################################################"<<endl;
		char i;
		cout<<"请输入要执行的操作:";
		cin>>i;
		switch(i){
			case '1':
				system("clear");
				admin->query_all();
				wait();
				break;
			case '2':
				system("clear");
				admin->query_one();
				wait();
				break;
			case '3':
				system("clear");
				admin->add_account();
				wait();
				break;
			case '4':
				system("clear");
				admin->remove_account();
				wait();
				break;
			case '5':
				system("clear");
				admin->change_account();
				wait();
				break;
			case '0':
				mainMenu();
			default:
				cout<<"输入错误，请重新输入！"<<endl;
				sleep(2);
				break;
		}
	}
}
void ATM::userMenu(){
	while(1){
		system("clear");
		cout<<"###############################################################################"<<endl;
		cout<<"#                            $1.查询账户                                      #"<<endl;
		cout<<"#                                                                             #"<<endl;
		cout<<"#                            $2. 存  款                                       #"<<endl;
		cout<<"#                                                                             #"<<endl;
		cout<<"#                            $3. 取  款                                       #"<<endl;
		cout<<"#                                                                             #"<<endl;
		cout<<"#                            $4. 转  账                                       #"<<endl;
		cout<<"#                                                                             #"<<endl;
		cout<<"#                            $5.修改密码                                      #"<<endl;
		cout<<"#                                                                             #"<<endl;
		cout<<"#                            $0. 返  回                                       #"<<endl;
		cout<<"###############################################################################"<<endl;
		char i;
		cout<<"请输入要执行的操作:";
		cin>>i;
		switch(i){
			case '1':
				system("clear");
				user->query();
				admin->saveData();
				wait();
				break;
			case '2':
				system("clear");
				user->storeMoney();
				admin->saveData();
				wait();
				break;
			case '3':
				system("clear");
				user->fetchMoney();
				admin->saveData();
				wait();
				break;
			case '4':
				system("clear");
				admin->transfer(1,user->getID());
				wait();
				break;
			case '5':
				system("clear");
				user->change_userPasswd();
				admin->saveData();
				wait();
				break;
			case '0':
				mainMenu();
			default:
				cout<<"输入错误，请重新输入！"<<endl;
				sleep(2);
				break;
		}
	}
}
void ATM::wait(){
	cout<<"按任意键返回...";
	char ch;
	struct termios save,raw;
	tcgetattr(0,&save);
	cfmakeraw(&raw);
	tcsetattr(0,0,&raw);
	while(1){
		ch=getchar();
		if(ch!='\n')//ascii中\n为10
			break;
	}
	tcsetattr(0,0,&save);
} 
