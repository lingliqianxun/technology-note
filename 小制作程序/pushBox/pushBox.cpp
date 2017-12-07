void print(){//打印
	int h,w;
	for(h=1;h<22;h++){
		for(w=1;w<=66;w++){
			switch(s[h][w]){
				case 0:
					printf("\33[%d;%dH\33[40m  \33[0m",h,w);
					break;
				case 1:
					printf("\33[%d;%dH\33[41m[]\33[0m",h,w);
					break;
				case 2:
					printf("\33[%d;%dH\33[42m[]\33[0m",h,w);
					break;
				case 3:
					printf("\33[%d;%dH\33[43m  \33[0m",h,w);
					break;
				case 4:
				case 7:
					printf("\33[%d;%dH\33[47m  \33[0m",h,w);
					break;
				case 8:
					printf("\33[%d;%dH  ",h,w);
					break;
			}
			w++;
		}
	}
	printf("\33[22;1H当前关卡:%d     【Q】退出     【R】重新本关卡",num);
}
void getData(){//获取地图
	x=33;
	y=10;
	char filename[16];
	sprintf(filename,"map/map%d.dat",num);
	ifstream in(filename);
	//出错判断
	if(in==NULL){
		printf("\33[10;25H\033[31m所有关卡已经通关！\33[0m\n");
		flag=0;
		sleep(3);
		return;
	}
	string line;
	int h=0,w;
	while(getline(in,line)){
		w=0;
		while(*(line.data()+w)){
			s[h][w]=*(line.data()+w)-48;
			w++;
		}
		h++;
	}
	in.close();
	print();
}
void init(){//初始化
	printf("\33[2J");//清屏
	int h,w;
	for(h=1;h<22;h++){
		for(w=1;w<=66;w++){
			printf("\33[%d;%dH\33[47m  \33[0m",h,w);//设置背景为白色
			w++;
		}
	}
	getData();
}
void win(){//判断是否过关
	int h,w;
	for(h=1;h<22;h++){
		for(w=1;w<=66;w++){
			if(s[h][w]==1){
				return;
			}
			w++;
		}
	}
	num++;
	printf("\33[22;1H已完成本关，即将进入下一关！\33[K\n");
	sleep(1);
	getData();
}
void up(){
	//墙
	if(s[y-1][x]==0)
		return;
	//空地
	if(s[y-1][x]==8){
		s[y-1][x]=7;
		if(s[y][x]==7)//人物
			s[y][x]=8;
		if(s[y][x]==4)//人物+箱子地
			s[y][x]=3;
	}
	//箱子地
	else if(s[y-1][x]==3){
		s[y-1][x]=4;
		if(s[y][x]==7)//人物
			s[y][x]=8;
		if(s[y][x]==4)//人物+箱子地
			s[y][x]=3;
	}

	//箱子/箱子+箱子地
	else if(s[y-1][x]==1||s[y-1][x]==2){
		//墙/箱子/箱子+箱子地
		if(s[y-2][x]==0||s[y-2][x]==1||s[y-2][x]==2)
			return;
		//空地
		if(s[y-2][x]==8){
			s[y-2][x]=1;
			if(s[y-1][x]==1)//箱子
				s[y-1][x]=7;
			if(s[y-1][x]==2)//箱子+箱子地
				s[y-1][x]=4;
			if(s[y][x]==7)//人物
				s[y][x]=8;
			if(s[y][x]==4)//人物+箱子地
				s[y][x]=3;
		}
		//箱子地
		else if(s[y-2][x]==3){
			s[y-2][x]=2;
			if(s[y-1][x]==1)//箱子
				s[y-1][x]=7;
			if(s[y-1][x]==2)//箱子+箱子地
				s[y-1][x]=4;
			if(s[y][x]==7)//人物
				s[y][x]=8;
			if(s[y][x]==4)//人物+箱子地
				s[y][x]=3;
		}
	}
	y-=1;
	print();
	win();
}
void down(){
	//墙
	if(s[y+1][x]==0)
		return;
	//空地
	if(s[y+1][x]==8){
		s[y+1][x]=7;
		if(s[y][x]==7)//人物
			s[y][x]=8;
		if(s[y][x]==4)//人物+箱子地
			s[y][x]=3;
	}
	//箱子地
	else if(s[y+1][x]==3){
		s[y+1][x]=4;
		if(s[y][x]==7)//人物
			s[y][x]=8;
		if(s[y][x]==4)//人物+箱子地
			s[y][x]=3;
	}

	//箱子/箱子+箱子地
	else if(s[y+1][x]==1||s[y+1][x]==2){
		//墙/箱子/箱子+箱子地
		if(s[y+2][x]==0||s[y+2][x]==1||s[y+2][x]==2)
			return;
		//空地
		if(s[y+2][x]==8){
			s[y+2][x]=1;
			if(s[y+1][x]==1)//箱子
				s[y+1][x]=7;
			if(s[y+1][x]==2)//箱子+箱子地
				s[y+1][x]=4;
			if(s[y][x]==7)//人物
				s[y][x]=8;
			if(s[y][x]==4)//人物+箱子地
				s[y][x]=3;
		}
		//箱子地
		else if(s[y+2][x]==3){
			s[y+2][x]=2;
			if(s[y+1][x]==1)//箱子
				s[y+1][x]=7;
			if(s[y+1][x]==2)//箱子+箱子地
				s[y+1][x]=4;
			if(s[y][x]==7)//人物
				s[y][x]=8;
			if(s[y][x]==4)//人物+箱子地
				s[y][x]=3;
		}
	}
	y+=1;
	print();
	win();
}
void right(){
	//墙
	if(s[y][x+2]==0)
		return;
	//空地
	if(s[y][x+2]==8){
		s[y][x+2]=7;
		if(s[y][x]==7)//人物
			s[y][x]=8;
		if(s[y][x]==4)//人物+箱子地
			s[y][x]=3;
	}
	//箱子地
	else if(s[y][x+2]==3){
		s[y][x+2]=4;
		if(s[y][x]==7)//人物
			s[y][x]=8;
		if(s[y][x]==4)//人物+箱子地
			s[y][x]=3;
	}

	//箱子/箱子+箱子地
	else if(s[y][x+2]==1||s[y][x+2]==2){
		//墙/箱子/箱子+箱子地
		if(s[y][x+4]==0||s[y][x+4]==1||s[y][x+4]==2)
			return;
		//空地
		if(s[y][x+4]==8){
			s[y][x+4]=1;
			if(s[y][x+2]==1)//箱子
				s[y][x+2]=7;
			if(s[y][x+2]==2)//箱子+箱子地
				s[y][x+2]=4;
			if(s[y][x]==7)//人物
				s[y][x]=8;
			if(s[y][x]==4)//人物+箱子地
				s[y][x]=3;
		}
		//箱子地
		else if(s[y][x+4]==3){
			s[y][x+4]=2;
			if(s[y][x+2]==1)//箱子
				s[y][x+2]=7;
			if(s[y][x+2]==2)//箱子+箱子地
				s[y][x+2]=4;
			if(s[y][x]==7)//人物
				s[y][x]=8;
			if(s[y][x]==4)//人物+箱子地
				s[y][x]=3;
		}
	}
	x+=2;
	print();
	win();
}
void left(){
	//墙
	if(s[y][x-2]==0)
		return;
	//空地
	if(s[y][x-2]==8){
		s[y][x-2]=7;
		if(s[y][x]==7)//人物
			s[y][x]=8;
		if(s[y][x]==4)//人物+箱子地
			s[y][x]=3;
	}
	//箱子地
	else if(s[y][x-2]==3){
		s[y][x-2]=4;
		if(s[y][x]==7)//人物
			s[y][x]=8;
		if(s[y][x]==4)//人物+箱子地
			s[y][x]=3;
	}

	//箱子/箱子+箱子地
	else if(s[y][x-2]==1||s[y][x-2]==2){
		//墙/箱子/箱子+箱子地
		if(s[y][x-4]==0||s[y][x-4]==1||s[y][x-4]==2)
			return;
		//空地
		if(s[y][x-4]==8){
			s[y][x-4]=1;
			if(s[y][x-2]==1)//箱子
				s[y][x-2]=7;
			if(s[y][x-2]==2)//箱子+箱子地
				s[y][x-2]=4;
			if(s[y][x]==7)//人物
				s[y][x]=8;
			if(s[y][x]==4)//人物+箱子地
				s[y][x]=3;
		}
		//箱子地
		else if(s[y][x-4]==3){
			s[y][x-4]=2;
			if(s[y][x-2]==1)//箱子
				s[y][x-2]=7;
			if(s[y][x-2]==2)//箱子+箱子地
				s[y][x-2]=4;
			if(s[y][x]==7)//人物
				s[y][x]=8;
			if(s[y][x]==4)//人物+箱子地
				s[y][x]=3;
		}
	}
	x-=2;
	print();
	win();
}
