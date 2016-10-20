#include <iostream> 
#include <cmath>

using namespace std;

//矩阵相乘序列，求解关于某种次序，矩阵相乘的所需乘发次数最少 

int m[6][6],s[6][6];
int p[5];

void MatrixChain(int *p, int n) {
	//p[i]为矩阵序列中矩阵[i]的行数==下一矩阵的列数 
	//n==矩阵数，m记录计算数量，s记录断开位置 
	
	for(int i=1; i<=n; ++i) m[i][i]=0;//单个矩阵计算次数为0 
	for(int r=2; r<=n; ++r) {         // 每一斜行 
		for(int i=1;i <=n-r+1; ++i) {  //行 
			int j=i+r-1;		       //列 
			m[i][j]=m[i+1][j]+p[i-1]*p[i]*p[j];
			s[i][j]=i;				   //在A[i:j]之间在s[i][j]开断 
			for(int k=i+1; k<j; ++k) {
				//求解本次分组(含有j-i个元素的分组)中最小的计算次数 
				int t=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(t<m[i][j]) {
					m[i][j] =t;
					s[i][j] = k;//加括号位置 
				}
			}
		}
	}
}

int RecurMatrixChain(int i,int j) {
	//递归式并采取备忘录方法 
	//需初始化m[i][j]=-1; 
	if(m[i][j]>0) return m[i][j]; //备忘记录，以此减少递归计算量 
	if(i==j) return 0;
	int u = RecurMatrixChain(i,i)+RecurMatrixChain(i+1,j)+p[i-1]*p[i]*p[j];
	s[i][j]=i;
	for(int k=i+1; k<j; ++k) {
		int t = RecurMatrixChain(i,k)+RecurMatrixChain(k+1,j)+p[i-1]*p[k]*p[j];
		if(t<u) {
			u = t;
			s[i][j]=k;
		}
	}
	m[i][j]=u;
	return u;
} 

void Traceback(int i,int j) {
	//A[i:n]最优加括号方式 (A[1:s[1][n]]) (A[s[1][n]+1:n])
	if(i==j) return ;
	Traceback(i,s[i][j]); 
	Traceback(s[i][j]+1,j);
	cout<<"Multiply A "<<i<<","<<s[i][j];
	cout<<" and A "<<(s[i][j]+1)<<","<<j<<endl;
} 

int main(int argc,char*argv[]) {
	p[0]=10;	p[1]=20;	p[2]=10;	p[3]=30;
	p[4]=40;
	for(int i=0; i<6; ++i) {
		for(int j=0; j<6; ++j) {
			m[i][j]=0;
			s[i][j]=0;
		}
	}
	MatrixChain(p,5);
	//RecurMatrixChain(1,5);
	Traceback(1,5);
	return 0;
}
