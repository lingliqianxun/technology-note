#include<stdio.h>
#include<stdlib.h>
int maze[7][7]={{2,2,2,2,2,2,2},
				{2,0,0,0,0,0,2},
				{2,0,2,0,2,0,2},
				{2,0,0,0,0,2,2},
				{2,2,0,2,0,2,2},
				{2,0,0,0,0,0,2},
				{2,2,2,2,2,2,2}};
int startI=1,startJ=1;
int endI=5,endJ=5;
int success=0;
void visit_all(int i,int j){
	maze[i][j]=1;
	if(i==endI&&j==endJ){
		int m,n;
		printf("\n显示路径：\n");
		for(m=0;m<7;m++){
			for(n=0;n<7;n++){
				if(maze[m][n]==2)
					printf("██");
				else if(maze[m][n]==1)
					printf("◇ ");
				else
					printf("  ");
			}
			printf("\n");
		}
	}
	if(maze[i][j+1]==0)visit(i,j+1);
	if(maze[i+1][j]==0)visit(i+1,j);
	if(maze[i][j-1]==0)visit(i,j-1);
	if(maze[i-1][j]==0)visit(i-1,j);
	maze[i][j]=0;
}
int visit(int i,int j){
	maze[i][j]=1;
	if(i==endI&&j==endJ)
		success=1;
	if(success!=1&&maze[i][j+1]==0)visit(i,j+1);
	if(success!=1&&maze[i+1][j]==0)visit(i+1,j);
	if(success!=1&&maze[i][j-1]==0)visit(i,j-1);
	if(success!=1&&maze[i-1][j]==0)visit(i-1,j);
	if(success!=1)
		maze[i][j]=0;
	return success;
}
int main(){
	int i,j;
	printf("显示迷宫：\n");
	for(i=0;i<7;i++){
		for(j=0;j<7;j++)
			if(maze[i][j]==2)
				printf("██");
			else
				printf("  ");
		printf("\n");
	}
	if(visit(startI,startJ)==0)
		printf("\n没有找到出口！\n");
	else{
		printf("\n显示路径：\n");
		for(i=0;i<7;i++){
			for(j=0;j<7;j++){
				if(maze[i][j]==2)
					printf("██");
				else if(maze[i][j]==1)
					printf("◇ ");
				else
					printf("  ");
			}
			printf("\n");
		}
	}
	return 0;
}
