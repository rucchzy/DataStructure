#include "stdio.h"
#include "stdlib.h"

#define INIT_SIZE 420
#define INCREMENT 20
#define OK 1
#define ERROR 0
#define M 14
#define N 30

typedef struct {
	int x,y;
} PosType;

typedef struct{
	PosType pos;
	int link;
}QElemType;

typedef struct{
	QElemType *base;
	int rear;
	int queuesize;
}SeqQueue;

//创建空队
SeqQueue *InitQueue(){
	SeqQueue *Q;
	Q = (SeqQueue *)malloc(sizeof(QElemType));
	Q->base = (QElemType *)malloc(INIT_SIZE * sizeof(QElemType));
	if(!Q->base){
		printf("分配失败！");
	}
	Q->queuesize = INIT_SIZE;
	Q->rear = 0;
	return Q;
}

//元素e入队
void InQueue(SeqQueue *Q,QElemType e){
	if(Q->rear + 1 == Q->queuesize){
		Q->base = (QElemType *) realloc (Q->base, (Q->queuesize + INCREMENT) * sizeof(QElemType));
		if(!Q->rear){
			printf("分配失败！");
		}
	}
	Q->base[Q->rear] = e;
	Q->rear = Q->rear + 1;
}

//出队
QElemType OutQueue(SeqQueue *Q){
	if(Q->rear == 0){
		printf("对为空！");
	}
	QElemType e;
	e = Q->base[Q->rear - 1];
	Q->rear = Q->rear - 1;
	return e;
}

//根据当前位置pos和行进方向计算下一个位置坐标
PosType NextPos(PosType pos,int d){
	if(d == 0){
		pos.y = pos.y + 1;
	}
	if(d == 1){
		pos.x = pos.x + 1;
	}
	if(d == 2){
		pos.y = pos.y - 1;
	}
	if(d == 3){
		pos.x =pos.x - 1;
	}
	return pos;	
}

//搜索从起点到终点的路径
int FindPath(int maze[][N],PosType startpos,PosType endpos){
	SeqQueue *Q = InitQueue();
	QElemType e;
	QElemType E;
	int p;
	PosType nowpos;
	e.pos = startpos;
	e.link = -1;
	InQueue(Q,e);
	maze[e.pos.x][e.pos.y] = 9;//表示走过的路
	p = 0; 
	for(;;p++){
		e.link = p;
		nowpos.x = Q->base[p].pos.x;
		nowpos.y = Q->base[p].pos.y;
		if(maze[nowpos.x + 1][nowpos.y] == 0){
			e.pos.x = nowpos.x + 1;
			e.pos.y = nowpos.y;
			maze[e.pos.x][e.pos.y] = 2;//表示向下走 
			InQueue(Q,e);
			if(e.pos.x == endpos.x & e.pos.y == endpos.y){
				for(;e.link != -1;){
					if(maze[e.pos.x][e.pos.y] == 6){
						maze[e.pos.x][e.pos.y] = 66;
					}
					if(maze[e.pos.x][e.pos.y] == 2){
						maze[e.pos.x][e.pos.y] = 22;
					}
					if(maze[e.pos.x][e.pos.y] == 4){
						maze[e.pos.x][e.pos.y] = 44;
					}
					if(maze[e.pos.x][e.pos.y] == 8){
						maze[e.pos.x][e.pos.y] = 88;
					}
					e = Q->base[e.link];
				}			
				break;
			}
		}
		if(maze[nowpos.x][nowpos.y + 1] == 0){
			e.pos.x = nowpos.x;
			e.pos.y = nowpos.y + 1;
			maze[e.pos.x][e.pos.y] = 6;//表示向右走 
			InQueue(Q,e);
			if(e.pos.x == endpos.x & e.pos.y == endpos.y){
				for(;e.link != -1;){
					if(maze[e.pos.x][e.pos.y] == 6){
						maze[e.pos.x][e.pos.y] = 66;
					}
					if(maze[e.pos.x][e.pos.y] == 2){
						maze[e.pos.x][e.pos.y] = 22;
					}
					if(maze[e.pos.x][e.pos.y] == 4){
						maze[e.pos.x][e.pos.y] = 44;
					}
					if(maze[e.pos.x][e.pos.y] == 8){
						maze[e.pos.x][e.pos.y] = 88;
					}
					e = Q->base[e.link];
				}			
				break;
			}
		}
		if(maze[nowpos.x - 1][nowpos.y] == 0){
			e.pos.x = nowpos.x - 1;
			e.pos.y = nowpos.y;
			maze[e.pos.x][e.pos.y] = 8;//表示向上走 
			InQueue(Q,e);
			if(e.pos.x == endpos.x & e.pos.y == endpos.y){
				for(;e.link != -1;){
					if(maze[e.pos.x][e.pos.y] == 6){
						maze[e.pos.x][e.pos.y] = 66;
					}
					if(maze[e.pos.x][e.pos.y] == 2){
						maze[e.pos.x][e.pos.y] = 22;
					}
					if(maze[e.pos.x][e.pos.y] == 4){
						maze[e.pos.x][e.pos.y] = 44;
					}
					if(maze[e.pos.x][e.pos.y] == 8){
						maze[e.pos.x][e.pos.y] = 88;
					}
					e = Q->base[e.link];
				}			
				break;
			}
		}
		if(maze[nowpos.x][nowpos.y - 1] == 0){
			e.pos.x = nowpos.x;
			e.pos.y = nowpos.y - 1;
			maze[e.pos.x][e.pos.y] = 4;//表示向左走 
			InQueue(Q,e);
			if(e.pos.x == endpos.x & e.pos.y == endpos.y){
				for(;e.link != -1;){
					if(maze[e.pos.x][e.pos.y] == 6){
						maze[e.pos.x][e.pos.y] = 66;
					}
					if(maze[e.pos.x][e.pos.y] == 2){
						maze[e.pos.x][e.pos.y] = 22;
					}
					if(maze[e.pos.x][e.pos.y] == 4){
						maze[e.pos.x][e.pos.y] = 44;
					}
					if(maze[e.pos.x][e.pos.y] == 8){
						maze[e.pos.x][e.pos.y] = 88;
					}
					e = Q->base[e.link];
				}			
				break;
			}
		}
	}
}

//显示■、□组成的迷宫，路径可以用*(不带方向)，也可以考虑方向→ ↓ ← ↑
void PrintMaze(int maze[][N]){
	int i,j;
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
			if(maze[i][j] == 1){
				printf("■");
			}
			if(maze[i][j] == -1 | maze[i][j] == 0 | maze[i][j] == 6 | maze[i][j] == 8 | maze[i][j] == 4 | maze[i][j] == 2 ){
				printf("□");				
			}
			if(maze[i][j] == 9){
				printf("+ ");
			}
			if(maze[i][j] == 66){
				printf("→");
			}
			if(maze[i][j] == 22){
				printf("↓");
			}
			if(maze[i][j] == 44){
				printf("←");
			}
			if(maze[i][j] == 88){
				printf("↑");
			}
		}
		printf("\n");
	}
}

int main(){
    int a;
    PosType startpos, endpos;

	//描述迷宫（人大校园）
	int maze[M][N]=
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	 1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,1,0,1,1,
	 1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,
	 1,1,1,1,0,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,0,1,1,1,
	 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,
	 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
	 1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,
	 1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,
	 1,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,
	 1,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
	 1,1,0,0,0,0,1,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	 1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,
	 1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,
	 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

	 int place[8][2]= //作为示例,可自行增加,注意应该是0处
{	    7,1,//人大西门
        3,4,//明德楼
        8,15,//人文楼
        1,25,//北门
        5,23,//图书馆
        1,27,//邮局
        10,28,//东门
        2,23};//足球场

	printf("\n简版人大地图\n");
    PrintMaze(maze);
    printf("1.人大西门 2.明德楼  3.人文楼  4.北门\n");
    printf("5.图书馆   6.邮局    7.东门    8.足球场\n\n");

    printf("请选择起点位置： \n");
 	scanf("%d",&a);
    startpos.x=place[a-1][0];
    startpos.y=place[a-1][1];
    printf("请选择终点位置： \n");
 	scanf("%d",&a);
    endpos.x=place[a-1][0];
    endpos.y=place[a-1][1];

	if(FindPath(maze,startpos,endpos)){
	    printf("\n路线如下所示:\n");
	    PrintMaze(maze);
	}
	else
        printf("Sorry, no path found.\n");

    return 1;
}
