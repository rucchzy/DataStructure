#include <stdio.h>  
#include <stdlib.h>  

#define INIT_SIZE 100
#define STACKINCREMENT 20
#define M 15
#define N 30
 
//�������X��һ����ַ����ô�����ĸ������Եĵ���Ҫʹ�á�->���������һ�����ݽṹ������������Ҫʹ�á�.������ 
typedef struct {
	int x,y;
} PosType;

typedef struct{
	PosType pos;
	int d;
}SElemType;

typedef struct{
	SElemType *base;//����ָ��base��ָ�뱾�������������SElemType��ָ��洢�ĵ�ַ��һ��SElemType���͵����ݵĵ�ַ 
	SElemType *top;//����ָ��top��ָ�뱾�������������SElemType��ָ��洢�ĵ�ַ��һ��SElemType���͵����ݵĵ�ַ 
	int stacksize;
} SeqStack;

//������ջ
SeqStack *InitStack(){
	SeqStack *S; //�����洢��ַ��ָ��S��ָ�뱾�������������SeqStack��ָ��Ҫ�洢�ĵ�ַ��һ��SeqStack�����ݵ�ַ 
	S=(SeqStack *)malloc(sizeof(SeqStack));//ָ������Ϊһ��SeqStack���ݵĴ洢λ��,���洢�����ռ����ַ
	S->base = (SElemType *)malloc(INIT_SIZE * sizeof(SElemType));
//��ΪS������SeqStack���͵����ݣ�����base��һ���ԣ���Ϊbase��һ��ָ�룬��������ΪINIT_SIZE����SElemType�Ĵ洢λ�ã����洢�����ռ����ַ����һ�����ݿ�ĵ�ַ�� 
	if(!S->base) printf("�ڴ�������");
	S->top = S->base;
	S->stacksize = INIT_SIZE; 
	return S; 
}

//��ջ
void Push(SeqStack *S, SElemType e){
	if(S->top - S->base >= S->stacksize){
		S->base = (SElemType *) realloc (S->base, (S->stacksize + STACKINCREMENT)*sizeof(SElemType));
		if(!S->base) printf("�ڴ�������");
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT ;
	}
	//*S->top++ = e;
	*(S->top) = e;
	S->top = S->top + 1; 
}

//��ջ
SElemType Pop(SeqStack *S){
	if(S->top == S->base) printf("ջΪ�գ�");
	//ElemType *e;
	//e = --S->top;
	//return *e; 
	SElemType e;
	S->top = S->top - 1;
	e = *(S->top);
	return e;
}

//���ݵ�ǰλ�ü�����һ��λ������
PosType NextPos(PosType pos,int d){
	if(d == 0){
		pos.y += 1;
	}
	if(d == 1){
		pos.x += 1;
	}
	if(d == 2){
		pos.y -= 1;
	}
	if(d == 3){
		pos.x -= 1;
	}
	return pos;
}

//��ʾ��������ɵ��Թ�
void PrintMaze(int maze[M][N],int dir[M][N]){
	int i,j;
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
			if(maze[i][j] == 1){
				printf("��");
			}else if(maze[i][j] == 2){
				if(dir[i][j] == 0){
					printf("* ");
				}
				if(dir[i][j] == 1){
					printf("��");
				}
				if(dir[i][j] == 2){
					printf("��");
				}
				if(dir[i][j] == 3){
					printf("��");
				}
				if(dir[i][j] == 4){
					printf("��");
				}
			}else{
				printf("��");
			}
		}
		printf("\n");
	}
}

//��������㵽�յ��·��
int FindPath(int maze[M][N],int dir[M][N],PosType startpos,PosType endpos)
{
	SeqStack *s = InitStack();//����InitStack���ɿ�ջ��sΪָ�� 
	SElemType e;
	PosType nowpos;
	nowpos = startpos;
	e.d = 0;
	do{
		if(maze[nowpos.x][nowpos.y]==0){                            //�����ǰλ�����ߣ�ֵΪ0�� 
			e.pos = nowpos;                                         //��¼���ڵ����� 
			e.d = dir[nowpos.x][nowpos.y] + 1;                      //��¼�˴���һ��Ҫ�ߵķ��� 
			Push(s,e);                                              //������ͷ����¼����һ��������ջ 
			maze[nowpos.x][nowpos.y]=3;                             //���˴����Ϊ���߹���·��ֵΪ3�� 
			if ((nowpos.x == endpos.x)&&(nowpos.y == endpos.y)){    //����˴������յ� 
				while(!(s->top == s->base)){                        //��ջ���յ������ 
					SElemType elem = Pop(s);                        //��elem��¼ÿһ��ֵ 
					maze[elem.pos.x][elem.pos.y]=2;                 //��ÿһ��λ�ö����Ϊ��ȷ·�ߣ�ֵΪ2�� 
				}
				break;                                              //ֹͣ 
			}
	        nowpos = NextPos(nowpos,dir[nowpos.x][nowpos.y]++);     //������һ�������꣬���Ұ���֮ǰ��λ�õķ���+1�����ֿܷ�д�������ҷ������� 
		}
		else{                                                       //�����ǰλ�ò����ߣ�ֵ������0�� 
			if(!(s->top == s->base)){                               //��ջ����ʱ 
				e = Pop(s);                                         //�ó���һ�����ݲ���ֵ��e 
				maze[e.pos.x][e.pos.y]=-1;                          //�Ѵ˴�����Ϊ����·����ֵΪ-1�� 
				while(e.d == 4){                                    //�ڴ˴����з���̽�����d��ֵΪ4��ʱ 
						e = Pop(s);                                 //�ҵ���һ��Ԫ�ز��Ҹ�ֵ��e 
						maze[e.pos.x][e.pos.y]=-1;                  //�Ѵ˴����Ϊ����·����ֵΪ-1�� 
				}
				if(e.d < 4){                                        //����˴�����û�б�̽���� 
					e.d = dir[e.pos.x][e.pos.y] + 1;                //��¼�˴���һ��Ҫ�ߵķ��� 
					nowpos = e.pos;                                 //��¼�˴������� 
					Push(s,e);                                      //��¼�˴�����Ϣ��������ͷ�����ջ�� 
					maze[nowpos.x][nowpos.y]=3;                     //�Ѵ˴����Ϊ���߹���· 
					nowpos = NextPos(nowpos,dir[e.pos.x][e.pos.y]++);//������һ�������꣬���Ұ���֮ǰ��λ�õķ���+1�����ֿܷ�д�������ҷ�������
				}				
			}else{                                                  //���ջΪ�� 
				printf("ջΪ�գ�");                                 //���ء�ջΪ�ա� 
			}
		}
	}while(!(s->top == s->base));                                   //��ջ��Ϊ��ʱִ������ѭ�� 
}


int main(){
    int a,i,j;
    PosType startpos, endpos;

	//�����Թ����˴�У԰��
	int maze[M][N]=
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,
	 1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,1,0,1,1,
	 1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,
	 1,1,1,1,0,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,0,1,1,1,
	 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,
	 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
	 1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,
	 1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,
	 1,1,1,1,1,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,
	 1,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
	 1,1,0,0,0,0,1,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	 1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,
	 1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,
	 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

	int place[8][2]= //��Ϊʾ��,����������,ע��Ӧ����0��
{	    8,1,//�˴�����
        4,4,//����¥
        9,15,//����¥
        1,25,//����
        6,23,//ͼ���
        2,27,//�ʾ�
        11,28,//����
        3,23};//����
        
    int dir[M][N];
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
		dir[i][j]=0;
		}
	}

	printf("\n����˴��ͼ\n");
    PrintMaze(maze,dir);
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
	
	if(FindPath(maze,dir,startpos,endpos)){
	    printf("\n·��������ʾ:\n");
	    PrintMaze(maze,dir);
	}
	else
        printf("Sorry, no path found.\n");

    return 1;
}
