#include <iostream>
#include <algorithm>

//背包问题
 
using namespace std;
class Goods{
public:
	int i;//编号 
	float v,w;//价值，重量 
}; 
bool cmp(Goods a,Goods b) {
	if(a.v/a.w > b.v/b.w) return true;
	return false;
}
void printResult(Goods g[] ,float x[],int n) {
	for(int i=0;i<n;++i) {
		cout<<"seletc "<<x[i]<<" 份 "<<g[i].i<<endl; 
	}
}
void Knapsack(int n,float c,Goods g[],float x[]) 
	//背包问题 
{	//n物品总数，c背包总承重 
	//g[i].v=i的总价值，g[i].w=i 的总重量 
	//x[i] 选择i多少份 
	sort(g,g+n,cmp);
	int i;
	for(i=0;i<n;++i) x[i]=0;
	for(i=0;i<n;++i) {
		if(g[i].w>c) break;
		x[i]=1;
		c-=g[i].w;
	}
	if(i<=n) x[i]=c/g[i].w;
} 



int main()
{
	Goods a[10];
	for(int i=0;i<10;++i) a[i].i=i;
	float x[10]={0};
	a[0].w=10;a[0].v=60;	//6
	a[1].w=20;a[1].v=100;	//5
	a[2].w=30;a[2].v=120;	//4
	a[3].w=40;a[3].v=200;	//5
	
	Knapsack(4,50,a,x);
	printResult(a,x,4);
	getchar();
	return 0;
}
