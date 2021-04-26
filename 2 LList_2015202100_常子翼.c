#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node{
    ElemType data;
    struct Node *next;
}Node, *LinkList;

    //������ͷ������
    LinkList InsertFront(LinkList L)
{/*Your code*/		
		printf("��ѡ����ͷ�����뷨^_^\n");
		int i;
		int n;
		printf("���������Ԫ�صĸ�����");
		scanf("%d",&n);
		while(n==0){
			printf("�������������Ԫ�صĸ���(T_T,0�ǲ��е�)��");
			scanf("%d",&n);
		}
		for(i=1;i<=n;i++){
		LinkList p = (Node *)malloc(sizeof(Node));
		printf("��������Ҫ�����Ԫ�أ�");
		scanf("%d",&p->data);
		p->next = L->next;
		L->next = p;			
		}
		return L;
				
}
    //������β������
    LinkList InsertRear (LinkList L)
{/*Your code*/
		printf("��ѡ����β�����뷨^_^\n");
		int i;
		int n;
		LinkList r = L;
		printf("���������Ԫ�صĸ�����");
		scanf("%d",&n);
		while(n==0){
			printf("�������������Ԫ�صĸ���(T_T,0�ǲ��е�)��");
			scanf("%d",&n);
		}
		for(i=1;i<=n;i++){
			LinkList p = (Node *)malloc(sizeof(Node));
			printf("��������Ҫ�����Ԫ�أ�");
			scanf("%d",&p->data);
			r->next=p;
			p->next=NULL;
			r=p;
		}
		return L;
}
    //������pos��λ���ϲ���ֵΪval�Ľ��
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
    //ɾ��������ֵΪval�����н��
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
    //ɾ����posλ���ϵĽ��
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
    //��ͷ������ʾ���������
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

        L1 = (Node *)malloc(sizeof(Node)); //������ͷ��������L1
		if (!L1){
                printf("out of memory.\n");
                exit(1);
            }
        L1->next=NULL;

        printf("��ѡ��������ķ�����1��ͷ������ 2��β������\n");
        scanf("%d",&c);

        switch(c){
            case 1:L1=InsertFront(L1);break;
            case 2:L1=InsertRear(L1);break;
            default:printf("Invalid input.\n");return 0;
        }
        printf("����L1��");
		PrintList(L1);
		printf("\n");

        printf("��������Ҫ�����λ�ã�");
        scanf("%d",&pos);
        printf("��������Ҫ�����ֵ��");
        scanf("%d",&value);
		L1=InsertByPos(L1,pos,value);
		PrintList(L1);

        printf("��������Ҫɾ����ֵ��");
        scanf("%d",&value);
		L1=DelByValue(L1,value);
		PrintList(L1);
		printf("\n");

        printf("����Ҫɾ���ڼ������ݣ�");
        scanf("%d",&pos);
		L1=DelByPos(L1,pos);
		PrintList(L1);

		return 1;
	}
