#include<iostream>
#include<algorithm>
//贪心算法活动安排问题 
using namespace std;

//需要对输入的数据事先排序(nlog(n))
//函数本身为O(n) 
template<class T_> 
void GreedSelector(int n,T_ s[],T_ f[],bool ret[]) 
{ 
	//n:活动数量，s[i]:i活动起始时间，f[i]:i活动结束时间
	//s[i]与f[i]按照f[i]非递减序，ret[] 入选活动标志
	ret[0]=true;
	int j=0;
	for(int i=1; i<n; ++i) {
		if(s[i]>=f[j]) {
			ret[i]=true;
			j = i;
		} else {
			ret[i]=false;
		}
	}
}

void GetPlan(bool ret[],int n)
{
	cout<<"选择活动:";
	for(int i=0;i<n;++i){
		if(ret[i])
			cout<<i<<' ';
	}
	cout<<"End.\n";
} 


int main(int argc,char *argv[])
{
	int s[]={1,3,0,5,3,5,6,8,8,2,12};
	int f[]={4,5,6,7,8,9,10,11,12,13,14};
	bool ret[11];
	GreedSelector(11,s,f,ret);
	GetPlan(ret,11);
	getchar();
	return 0;
} 
