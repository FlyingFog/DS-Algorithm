#include <cstdio> 
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>
#include <cassert>
#include <stdexcept>
#include <iostream>
using namespace std;

struct HuffmanTree {
	char c; // char
	int cfreq; // frequency of c.
	HuffmanTree *left;
	HuffmanTree *right;
	
	HuffmanTree(char c, int cfreq, HuffmanTree *left = NULL, HuffmanTree *right = NULL) :
		c(c), cfreq(cfreq), left(left), right(right) {}
	
	~HuffmanTree() {
		delete left, delete right;
	}
	// define Compare in priority_queue
	struct Compare{
		bool operator()(HuffmanTree *a, HuffmanTree *b) {
			return a->cfreq > b->cfreq;
		}
	};
};
//文件
ofstream fout;
ifstream fin;

//-------二进制位输入输出------
void bitpri1(int x) {
	int a[1];
	a[0] = x;
	fout.write(reinterpret_cast<const char*>(a), 1);
}

void bitpri2(int x) {
	int a[1];
	a[0] = x;
	fout.write(reinterpret_cast<const char*>(a), 2);
}

void bitpri4(int x) {
	int a[1];
	a[0] = x;
	fout.write(reinterpret_cast<const char*>(a), 4);
}

int bitread1() {
	unsigned char a;
	fin.read(reinterpret_cast<char*>(&a), 1);
	return a;
}

int bitread2() {
	short int a;
	fin.read(reinterpret_cast<char*>(&a), 2);
	return a;
}

int bitread4() {
	int a;
	fin.read(reinterpret_cast<char*>(&a), 4);
	return a;
}
//-------------finish------------------


typedef vector<bool> code_t;         //01编码
typedef map<char, code_t> codeTable; //编码表

vector< pair<char, unsigned> > make_freqTable(string inp) {
	map<char, unsigned> cfmap;
	vector< pair<char, unsigned> >cfvec;

	for (unsigned i = 0; i < inp.size(); i++) {
		if (cfmap.find(inp[i]) == cfmap.end()) {
			cfmap.insert(make_pair(inp[i], 1));
		}
		cfmap[inp[i]] += 1;
	}

	for (auto it = cfmap.begin(); it != cfmap.end(); ++it) {
		cfvec.push_back(make_pair(it->first, it->second));
	}

	return cfvec;
}

HuffmanTree *build_tree(vector< pair<char, unsigned> > &alph) {
	//build a min-heap
	priority_queue<HuffmanTree *, vector<HuffmanTree *>, HuffmanTree::Compare > min_heap;
	for (auto it = alph.begin(); it != alph.end(); ++it) {
		HuffmanTree *leaf = new HuffmanTree(it->first, it->second);
		min_heap.push(leaf);
	}
	//build tree  
	HuffmanTree *root = NULL;
	//last is the root
	while (min_heap.size() > 1) {
		HuffmanTree *l, *r;
		l = min_heap.top();
		min_heap.pop();
		r = min_heap.top();
		min_heap.pop();
		root = new HuffmanTree(0, l->cfreq + r->cfreq, l, r);
		min_heap.push(root);
	}
	return root;
}

code_t encode(string input, codeTable &lookup) {
	code_t result;

	for (auto it = input.begin(); it != input.end(); ++it) {
		code_t b = lookup[*it];
		result.insert(result.end(), b.begin(), b.end());
	}
	return result;
}

char code_lookup(code_t::iterator &biter, const code_t::iterator &biter_end,
	const HuffmanTree *htree) {
	const HuffmanTree *node = htree;

	while (true) {
		if (!node->left) {
			break;
		}
		if (biter == biter_end) {
			throw std::out_of_range("None");
		}
		if (*biter) {
			node = node->right;
		}
		else {
			node = node->left;
		}
		++biter;
	}
	return node->c;
}

string decode(code_t &compresse, const HuffmanTree *htree) {
	string result;

	auto bite = compresse.begin();
	while (true) {
		try {
			result += code_lookup(bite, compresse.end(), htree);
		}
		catch (const std::out_of_range &oor) { //out-of-range
			break;
		}
	}
	return result;
}

map<char, code_t> build_code_table(HuffmanTree *htree) {
	codeTable lookup;
	deque< pair<HuffmanTree*, code_t> > q;

	q.push_back(make_pair(htree, code_t()));
	while (!q.empty()) {
		HuffmanTree *node, *lc, *rc;
		code_t code;
		node = q.front().first;
		code = q.front().second;
		q.pop_front();
		lc = node->left;
		rc = node->right;
		if (lc) {
			code_t code_cp(code);
			q.push_back(make_pair(lc, (code.push_back(0), code)));
			q.push_back(make_pair(rc, (code_cp.push_back(1), code_cp)));
		}
		else {
			lookup.insert(make_pair(node->c, code));
			//编码表
			/*
			cout << "(" << node->c << "  ";
			for (size_t i = 0; i < code.size(); i++) {
				cout << code[i];
			}
			cout << ")" << endl;
		    */
		}
	}
	return lookup;
}

string bitvec_to_string(code_t &bitvec) {
	string result;
	size_t nbits;

	nbits = bitvec.size() & 7;

	// at most 7bits
	result += static_cast<char>(nbits);

	char byte = 0;
	for (unsigned i = 0; i < bitvec.size(); i++) {
		unsigned boff = i & 7;
		byte |= bitvec[i] << boff;
		if (boff == 7) {
			// Write a byte
			result += byte;
			byte = 0;
		}
	}
	if (nbits) {
		result += byte;
	}
	return result;
}


code_t string_to_bitvec(string packed) {
	code_t result;

	assert(packed.size());
	if (packed.size() == 1) {
		assert(packed[0] == 0);
		return result;
	}
	unsigned nbits = packed[0];
	for (auto it = packed.begin() + 1; it != packed.end(); ++it) {
		for (unsigned i = 0; i < 8; i++) {
			result.push_back((*it >> i) & 1);
		}
	}
	// the last byte
	if (nbits) {
		for (unsigned i = 0; i < (8 - nbits); i++) {
			result.pop_back();
		}
	}
	return result;
}


int main() {		
	cout << "操作提示：" << endl;
	cout << "1->编码" << endl;
	cout << "2->解码" << endl;
	cout << "3->退出" << endl;
	string op;
	cout << "请输入操作码：" ;
	cin >> op;
	while (op.size() != 1) {
		cout << "请输入正确的操作码：";
		cin >> op;
	}
	while (op[0] != '3')
	{
		bool hadOp = 0;
		char input[128], output[128];
		cout << "输入文件名：";
		cin >> input;
		cout << "输出文件名：";
		cin >> output;
		if (op[0] == '1') {
			hadOp = 1;
			fin.open(input);
			fout.open(output, ios::binary);
			string s = "", line;
			while (getline(fin, line))
			{
				s = s + line;
				s = s + "\n";
			}
			s = s.substr(0, s.length() - 1);
			vector< pair<char, unsigned> > cfvec = make_freqTable(s); // char freq vector
			//build tree
			HuffmanTree *htree = build_tree(cfvec);       // huffmanTree
			codeTable ctbl = build_code_table(htree);   //codeTable
			//encode
			code_t t = encode(s, ctbl);                
			string packed = bitvec_to_string(t);          
			bitpri2(cfvec.size());
			for (auto it = cfvec.begin(); it != cfvec.end(); it++) {
				bitpri1(it->first);
				bitpri4(it->second);
			}
			for(size_t i=0 ;i<packed.size() ;i++)
				fout.put(packed[i]);
			cout << "编码完成" << endl;
			delete htree;
			fin.close();
			fout.close();
		}
		if (op[0] == '2') {
			hadOp = 1;
			fin.open(input ,ios::binary);
			fout.open(output);
			vector< pair<char, unsigned> > cfvec;
			unsigned num = bitread2();
			for (unsigned i = 1; i <= num; i++) {
				int c = bitread1();
				int fre = bitread4();
				cfvec.push_back(make_pair(c, fre));
			}
			HuffmanTree *htree = build_tree(cfvec);
			codeTable ctbl = build_code_table(htree);
			string p1;
			getline(fin ,p1);
			code_t t1 = string_to_bitvec(p1);
			string s1 = decode(t1, htree);
			for(size_t i = 0; i < s1.size(); i++)
				fout << s1[i];
			cout << "译码完成" << endl;
			delete htree;
			fin.close();
			fout.close();
		}
		if(hadOp)
		cout << endl <<"请输入操作码：";
		else cout << endl << "请输入正确的操作码：";
		cin >> op;
		while (op.size() != 1) {
			cout << "请输入正确的操作码：";
			cin >> op;
		}
	}
	return 0;
}
