class Elevator{
	public:
		Elevator(){}
		Elevator(int f,int fu,int fd):F(f),FU(fu),FD(fd){}
		int getF(){return F;}
		int getFU(){return FU;}
		int getFD(){return FD;}
		void setF(int f){F=f;}
		void setFU(int fu){FU=fu;}
		void setFD(int fd){FD=fd;}
	private:
		int F,FU,FD;
};
