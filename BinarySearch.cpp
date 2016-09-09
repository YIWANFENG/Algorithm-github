#include <iostream>
#include <cmath>
///分治
 
using namespace std;

///二分查找 

template<class T_> 
int BinarySearch(T_ Data[], const T_ val, int len) {
	//在0 -- len-1之间二分查找查找val 
	int left = 0, right = len-1, mid;
	while(left<=right) {
		mid = (left+right)/2;
		if(Data[mid]==val) return mid;
		else if(Data[mid]<val) left = mid+1;
		else right = mid-1; 
	}
	return -1;
} 

template<class T_>
int BinarySearch2(T_ Data[], const T_ val, int len) {
	int left = 0, right = len-1, mid;
	while(left<right) {
		mid = (left+right+1)/2;
		if(Data[mid]>val) right = mid-1;
		else left = mid;
	}
	if(val == Data[left]) return left;
	return -1;
} 

template<class T_>
int BinarySearch3(T_ Data[], const T_ val,int start, int end) {
	int mid = (start+end)/2;
	if(Data[mid] == val) return mid;
	else if (start == end) return -1;
	if(Data[mid]>val) 
		return BinarySearch3<T_>(Data, val, start, mid-1);
	else 
		return BinarySearch3<T_>(Data, val, mid+1, end);
} 


int main()
{
	int a[] = {1,2,3,4,5,7,6,8,9,10};
	cout<<BinarySearch<int>(a, 3, 10)<<endl;
	cout<<BinarySearch2<int>(a, 9, 10)<<endl;
	cout<<BinarySearch3<int>(a, 9, 0, 9)<<endl; 
	
	
	
	
	
	return 0;
}
