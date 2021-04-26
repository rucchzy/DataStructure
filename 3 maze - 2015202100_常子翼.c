#include <stdio.h>  
#include <stdlib.h>  

#define INIT_SIZE 100
#define STACKINCREMENT 20
#define M 15
#define N 30
 
//如果变量X是一个地址，那么所含的各种属性的调用要使用“->”；如果是一个数据结构，所含的属性要使用“.”调用 
typedef struct {
	int x,y;
} PosType;

typedef struct{
	PosType pos;
	int d;
}SElemType;

typedef struct{
	SElemType *base;//声明指针base，指针本身的数据类型是SElemType，指针存储的地址是一个SElemType类型的数据的地址 
	SElemType *top;//声明指针top，指针本身的数据类型是SElemType，指针存储的地址是一个SElemType类型的数据的地址 
	int stacksize;
} SeqStack;

//创建空栈
SeqStack *InitStack(){
	SeqStack *S; //声明存储地址的指针S，指针本身的数据类型是SeqStack，指针要存储的地址是一个SeqStack的数据地址 
	S=(SeqStack *)malloc(sizeof(SeqStack));//指针内容为一个SeqStack数据的存储位置,即存储了这块空间的首址
	S->base = (SElemType *)malloc(INIT_SIZE * sizeof(SElemType));
//因为S本身是SeqStack类型的数据，故有base这一属性；因为base是一个指针，故其内容为INIT_SIZE个的SElemType的存储位置，即存储了这块空间的首址（第一个数据块的地址） 
	if(!S->base) printf("内存分配出错！");
	S->top = S->base;
	S->stacksize = INIT_SIZE; 
	return S; 
}

//入栈
void Push(SeqStack *S, SElemType e){
	if(S->top - S->base >= S->stacksize){
		S->base = (SElemType *) realloc (S->base, (S->stacksize + STACKINCREMENT)*sizeof(SElemType));
		if(!S->base) printf("内存分配出错！");
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT ;
	}
	//*S->top++ = e;
	*(S->top) = e;
	S->top = S->top + 1; 
}

//出栈
SElemType Pop(SeqStack *S){
	if(S->top == S->base) printf("栈为空！");
	//ElemType *e;
	//e = --S->top;
	//return *e; 
	SElemType e;
	S->top = S->top - 1;
	e = *(S->top);
	return e;
}

//根据当前位置计算下一个位置坐标
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

//显示■、□组成的迷宫
void PrintMaze(int maze[M][N],int dir[M][N]){
	int i,j;
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
			if(maze[i][j] == 1){
				printf("■");
			}else if(maze[i][j] == 2){
				if(dir[i][j] == 0){
					printf("* ");
				}
				if(dir[i][j] == 1){
					printf("→");
				}
				if(dir[i][j] == 2){
					printf("↓");
				}
				if(dir[i][j] == 3){
					printf("←");
				}
				if(dir[i][j] == 4){
					printf("↑");
				}
			}else{
				printf("□");
			}
		}
		printf("\n");
	}
}

//搜索从起点到终点的路径
int FindPath(int maze[M][N],int dir[M][N],PosType startpos,PosType endpos)
{
	SeqStack *s = InitStack();//利用InitStack生成空栈，s为指针 
	SElemType e;
	PosType nowpos;
	nowpos = startpos;
	e.d = 0;
	do{
		if(maze[nowpos.x][nowpos.y]==0){                            //如果当前位置能走（值为0） 
			e.pos = nowpos;                                         //记录现在的坐标 
			e.d = dir[nowpos.x][nowpos.y] + 1;                      //记录此处下一步要走的方向 
			Push(s,e);                                              //将坐标和方向记录后，这一组数据入栈 
			maze[nowpos.x][nowpos.y]=3;                             //将此处标记为已走过的路（值为3） 
			if ((nowpos.x == endpos.x)&&(nowpos.y == endpos.y)){    //如果此处就是终点 
				while(!(s->top == s->base)){                        //在栈不空的情况下 
					SElemType elem = Pop(s);                        //用elem记录每一个值 
					maze[elem.pos.x][elem.pos.y]=2;                 //将每一个位置都标记为正确路线（值为2） 
				}
				break;                                              //停止 
			}
	        nowpos = NextPos(nowpos,dir[nowpos.x][nowpos.y]++);     //计算下一步的坐标，并且把走之前的位置的方向+1（不能分开写，那样找方向会出错） 
		}
		else{                                                       //如果当前位置不能走（值不等于0） 
			if(!(s->top == s->base)){                               //当栈不空时 
				e = Pop(s);                                         //拿出上一个数据并赋值给e 
				maze[e.pos.x][e.pos.y]=-1;                          //把此处设置为错误路径（值为-1） 
				while(e.d == 4){                                    //在此处所有方向都探测过（d的值为4）时 
						e = Pop(s);                                 //找到上一个元素并且赋值给e 
						maze[e.pos.x][e.pos.y]=-1;                  //把此处标记为错误路径（值为-1） 
				}
				if(e.d < 4){                                        //如果此处方向没有被探测完 
					e.d = dir[e.pos.x][e.pos.y] + 1;                //记录此处下一步要走的方向 
					nowpos = e.pos;                                 //记录此处的坐标 
					Push(s,e);                                      //记录此处的信息（把坐标和方向入栈） 
					maze[nowpos.x][nowpos.y]=3;                     //把此处标记为已走过的路 
					nowpos = NextPos(nowpos,dir[e.pos.x][e.pos.y]++);//计算下一步的坐标，并且把走之前的位置的方向+1（不能分开写，那样找方向会出错）
				}				
			}else{                                                  //如果栈为空 
				printf("栈为空！");                                 //返回“栈为空” 
			}
		}
	}while(!(s->top == s->base));                                   //当栈不为空时执行上述循环 
}


int main(){
    int a,i,j;
    PosType startpos, endpos;

	//描述迷宫（人大校园）
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

	int place[8][2]= //作为示例,可自行增加,注意应该是0处
{	    8,1,//人大西门
        4,4,//明德楼
        9,15,//人文楼
        1,25,//北门
        6,23,//图书馆
        2,27,//邮局
        11,28,//东门
        3,23};//足球场
        
    int dir[M][N];
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
		dir[i][j]=0;
		}
	}

	printf("\n简版人大地图\n");
    PrintMaze(maze,dir);
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
	
	if(FindPath(maze,dir,startpos,endpos)){
	    printf("\n路线如下所示:\n");
	    PrintMaze(maze,dir);
	}
	else
        printf("Sorry, no path found.\n");

    return 1;
}
