#include <iostream>

using namespace std;

int DevideInteger(int n, int m){
	if(n<1 || m<1) return 0;
	if(n==1 || m==1) return 1;
	if(n<m) return DevideInteger(n, n); 
	if(n==m) return DevideInteger(n, m-1)+1;
	return DevideInteger(n, m-1) + DevideInteger(n-m, m);
}

int main()
{
	int n;
	cin >> n;
	cout<< DevideInteger(n, n) <<endl;
	
	
	
}
