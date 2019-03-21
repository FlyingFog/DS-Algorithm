#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define Template template<class ElemType>

Template
struct Node{
    ElemType data;
    Node<ElemType> *next;
    Node();
	Node(ElemType item , Node<ElemType>*link=NULL); 
}; 

//Node 构造函数 
Template
Node<ElemType>::Node(){
	next = NULL;
}
Template
Node<ElemType>::Node(ElemType item , Node<ElemType>*link){
	data = item;
	next = link;
}

//define 链表类                   
Template
class LinkList{
	protected:
		Node<ElemType>*head;
	    void init();
	public:
	    LinkList();
		virtual ~LinkList();
		void MakeList(int n);
		void PrintList();
		Node<ElemType>*Locate(int pos);  
		Node<ElemType>*max();         
		int number(ElemType &x);
		void create(ElemType *a, int n);
		void tidyup();  
};          
//定义构造函数  及 建立链表函数 
Template 
void LinkList<ElemType>::init(){
	head = new Node<ElemType>;
}
Template 
LinkList<ElemType>::LinkList(){
	init();
}

Template 
void LinkList<ElemType>::MakeList(int n){
	init();
	int cnt = 0;
	Node<ElemType>*p = head;
	while(cnt < n){
        Node<ElemType>*q = new Node<ElemType>;
		p->next = q;
		cin>>q->data;
		p = q;
		cnt++;		
	}
}

//定义析构函数 
Template
LinkList<ElemType>::~LinkList(){
	delete head;
}

//打印链表函数 
Template 
void LinkList<ElemType>::PrintList(){
	Node<ElemType>*p = head;
	while((p=p->next) != NULL){
		cout<<p->data<<" ";
	}
	puts("");
}
         
//Locate         
Template             
Node<ElemType>*LinkList<ElemType>::Locate(int pos){
	if(pos <= 0)return NULL;
	Node<ElemType>*p = head;
	int k = 0;
	while(p != NULL && k<pos){
		p = p->next;
		k++;
	}
	if(p != NULL && k == pos){
		return p;
	}else {
		return NULL;
	}
} 

//
Template             
Node<ElemType>*LinkList<ElemType>::max(){
	if(head->next == NULL) return NULL;
	Node<ElemType>*pmax = head->next , *p = (head->next)->next; 
	while(p!=NULL){
		if(p->data > pmax->data)pmax = p;
		p = p->next;
	}
	return pmax;
}

//
Template             
int LinkList<ElemType>::number(ElemType &x){
     int n = 0;
     Node<ElemType>*p = head->next;
     while(p!=NULL){
     	if(p->data == x)n++;
     	p = p->next;
	 }
     return n;
}

//
Template             
void LinkList<ElemType>::create(ElemType *a, int n){
     Node<ElemType>*p = head;
	 for(int i=0 ;i < n; i++){
	 	p->next = new Node<ElemType>(a[i]);
	 	p = p->next;
	 }
	 p->next = NULL; 
}

//
Template             
void LinkList<ElemType>::tidyup(){
    Node<ElemType>*p = head->next , *tep;
    while(p!=NULL && p->next!=NULL)
	if(p->data == p->next->data){
    	tep = p->next;
    	p->next = tep->next;
    	delete tep;
	}
    else p = p->next;   
}

// main and test 
int main(){
	int str[5] = {3,4,5,6,7}, x,n,pos;//定义已知数组 
	LinkList<int > a,b;
	cout<<"输入你要构建的列表的长度 及该链表的元素: ";
	cin>>n;
	a.MakeList(n);
	cout<<"打印刚才输入的链表：";
	a.PrintList();
    cout<<"输入你要查找的位置pos：";
    cin>>pos; 
	cout<<"该位置元素地址 值： "<<a.Locate(pos)<<" "<<(a.Locate(pos)->data)<<endl;
	cout<<"最大的元素地址 值： "<<a.max()<<" "<<(a.max()->data)<<endl;
	cout<<"输入你要查找的元素x的值：";
	cin>>x;
	cout<<"x元素的个数： "<<a.number(x)<<endl;
   
	b.create(str , 5);
	cout<<"create函数输出测试：" ;
	b.PrintList();
	
	a.tidyup();
	cout<<"tidyup函数输出测试：" ;
	a.PrintList();
	return 0;
}

