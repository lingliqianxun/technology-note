bool check_num(char *num){
	if(strlen(num)!=16){
		cout<<"卡号非16位"<<endl;
		return false;
	}
	for(int i=0;i<16;i++){
		if(num[i]<48||num[i]>57){
			cout<<"卡号含有非数字字符！"<<endl;
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
		cout<<"卡密错误！"<<endl;
		return false;
	}
	return true;
}
