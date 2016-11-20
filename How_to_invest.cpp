#include <iostream>
#include <stdlib.h>
#include <memory.h>
using namespace std;
//整数线性规划 


const int my_n = 5;
const int my_all = 20; 



int m[my_n+1][my_all+1];		//m[i][j]为选择前i项，总资源为j时的最优回报值。
int X[my_n+1][my_all+1];	//X[i][j]该最由下投资第i物品多少单位 

void how_to_invest(int n,int all,int w[],int v[])
{
	//n个选项  all=所有资源 
	//x[i]/w[i]/v[i] 第i个项目 投资了多少单位/单位需求资源数/单位回报数 
	//m[i][j]为选择前i项，总资源为j时的最优回报值。  
	//X[i][j]该最由下投资第i物品多少单位 
	for(int i=1; i<=n; i++)  m[i][0]=0;
	for(int i=1; i<w[1]; i++)  m[1][i]=0;
	for(int i=w[1]; i<=all; i++) {
		m[1][i] = int(i/w[1])*v[1];
		X[1][i] = int(i/w[1]);
	}
	//for(int i=1; i<=all; i++) cout<<m[1][i]<<endl;
	for(int i=2; i<=n; i++) {
		//从前向后
		int Jmax = all<(w[i]-1)?all:w[i]-1;
		for(int j=1; j<=Jmax; j++) {  //j<w[i];
			m[i][j] = m[i-1][j];
			X[i][j]=0;
		}
		for(int j=w[i]; j<=all; j++) { //j>=w[i];
			//max{m(i-1,j-x*wi)+x*vi}(1<=x<=k)}
			int Mmax = 0;
			int k = int(j/w[i]);
			for(int x=w[i]; x<=k; x++) {
				if(Mmax<m[i-1][j-x*w[i]]+x*v[i]) {
					X[i][j]=x;
					Mmax = m[i-1][j-x*w[i]]+x*v[i];
				}
			}
			//max{ m(i-1,j) , max{m(i-1,j-x*wi)+x*vi}(1<=x<=k)}
			if(m[i-1][j]>Mmax) {
				m[i][j]=m[i-1][j];
				X[i][j]=0;
			} else {
				m[i][j] = Mmax;
			}
		}
	}
}


void TraceBack(int w[],int n,int all) {
	//n个选项  all=所有资源 
	if(X[n][all]==-1) return ;
	if(X[n][all]!=0) {
		cout<<"第"<<n<<"投资资源数"<<X[n][all]*w[n]<<endl;
	}
	TraceBack(w,n-1,all-X[n][all]*w[n]);
}

int main(int argc,char *argv[])
{
	memset(X,-1,sizeof(int)*(my_n+1)*(my_all+1));
	int w[] = {0,2,3,4,5,6};
	int v[] = {0,3,4,8,6,9};
	how_to_invest(my_n,my_all,w,v);
	cout<<"最大收益"<<m[my_n][my_all]<<endl;
	TraceBack(w,my_n,my_all);
	cin.get();
	return 0;
}
