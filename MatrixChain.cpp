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

#include <iostream>


using namespace std;


const int n = 5;
int m[6][6],s[6][6]; 
int p[5]; 
  
 void MatrixChain(int *p, int n) { 
 	//p[i]为矩阵序列中矩阵[i]的行数==下一矩阵的列数
	//P[n]为最后矩阵的列数  
 	//n==矩阵数，m记录计算数量，s记录断开位置  
 	 
 	for(int i=1; i<=n; ++i) m[i][i]=0;//单个矩阵计算次数为0  
 	for(int r=2; r<=n; ++r) {         // 每一斜行  
 		for(int i=1;i <=n-r+1; ++i) {  //行开始  
 			int j=i+r-1;		       //行结束  
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


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
void MatrixChain_Traceback(int i,int j,int n,int *ss,int *rec) 
{
	//i,j :in子链开始及结束位置
	//n :in 矩阵的数量 
	//ss[] :in子链最优断开位置 
	//rec[] :out 每个矩阵左侧'('的数量以及右侧')'的数量 
	
	if(i==j) return ;
	int k=ss[i*(n+1)+j];
	MatrixChain_Traceback(i,k,n,ss,rec);
	MatrixChain_Traceback(k+1,j,n,ss,rec);
	if(i!=k) {
		rec[i+i]++;
		rec[k+k+1]++;	
	} 
	if(k+1!=j) {
		rec[k+k+2]++;
		rec[j+j+1]++;	
	}
}

void PrintResult(int n,int *rec) 
{
	//n :in 矩阵的数量 
	//rec[] :out 每个矩阵左侧'('的数量以及右侧')'的数量 
	
	for(int i=1;i<=n;++i) {
		for(int k=0;k<rec[i+i];k++) 
			cout<<'(';
		cout<<"A"<<i;
		for(int k=0;k<rec[i+i+1];k++) 
			cout<<')';
	}
}


int main0() 
{
	//int *s = new int[n+1][n+1];
	p[0]=10;	p[1]=20;	p[2]=10;	p[3]=30; 
 	p[4]=40; 
 	for(int i=0; i<=n; ++i) { 
 		for(int j=0; j<=n; ++j) { 
 			m[i][j]=0; 
 			s[i][j]=0; 
 		}
 	}
 	
	MatrixChain(p,n);
	int *rec  = new int[n+n+2];
	for(int i=2;i<=n+n+1;i++) rec[i] = 0;
	MatrixChain_Traceback(1,n,n,reinterpret_cast<int*>(s),rec);
	PrintResult(n,rec);
	cin.get();
	delete[] rec;
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////

