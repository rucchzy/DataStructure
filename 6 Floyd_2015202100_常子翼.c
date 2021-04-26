#include <stdio.h>  
#include <stdlib.h>  
#define MAX_VERTEX_NUM 100              //最大顶点数  
#define MAX_INT 10000                   //无穷大   
//http://blog.csdn.net/u012965373/article/details/47844725
typedef int AdjType;   
typedef struct  
{  
    int pi[MAX_VERTEX_NUM];         //存放v到vi的一条最短路径  
    int end;  
}PathType;  
   
typedef char VType;                 //设顶点为字符类型  
  
  
//邻接矩阵表示的图  
typedef struct  
{  
    VType V[MAX_VERTEX_NUM];        //顶点存储空间   
    AdjType A[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //邻接矩阵   
}MGraph;  
  
int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//v到各顶点的最短路径向量  
int D[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//v到各顶点最短路径长度向量   
      
  
//Floyd算法  
//求网G（用邻接矩阵表示）中任意两点间最短路径   
//D[][]是最短路径长度矩阵，path[][]最短路径标志矩阵   
void Floyd(MGraph * G,int path[][MAX_VERTEX_NUM],int D[][MAX_VERTEX_NUM],int n)  
{   
    int i,j,k;  
    //初始化  
    for(i=0;i<n;i++)  
    {   
        for(j=0;j<n;j++)  
        {  
            if(G->A[i][j]<MAX_INT)  
            {  
                path[i][j]=j;  
            }  
            else  
            {  
                path[i][j]=-1;  
            }  
            D[i][j]=G->A[i][j];  
        }  
    }   
      
    //进行n次搜索  
    for(k=0;k<n;k++)  
    {   
        for(i=0;i<n;i++)  
        {  
            for(j=0;j<n;j++)  
            {  
                if(D[i][j] > D[i][k] + D[k][j])  
                {  
                    D[i][j]=D[i][k]+D[k][j];            //取小者   
                    path[i][j]=path[i][k];              //改Vi的后继   
                }  
            }  
        }  
    }  
}  
  
  
int main()  
{  
    int i,j,k,v=0,n=6;                              //v为起点，n为顶点个数   
    MGraph G;  
      
    //初始化   
    AdjType a[MAX_VERTEX_NUM][MAX_VERTEX_NUM]=  
    {  
        {MAX_INT,6,1,5,MAX_INT,MAX_INT},  
        {6,MAX_INT,5,MAX_INT,3,MAX_INT},  
        {1,5,MAX_INT,5,6,4},  
        {5,MAX_INT,5,MAX_INT,MAX_INT,2},  
        {MAX_INT,3,6,MAX_INT,MAX_INT,6},  
        {MAX_INT,MAX_INT,4,2,6,MAX_INT}   
    };  
    for(i=0;i<n;i++)  
    {  
        for(j=0;j<n;j++)  
        {  
            G.A[i][j]=a[i][j];  
        }  
    }   
      
    Floyd(&G,path,D,6);  
    //输出每对顶点间最短路径长度及最短路径  
    for(i=0;i<n;i++)  
    {                     
        for(j=0;j<n;j++)  
        {  
            printf("顶点%d到顶点%d的最短长度: ",i,j);   
            printf("%d\t",D[i][j]);                     //输出Vi到Vj的最短路径长度  
            k=path[i][j];                               //取路径上Vi的后续Vk  
            if(k==-1)  
            {  
                printf("顶点%d 和 顶点%d 之间没有路径\n",i,j);//路径不存在   
            }  
            else  
            {  
                printf("最短路径为:");   
                printf("(边%d",i);                   //输出Vi的序号i  
                //k不等于路径终点j时  
                while(k!=j)  
                {                          
                    printf(",V%d",k);               //输出k  
                    k=path[k][j];                   //求路径上下一顶点序号   
                }  
                printf("，边%d)\n",j);            //输出路径终点序号   
            }  
            printf("\n");  
        }   
    }  
    return 0;  
}  
