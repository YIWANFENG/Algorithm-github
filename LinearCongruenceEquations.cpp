#include <iostream>

using namespace std;

/*	两种方法求解线性同余方程组
	1. 中国剩余定理
	2. 合并方程  
*/

#define LCM(a,b) (a)*(b)/gcd((a),(b))

int gcd(int a,int b) {
	int c = 0;
	if(a < b) {
		c = a;
		a = b;
		b = c;
	}
	if(!b) return a;
	while(a%b!=0) {
		c = a % b;
		a = b;
		b = c;
	}
	return b;
} 

int gcdEx(int a,int b,int &x,int &y) {
	//扩展欧几里得算法
	//求得aX + nY = gcd(a,n) 的一个(X,Y)
	if(b!=0) {
		int r = gcdEx(b,a%b,x,y);
		int t = x;
		x = y;
		y = t - a/b*y;
		return r;
	} else {
		x = 1;
		y = 0;
		return a;
	}
	
}


////////////////////////////////////////////////// 
//中国剩余定理求解线性同余方程组(不判断是否有解)
//////////////////////////////////////////////////
int linear_congruences(int a,int b,int n){
	//求得 ax = b (mod n) 
	if(b % gcd(a,n) == 0){
		int x,y,d,c,re;
		if (n>a) {
			c = a;
			a = n;
			n = c;
			d = gcdEx(a,n,x,y); 
			re = y*b/d;
			
		} else {
			d = gcdEx(a,n,x,y); 
			re = x*b/d;
		}	
		return re ;
	} else {
		return 0; 	//error
	}
}


void crh(int a[],int m[],int n) {
	//中国剩余定理求解线性同余方程组(不判断是否有解)
	//x = a1 (mod m1)
	//x = a2 (mod m2)
	// ...
	//x = a_n (mod m_n)
	int m_product = 1;
	int M[n];
	int t[n];
	int x=0;
	for(int i=0;i<n;i++)
		m_product *= m[i]; 
	for(int i=0;i<n;i++)
		M[i] = m_product / m[i]; 
	for(int i=0;i<n;i++) 
		t[i] = linear_congruences(M[i],1,m[i]);	
	for(int i=0;i<n;i++)
		x +=a[i]*t[i]*M[i];
	cout<<"通解"<<x<<"+"<<"Z*"<<m_product; 
}

//////////////////////////////////////////////////
//		合并方程求解线性同余方程组 
//////////////////////////////////////////////////
void linear_congruences2(int a,int b,int n){
	//求得 ax = b (mod n) 
	if(b % gcd(a,n) == 0){
		int x,y,d,c,re;
		if (n>a) {
			c = a;
			a = n;
			n = c;
			d = gcdEx(a,n,x,y); 
			re = y*b/d;
			cout<<"通解"<<re<<" + Z*"<<a/d<<endl;
		} else {
			d = gcdEx(a,n,x,y); 
			re = x*b/d;
			cout<<"通解"<<re<<" + Z*"<<n/d<<endl;
		}	
	} else {
		cout<<("No result")<<endl;
	}
}


void MergeEquations(int a[],int m[],int n) {
	//合并方程求解线性同余方程组 
	//x = a1 (mod m1)
	//x = a2 (mod m2)
	// ...
	//x = a_n (mod m_n)
	int A=a[0],M=m[0],x,y,k1_t;
	for (int i=1;i<n;i++) {
		gcdEx(M,m[i],x,y);
		k1_t = x;
		A = A - M*k1_t*(A-a[i]) / gcd(M,m[i]);
		M = LCM(M,m[i]);
	}
	linear_congruences2(1,A,M);
}


int main(int argc,char* argv[])
{
	int a[] = {2,3,2};
	int n[] = {3,5,7};
	crh(a,n,3);
	cout<<endl;
	MergeEquations(a,n,3);
    cin.get();
    return 0;
}

