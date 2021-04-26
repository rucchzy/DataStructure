#include<stdio.h>  
#include<stdlib.h>  
#define Leave_Num 26 //叶子结点数目 
#define Node_Num  (26*2-1)  //结点数目 
typedef struct _Node  
{  
    char character;  //字母 
    float weight;  //权重 
    int lchild;  //左结点 
    int rchild;  //右结点 
    int parent;  //父节点 
}Node,*pNode;  
  
typedef struct _Code  
{  
    int HufCode[Leave_Num];   //最长编码位数是树的最长路径 
    int  Start;              //编码起始位 
    char Char;               //编码字符值 
}Code,*pCode;  
  
//----------------------构造哈夫曼树----------------  
void Huffman(Node Ht[],float Wt[])  
{  
    int i,j,x1,x2;  
    float min1,min2;  
      
    //初始化结点数组Ht  
    for(i=0;i<Node_Num;i++)  
    {  
        Ht[i].parent = -1;  
        Ht[i].lchild = -1;  
        Ht[i].rchild = -1;  
        if(i<Leave_Num)  
        {  
            Ht[i].weight = Wt[i];  
            Ht[i].character = i+65;   //A到Z的ASCii编码  
        }  
        else  
        {  
            Ht[i].weight = 0;  
            Ht[i].character = '?';   //生成的中间结点字符值为'?'  
        }  
    }  
      
    //控制n-1次结点的结合(一共有n个叶子结点)  
    for(i=1;i<=Leave_Num-1;i++)  
    {  
        min1 = min2 = 100;              //min1表示最小权值，min2表示次小权值  
        x1 = x2 = 0;                    //x1表示当前最小权值的位置，x2表示当前次小权值的位置  
        for(j=0;j<Leave_Num-1+i;j++)       //找最小的两个 
        {  
            if(Ht[j].parent == -1 && Ht[j].weight<min1 )  //未访问过的结点且权重小于最小的  
            {  
                min2 = min1;         
                x2 = x1;  
                min1 = Ht[j].weight;  
                x1 = j;  
            }  
            else  
            {  
                if( Ht[j].parent == -1 && Ht[j].weight<min2 )  //未访问过的结点且权重大于最小的，却小于次小的 
                {  
                    min2 = Ht[j].weight;  
                    x2 = j;  
                }  
            }  
        }  
          
        //由最小的两个结点产生中间结点，权重为二者之和，并把父节点和左右结点设置好  
        Ht[x1].parent = Leave_Num-1+i;  
        Ht[x2].parent = Leave_Num-1+i;  
        Ht[Leave_Num-1+i].weight = Ht[x1].weight + Ht[x2].weight;  
        Ht[Leave_Num-1+i].lchild = x1;  
        Ht[Leave_Num-1+i].rchild = x2;  
    }  
}  
  
//---根据哈夫曼树产生编码并输出---    
void Code_Ht(Node Ht[],Code Hc[])  
{  
    int i,d,p,j;  
    Code x;  
      
    //对每一个叶子结点，从下往上追溯直到树根  
    for(i=0;i<Leave_Num;i++)  
    {  
        x.Char = Ht[i].character;  
        x.Start = Leave_Num-1;       //编码从后往前填  
        d = i;  
        p = Ht[i].parent;  
  
        while( 1 )       
        {  
            if(Ht[p].lchild == d)  
                x.HufCode[x.Start] = 0;     //如果是左结点，就填0  
            else if(Ht[p].rchild == d)  
                x.HufCode[x.Start] = 1;   //如果是右结点，就填1               
            d = p;  //记录中间结点的位置 
            p = Ht[d].parent;  //找到中间结点的父节点 
            if(p == -1) break;             //只有根节点的父节点才会是-1  
            x.Start--;  //进入编码的上一位 
        }  
        for(j=x.Start;j<=Leave_Num-1;j++)  //将编码记录在Hc中 
        {  
            Hc[i].HufCode[j] = x.HufCode[j];  //m每一位对位赋值 
        }  
        Hc[i].Start = x.Start;  
        Hc[i].Char = x.Char;
		for(j=Hc[i].Start;j<Leave_Num;j++)  
        {  
            printf("%d",Hc[i].HufCode[j]);  
        }  
        printf("%5c\n",Hc[i].Char);   
    }  
}  

int main()  
{  
    Node HufTree[Node_Num];     
    Code HCode[Leave_Num];  
    float Wt[Leave_Num] = {0.0834,0.0154,0.0273,0.0414,0.1260,0.0203,0.0192,0.0611,0.0671,  
                         0.0023,0.0087,0.0424,0.0253,0.0680,0.0770,0.0166,0.0009,0.0568,  
                         0.0611,0.0937,0.0285,0.0106,0.0234,0.0020,0.0204,0.0006};      
    Huffman(HufTree,Wt);  
    Code_Ht(HufTree,HCode);   
    return 0;
} 
