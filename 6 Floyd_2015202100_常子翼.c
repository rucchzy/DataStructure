#include <stdio.h>  
#include <stdlib.h>  
#define MAX_VERTEX_NUM 100              //��󶥵���  
#define MAX_INT 10000                   //�����   
//http://blog.csdn.net/u012965373/article/details/47844725
typedef int AdjType;   
typedef struct  
{  
    int pi[MAX_VERTEX_NUM];         //���v��vi��һ�����·��  
    int end;  
}PathType;  
   
typedef char VType;                 //�趥��Ϊ�ַ�����  
  
  
//�ڽӾ����ʾ��ͼ  
typedef struct  
{  
    VType V[MAX_VERTEX_NUM];        //����洢�ռ�   
    AdjType A[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //�ڽӾ���   
}MGraph;  
  
int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//v������������·������  
int D[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//v�����������·����������   
      
  
//Floyd�㷨  
//����G�����ڽӾ����ʾ����������������·��   
//D[][]�����·�����Ⱦ���path[][]���·����־����   
void Floyd(MGraph * G,int path[][MAX_VERTEX_NUM],int D[][MAX_VERTEX_NUM],int n)  
{   
    int i,j,k;  
    //��ʼ��  
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
      
    //����n������  
    for(k=0;k<n;k++)  
    {   
        for(i=0;i<n;i++)  
        {  
            for(j=0;j<n;j++)  
            {  
                if(D[i][j] > D[i][k] + D[k][j])  
                {  
                    D[i][j]=D[i][k]+D[k][j];            //ȡС��   
                    path[i][j]=path[i][k];              //��Vi�ĺ��   
                }  
            }  
        }  
    }  
}  
  
  
int main()  
{  
    int i,j,k,v=0,n=6;                              //vΪ��㣬nΪ�������   
    MGraph G;  
      
    //��ʼ��   
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
    //���ÿ�Զ�������·�����ȼ����·��  
    for(i=0;i<n;i++)  
    {                     
        for(j=0;j<n;j++)  
        {  
            printf("����%d������%d����̳���: ",i,j);   
            printf("%d\t",D[i][j]);                     //���Vi��Vj�����·������  
            k=path[i][j];                               //ȡ·����Vi�ĺ���Vk  
            if(k==-1)  
            {  
                printf("����%d �� ����%d ֮��û��·��\n",i,j);//·��������   
            }  
            else  
            {  
                printf("���·��Ϊ:");   
                printf("(��%d",i);                   //���Vi�����i  
                //k������·���յ�jʱ  
                while(k!=j)  
                {                          
                    printf(",V%d",k);               //���k  
                    k=path[k][j];                   //��·������һ�������   
                }  
                printf("����%d)\n",j);            //���·���յ����   
            }  
            printf("\n");  
        }   
    }  
    return 0;  
}  
