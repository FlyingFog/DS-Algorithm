#include <iostream>
#include <cstdio>
#include <string>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;

struct course{
	string name;
	int period , term;
};

class Course {
private:
	int totCou;
	course cou[40];
	vector<int >e[50];
	vector<string >proCourse[9];
	int in[50];
	int courseNum[10];
public:
	Course();
	~Course();
	void readdata();
	void work();
	void run();
};

Course::Course() {
	for(int i=0 ;i<=45 ;i++)
		e[i].clear();
	for (int i = 0; i <= 8; i++)
		proCourse[i].clear();
	memset(in, 0, sizeof(in));
}

Course::~Course() {
	for (int i = 0; i <= 45; i++)
		e[i].clear();
	for (int i = 0; i <= 8; i++)
		proCourse[i].clear();
	memset(in, 0, sizeof(in));
}

void Course::readdata() {
	ifstream fin("course_inf.txt");
	if (!fin)
		throw "打开文件失败，请检查course_inf.txt文件";
	string ids, name;
	int per, term;
	char sy;
	int id=0;
	for (int i = 1; i <= 8; i++)
		fin >> courseNum[i];
	
	while (fin >> ids >> name >> per >> term){
		id++;
		cou[id].name = name;
		cou[id].period = per;
		cou[id].term = term;
		if (term)proCourse[term].push_back(name);

		//specical check
		char ch;
		ch = fin.get();
		if (ch == '\n')continue;
		ch = fin.get();
		if (ch == '\n')continue;

		//build e
		string pre;
		while ((sy = fin.get()) != '\n'  && sy != -1) {
			int preid;
			fin >> pre;
			if(sy!='c')
				pre.erase(0,1);
			preid = atoi(pre.c_str());
			e[preid].push_back(id);
			in[id]++;
			char ch = fin.get();
			if (ch == '\n')break;
		}
	}
	totCou = id;
}


void Course::work() {
	ofstream fout("Timetable.txt");
	queue<int >q;
	for (int i = 1; i <= totCou; i++)
		if (in[i] == 0 && cou[i].term == 0)
			q.push(i);
	
	int curTerm = 1;
	int hadChose = 0;
	fout << "课表如下：";
	while (curTerm <= 8) {
		fout << endl;
		fout << "第" << curTerm << "学期：";
		
		for (size_t i = 0; i < proCourse[curTerm].size(); i++) {
			fout << proCourse[curTerm][i]<<"  ";
			hadChose++;
		}

		if (hadChose == courseNum[curTerm]) {
			hadChose = 0;
			curTerm++;
			continue;
		}

		while (!q.empty()) {
			int id = q.front();
			q.pop();
			for (size_t i = 0; i < e[id].size(); i++) {
				int v = e[id][i];
				in[v]--;
				if (in[v] == 0)q.push(v);
			}
			fout << cou[id].name << "  ";
			hadChose++;
			if (hadChose == courseNum[curTerm]) {
				hadChose = 0;
				curTerm++;
				break;
			}
		}
	}
}

void Course::run() {
	readdata();
	cout << "开始排课" << endl;
	work();
	cout << "排课完成，请在生成文件中查看" << endl;
	system("pause");
}

int main(){
	Course myCourse;
	try
	{
		myCourse.run();
	}
	catch (const char* msg) {
		cout << msg << endl;
	}
	
	return 0;
}
