#include <iostream>

using namespace std;

template<class T_>
void Knapsack(T_ v[],int w[],int c,int n,T_ m[])
{
	//v[]/w[] 每物品价值 /重量 
	//c背包容量，n物品个数，m最优值结果 
	//m[i][j] 表示背包容量为j ,可选物品为 {i,i+1,...,n}时的最优解
	int jMax = w[n]-1>c?c:w[n]-1;
	for(int j=0; j<=jMax; j++) m[n*(c+1)+j]=0;
	for(int j=w[n]; j<=c; j++) m[n*(c+1)+j] = v[n];
	for(int i=n-1; i>1; i--) {
		//计算第i物品，放入背包时的最优值。 
		jMax = w[i]-1>c?c:w[i]-1;
		for(int j=0; j<=jMax; j++) 
			m[i*(c+1)+j] = m[(i+1)*(c+1)+j];
		
		for(int j=w[i]; j<=c; j++) {
			T_ bb = (m[(i+1)*(c+1)+(j-w[i])]+v[i]);
			m[i*(c+1)+j] = m[(i+1)*(c+1)+j]>bb?m[(i+1)*(c+1)+j]:bb;
		}
		//只计算i=1时最后一个，节省一点计算 
		m[c+1+c]=m[2*(c+1)+c];
		if(c>=w[1]) {
			T_  cc = m[2*(c+1)+(c-w[1])]+v[1];
			m[c+1+c] = m[c+1+c]>cc?m[c+1+c]:cc;
		}
	}  
}

template<class T_>
void Traceback(T_ m[],int w[],int c,int n,int x[])
{
	//m[i][j] 表示背包容量为j ,可选物品为 {i,i+1,...,n}时的最优解
	//w[] 每物品价值 /重量 
	//c背包容量，n物品个数
	//x[]选择结果序列 
	int current_c=c;
	for(int i=1; i<n; ++i) {
		if(m[i*(c+1)+current_c] == m[(i+1)*(c+1)+current_c]) x[i] = 0;
		else {
			x[i]=1;
			current_c-= w[i];
		}
 	}
 	x[n]=(m[n*(c+1)+current_c])?1:0;
}




int main()
{
	int n=5;
	int c= 10;
	int w[]={0,2,2,6,5,4};
	int v[]={0,6,3,5,4,6};
	int m[(n+1)*(c+1)];
	Knapsack(v,w,c,n,m);
	cout<<"最优值 "<<m[c+1+c]<<endl;
	int x[5+1];
	Traceback(m,w,c,n,x);
	cout<<"Select: ";
	for(int i=1; i<=n; ++i) {
		cout<<x[i]<<' ';
	}
	cout<<endl;
	cin.get();
	return 0;
}
