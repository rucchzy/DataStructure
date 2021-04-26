    #include <stdio.h>  
    #include <stdlib.h>
    #include <malloc.h>
	#define LIST_INIT_SIZE 20  
    #define LISTINCREMENT 10   
    
    typedef int ElemType;//元素类型  
    typedef struct SqList{  
        ElemType *elem;//线性表首地址  
        int length;//当前的长度  
        int listsize;//当前分配的存储容量，以elemType为单位  
    }SqList;  
      
     
    //创建一个线性表
    int InitList_Sq(SqList *L){
	    /*your-code-here*/
	    L->elem=(ElemType *)malloc(LIST_INIT_SIZE *sizeof(ElemType));  
        if(!L->elem) return 0;
        L->length=0;
        L->listsize=LIST_INIT_SIZE;
        return 1;
    }
      
    //依次显示顺序表中的元素 
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
    //在表中第pos个位置之前插入新元素e，注意pos指队伍编号是从1开始的 
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

    //删除第pos个元素，注意pos指队伍编号是从1开始的   
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
    
    //(选作)将两个顺序表合并存入第一个顺序表，使所有元素从小到大排列
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

		//建立一个新的顺序表list1
        InitList_Sq(&list1);
		printf("list1:\t");
		PrintList(&list1);

		//在list1中依次插入1-3-5-7-9
		for(i=1;i<=5;i++){
			temp=2*i-1;
		    Insert_Sq(&list1,temp,i);  
		}
		PrintList(&list1);

		//删除指定的位置上的元素 
		printf("Pls enter the position (starting from 1) to delete:\t");
        scanf("%d",&pos);
        DeleteElem(&list1,pos);  
		PrintList(&list1);

		//建立一个新的顺序表list2，依次插入2-4-6-8 
        InitList_Sq(&list2);
		for(i=1;i<=4;i++){
			temp=2*i;
		    Insert_Sq(&list2,temp,i);  
		}
		printf("list2:");
		PrintList(&list2);
		
		//将上述两个顺序表合并 
	    MergeList(&list1,&list2);  
        printf("Merged list:");  
		PrintList(&list1);

        return 1;  
    }  
