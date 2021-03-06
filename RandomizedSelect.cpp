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
	if(k==j) return a[i]; 
	if(k<j) {		//分治，不过每次只计算一边 
		return RandomizedSelect<T_>(a,s,i-1,k);
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
int Location(T_ a[],int s,int e,T_ x) {
	int i=s, j=e+1;
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
template<class U_>
U_ Select_T(U_[], int s, int e, int k) {
	if(e-s<75) {
		sort(a,a+e,cmp<U_>); //某简单算法将a排序 
		return a[s+k-1];
	}
	for(int i=0;i<=(e-s-4)/5;++i) {
		//(e-s+1)/5 = 一共有多少分组 
		//(e-s-4)/5 = (e-s+1)/5-1 
		//将a[s+5*i]至a[s+5*i+4]的第三小元素与a[s+i]
		//Swap<U_>(a[s+i],?); 
		for(int j_1=s+5*i;j_1<s+5*i+5;++j_1) 
			for(int j_2=j_1+1;j_2<s+5*i+5;++j_2) 
				if(a[j_1]>a[j_2]) 
					Swap<U_>(a[j_1],a[j_2]);
		Swap<U_>(a[s+i],a[s+5*i+2]);
	}
	//交换位置，找到中位数的中位数
	U_ x = Select_T<U_>(a,s,s+(e-s-4)/5,(e-s-4)/10);
	int i = Location<U_>(a,s,e,x);//x在a[s]-a[e]的位置 
	int j=i-s+1;
	if(k==j) return a[i];
	if(k<j)
		return Select_T<U_>(a,s,i-1,k);
	else
		return Select_T<U_>(a,i+1,e,k-j);
} 

int main() {
	
	for(int i=0;i<100;++i) {
		a[i] = i;
	}
	
	int pp=0;
	cin>>pp;
	int j = 0;
	j = RandomizedSelect<int>(a,0,99,pp);
	int c = Select_T<int>(a,0,99,pp);
	cout<<j<<endl<<c<<endl;
		
	
	
	//sort(a,a+50,cmp<int>); //某简单算法将a排序 
	for(int i=0;i<100;++i) {
		cout<<a[i]<<' ';
	}
	
	cin>>pp;
	
	
	return 0;
} 
