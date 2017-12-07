/*
电梯系统(服务器联机)
2014年08月27日
By绫里千寻
配置文件(elevator.txt):
当前电梯所处楼层位置F(B1~12)
当前电梯人数num(最多10人)
电梯运行方向d:上(1),下(0)
电梯状态s:关(1),开(0),运行(2),停止(3)
B2，B2U，B2D 2
B1，B1U，B1D 3
F1，F1U，F1D 4
F2，F2U，F2D 5
F3，F3U，F3D 6
F4，F4U，F4D 7
F5，F5U，F5D 8
F6，F6U，F6D 9
F7，F7U，F7D 10
F8，F8U，F8D 11
F9，F9U，F9D 12
F10，F10U，F10D 13
F11，F11U，F11D 14
F12，F12U，F12D 15

目前Bug:未扫描用户楼层上或下是否有按钮
*/
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<sys/time.h>
#include<signal.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
#include"Floor.cpp"
int main(){
	printf("\033[2J");
	printf("\033[10;1H说明:\n");
	printf("\033[11;1H电梯外部:i(进入电梯)、d(下楼按钮)、u(上楼按钮)、q(退出)\n");
	printf("\033[12;1H电梯内部:o(出电梯)、p(开电梯门)\n");
	printf("\033[13;1H电梯状态:\033[47m  \033[0m(关门) \033[47m \033[0m \033[47m \033[0m(开门)\n");
	Floor f;
	f.out_wait();
	return 0;
}
