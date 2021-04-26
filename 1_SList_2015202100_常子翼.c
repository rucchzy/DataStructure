    #include <stdio.h>  
    #include <stdlib.h>
    #include <malloc.h>
	#define LIST_INIT_SIZE 20  
    #define LISTINCREMENT 10   
    
    typedef int ElemType;//Ԫ������  
    typedef struct SqList{  
        ElemType *elem;//���Ա��׵�ַ  
        int length;//��ǰ�ĳ���  
        int listsize;//��ǰ����Ĵ洢��������elemTypeΪ��λ  
    }SqList;  
      
     
    //����һ�����Ա�
    int InitList_Sq(SqList *L){
	    /*your-code-here*/
	    L->elem=(ElemType *)malloc(LIST_INIT_SIZE *sizeof(ElemType));  
        if(!L->elem) return 0;
        L->length=0;
        L->listsize=LIST_INIT_SIZE;
        return 1;
    }
      
    //������ʾ˳����е�Ԫ�� 
    void PrintList(SqList *L) {
       /*your-code-here*/
   	    ElemType *p,*q;
   	    q=L->length+L->elem-1;
   	    p=L->elem;
   	    for(;p<=q;p++){
    	    printf("%d",*p);   	
   	    }
   	    printf("\n");       
    }
    //�ڱ��е�pos��λ��֮ǰ������Ԫ��e��ע��posָ�������Ǵ�1��ʼ�� 
    int Insert_Sq(SqList *L,ElemType e,int pos)  {
       /*your-code-here*/
       ElemType *newbase;
       if((pos<1)|(pos>L->length+1)) return 0;
       if(L->length>=L->listsize){        
	       L->listsize=L->listsize+LISTINCREMENT;
       }
       int p,q;
	   q=pos-1;
       p=L->length-1;
       for(;p>=q;--p){           
		   L->elem[p+1]=L->elem[p];		
       }
       L->elem[pos-1]=e;
       ++L->length;
    }

    //ɾ����pos��Ԫ�أ�ע��posָ�������Ǵ�1��ʼ��   
    int DeleteElem(SqList *L,int pos) {
       /*your-code-here*/
       if((pos<1)|(pos>L->length)) return 0;
       int p=pos-1;
       ElemType e;
	   e=L->elem[pos-1];
       int q=L->length-1;
       for(++p;p<=q;++p){       	
	       L->elem[p-1]=L->elem[p];	       
       }
       --L->length;
       return 1;
    }
    
    //(ѡ��)������˳���ϲ������һ��˳���ʹ����Ԫ�ش�С��������
    void MergeList(SqList *La,SqList *Lb){ 
       /*your-code-here*/
       //La->listsize += Lb->listsize;       
       int m;
       /*for (m=0; m < Lb->length; m++) {
			La->length = La->length + 1;
			La->elem[La->length + m] = Lb->elem[m];			
		}*/
		for(m=1;m<=Lb->length;m++){			
			Insert_Sq(La,Lb->elem[m-1],La->length);
		}		
		
		ElemType e;
		int b,j;
		for (b=0 ;b < La->length; b++) {			
			
			for (j=b+1; j < La->length; j++) {
				if (La->elem[b] > La->elem[j]) {
					e = La->elem[b];
					La->elem[b] = La->elem[j];
					La->elem[j] = e;
				}
			}
		}
       
    }
    
    int main(){  
        SqList list1, list2;  
		int i,pos;  
        ElemType temp;  

		//����һ���µ�˳���list1
        InitList_Sq(&list1);
		printf("list1:\t");
		PrintList(&list1);

		//��list1�����β���1-3-5-7-9
		for(i=1;i<=5;i++){
			temp=2*i-1;
		    Insert_Sq(&list1,temp,i);  
		}
		PrintList(&list1);

		//ɾ��ָ����λ���ϵ�Ԫ�� 
		printf("Pls enter the position (starting from 1) to delete:\t");
        scanf("%d",&pos);
        DeleteElem(&list1,pos);  
		PrintList(&list1);

		//����һ���µ�˳���list2�����β���2-4-6-8 
        InitList_Sq(&list2);
		for(i=1;i<=4;i++){
			temp=2*i;
		    Insert_Sq(&list2,temp,i);  
		}
		printf("list2:");
		PrintList(&list2);
		
		//����������˳���ϲ� 
	    MergeList(&list1,&list2);  
        printf("Merged list:");  
		PrintList(&list1);

        return 1;  
    }  
