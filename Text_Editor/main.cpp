// Text_Editor.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

int main()
{   
	cout << "………欢迎使用该行文本编辑器V1.0………" << endl;
	cout << "---------请按照提示进行操作---------" << endl;
	cout << "使用命令h可以获取帮助 *请注意该编辑器s与t命令*" << endl;
	try				//IOException			
	{
		string infName, outfName;
		cout << "请输入输入文件名：";
		getline(cin, infName);
		cout << "请输入输出文件名：";
		getline(cin, outfName);
		textEditor text(infName, outfName);	
		text.run();
		cout << "bye" << endl;
	}catch (const char* msg){		
		 cerr << msg << endl;				// 异常
		 cout << "请确认文件名后重新运行程序。" << endl;
	 }
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
