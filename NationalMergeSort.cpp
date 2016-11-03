#include <iostream>
//#include <cmath>
//分治

using namespace std;

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
void NaturalMergePass(T_ x[], T_ y[],int seg_i0[], int s ,int nseg) {
	//将 
	int i=0;
	while(i<=nseg-s-s) {
		//合并大小为s的相邻两端子数组
		Merge(x,y,seg_i0[i],seg_i0[i+s]-1,seg_i0[i+s+s]-1);
		i=i+s+s; 
	}
	//剩下元素个数少于2s
	if(i+s<nseg) Merge(x,y,seg_i0[i],seg_i0[i+s]-1,seg_i0[nseg]-1);
	else {
		for(int j=seg_i0[i];j<=seg_i0[nseg]-1;++j) {
			y[j] = x[j];
		}
	}
}
template<class T_>
int getSort(T_ a[],int n,int seg_i0[]) {
	seg_i0[0]=0;
	int k=1;
	for(int i=1;i<n;++i) {
		if(a[i]<a[i-1])
			seg_i0[k++] = i;
	}
	seg_i0[k]=n;
	return k;
}

template<class T_>
void NaturalMergeSort(T_ a[],int n) {
	T_ *b = new T_[n];
	int s = 1;
	int seg_i0[n+1];
	int nseg=getSort(a,n,seg_i0);
	
	
	while(s<nseg) {
		NaturalMergePass(a,b,seg_i0,s,nseg);	//合并到数组b
		s += s;
		NaturalMergePass(b,a,seg_i0,s,nseg);	//合并到数组a
		s += s;
	}
	
	delete[] b;
}


int main()
{
	int a[]={2,5,1,2,5,5,15,78,15,64,32,124,55,122};
	
	NaturalMergeSort<int>(a,sizeof(a)/sizeof(int));
	for(int i=0;i<sizeof(a)/sizeof(int);++i)
		cout<<a[i]<<' ';
	getchar();
	return 0;
} 


