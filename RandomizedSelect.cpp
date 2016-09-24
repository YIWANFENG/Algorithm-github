#include <iostream>
#include <cmath> 
#include <stdlib.h>
#include <ctime>
#include <algorithm>
//线性时间查找


using namespace std;

int a[100];
///////////////////////////////////
///////一般来说此法时间复杂度O(N)//
///////////////////////////////////
template<class T_> 
void Swap(T_ &a,T_ &b) {
	T_ it = a;
	a = b;
	b = it;
}
template<class T_>
int Partition(T_ a[],int s,int e) {
	int i=s, j=e+1;
	T_ x = a[s];
	//将 < x 的所有元素移到左边
	//将 > x 的所有元素移到右边 
	while(true) {
		while(a[++i]<x&&i<e);
		while(a[--j]>x);
		if(i>=j) break;
		Swap<T_>(a[i],a[j]);
	}
	a[s] = a[j];
	a[j] = x;
	return j;//返回中间位置(严格来说这并不是中间数)
}
template<class T_> 
int RandomizedPartition(T_ a[], int s,int e) {
	srand(time(NULL));
	int i = 0;
	i = rand()%(e-s)+s;
	Swap<T_>(a[i],a[s]);
	return Partition<T_>(a,s,e); 
}

template<class T_>
T_ RandomizedSelect(T_ a[],int s,int e,int k) {
	if(s==e) return a[s];
	int i = RandomizedPartition<T_>(a,s,e);	//获得中间某值元素位置 
	int j = i-s+1;
	if(k<=j) {		//分治，不过每次只计算一边 
		return RandomizedSelect<T_>(a,s,i,k);
	} else {
		return RandomizedSelect<T_>(a,i+1,e,k-j);
	}
	
}

///////////////////////////////////
///////此法最差时间复杂度O(N)//////
///////////////////////////////////

template<class T_>
bool cmp(T_ a,T_ b) {
	if(a<=b)
		return true;
	return false;
}

template<class T_>
T_ Select(T_　a[],int s,int e,int k) {
	if(e-s<75) {
		sort(a,a+e,cmp<T_>); //某简单算法将a排序 
		return a[s+k-1];
	}
	for(int i=0;i<=(e-s-4)/5;++i) {
		//将a[s+5*i]至a[s+5*i+4]的第三小元素与a[s+i]
		//Swap<T_>(a[s+i],); 
	}
	//交换位置，找到中位数的中位数
	T_ x = Select<T_>(a,s,s+(e-s-4)/5,(e-s-4)/10);
	int i = Partition<T_>(a,s,e,x),j=i-s+1;
	if(k<=j) 
		return Select<T_>(a,s,i,k);
	else
		return Select<T_>(a,i+1,e,k-j);
	
} 


int main() {
	
	for(int i=0;i<100;++i) {
		a[i] = i;
	}
	
	int pp=0;
	cin>>pp;
	int j = RandomizedSelect<int>(a,0,99,pp);
	int c = Select<int>(a,0,99,pp);
	cout<<j<<endl<<c;
	cin>>pp;
	
	
	return 0;
} 
