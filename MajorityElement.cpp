#include <time.h> 
#include <stdlib.h>
#include <math.h>

#include <iostream>


//主元素问题-- 蒙特卡洛算法
using namespace std;

template <class T_>
bool Majority(const T_ *t,int n)
{
	srand(time(0));//取消后正确几率下降
	int i = rand()%n;
	T_ x = t[i];
	int k =0;
	for(int j=0;j<n;++j) {
		if(t[j]==x) k++;
	}
	return (k>n/2);
}

template <class T_>
bool MajorityMC(const T_*t,int n,double e)
{
	//e允许的最大错误几率 
	int k =ceil(-log(e)/log(2.0));
	for(int i=1;i<=k;++i) {
		if(Majority(t,n)) return true;
	}
	return false;
}



int main()
{

	srand(time(0));
	int i,n  = 10000;
	int *a = new int[n];
	for(i=0;i<n;++i) a[i] = i+1;
	int counter = 0 ;
	while (counter<n/2+1) {
		i = rand()%n;
		if(a[i]!=0) {
			a[i]=0;
			++counter;
		}
 	}
 	
 	for(i = 0;i<40;++i) {
 		if(MajorityMC(a,n,0.1)) 
 			cout<<true<<endl;
 		else
 			cout<<false<<endl;
    }
    
	cin.get();
	delete []a;
	return 0;
}
