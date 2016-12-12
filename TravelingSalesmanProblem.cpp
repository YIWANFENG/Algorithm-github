#include <iostream>

using namespace std;
template<class T_>
class TSP
{
private:
	int n;		//图的顶点数量 
	T_ *a;		//图的邻接矩阵 
	T_ NoEdge;	//无边标记
	
	int *x ;	//当前解
	T_ cc;		//当前耗费
	int *bestx;	//最优解、
	T_ bestc;	//最短路长
	
private:
	void Backtrack(int i) 
	{
		int itemp;
		if(i==n) {
			//检查当前解是否形成回路 
			if(a[x[n-1]*(n+1)+x[n]]!=NoEdge && a[x[n]*(n+1)+x[1]]!=NoEdge) {
				T_ ctemp = cc + a[x[n-1]*(n+1)+x[n]] + a[x[n]*(n+1)+x[1]];
				//回路长度是否更优 
				if(ctemp<bestc || bestc == NoEdge) {
					bestc = ctemp;
					for(int j=1; j<=n; ++j) bestx[j] = x[j]; 
				} 
			}
		} else {
			for(int j=i; j<=n; ++j) {
				//约束条件 
				if(a[x[i-1]*(n+1)+x[j]]!=NoEdge &&
					(cc + a[x[i-1]*(n+1)+x[j]] <bestc || bestc == NoEdge)) {
					itemp =x[i]; x[i] = x[j]; x[j] = itemp;
					cc += a[x[i-1]*(n+1)+x[i]];
					Backtrack(i+1);
					cc -= a[x[i-1]*(n+1)+x[i]];	
					itemp =x[i]; x[i] = x[j]; x[j] = itemp;		
				}
			}
		}
	}
public:
	T_ Solve(int n_,T_ *a_,T_ NoEdge_,int *v)
	{
		// n_;		//图的顶点数量 
		// a_;		//图的邻接矩阵 
		// NoEdge_;	//无边标记	
		// v (out)  最优解
		//返回最短路长
		n = n_;
		a = a_;
		NoEdge = NoEdge_;
		bestx = v;
		
		cc = 0;
		bestc=NoEdge;
		
		x = new int[n+1];
		for(int i=1;i<=n; ++i) x[i]=i;
		Backtrack(2);
		delete [] x;
		return bestc;		
	}
};


int main()
{
	int n=4;
	int NoEdge = 0x7fffffff;
	int a[] = {
		0,0,0,0,0,
		0,0,30,6,4,
		0,30,0,5,10,
		0,6,5,0,20,
		0,4,10,20,0
	};
	int v[5];
	TSP<int> tsp;
	int c = tsp.Solve(n,a,NoEdge,v);
	cout<<"最短路长"<<c<<endl;
	cout<<"路线:";
	for(int i=1; i<=n; ++i) 
		cout<<' '<<v[i];
	cout<<" 1"<<'\n';
	cin.get(); 
	return 0;
}
