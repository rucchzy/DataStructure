#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node{
    ElemType data;
    struct Node *next;
}Node, *LinkList;

    //在链表头部插入
    LinkList InsertFront(LinkList L)
{/*Your code*/		
		printf("您选的是头部插入法^_^\n");
		int i;
		int n;
		printf("请输入插入元素的个数：");
		scanf("%d",&n);
		while(n==0){
			printf("请重新输入插入元素的个数(T_T,0是不行的)：");
			scanf("%d",&n);
		}
		for(i=1;i<=n;i++){
		LinkList p = (Node *)malloc(sizeof(Node));
		printf("请输入所要插入的元素：");
		scanf("%d",&p->data);
		p->next = L->next;
		L->next = p;			
		}
		return L;
				
}
    //在链表尾部插入
    LinkList InsertRear (LinkList L)
{/*Your code*/
		printf("您选的是尾部插入法^_^\n");
		int i;
		int n;
		LinkList r = L;
		printf("请输入插入元素的个数：");
		scanf("%d",&n);
		while(n==0){
			printf("请重新输入插入元素的个数(T_T,0是不行的)：");
			scanf("%d",&n);
		}
		for(i=1;i<=n;i++){
			LinkList p = (Node *)malloc(sizeof(Node));
			printf("请输入所要插入的元素：");
			scanf("%d",&p->data);
			r->next=p;
			p->next=NULL;
			r=p;
		}
		return L;
}
    //在链表pos个位置上插入值为val的结点
    LinkList InsertByPos(LinkList L, int pos, int val)
{/*Your code*/
		int i;		
		LinkList p =L;
		LinkList q = (Node *)malloc(sizeof(Node));
		q->data=val;
		q->next=NULL;
		for(i=0;i<pos-1;i++){
			p=p->next;
		}
		q->next=p->next;
		p->next=q;
		return L;
}
    //删除链表中值为val的所有结点
	LinkList DelByValue(LinkList L, ElemType val)
{/*Your code*/
		LinkList p = L;		
		while(p->next!=NULL){
			LinkList s = p->next;
			if(s->data==val){
				p->next=s->next;
				free(s);
			}else{
				p=s;				
			}			
		}		  
		return L;
}
    //删除第pos位置上的结点
	LinkList DelByPos(LinkList L, const int pos)
{/*Your code*/
		LinkList p = L;
		int i;
		for(i=0;i<pos-1;i++){
			p=p->next;
		}
		LinkList s = p->next;
		p->next = s->next;
		free(s);
		return L;
}
    //从头依次显示各结点数据
    void PrintList(LinkList L)
{/*Your code*/		
		LinkList p =L->next;
		while(p->next!=NULL){
			printf("%d",p->data);
			p=p->next;
		};
		printf("%d",p->data);
}

	int main(){
		int c,value,pos;
		LinkList L1;
		Node *s, *q;

        L1 = (Node *)malloc(sizeof(Node)); //建立带头结点的链表L1
		if (!L1){
                printf("out of memory.\n");
                exit(1);
            }
        L1->next=NULL;

        printf("请选择建立链表的方法：1、头部插入 2、尾部插入\n");
        scanf("%d",&c);

        switch(c){
            case 1:L1=InsertFront(L1);break;
            case 2:L1=InsertRear(L1);break;
            default:printf("Invalid input.\n");return 0;
        }
        printf("链表L1：");
		PrintList(L1);
		printf("\n");

        printf("请输入所要插入的位置：");
        scanf("%d",&pos);
        printf("请输入所要插入的值：");
        scanf("%d",&value);
		L1=InsertByPos(L1,pos,value);
		PrintList(L1);

        printf("请输入所要删除的值：");
        scanf("%d",&value);
		L1=DelByValue(L1,value);
		PrintList(L1);
		printf("\n");

        printf("请问要删除第几个数据：");
        scanf("%d",&pos);
		L1=DelByPos(L1,pos);
		PrintList(L1);

		return 1;
	}
