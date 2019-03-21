#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;

class BinNodePtr{
public:
	char val;         //value
	BinNodePtr* lc;  //left child
	BinNodePtr* rc;  //right child
}*root;  // root node

BinNodePtr* elementAtLevel(int theLevel){
	queue<BinNodePtr* >q;
	
	int curlevel = 0;
	int cursize = 0;
	q.push(root);
	while(!q.empty()){
		++curlevel;
		cursize = q.size();
		if(curlevel == theLevel)break;
		int temsize = 0;
		while(temsize < cursize){
			temsize++;
			BinNodePtr* tem = q.front();
			q.pop();
			if(tem->lc != NULL)q.push(tem->lc);
			if(tem->rc != NULL)q.push(tem->rc);
		}
	}    	
    if(q.empty())return NULL;
     else return q.front();
}


int main(){
	
	
} 
