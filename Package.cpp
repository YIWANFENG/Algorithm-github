#include <iostream>


//0-1背包问题
 
using namespace std;


void Knapsack(int n,float c,float v[],float w[],float x[]) 
	//背包问题 
{	//n物品总数，c背包总承重 
	//v[i] i的总价值，w[i] i 的总重量 
	//x[i] 选择i多少份 
	int i;
	for(i=0;i<n;++i) x[i]=0;
	for(i=0;i<n;++i) {
		if(w[i]>c) break;
		x[i]=1;
		c-=w[i];
	}
	if(i<=n) x[i]=c/w[i];
} 

void printResult(float x[],int n) {
	for(int i=0;i<n;++i) {
		cout<<"seletc "<<x[i]<<" 份 "<<i<<endl; 
	}
}

int main()
{
	
	
	
	return 0;
}
