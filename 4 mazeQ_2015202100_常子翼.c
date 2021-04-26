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

//�����ն�
SeqQueue *InitQueue(){
	SeqQueue *Q;
	Q = (SeqQueue *)malloc(sizeof(QElemType));
	Q->base = (QElemType *)malloc(INIT_SIZE * sizeof(QElemType));
	if(!Q->base){
		printf("����ʧ�ܣ�");
	}
	Q->queuesize = INIT_SIZE;
	Q->rear = 0;
	return Q;
}

//Ԫ��e���
void InQueue(SeqQueue *Q,QElemType e){
	if(Q->rear + 1 == Q->queuesize){
		Q->base = (QElemType *) realloc (Q->base, (Q->queuesize + INCREMENT) * sizeof(QElemType));
		if(!Q->rear){
			printf("����ʧ�ܣ�");
		}
	}
	Q->base[Q->rear] = e;
	Q->rear = Q->rear + 1;
}

//����
QElemType OutQueue(SeqQueue *Q){
	if(Q->rear == 0){
		printf("��Ϊ�գ�");
	}
	QElemType e;
	e = Q->base[Q->rear - 1];
	Q->rear = Q->rear - 1;
	return e;
}

//���ݵ�ǰλ��pos���н����������һ��λ������
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

//��������㵽�յ��·��
int FindPath(int maze[][N],PosType startpos,PosType endpos){
	SeqQueue *Q = InitQueue();
	QElemType e;
	QElemType E;
	int p;
	PosType nowpos;
	e.pos = startpos;
	e.link = -1;
	InQueue(Q,e);
	maze[e.pos.x][e.pos.y] = 9;//��ʾ�߹���·
	p = 0; 
	for(;;p++){
		e.link = p;
		nowpos.x = Q->base[p].pos.x;
		nowpos.y = Q->base[p].pos.y;
		if(maze[nowpos.x + 1][nowpos.y] == 0){
			e.pos.x = nowpos.x + 1;
			e.pos.y = nowpos.y;
			maze[e.pos.x][e.pos.y] = 2;//��ʾ������ 
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
			maze[e.pos.x][e.pos.y] = 6;//��ʾ������ 
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
			maze[e.pos.x][e.pos.y] = 8;//��ʾ������ 
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
			maze[e.pos.x][e.pos.y] = 4;//��ʾ������ 
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

//��ʾ��������ɵ��Թ���·��������*(��������)��Ҳ���Կ��Ƿ���� �� �� ��
void PrintMaze(int maze[][N]){
	int i,j;
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
			if(maze[i][j] == 1){
				printf("��");
			}
			if(maze[i][j] == -1 | maze[i][j] == 0 | maze[i][j] == 6 | maze[i][j] == 8 | maze[i][j] == 4 | maze[i][j] == 2 ){
				printf("��");				
			}
			if(maze[i][j] == 9){
				printf("+ ");
			}
			if(maze[i][j] == 66){
				printf("��");
			}
			if(maze[i][j] == 22){
				printf("��");
			}
			if(maze[i][j] == 44){
				printf("��");
			}
			if(maze[i][j] == 88){
				printf("��");
			}
		}
		printf("\n");
	}
}

int main(){
    int a;
    PosType startpos, endpos;

	//�����Թ����˴�У԰��
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

	 int place[8][2]= //��Ϊʾ��,����������,ע��Ӧ����0��
{	    7,1,//�˴�����
        3,4,//����¥
        8,15,//����¥
        1,25,//����
        5,23,//ͼ���
        1,27,//�ʾ�
        10,28,//����
        2,23};//����

	printf("\n����˴��ͼ\n");
    PrintMaze(maze);
    printf("1.�˴����� 2.����¥  3.����¥  4.����\n");
    printf("5.ͼ���   6.�ʾ�    7.����    8.����\n\n");

    printf("��ѡ�����λ�ã� \n");
 	scanf("%d",&a);
    startpos.x=place[a-1][0];
    startpos.y=place[a-1][1];
    printf("��ѡ���յ�λ�ã� \n");
 	scanf("%d",&a);
    endpos.x=place[a-1][0];
    endpos.y=place[a-1][1];

	if(FindPath(maze,startpos,endpos)){
	    printf("\n·��������ʾ:\n");
	    PrintMaze(maze);
	}
	else
        printf("Sorry, no path found.\n");

    return 1;
}
