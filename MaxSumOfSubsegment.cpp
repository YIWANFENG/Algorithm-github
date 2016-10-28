#include <iostream>
#include <algorithm>

//最大子段和 
using namespace std;


int MaxSum(int n,int a[],int &start,int &end) 
{
	//遍历法求最大子段和 
	//n元素数，a元素数组 
	//start选中的字段开始元素下标 
	//end选中的字段结束元素下标 
	int sum=0;
	for(int i=0;i<=n;++i) {
		int this_sum = 0;
		for(int j=i;j<=n;++j) {
			this_sum += a[j];
			if(this_sum>sum) {
				sum  = this_sum;
				start = i;
				end = j;
			}
		}
	}
	return sum;
}

int MaxSum(int n,int a[]) 
{
	//动态规划求最大子段和 
	int sum = 0,b= 0;
	for(int i=0;i<n;++i) {
		if(b>0) b+=a[i];
		else b = a[i];
		if(b>sum) sum = b;
	}
	return sum;
} 


int main() 
{
	int a[] = {1,2,-11,15,6,-5,-6,8,10,-12};
	int start,end;
	cout<<MaxSum(sizeof(a)/sizeof(int),a,start,end)<<endl;
	cout<<start<<' '<<end<<endl;
	cout<<MaxSum(sizeof(a)/sizeof(int),a)<<endl;
	getchar(); 
	return 0;
}
