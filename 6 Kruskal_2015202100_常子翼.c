/* ��С��������Kruskal�㷨 */  
//http://blog.csdn.net/u014488381/article/details/41447229
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
  
#define MaxSize 20  
  
typedef char VertexType;  
  
typedef struct Graph {      //����ͼ���ڽӾ����ʾ���ṹ  
    VertexType ver[MaxSize+1];  
    int edg[MaxSize][MaxSize];  
}Graph;  
  
typedef struct gEdge {      //����һ���߼��ṹ�������洢ͼ�����б���Ϣ  
    int begin;  
    int end;  
    int weight;  
}gEdge;  
  
void CreateGraph( Graph *g )        //�ڽӾ���ͼ�����ɺ���  
{  
    int i = 0;  
    int j = 0;  
    int VertexNum;  
    VertexType Ver;  
  
    printf("������ͼ�Ķ���:\n");  
    while( '\n' != (Ver=getchar()) ) {  
        g->ver[i++] = Ver;  
    }  
    g->ver[i] = '\0';  
  
    VertexNum = strlen(g->ver);  
    printf("��������Ӧ�ĵ��ڽӾ���:\n");  
    for( i=0; i<VertexNum; i++ )  
        for( j=0; j<VertexNum; j++ )   
            scanf("%d", &g->edg[i][j]);  
}  
  
void PrintGraph( Graph g )      //��ӡͼ�Ľ���ʶ�����ڽӾ���  
{  
    int i, j;  
    int VertexNum = strlen(g.ver);  
    printf("ͼ�Ķ���Ϊ:\n");  
    for( i=0; i<VertexNum; i++ )  
        printf("%c ", g.ver[i]);  
    printf("\n");  
  
    printf("ͼ���ڽӾ���Ϊ:\n");  
    for( i=0; i<VertexNum; i++ ) {  
        for( j=0; j<VertexNum; j++ )  
            printf("%d ", g.edg[i][j]);  
        printf("\n");  
    }  
}  
  
int CalVerNum( Graph g )        //��ͼ�Ķ�����  
{  
    return strlen(g.ver);  
}  
  
int CalEdgNum( Graph g )        //��ȡͼ�ı���  
{  
    Graph p = g;  
    int count = 0;  
    int VertexNum = CalVerNum( p );  
    int i;
    int j;
    for( i=0; i<VertexNum; i++ )  
        for( j=i; j<VertexNum; j++ )     //�ڽӾ���Գƣ�����������Ԫ�غͼ���  
            if( 0 != p.edg[i][j] )  
                count++;  
    return count;  
}  
  
gEdge *CreateEdges( Graph g )                   //����ͼ��������ı߼�����  
{  
    int i, j;  
    int k = 0;  
    int EdgNum = CalEdgNum( g );  
    int VertexNum = CalVerNum( g );  
    gEdge temp;  
    gEdge *p = (gEdge *)malloc(sizeof(gEdge)*EdgNum);     
  
    for( i=0; i<VertexNum; i++ )             //�߼������ʼ��,ͬ��ֻ���������Ǿ���  
        for( j=i; j<VertexNum; j++ )  
            if( 0 != g.edg[i][j] ) {  
                p[k].begin = i;  
                p[k].end = j;  
                p[k].weight = g.edg[i][j];  
                k++;  
            }  
      
    for( i=0; i<EdgNum-1; i++ )                  //�Ա߼��������ѡ������  
        for( j=i+1; j<EdgNum; j++ )  
            if( p[i].weight > p[j].weight ) {  
                temp = p[i];  
                p[i] = p[j];  
                p[j] = temp;  
            }  
  
    return p;  
}  
  
//Kruskal�㷨����MST  
void Kruskal( Graph g )  
{  
    int VertexNum = CalVerNum( g );  //ͼ�Ķ����� 
    int EdgNum = CalEdgNum( g );  //ͼ�ı��� 
    gEdge *p = CreateEdges( g );  //��ͼ�ı߽������� 
    int *index = (int *)malloc(sizeof(int)*VertexNum);          //index���飬��Ԫ��Ϊ��ͨ�����ı�ţ�index[i] = index[j] ��ʾ���Ϊi �� j�Ķ�����ͬһ����ͨ�����У���֮����ͬһ����ͨ����  
    int *MSTEdge = (int *)malloc(sizeof(int)*VertexNum-1);      //MSTEdge���飬�����洢��ȷ����MST�ıߵı�ţ���VertexNum-1����  
    int k= 0;  
    int WeightSum = 0;  
    int IndexBegin, IndexEnd;  
    int i; 
    int j;
    for(i=0; i<VertexNum; i++ ){
    	index[i] = -1;
    }      //��ʼ������index = -1  
          
  
    for( i=0; i<VertexNum-1; i++ ) {  //Ҫ��ӵı��� 
        for(j=0; j<EdgNum; j++ ) {  //����ͼ�����б� 
            if( !(index[p[j].begin]>=0 && index[p[j].end]>=0 && index[p[j].begin]==index[p[j].end]) ) {  //�ҵ���ǰ��û���뵽ͬһ����ͨ������Ȩֵ���µı�  
                MSTEdge[i] = j;     //������뵽MST��ȥ  
  
                if( (-1 == index[p[j].begin]) && (-1 == index[p[j].end]) ){
                	index[p[j].begin] = index[p[j].end] = i;
                }          //�ñߵ��������㶼û������κ�һ����ͨ����  
                          
  
                else if( (-1 == index[p[j].begin]) && (index[p[j].end] >= 0) ) { //�ñߵ�βend����һ����ͨ������ͷbeginδ������κ���ͨ����  
                    index[p[j].begin] = i;  
                    IndexEnd = index[p[j].end];  
                    int n;
					for(n=0; n<VertexNum; n++ )  
                        if( index[n] == IndexEnd )  
                            index[n] = i;  
                }  
  
                else if( (-1 == index[p[j].end]) && (index[p[j].begin] >= 0) ) { //�ñߵ�ͷbegin����һ����ͨ������βendδ������κ���ͨ����  
                    index[p[j].end] = i;  
                    IndexBegin = index[p[j].begin];  
                    int n;
					for(n=0; n<VertexNum; n++ )  
                        if( index[n] == IndexBegin ){
                        	index[n] = i;
                        }  
                              
                }  
  
                else {  
                    IndexEnd = index[p[j].end];  
                    IndexBegin = index[p[j].begin];  
                    int n;
					for(n=0; n<VertexNum; n++ )                              //�ñߵ��������㶼�Ѿ�������������ͬ����ͨ������  
                        if( index[n] == IndexBegin || index[n] == IndexEnd )  
                            index[n] = i;                                       //������ͨ�������ȫ���޸�Ϊ��ͬ��ֵ  
                }  
                break;  
            }  
        }  
    }  
  
    printf("MST�ı�Ϊ:\n");                //���MST�ı�  
    for( i=0; i<VertexNum-1; i++ ) {  
        printf("%c--%c\n", g.ver [p[MSTEdge[i]].begin] , g.ver [p[MSTEdge[i]].end] );  
        WeightSum+=p[MSTEdge[i]].weight;  
    }  
    printf("MST��ȨֵΪ:%d\n", WeightSum);      //���MST��Ȩֵ  
}  
  
int main()  
{  
    Graph g;  
    CreateGraph( &g );  
  
    PrintGraph( g );  
  
    Kruskal( g );  
  
    return 0;  
} 
