#include <iostream> 


//凸多边形最优三角剖分 
//2016-11-3
//矩阵链相乘是一种特殊的凸多边形最优三角剖分 
using namespace std;
const int N = 7;





int weight(int i,int j,int k) {
	//根据题意决定
	//这里我随便 
	return abs(k+k-i-j); 
} 

void MinWeightTri(int n, int t[][N+1],int s[][N+1])
{
	//计算n+1边形关于weight的最优划分
	//t[i][j] {Vi..Vj}多边形权值
	//s[i][j] 划分使用的顶点
	for(int i=1;i<=n;i++) t[i][i]=0; 	//退化多边形设置 
	for(int r=2;r<=n;r++) {				//每斜行 
		for(int i=1;i<=n-r+1;++i) {		
			int j = i+r-1;
			t[i][j]=t[i][i]+t[i+1][j]+weight(i-1,i,j);
			s[i][j]=i;
			for(int k=i+1;k<i+r-1;++k) {//该层最优 
				int u=t[i][k]+t[k+1][j]+weight(i-1,k,j);
				if(u<t[i][j]) {
					t[i][j]=u;
					s[i][j]=k;
				}
			}	
		}
	}	
} 

void Traceback(int i,int j,int s[][N+1]) {
	//输出选择的构成三角的顶点 
	if(i==j) return ;
	Traceback(i,s[i][j],s); 
	cout<<s[i][j]<<" ";
} 

int main(int argc,char *argv[])
{
	
	int  t[N+1][N+1];
	int s[N+1][N+1];
	MinWeightTri(N,t,s);
	Traceback(1,N,s);
	
	cin.get(); 
	return 0;
}
