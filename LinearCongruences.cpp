#include <iostream>

using namespace std;

//解决线性同余问题 
//包含扩展欧几里得算法 
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


void linear_congruences(int a,int b,int n){
	//ax = b (mod n)
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

void POJ() {
	int X,Y,M,N,L,a,n,b;
	cin>>X>>Y>>M>>N>>L;
	a = (M-N);
	n = L ;
	b = -(X-Y); 
	if(b%gcd(a,n)==0) {
		
		int x,y,d,c,re;
		if (n>a) {
			c = a;
			a = n;
			n = c;
			d = gcdEx(a,n,x,y); 
			re = y*b/d;
			while(re>0) re-=abs(a/d);
			re+=abs(a/d);
			cout<<re<<endl;
		} else {
			d = gcdEx(a,n,x,y); 
			re = x*b/d;
			while(re>0) re-=abs(n/d);
			re+=abs(a/d);
			cout<<re<<endl;
		}	
	} else {
		cout<<"Impossible"<<endl;
	}
} 


int main(int argc,char* argv[])
{
	/*
	// 3x 恒等于 2 （mod6） 
	linear_congruences(3,2,6);
	//5x 恒等于 2 （mod6）  
	linear_congruences(5,2,6);
	//4x 恒等于 2 （mod6）  
	linear_congruences(4,2,6);
	//10x 恒等于 2 （mod6）  
	linear_congruences(6,2,4);
    */
    POJ();
    return 0;
}

