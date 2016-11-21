#include <iostream>
#include <queue>
#include <vector>

using namespace std;


class Edge{
public:
	int weight;
	int u,v;
};

bool cmp(Edge &a,Edge&b) {
	return a.weight < b.weight;
}

bool Kruskal(int n,int e,Edge E[],Edge t[]) 
{
	priority_queue<Edge,vector<Edge>,cmp > q;
	for(int i=0; i<n; ++i) {
		q.push(Edge[i]);
	}
	CUnionFind U(n);
	
	int k =0;
	while(e && k<n-1) {
		Edge x;
		x = q.top();
		q.pop();
		e--;
		int a = U.FindSubSet(x.u);
		int b = U.FindSubSet(x.v);
		
		if(a!=b) {
			t[k++] = x;
			U.SubSetUnion(a,b);
		}
	}
	
}
int main() {
	int n = 10;
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
	
	Kruskal(n,e,E,t);
	
	cin.get();
	return 0;
}
