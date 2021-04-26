#include<stdio.h>  
#include<stdlib.h>  
#define Leave_Num 26 //Ҷ�ӽ����Ŀ 
#define Node_Num  (26*2-1)  //�����Ŀ 
typedef struct _Node  
{  
    char character;  //��ĸ 
    float weight;  //Ȩ�� 
    int lchild;  //���� 
    int rchild;  //�ҽ�� 
    int parent;  //���ڵ� 
}Node,*pNode;  
  
typedef struct _Code  
{  
    int HufCode[Leave_Num];   //�����λ���������·�� 
    int  Start;              //������ʼλ 
    char Char;               //�����ַ�ֵ 
}Code,*pCode;  
  
//----------------------�����������----------------  
void Huffman(Node Ht[],float Wt[])  
{  
    int i,j,x1,x2;  
    float min1,min2;  
      
    //��ʼ���������Ht  
    for(i=0;i<Node_Num;i++)  
    {  
        Ht[i].parent = -1;  
        Ht[i].lchild = -1;  
        Ht[i].rchild = -1;  
        if(i<Leave_Num)  
        {  
            Ht[i].weight = Wt[i];  
            Ht[i].character = i+65;   //A��Z��ASCii����  
        }  
        else  
        {  
            Ht[i].weight = 0;  
            Ht[i].character = '?';   //���ɵ��м����ַ�ֵΪ'?'  
        }  
    }  
      
    //����n-1�ν��Ľ��(һ����n��Ҷ�ӽ��)  
    for(i=1;i<=Leave_Num-1;i++)  
    {  
        min1 = min2 = 100;              //min1��ʾ��СȨֵ��min2��ʾ��СȨֵ  
        x1 = x2 = 0;                    //x1��ʾ��ǰ��СȨֵ��λ�ã�x2��ʾ��ǰ��СȨֵ��λ��  
        for(j=0;j<Leave_Num-1+i;j++)       //����С������ 
        {  
            if(Ht[j].parent == -1 && Ht[j].weight<min1 )  //δ���ʹ��Ľ����Ȩ��С����С��  
            {  
                min2 = min1;         
                x2 = x1;  
                min1 = Ht[j].weight;  
                x1 = j;  
            }  
            else  
            {  
                if( Ht[j].parent == -1 && Ht[j].weight<min2 )  //δ���ʹ��Ľ����Ȩ�ش�����С�ģ�ȴС�ڴ�С�� 
                {  
                    min2 = Ht[j].weight;  
                    x2 = j;  
                }  
            }  
        }  
          
        //����С�������������м��㣬Ȩ��Ϊ����֮�ͣ����Ѹ��ڵ�����ҽ�����ú�  
        Ht[x1].parent = Leave_Num-1+i;  
        Ht[x2].parent = Leave_Num-1+i;  
        Ht[Leave_Num-1+i].weight = Ht[x1].weight + Ht[x2].weight;  
        Ht[Leave_Num-1+i].lchild = x1;  
        Ht[Leave_Num-1+i].rchild = x2;  
    }  
}  
  
//---���ݹ��������������벢���---    
void Code_Ht(Node Ht[],Code Hc[])  
{  
    int i,d,p,j;  
    Code x;  
      
    //��ÿһ��Ҷ�ӽ�㣬��������׷��ֱ������  
    for(i=0;i<Leave_Num;i++)  
    {  
        x.Char = Ht[i].character;  
        x.Start = Leave_Num-1;       //����Ӻ���ǰ��  
        d = i;  
        p = Ht[i].parent;  
  
        while( 1 )       
        {  
            if(Ht[p].lchild == d)  
                x.HufCode[x.Start] = 0;     //��������㣬����0  
            else if(Ht[p].rchild == d)  
                x.HufCode[x.Start] = 1;   //������ҽ�㣬����1               
            d = p;  //��¼�м����λ�� 
            p = Ht[d].parent;  //�ҵ��м���ĸ��ڵ� 
            if(p == -1) break;             //ֻ�и��ڵ�ĸ��ڵ�Ż���-1  
            x.Start--;  //����������һλ 
        }  
        for(j=x.Start;j<=Leave_Num-1;j++)  //�������¼��Hc�� 
        {  
            Hc[i].HufCode[j] = x.HufCode[j];  //mÿһλ��λ��ֵ 
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
