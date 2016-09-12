#include <iostream>
//#include <cmath>
//分治

using namespace std;

/*//算法递归描述 
template<class T_>
void MergeSort(T_ a[], int left, int right) {
	if(left<right) { //至少2个元素 
		int i = (left+right)/2;
		MergeSort(a,left,i);
		MergeSort(a,i+1,right);
		Merge(a,b,left,i,right);//合并到数组 b
		Copy(a,b,left,right);//复制回数组a 
	}
}
*/
template<class T_>
void Merge(T_ c[],T_ d[],int l, int m, int r) {
	//合并c[l:m] 和 c[m+1:r]到d[l:r]
	int i=l,j=m+1,k=l;
	while(i<=m && j<=r) {
		if(c[i] <= c[j])
			d[k++] = c[i++];
		else 
			d[k++] = c[j++]; 
	}
	if(i>m) {
		for(int q=j;q<=r;q++) 
			d[k++] = c[q];
	}
	else {
		for(int q=i; q<=m; q++)
			d[k++] = c[q]; 
	}
}

template<class T_>
void MergePass(T_ x[], T_ y[],int s ,int n) {
	int i=0;
	while(i<=n-2*s) {
		//合并大小为s的相邻两端子数组
		Merge(x,y,i,i+s-1,i+2*s-1);
		i=i+2*s; 
	}
	//剩下元素个数少于2s
	if(i+s<n) Merge(x,y,i,i+s-1,n-1);
	else {
		for(int j=i;j<=n-1;++j) {
			y[j] = x[j];
		} 
	}
}

template<class T_>
void MergeSort(T_ a[],int n) {
	T_ *b = new T_[n];
	int s = 1;
	while(s<n) {
		MergePass(a,b,s,n);	//合并到数组b
		s += s;
		MergePass(b,a,s,n);	//合并到数组a
		s += s; 
	}
	delete[] b;
}



int main()
{
	int a[]={2,5,1,4,7,8,3,1,2,45,15,21,45,78,15,64,32,124,55,122};
	MergeSort<int>(a,18);
	for(int i=0;i<18;++i)
		cout<<a[i]<<' ';
	return 0;
} 
