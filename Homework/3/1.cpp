#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring> 
using namespace std;

#define new_node (Node*)malloc(sizeof(Node))

typedef struct Node
{
    int data;
    struct Node *next;
}LinkList;

//向前构建链表 
void CreatLinkList(Node **head,int n){
    Node *p;
    int x;
    (*head) = new_node;
    (*head)->next = NULL;
    while(n--)
    {
        p = new_node;
        scanf("%d",&x);
		p->data = x;
        p->next = (*head)->next;
        (*head)->next = p;
	}
}


void PrintList(Node *c){   
    Node *p = c;
    while((p=p->next)!=NULL)
    {
        printf("%d ",p->data);
    }
}

Node *MergeLinkList(Node *a,Node *b){
    Node *p,*q,*c;
    c = new_node;//new LinkList 
    c->next = NULL;
    c->data = 0x3f3f3f3f;
    p = c;
    q = p;
    while((a->next!=NULL) && (b->next!=NULL)) 
    {
        if((a->next)->data > (b->next)->data)
        {   if((a->next)->data != p->data) //check the same
            { 
            p = new_node;
            p->data = (a->next)->data;
            p->next = NULL;
            q->next = p;
            q = p;
            }
		a = a->next;    
		}
        else
        {   if((b->next)->data != p->data)
            {
			p = new_node;
            p->data = (b->next)->data;
            p->next = NULL;
            q->next = p;
            q = p;
            }
		b = b->next;
		}
    }
    //finish copy left list
    if(b->next == NULL&&a->next!=NULL)
    {
		while(a->next !=NULL){
		if((a->next)->data != p->data)
		p->next = a -> next;
        a = a->next; 
        }
	}
    if(a->next == NULL && b->next !=NULL)
    {   
        while(b->next !=NULL){
        if((b ->next)->data != p->data)
		p->next = b ->next;
		b = b->next; 
	    }
    }
    return c;
}

int main()
{
    int n;
    LinkList *a,*b,*c;
    printf("输入A链表长度并输入递增的链表：");
	scanf("%d",&n);
	CreatLinkList(&a,n);
	printf("输入B链表长度并输入递增的链表："); 
	scanf("%d",&n);
    CreatLinkList(&b,n);
    c = MergeLinkList(a,b);
    printf("降序排序去重后的结果是："); 
	PrintList(c);
    return 0;
}

