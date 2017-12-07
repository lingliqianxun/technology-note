#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include "snake.h"
//打印游戏界面
void print_start_interface(){
    int x,y;
    printf("\33[2J");//清屏
    printf("\33[%d;%dH\33[32m分数:\33[0m", p_y -2, p_x+20);
    printf("\33[%d;%dH\33[32m等级:\33[0m", p_y -3, p_x+20);
    for(x=p_x,y=p_y;x<=62;x++)
        printf("\33[%d;%dH\33[44m==\33[0m",y,x);
    for(x=p_x,y=p_y+1;y<=25;y++)
        printf("\33[%d;%dH\33[44m||\33[0m",y,x);
    for(x=p_x,y=p_y+21;x<=62;x++)
        printf("\33[%d;%dH\33[44m==\33[0m",y,x);
    for(x=p_x+52,y=p_y+1;y<=25;y++)
        printf("\33[%d;%dH\33[44m||\33[0m",y,x);
}
//打印蛇身
void print_snake(){
    int x1=p_x+2,y1=p_y+1;
    for(int i=0;i<Y;i++){
        for(int j=0;j<X;j++){
            if(matirx[i][j]==1){
                printf("\33[%d;%dH\33[41m[]\33[0m",y1,x1+j);
//在19，20运行时进入这个条件时，printf未被实行，求问大神是为什么？其他行都正确执行，我把蛇身打印到文件中，也是显示正确的，但输出到屏幕就有问题。
                j++;
            }
            else if(i==y&&j==x)
                j++;
            else
                printf("\33[%d;%dH \33[0m",y1,x1+j);
        }
        y1++;
    }
}
//将蛇身放如数组中
void Init_matirx(){
    memset(matirx,0,sizeof(matirx));
    list<Snake>::iterator it=L.begin();
    while(it!=L.end()){
        matirx[it->y][it->x]=1;
        matirx[it->y][it->x+1]=1;
        it++;
    }
}
//打印目标
void print_goal(){
    printf("\33[%d;%dH\33[43m[]\33[0m",y+p_y+1,x+p_x+2);
}
//是否吃掉目标
bool eat_goal(){
    int x1=L.front().x;
    int y1=L.front().y;
    if(x1==x&&y1==y){
        srand(time(0));
        do{
            x=(rand()%25)*2;
            y=rand()%20;
        }while(matirx[y][x]==1);
        score+=100;//分数+100
        if(score%LEVEL_SCORE==0){
            level+=1;
            if(level>=9)
                level=9;
            change_level();
        }
        print_score();
        print_level();
        return true;
    }
    else
        return false;
}
void move_down(int n=0){
    int x1=L.front().x;
    int y1=L.front().y;
    int x2=L.back().x;
    int y2=L.back().y;
    L.pop_front();
    int x3=L.front().x;
    int y3=L.front().y;
    L.push_front(Snake(y1,x1));
    if(y1<y3&&x1==x3)
        return;
    L.pop_back();
    L.push_front(Snake(y1+1,x1));
    Init_matirx();
    game_over();
    if(eat_goal()){
        L.push_back(Snake(y2,x2));
        matirx[y2][x2]=1;
    }
    print_snake();
    print_goal();
    signal(SIGALRM,move_down);
}
void move_up(int n=0){
    int x1=L.front().x;
    int y1=L.front().y;
    int x2=L.back().x;
    int y2=L.back().y;
    L.pop_front();
    int x3=L.front().x;
    int y3=L.front().y;
    L.push_front(Snake(y1,x1));
    if(y1>y3&&x1==x3)
        return;
    L.pop_back();
    L.push_front(Snake(y1-1,x1));
    Init_matirx();
    game_over();
    if(eat_goal()){
        L.push_back(Snake(y2,x2));
        matirx[y2][x2]=1;
    }
    print_snake();
    print_goal();
    signal(SIGALRM,move_up);
}
void move_right(int n=0){
    int x1=L.front().x;
    int y1=L.front().y;
    int x2=L.back().x;
    int y2=L.back().y;
    L.pop_front();
    int x3=L.front().x;
    int y3=L.front().y;
    L.push_front(Snake(y1,x1));
    if(y1==y3&&x1<x3)
        return;
    L.pop_back();
    L.push_front(Snake(y1,x1+2));
    Init_matirx();
    game_over();
    if(eat_goal()){
        L.push_back(Snake(y2,x2));
        matirx[y2][x2]=1;
    }
    print_snake();
    print_goal();
    signal(SIGALRM,move_right);
}
void move_left(int n=0){
    int x1=L.front().x;
    int y1=L.front().y;
    int x2=L.back().x;
    int y2=L.back().y;
    L.pop_front();
    int x3=L.front().x;
    int y3=L.front().y;
    L.push_front(Snake(y1,x1));
    if(y1==y3&&x1>x3)
        return;
    L.pop_back();
    L.push_front(Snake(y1,x1-2));
    Init_matirx();
    game_over();
    if(eat_goal()){
        L.push_back(Snake(y2,x2));
        matirx[y2][x2]=1;
    }
    print_snake();
    print_goal();
    signal(SIGALRM,move_left);
}
//根据输入信号控制射身运动方向
void snake_control(){
    int ch, flag = 1;
    struct termios save, raw;
    tcgetattr(0, &save);//取终端属性
    cfmakeraw(&raw);
    //cfmakeraw将终端设置为原始模式，该模式下所有输入数据以字节为单位被处理
    //在原始模式下，终端是不可回显的，而已所有特定的终端输入/输出
    //模式不可以用
    tcsetattr(0, 0, &raw);//设置终端为原始模式
    if(setjmp(env)==0){
        while(flag){
            ch=getchar();
            if(ch=='\33'){
                ch=getchar();
                if(ch=='['){
                    ch=getchar();
                    switch(ch){
                        case 'A':
                            move_up();break;
                        case 'B':
                            move_down();break;
                        case 'C':
                            move_right();break;
                        case 'D':
                            move_left();break;
                    }
                }
            }
            if(ch=='q'||ch=='Q')
                flag=0;
        }
        printf("\33[%d;%dH\33[31m-----game interrupt exit!-    ----\33[0m",
                p_y + Y + 3, p_x+15);
        //显示光标
        printf("\33[%d;0H\33[?25h", p_y + Y + 4);
    }
    tcsetattr(0, 0, &save);//恢复终端原来属性
}
//不同等级的速度
void change_level(){
    switch (level) {
        case 1:
            setitimer(ITIMER_REAL, &level_01, NULL);
            break;
        case 2:
            setitimer(ITIMER_REAL, &level_02, NULL);
            break;
        case 3:
            setitimer(ITIMER_REAL, &level_03, NULL);
            break;
        case 4:
            setitimer(ITIMER_REAL, &level_04, NULL);
            break;
        case 5:
            setitimer(ITIMER_REAL, &level_05, NULL);
            break;
        case 6:
            setitimer(ITIMER_REAL, &level_06, NULL);
            break;
        case 7:
            setitimer(ITIMER_REAL, &level_07, NULL);
            break;
        case 8:
            setitimer(ITIMER_REAL, &level_08, NULL);
            break;
        case 9:
            setitimer(ITIMER_REAL, &level_09, NULL);
            break;
        default:
            break;
    }
}
//打印等级
void print_level(){
    printf("\33[%d;%dH\33[31m%d\33[0m", p_y -2, p_x +30,score);
    printf("\33[?25l");//隐藏光标
}
//打印分数
void print_score(){
    printf("\33[%d;%dH\33[31m%d\33[0m", p_y -3, p_x +30,level);
    printf("\33[?25l");
}
//判断游戏是否结束
void game_over(){
    int x1=L.front().x;
    int y1=L.front().y;
    if(y1<0||y1>=20||x1<0||x1>=50){
        printf("\n\33[31m\33[%d;%dH-------game over!--------\33[0m",p_y + Y + 3, p_x+15);
        printf("\33[0m\33[?25h\33[%d;0H", p_y + Y + 4); 
        longjmp(env,2);
    }
    else{
        list<Snake>::iterator it=L.begin();
        it++;
        while(it!=L.end()){
            if(it->x==x1&&it->y==y1){
                printf("\n\33[31m\33[%d;%dH-------game over!--------\33[0m",p_y + Y + 3, p_x+15);
                printf("\33[0m\33[?25h\33[%d;0H", p_y + Y + 4); 
                longjmp(env,2);
            }
            it++;
        }
    }
}
    int main(){
        srand(time(0));
        do{
            x=(rand()%25)*2;
            y=rand()%20;
        }while(matirx[y][x]==1);
        L.push_front(Snake(0,0));
        L.push_front(Snake(0,2));
        print_start_interface();
        print_score();
        print_level();
        print_snake();
        print_goal();
        setitimer(ITIMER_REAL, &level_01, NULL);
        signal(SIGALRM,move_right);
        snake_control();
        return 0;
    }
