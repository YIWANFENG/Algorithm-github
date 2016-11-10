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

int MaxSubSum(int *a,int left,int right) 
{
	//分治法 
	int sum = 0;
	if(left == right) sum = a[left]>0?a[left]:0;
	else {
		int center =(left+right) / 2;
		int leftsum = MaxSubSum(a,left,center);
		int rightsum = MaxSubSum(a,center+1,right);
		int s1 = 0;
		int lefts = 0;
		for(int i=center;i>=left;i--) {
			lefts +=a[i];
			if(lefts>s1) s1 = lefts;
		}
		int s2 = 0;
		int rights = 0;
		for(int i=center+1;i<=rights;++i) {
			rights+=a[i];
			if(rights>s2) s2=right;
		}
		sum = s1+s2;
		if(sum<leftsum) sum = leftsum;
		if(sum<rightsum) sum = rightsum;
	} 
	return sum;
}

int MaxSubSum(int n,int *a,int &istart,int &iend) 
{
	//n元素数
	//a求解最大字段和的数组 
	//start end最大字段和的起始与终止位置
	//返回最大字段和 
	int b[n+1];//b[i]是a[i]结尾的所有字段和的最大值 
	int d[n+1];
	
	int sum = 0;
	b[0]=0;
	for(int i=1;i<=n;i++) {
		if(b[i-1]>0) {
			b[i]=b[i-1]+a[i];
			d[i]=1;
		} else {
			b[i]=a[i];
			d[i]=2;
		}
		if(sum<b[i]) {
			sum = b[i];
			iend = i;
		}
	}
	istart =iend;
	while(istart>0&&d[istart]==1) istart--;
	return sum;
}

int main() 
{
	
	int a[] = {0,-1,2,3,45,-34,15,33,-24};
	int i,j;
	cout<<"最大字段和："<<MaxSubSum(sizeof(a)/sizeof(int)-1,a,i,j)<<endl;
	cout<<"最大字段从"<<i<<"到"<<j<<endl; 
	cin.get();
	return 0;
} 



