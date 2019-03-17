
#ifndef PCH_H
#define PCH_H

#include<iostream>
#include<string>
#include<cstdlib>
#include<stack>
using namespace std;

// TODO: 添加要在此处预编译的标头
class calculator {
private:
	string expression;
	stack<double >opnd;  //操作数
	stack<char>optr;     //操作符
public:
	calculator();
	~calculator();
	bool read();
	void clear();
	int judgePri(char a, char b);
	double calTwoNum(double a, char c, double b);
	void cal();
};


#endif //PCH_H