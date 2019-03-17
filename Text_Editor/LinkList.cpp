#include "pch.h"


doubleLinkList::doubleLinkList() {
	init();
}
doubleLinkList::~doubleLinkList() {
	clear();			// 清空链表
	delete head;		
}

void doubleLinkList::clear() {
	while (length()> 0)
	{
		Delete(1);
	}
}

void doubleLinkList::init()
{
	head = new dbNode;	// 构造头指针
	head->next = head;				
	head->back = head;				
	curPtr = head;	
	curPosition = 0;	// 初始化当前位置
	count = 0;			// 初始化元素个数
}

dbNode*doubleLinkList::getElemPtr(int position) const{
	if (curPosition < position)
	{
		for (; curPosition < position; curPosition++)
			curPtr = curPtr->next;
	}
	else if (curPosition > position)
	{
		for (; curPosition > position; curPosition--)
			curPtr = curPtr->back;
	}
	return curPtr;
}

string doubleLinkList::getElem(int position) {
	return getElemPtr(position)->data;
}

void doubleLinkList::setElem(int position, string s) {
	dbNode* tmpPtr;
	tmpPtr = getElemPtr(position);
	tmpPtr->data = s;
}

int doubleLinkList::length() const {
	return count;
}

bool doubleLinkList::empty() const{
	return head->next == head;
}

bool doubleLinkList::view() {
	if (count < 1)return 0;
	dbNode* temPtr = head->next;
	while (temPtr != head)
	{
		cout << temPtr->data << endl;
		temPtr = temPtr->next;
	}
	return 1;
}
int doubleLinkList::statistic() {    //a
	dbNode* temPtr = head->next;
	int cnt = 0;
	while (temPtr != head)
	{
		cnt += (temPtr->data).size();
		temPtr = temPtr->next;
	}
	return cnt;
}

bool doubleLinkList::Delete(int position) {
	if (position < 1 || position > length())
	{	// position范围错
		return 0;
	}
	else
	{	
		dbNode *tmpPtr;
		tmpPtr = getElemPtr(position - 1);		
		tmpPtr = tmpPtr->next;					
		tmpPtr->back->next = tmpPtr->next;		// 修改前一个指向
		tmpPtr->next->back = tmpPtr->back;		// 修改后一个指向
		if (position == length())
		{	
			curPosition = 0;					// 设置当前位置的序号
			curPtr = head;						// 设置指向当前位置的指针
		}
		else
		{	
			curPosition = position;				
			curPtr = tmpPtr->next;				
		}
		count--;								 
		delete tmpPtr;							// 释放被删结点
		return 1;
	}
}
bool doubleLinkList::insert(int position,string s){
	if (position < 1 || position > length() + 1)
	{	
		return 0; 
	}
	else
	{	
		dbNode* tmpPtr, *nextPtr, *newPtr;
		tmpPtr = getElemPtr(position - 1);	// 前一个位置
		nextPtr = tmpPtr->next;				// 后一个
		newPtr = new dbNode(s, tmpPtr, nextPtr); //(elem , back , next)
		tmpPtr->next = newPtr;				// 修改向右的指针
		nextPtr->back = newPtr;				// 修改向左的指针
		curPosition = position;				// 设置当前位置的序号
		curPtr = newPtr;					// 指向当前位置的指针
		count++;							// 插入成功后元素个数加1 
		return 1;
	}
}