#include<iostream>
using namespace std;
#include<cstring>

class String{
public:
	String(const char *str=NULL);
	String(const String &other);
	~String();
	String & operator =(const String & other);
//private:
	char *m_data;

};
String::String(const char *str){
	if(str==NULL){
		m_data=new char[1];
		m_data[0]='\0';
	}else{
		int len=strlen(str);
		m_data=new char[len+1];
		strcpy(m_data,str);
		m_data[len]='\0';
	}
}
String::String(const String & other){
	int len=strlen(other.m_data);
	cout<<"len:"<<len<<endl;
	m_data=new char[len+1];
	strcpy(m_data,other.m_data);
	m_data[len]='\0';
}
String::~String(){
	if(m_data!=NULL){
		delete [] m_data;
		m_data=NULL;
	}
}
String & String::operator =(const String & other){
	if(this==&other)
		return *this;
	delete []m_data;
	m_data=NULL;
	int len=strlen(other.m_data);
	cout<<"=len:"<<len<<endl;
	m_data=new char[len+1];
	strcpy(m_data,other.m_data);
	m_data[len]='\0';
	return *this;
}
//string
char *strcpy(char*strDest,const char*strSrc){
	assert((strDest!=NULL)&&(strSrc!=NULL));
	char *address=strDest;
	while((*strDest++=*strSrc++)!='\0');
	return address;
}
int strlen(const char*str){
	assert(str!=NULL);
	int len=0;
	while ((*str++)!='\0')
	{
		len++;
	}
	return len;
}
int main(){
	char a[3]={'1','2','\0'};
	String s1(a);
	String s2=s1;
	cout<<s2.m_data<<endl;
	s1=s1;
	return 0;
}
