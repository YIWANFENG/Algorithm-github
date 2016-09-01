#include <iostream>
#include <cmath>

using namespace std;
//双递归函数Ackerman 
//增长极快，很快无法计算 
long long Ackerman(int n, int m) {
	if(n==1 && !m) return 2;
	if(!n && m>=0) return 1;
	if(n>=2 && !m) return n+2;
	if(n>=1 && m>=1) return Ackerman(Ackerman(n-1, m), m-1);
}
int main() 
{
	int n, m;
	cin>>n>>m;
	cout<<Ackerman(n,m)<<endl;
	
	
	return 0;
}
