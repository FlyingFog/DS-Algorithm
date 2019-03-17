#include "pch.h"
#include <iostream>

int main() {
	calculator Cal;
	cout << "***********欢迎使用简单的表达式计算器************" << endl;
	cout << "                请按照提示输入   " << endl;
	cout << "              若要退出请输入exit" << endl;
	cout << endl;
	try {
		 Cal.cal();
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
}
