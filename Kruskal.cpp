#include <iostream>
#include <queue>
#include <vector>

using namespace std;

//////////并差集实现的////////////////// 
class CUnionFind {
public:
	CUnionFind();
	~CUnionFind(); 
	void Init(int num_elem) ;
	
	int FindSubSet(int elem_id) ;
	
	void SubSetUnion(int set1,int ste2);
protected:
	int n_;			//元素数量 
	int *parent_id_;	//每个元素的父节点索引,-1表示该点为根节点
	int *depth_;		//每个元素所属子树的深度 
	void Release();
};

void CUnionFind::Release() {
	n_ = 0;
	if(parent_id_) {
		delete [] parent_id_;
		parent_id_ = NULL;
	}
		
	if(depth_) {
		delete [] depth_;
		depth_ = NULL;
	}
}

CUnionFind::CUnionFind() {
	n_ = 0;
	parent_id_ = NULL;
	depth_ = NULL; 
}
 
CUnionFind::~CUnionFind() {
	Release();
}
void CUnionFind::Init(int num_elem) {
	//元素编号从1开始
	Release();
	n_ = num_elem;
	parent_id_ = new int[n_];
	depth_ = new int[n_];
	for(int i=0;i<n_;++i) {
		parent_id_[i]=-1;
		depth_[i]=0;
	}
}
	
int CUnionFind::FindSubSet(int elem_id) {
	//返回元素elem_id所属自己的编号
	int i = elem_id-1;
	while(parent_id_[i]!=-1)
		i = parent_id_[i];
	return i;
}
void CUnionFind::SubSetUnion(int set1,int set2) {
	//合并set1,set2 
	if(set1 == set2) return ;
	if(depth_[set1]==depth_[set2]) {
		parent_id_[set2] = set1;
		depth_[set1]++;
	} else if(depth_[set1]<depth_[set2]){
		parent_id_[set1] = set2;
	} else {
		parent_id_[set2] = set1;
	}
}

///////////////////////////////////////////////// 


class Edge{
public:
	int weight;
	int u,v;
};
class cmp {
public:
	bool operator() (Edge &a,Edge&b) {
		return a.weight > b.weight;
	}
};


bool Kruskal(int n,int e,Edge E[],Edge t[]) 
{
	//n顶点数
	//e边数 
	//E[] 具体边 
	//t[](out) 筛选出的边
	
	priority_queue<Edge,vector<Edge>,cmp > q;
	for(int i=0; i<e; ++i) {
		q.push(E[i]);
	}
	CUnionFind U;
	U.Init(n);
	
	int k =0;
	while(e && k<n-1) {		//正常树应该会有n-1条边 
		Edge x;
		x = q.top();	
		q.pop();
		e--;
		int a = U.FindSubSet(x.u);
		int b = U.FindSubSet(x.v);
		
		if(a!=b) {
			t[k++] = x;
			//cout<<"["<<x.u<<','<<x.v<<"]"<<endl;
			U.SubSetUnion(a,b);
		}
	}
	
}
void Out(int n,Edge t[]) {
	//n顶点数
	// t[] 筛选出的边 
	for(int i=0;i<n-1;++i) {
		cout<<"["<<t[i].u<<','<<t[i].v<<"]"<<endl;
	}
}

int main() {
	int n = 6;
	Edge E[10];
	Edge t[10];
	E[0].u = 1;        E[1].u = 1;          E[2].u = 1;  
	E[0].v = 2;        E[1].v = 3;			E[2].v = 4;
	E[0].weight = 6;   E[1].weight = 1;     E[2].weight = 5;
	
	E[3].u = 3;        E[4].u = 5;          E[5].u = 3;  
	E[3].v = 2;        E[4].v = 2;			E[5].v = 4;
	E[3].weight = 5;   E[4].weight = 3;     E[5].weight = 5;
	
	E[6].u = 3;        E[7].u = 3;          E[8].u = 4;  
	E[6].v = 5;        E[7].v = 6;			E[8].v = 6;
	E[6].weight = 6;   E[7].weight = 4;     E[8].weight = 2;
	
	E[9].u = 5;
	E[9].v = 6;
	E[9].weight = 6;
	
	Kruskal(n,10,E,t);
	Out(n,t);
	cin.get();
	return 0;
}
