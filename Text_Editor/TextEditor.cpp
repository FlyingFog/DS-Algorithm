#include "pch.h"

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
textEditor::textEditor(string inName, string outName):inFile(inName.c_str()), outFile(outName.c_str()) {
	infName = inName;
	if (!inFile  ) throw "打开输入文件失败!";
	if (!outFile ) throw "打开输出文件失败!";	
	readFile();
}


//-*-*-*-*-*-*-*-IO*--*-*-*--*-*-*-*-*-*
void textEditor::readFile(){
	string s;
	textBuffer.clear();
	inFile.seekg(0);
	int lineNo = 1;
	cout << "读取文件成功" << endl;
	while (getline(inFile, s)) {
		textBuffer.insert(lineNo++, s);
	}
	if (textBuffer.empty())curLineNo = 0;
	else curLineNo = 1;
	inFile.clear();
}

void textEditor::writeFile() {
	string s;
	if (textBuffer.empty())
		cout << "-Error: 文本为空" << endl;
	else {
		for (int i = 1; i <= textBuffer.length(); i++) {
			s = textBuffer.getElem(i);
			outFile << s << endl;
		 }
		cout << "-写入输出文件完成" << endl;
	}
}

void textEditor::outInself() {
	ofstream outSelf(infName.c_str());
	string s;
	if (textBuffer.empty())
		cout << "-Error: 文本为空" << endl;
	else {
		for (int i = 1; i <= textBuffer.length(); i++) {
			s = textBuffer.getElem(i);
			outSelf << s << endl;
		}
		cout << "-保存在输入文件完成" << endl;
	}
}
//-*-*-*-*-*-*-*-IO END*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-* Line Op-*-*-*-*-*-*-*-*-*-*-*
bool textEditor::nextLine(){
	if (curLineNo >= textBuffer.length())
	{	// 当前行号已是最后一行
		return 0;
	}
	else
	{	// 当前行号不是最后一行
		curLineNo++;
		cout << "-已经移动到下一行" << endl;
		return 1;
	}
}

bool textEditor::previousLine(){
	if (curLineNo <= 1)
	{	
		return 0;
	}
	else
	{	
		curLineNo--;
		cout << "-已经移动到上一行" << endl;
		return 1;
	}
}

bool textEditor::gotoLine(){
	int lineNumber;
	cout << "-输入指定的行号: ";
	cin >> lineNumber;
	getchar();
	if (lineNumber < 1 || lineNumber > textBuffer.length())
	{	// 行号范围错
		return 0;
	}
	else
	{
		curLineNo = lineNumber;
		cout << "-已经移动到指定行" << endl;
		return 1;
	}
}
//*-*-*-*-*-*-*Line Op END--*-*-*-*--*-*-*-*

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void textEditor::showCurline() {
	cout << "-当前行内容为：";
	cout << textBuffer.getElem(curLineNo)<<endl;
}

bool textEditor::insertLine()
{
	int lineNumber;
	cout << "-输入插入的指定行号: ";
	cin >> lineNumber;
	cout << "-输入新插入行文本串: ";
	getchar();
	string s;
	getline(cin, s);
	if (textBuffer.insert(lineNumber, s) == 1)
	{	// 插入成功
		curLineNo = lineNumber;
		cout << "-插入完成" << endl;
		return 1;
	}
	else
	{	// 插入失败
		return 0;
	}
}

bool textEditor::changeLine() {

	cout << "-输入要被替换的指定文本串: ";
	string oldString;
	getline(cin, oldString);
	string newString;
	cout << "-输入新文本串:";
	getline(cin, newString);
	string curString = textBuffer.getElem(curLineNo);
	size_t position = curString.find(oldString);
	if (position < 0) {
		cout << "-不存在该串" << endl;
		return 0;
	}
	else {
		curString.erase(position, oldString.size());
		curString.insert(position, newString);
		textBuffer.setElem(curLineNo , curString);
		cout << "-替换完成" << endl;
		return 1;
	}
}  

void textEditor::substitude() {
	 string s;
	 getline(cin, s);
	 textBuffer.setElem(curLineNo, s);
	 cout << "-替换完成" << endl;
}

void textEditor::findString() {
	cout << "-输入要查找的串：";
	string findStr;
	getline(cin, findStr);
	int lineNumber = 1;
	while (lineNumber <= textBuffer.length())
	{
		string temStr = textBuffer.getElem(lineNumber);
		if (temStr.find(findStr) >= 0) {
			cout << "-该串第一次出现在行：" << lineNumber << endl;
			return;
		}
	}
	cout << "-未找到目标串" << endl;
}
//*-*-*-*-*-*-  END   -*-*-*-*-*-*-

//-*-*-*-*-*-*- RUN -*-*-*-*-*-*-*-*-*-*
void textEditor::run() {
	string userCommand;
	do
	{
		cout << "请输入命令：";
		getline(cin, userCommand);
		if (userCommand.size() > 1)
			cout << "-Warning: 命令仅为一个字母" << endl;
		else {
			switch (userCommand[0])
			{
			case 'a':
				if (textBuffer.empty())
				{
					cout << "-Warning: 文本缓存空 " << endl;
				}
				else {
					cout << "-共有："<< textBuffer.length() <<" 行" << endl;
					cout << "-共有：" << textBuffer.statistic() << " 字符" << endl;
				}
				break;

			case 'b':
				if (textBuffer.empty())
				{
					cout << "-Warning: 文本缓存空 " << endl;
				}
				else
				{
					curLineNo = 1;
					cout << "-已经返回第一行" << endl;
				}
				break;

			case 'c':
				if (textBuffer.empty())
				{
					cout << "-Warning: 文本缓存空" << endl;
				}
				else if (!changeLine())
				{
					cout << "-Warning: 替换失败 " << endl;
				}
				
				break;

			case 'd':
				if (!textBuffer.Delete(curLineNo))
				{
					cout << "-Error: 删除失败 " << endl;
				}
				else {
					cout << "-删除成功" << endl;
				}
				break;

			case 'e':
				if (textBuffer.empty())
				{
					cout << "-Warning: 文本缓存空 " << endl;
				}
				else
				{
					curLineNo = textBuffer.length();
					cout << "-已经移动到最后一行" << endl;
				}
				break;

			case 'f':
				if (textBuffer.empty())
				{
					cout << "-Warning: 文本缓存空 " << endl;
				}
				else
				{
					findString();
				}
				break;

			case 'g':
				if (!gotoLine())
				{
					cout << "-Warning: 没有该行" << endl;
				}
				break;

			case '?':
			case 'h':
				showHelp();
				break;

			case 'i':
				if (!insertLine())
					cout << "-Error：插入行出错 " << endl;
				break;
			case 'm':
				outInself();
				break;
			case 'n':
				if (!nextLine())
				{
					cout << "-Warning: 当前行已是最后一行" << endl;
				}
				break;

			case 'p':
				if (!previousLine())
				{
					cout << "-Warning: 当前行已是第一行" << endl;
				}
				break;

			case 'r':
				readFile();
				break;
			case 's':
				showCurline();
				break;
			case 'v':	// 显示文本v(iew)
				if (textBuffer.empty())
				{
					cout << "-Warning: 文本缓存空" << endl;
				}
				else
				{
					cout << "-整个文本为：" << endl;
					textBuffer.view();
				}
				break;

			case 'w':	// 写文本缓存到输出文件中w(rite)
				if (textBuffer.empty())
				{
					cout << "-Warning: 文本缓存空" << endl;
				}
				else
				{	// 写文本缓存到输出文件中
					writeFile();
				}
				break;
			default:
				cout << "输入h或?获得帮助或输入有效命令字符: \n";
			}
		}
	} while (userCommand[0] != 'q');
}
//-*-*-*-*-*-*-*-END RUN-*-*-*-*--*-*-*-*


//-*-*-*-*-*-*-*-  HELP  -*-*-*-*--*-*-*-*
void textEditor::showHelp() {
	cout << "-------------------help--------------------" << endl;
	cout << "命令(全称)    作用解释   " << endl;
	cout << " a (Analyze) 统计当前文本的信息" << endl;
	cout << " b (Begin)   移动到开始处" << endl;
	cout << " c (Change)  替换改行某一内容" << endl;
	cout << " d (Delete)  删除当前行并移动到下一行" << endl;
	cout << " e (End)     移动到结束行" << endl;
	cout << " f (Find)    查找包含目标串的第一行" << endl;
	cout << " g (Goto)    前往指定行" << endl;
    //help
	cout << " i (Insert)  在指定行插入单个新行" << endl;
	cout << " m (Memory)  保存修改后的文本" << endl;
	cout << " n (Next)    移动到当前行下一行" << endl;
	cout << " p (Previous)移动到当前行上一行 " << endl;
	cout << " q (Quit)    退出编辑器" << endl;
	cout << " r (Read)    读取文本" << endl;
	cout << " s (Show)    显示当前行内容" << endl;
	cout << " t (replace) 替换当前行内容" << endl;
	cout << " v (View)    查看全部内容" << endl;
	cout << " w (Write)   将缓冲区内容写入文本文件" << endl;
	cout << "----------------help End--------------------" << endl;
}
