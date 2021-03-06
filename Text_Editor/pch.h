#ifndef PCH_H
#define PCH_H
#include<iostream>
#include<string>
#include<cstring>
#include <fstream>
using namespace std;

//define node
struct dbNode{ 
	string data;
	dbNode* back;
	dbNode* next;

	dbNode();
	dbNode(string item, dbNode* linkBack, dbNode* linkNext);
};

//define DBLinkList class
class doubleLinkList{
protected:
	dbNode* head;
	mutable int curPosition;
	mutable dbNode* curPtr;
	int count;
	dbNode *getElemPtr(int position)const;
	void init();
public:
	doubleLinkList();
	virtual~doubleLinkList();
	string getElem(int position);
	void setElem(int position , string s);
	int length()const;
	bool empty()const;
	void clear();
	bool view();
	int statistic();
	bool Delete(int position);
	bool insert(int position , string e);
};


//define textEditor class
class textEditor{
private:
	doubleLinkList textBuffer;       
	int curLineNo;                  //当前行
	ifstream inFile;                // 输入文件
	ofstream outFile;				// 输出文件 
	string infName;
	void showHelp();    
	bool nextLine();    
	bool previousLine();
	bool gotoLine();
	bool insertLine();
	bool changeLine();
	void readFile();
	void outInself();
	void writeFile();
	void findString();
	void substitude();
	void showCurline();
public:
	textEditor(string inName , string outName);
	void run();
};
     
// TODO: 添加要在此处预编译的标头
   
#endif //PCH_H
