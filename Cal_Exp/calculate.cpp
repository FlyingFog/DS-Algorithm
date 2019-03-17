#include "pch.h"

calculator::calculator(){
	clear();
}
calculator::~calculator() {
	clear();
}

void calculator::clear() {
	while (opnd.size())opnd.pop();
	while (optr.size())optr.pop();
}

bool calculator::read() {
	cout << "请输入表达式（以 = 结束）：" << endl;
	cin >> expression;
	if (expression[expression.length() - 1] != '=')return 0;
	const string other = "!@#$%qwertyuiopasdfghjklzxcvbnm";
	int p = -1;
	if ((p = expression.find_first_of(other,0)) >= 0 )return 0;
	return 1;
}

int calculator::judgePri(char a, char b) {
	int lp, rp;
	//check leftPri
	if (a == '+' || a == '-')lp = 3;
	if (a == '*' || a == '/')lp = 5;
	if (a == '(')lp = 1;
	if (a == ')')lp = 7;
	if (a == '=')lp = 0;

	if (b == '+' || b == '-')rp = 2;
	if (b == '*' || b == '/')rp = 4;
	if (b == '(')rp = 6;
	if (b == ')')rp = 1;
	if (b == '=')rp = 0;

	if (lp > rp)return 1;
	if (lp == rp)return 0;
	if (lp < rp)return -1;
}

double calculator::calTwoNum(double a, char c, double b) {
	switch (c)
	{
	case '+': {
		return a + b;
	}
	case '-': {
		return a - b;
	}
	case '*': {
		return a * b;
	}
	case '/': {
		if (b - 0 < 1e-9)throw "除数不能为0，运算出错。";
		else {
			return a / b;
		}
	}
	default: {
		return 0.0;
	}
	}
}

void calculator::cal() {
	const string op = "+-*/()=";
	while (true){
		clear();
		int p1 = -1;
		if (!read()) {
			if (expression == "exit")break;
			else
				cout << "请输入正确的表达式（ = 结尾）" << endl;
		}
		else {
			optr.push('=');
			bool flag = 0;
			while (true){
				int p2 = p1 + 1;
				p1 = expression.find_first_of(op, p1 + 1);
				if (p1 == string::npos)break;
				if (expression[p1] == '-' && (p1 == 0 || !isdigit(expression[p1-1]))) {
					flag = 1;
					continue;
				}
				if (p1 != p2) {
					int sump = 0;
					bool right = 1;
					string snum(expression, p2, p1 - p2);
					for (int i = 0; i < snum.size(); i++) {
						if (!isdigit(snum[i]) && snum[i] != '.')right = 0;
						if (snum[i] == '.')sump++;
					}
					if (right == 0 || sump > 1) {
						cout << "表达式错误" << endl;
						break;
					}
					double d = atof(snum.c_str());
					if (flag) {
						d = d * (-1);
						flag = 0;
					}
					opnd.push(d);
				}
				int Pri = judgePri(optr.top(), expression[p1]);
				switch (Pri)
				{
				case -1: {
					optr.push(expression[p1]);
					break;
				    }
				case 0: {
					optr.pop();
					break;
				}
				case 1: {
					double n1 = opnd.top();
					opnd.pop();
					double n2 = opnd.top();
					opnd.pop();
					char c = optr.top();
					optr.pop();
					double cur = calTwoNum(n2, c, n1);
					opnd.push(cur);
					p1--;
				}
				default:
					break;
				}
			}
		}
		if (opnd.size())
			cout << "计算结果为：" << opnd.top() << endl << endl;
	}
}




/*  
    bool calculator::isdigit(char c) {
	if (c >= '0' && c <= '9')return 1;
	return 0;
}

	while (c != '=' || optr.top() != '=') {
		//如果是数字
		if(isdigit(c)){
			string num;
			num = num + c;
			while (isdigit(c = getchar()) || c == '.') {
				num = num + c;
			}
			opnd.push(atof(num.c_str()));
}*/ 