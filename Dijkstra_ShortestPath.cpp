#include <iostream>
#include <vector>

//Dijkstra最短路径求解 
 
using namespace std;

template <class T_> 
void Dijkstra_ShortestPath(int n,int v,T_ dist[],int prev[],
						const T_ *c,const T_ INF) 
{
	//n：(in)顶点数量
	//v：(in)源顶点索引 （0-...）
	//dist[]"(out) 从源定点 到每个定点的距离
	//prev[]：(out) 在最短路径上每个定点的前面的一个顶点 
	//c(in)：两个顶点间的距离
	bool s[n]; // s[i]表示该点是否在最短路径已知的顶点集合内。 
	for(int i=0;i<n;i++) s[i] = false;
	
	for(int i=0; i<n; ++i) {
		dist[i]=c[v*n+i];
		if(dist[i]==INF) prev[i] = -1;
		else prev[i]=v;
	}
	//add v to s
	dist[v] = 0;
	s[v] = true;
	
	for(int i=1; i<n; ++i) {
		T_  dist_tmp = INF;
		int u = v;
		//选出该次到v最短的点，该点不属于s 
		for(int j=0; j<n; ++j) {
			if(s[j]) continue;
			if(dist_tmp==INF || dist[j]<dist_tmp) {
				dist_tmp = dist[j];
				u = j;
			}
		}
		s[u] = true;
		//加入该点后对其他点的影响 
		for(int j=0; j<n; ++j) {
			if(s[j] || c[u*n+j]==INF) continue;
			T_ dist_new = dist[u]+c[u*n+j];
			if(dist_new<dist[j]) {
				dist[j]=dist_new;
				prev[j] = u;
			}
		}
	}
}  



template<class  T_>
void Out(int n,int v,T_ dist[],int prev[]) 
{
	//n：(in)顶点数量
	//v：(in)源顶点索引 （0-...）
	//dist[]"(out) 从源定点 到每个定点的距离
	//prev[]：(out) 在最短路径上每个定点的前面的一个顶点 
	int path_points[n*(n-1)/2+1];
	int i,j,k;
	for(i=0; i<n; ++i) {
		if(i==v) continue;
		cout<<"顶点"<<i<<",最短路径长度="<<dist[i]<<endl;
		
		j=1;
		path_points[0] =i;
		k = i;
		while(prev[k]!=v && prev[k]!=-1) {
			path_points[j++] = prev[k];
			k=prev[k];
		}
		for(--j; j>=0; j--) {
			cout<<path_points[j] <<" ";
		}
		cout<<endl;
	}
	
}

int main() {
	
	int n=5;
	const float  INF = 65535;
	float dist[n];
	int prev[n];
	float c[n*n];
	const float graph_edges[] = {
		0,10,INF,30,100,
		10,0,50,INF,INF,
		INF,50,0,20,10,
		30,INF,20,0,60,
		100,INF,10,60,0
	};
	for(int i=0;i<n*n;i++) {
		c[i]=graph_edges[i];
	}
	
	Dijkstra_ShortestPath<float>(n,0,dist,prev,c,INF);
	Out<float>(n,0,dist,prev);
	
	
	cin.get();
	return 0;
}
