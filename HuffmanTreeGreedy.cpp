#include <iostream>
#include <queue>
#include <vector>

//Huffman Encoding 
using namespace std;

class cmp {
public:
	bool operator() (const int &a,const int &b) {
		if(a>b) return true;
		return false;
	}
};

class CHuffmanChar {
public:
	char c_;			   //保存字符 
	CHuffmanChar *parent_; //指向父节点 
	int child_type_ ;		//1==left子节点  0 == right 
};

class CHuffmanChar_Heap {
public:
	int index_;			//原始编号 
	float weight_;		//权重 
	bool operator < (const CHuffmanChar_Heap &c2) const {
		return weight_ > c2.weight_;
	}
};

void HuffmanEncoding(int n, const char data[], float fre[])
{
	//Huffman编码 
	//n 字符数量 
	//data[] 原始字符 
	//fre[] 字符出现的频率 
	CHuffmanChar hc[n + n-1]; //中间出现节点数n-1 
	int i, j;
	for(i=0; i<n; ++i)
		hc[i].c_ = data[i];
	for(i=0; i<n+n-1; ++i)
		hc[i].parent_ = NULL;
	
	priority_queue<CHuffmanChar_Heap> q;
	CHuffmanChar_Heap h, hr;
	for(i=0; i<n; ++i) {
		h.index_= i;
		h.weight_ = fre[i];
		q.push(h);
	}
	
	for(i=0; i<n-1; ++i) {
		h = q.top();
		q.pop();
		hr = q.top();
		q.pop();
		hc[h.index_].parent_ = &hc[n+i];
		hc[h.index_].child_type_ = 1;
		hc[hr.index_].parent_ = &hc[n+i];
		hc[hr.index_].child_type_ = 0;
		h.weight_ += hr.weight_;
		h.index_ = n+i;
		q.push(h);
	}
	
	char code[n];
	for(i=0; i<n; ++i) {
		//从子节点寻根而上 
		j = 0;
		CHuffmanChar *pc = &hc[i];
		while(pc->parent_!=NULL) {
			code[j++]='1'-pc->child_type_;
			pc = pc->parent_;
		}
		cout<<hc[i].c_<<':';
		for(j--; j>=0; j--) {
			cout<<code[j];
		}
		cout<<'\n';
	}
	
} 

int main() {
	char c[] = {'a','b','c','d','e','f'};
	float f[] = {45,13,12,16,9,5};
	HuffmanEncoding(6,c,f);
	 	
	cin.get();
	return 0;
}
