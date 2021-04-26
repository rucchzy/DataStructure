#include<stdio.h>  
    
#define SIZE 110    
#define INF 1000000;    
//http://blog.csdn.net/qq_34845121/article/details/62056089  
int map[SIZE][SIZE];  //�ڽӾ���洢   
int len[SIZE];      //d[i]��ʾԴ�㵽i�����ľ���   
int visit[SIZE];  //�ڵ��Ƿ񱻷���   
int n,m;    
  
int dijkstra(int from, int to){ //��Դ�㵽Ŀ���   
      
    int i;    
      
    for(i = 1 ; i <= n ; i ++){  //��ʼ��   
        visit[i] = 0;   //һ��ʼÿ���㶼û������   
        len[i] = map[from][i];  //�ȼ���Դ�㵽������ľ���   
    }    
    
    int j;    
    for(i = 1 ; i < n ; ++i){    //�Գ�Դ���ÿһ���������̼���   
        int min = INF;  //��¼��Сlen[i]   
        int pos;  //��¼Сlen[i] �ĵ�   
    
        for(j = 1 ; j <= n ; ++j){     
            if(!visit[j] && min > len[j]){    
                pos = j;    
                min = len[j];    
            }    
        }    
        visit[pos] = 1;    
    
        for(j = 1 ; j <= n ; ++j){  
            if(!visit[j] && (len[j] > (len[pos] +map[pos][j]))){ //���j�ڵ�û�б����ʹ�&&j�ڵ㵽Դ�ڵ�����·��>pos�ڵ㵽Դ�ڵ�����·��+pos�ڵ㵽j�ڵ��·��    
                len[j] = len[pos] + map[pos][j];    //����j�ڵ㵽Դ�ڵ�����·��      
            }    
        }    
    }    
    
    return len[to];  
}  
    
    
int main () {    
  
    int i,j;    
      
  //  scanf("%d%d",&n,&m);  //��������  
    n = 6;  //��������   
    m = 9;  
  
    for(i = 1 ; i <= n ; ++i){   //��һ��ʼÿ���㶼���ɴ�   
        for(j = 1 ; j <= n ; ++j){    
            map[i][j] = INF;    
        }    
    }    
      
/*  int a,b,c;  //��������  
    for(i = 1 ; i <= m ; ++i){   
        scanf("%d%d%d",&a,&b,&c);   
        map[a][b] = map[b][a] = c;   
    }  */  
/*  �ߵ�����  
1 2 7 
1 3 9 
1 6 14 
2 3 10 
2 4 15 
3 6 2 
5 6 9 
4 5 6 
3 4 11 
*/ 
    map[1][2] = 6;  //��������   
    map[1][3] = 1;  
    map[1][4] = 5;  
    map[2][3] = 5;  
    map[2][5] = 3;  
    map[3][4] = 5;  
    map[3][5] = 6;  
    map[3][6] = 4;  
    map[4][6] = 6;  
    int temp = INF;  
    for(i = 1 ; i <= n ; ++i){  
        for(j = 1 ; j <= n ; ++j){  
            if(map[i][j] == temp)  
                map[i][j] = map[j][i];  
        }  
    }  
  
    int ans = dijkstra(5,1);    
  
    printf("%d",ans);    
  
    return 0;    
}
