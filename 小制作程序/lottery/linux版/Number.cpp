#include"Number.h"

Number::Number(){
	
}
Number::Number(char s_n[],char a_n[],time_t s_t,time_t a_t,int num,int type){
	strcpy(select_num,s_n);
	strcpy(announce_num,a_n);
	select_time=s_t;
	announce_time=a_t;
	this->num=num;
	this->type=type;
}
Number::Number(const Number &number){
	strcpy(select_num,number.select_num);
	strcpy(announce_num,number.announce_num);
	select_time=number.select_time;
	announce_time=number.announce_time;
	this->num=number.num;
	this->type=number.type;
}
void sort(char *s){
	char tmp;
	for(int i=0;i<5;i++){
		for(int j=0;j<4-i;j++){
			if(s[j]>s[j+1]){
				tmp=s[j];
				s[j]=s[j+1];
				s[j+1]=tmp;
			}
		}
	}
}
bool Number::is_win(){
	play_type p=play_type(type);//play_type p=(play_type)type;
	if(p==LSDS){//大小单双玩法(0)
		int d[4]={0},u[4]={0};//十位、个位状态
		if(announce_num[3]>='0'&&announce_num[3]<='4')
			d[0]=1;
		else
			d[1]=1;
		if(announce_num[3]=='1'||announce_num[3]=='3'||announce_num[3]=='5'||announce_num[3]=='7'||announce_num[3]=='9')
			d[2]=1;
		else
			d[3]=1;
		if(announce_num[4]>='0'&&announce_num[4]<='4')
			u[0]=1;
		else
			u[1]=1;
		if(announce_num[4]=='1'||announce_num[4]=='3'||announce_num[4]=='5'||announce_num[4]=='7'||announce_num[4]=='9')
			u[2]=1;
		else
			u[3]=1;
		if(d[select_num[3]-48]&&u[select_num[4]-48])
			return true;
		else
			return false;
	}
	if(p==ONE){//一星(1)
		if(select_num[4]==announce_num[4])
			return true;
		else
			return false;
	}
	if(p==TWO){//二星(2)
		if(select_num[3]==announce_num[3]&&select_num[4]==announce_num[4])
			return true;
		else
			return false;
	}
	if(p==TWO_GROUP){//二星组选(3)
		if(select_num[3]==announce_num[3]&&select_num[4]==announce_num[4]||
			select_num[4]==announce_num[3]&&select_num[3]==announce_num[4])
			return true;
		return false;
	}
	if(p==THREE){//三星(4)
		if(select_num[2]==announce_num[2]&&select_num[3]==announce_num[3]&&select_num[4]==announce_num[4])
			return true;
		else
			return false;
	}
	if(p==THREE_GROUP){//三星组选(5)
		char s[6],a[6];
		strcpy(s,select_num);
		sort(s);
		strcpy(a,announce_num);
		sort(a);
		if(s[2]==a[2]&&s[3]==a[3]&&s[4]==a[4])
			return true;
		else
			return false;
	}
	if(p==FOUR){//四星(6)
		if(select_num[1]==announce_num[1]&&select_num[2]==announce_num[2]&&select_num[3]==announce_num[3]&&select_num[4]==announce_num[4])
			return true;
		else
			return false;
	}
	if(p==FIVE){//五星(7)
		if(!strcmp(select_num,announce_num))
			return true;
		else
			return false;
	}
	if(p==FIVE_ONE){//五星通选一等(8)
		char s[6],a[6];
		strcpy(s,select_num);
		sort(s);
		strcpy(a,announce_num);
		sort(a);
		if(!strcmp(s,a))
			return true;
		else
			return false;
	}
	if(p==FIVE_TWO){//五星通选二等(9)
		if(select_num[2]==announce_num[2]&&select_num[3]==announce_num[3]&&select_num[4]==announce_num[4]||
			select_num[0]==announce_num[0]&&select_num[1]==announce_num[1]&&select_num[2]==announce_num[2])
			return true;
		else
			return false;
	}
	if(p==FIVE_THREE){//五星通选三等(10)
		if(select_num[3]==announce_num[3]&&select_num[4]==announce_num[4]||
			select_num[0]==announce_num[0]&&select_num[1]==announce_num[1])
			return true;
		else
			return false;
	}
	if(p==ANY_ONE){//任一(11)
		for(int i=0;i<5;i++){
			if(select_num[i]=='*')
					continue;
			else if(select_num[i]==announce_num[i])
				return true;
			else
				return false;
		}
	}
	if(p==ANY_TWO){//任二(12)
		for(int i=0;i<5;i++){
			if(select_num[i]=='*')
					continue;
			else if(select_num[i]!=announce_num[i])
				return false;
		}
		return true;
	}
}
