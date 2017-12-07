#ifndef _SNAKE_H
#define _SNAKE_H
#include <iostream>
#include <list>
#include <csetjmp>
#include <sys/time.h>
using namespace std;
#define p_x 10 //界面开始位置 
#define p_y 5
#define X 50  //游戏界面大小
#define Y 20
#define LEVEL_SCORE 800 //每次升级所需要的分数
typedef struct Node{ 
    int y;
    int x;
    Node(int y,int x):y(y),x(x){}
}Snake;
list<Snake> L;  //保存每个射节点的坐标
jmp_buf env;
static int x,y;  //游戏中目标出现的坐标
static int matirx[Y][X]={1,1,1,1};
static int level =1;  //游戏等级
static int score =0;  //游戏分数
typedef struct itimerval LEVEL;
//每个不同等级间歇计时器的值，用于改变游戏速度
static LEVEL level_01 = { {0, 400000},  {0, 400000} };
static LEVEL level_02 = { {0, 300000},  {0, 300000} };
static LEVEL level_03 = { {0, 250000},  {0, 250000} };
static LEVEL level_04 = { {0, 210000},  {0, 210000} };
static LEVEL level_05 = { {0, 180000},  {0, 180000} };
static LEVEL level_06 = { {0, 150000},  {0, 150000} };
static LEVEL level_07 = { {0, 120000},  {0, 120000} };
static LEVEL level_08 = { {0, 100000},  {0, 100000} };
static LEVEL level_09 = { {0,  80000},  {0,  80000} };
void print_start_interface();
void print_snake();
void print_goal();
void print_score();
void move_up(int);
void move_down(int);
void move_left(int);
void move_right(int);
void Init_matirx();
void snake_control();
bool eat_goal();
void print_level();
void change_level();
void game_over();
#endif
