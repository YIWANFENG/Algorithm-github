#include <iostream>
#include <cmath> 
using namespace std;


//求得第N个Fibonacci 

int Fib(int n) {
	if(n<=1)	return 1;
	return Fib(n-1) + Fib(n-2);
}

int Fib2(int n) {
	int i=1, j=1, c;
	while(n-- >0) {
		c = i+j;
		i = j;
		j = c;
	}
	return i;
}

int Fib3(int n) { //SP

	return (pow((1+sqrt(5))/2, n+1) - pow((1-sqrt(5))/2, n+1)) 
				/ sqrt(5);
}

int main(int argc,char* argv[])
{
	cout<< argv[0] <<endl;
	
	int n;
	cin >> n;
	cout<< Fib(n) <<endl;
	cout<< Fib2(n) <<endl;
	cout<< Fib3(n) <<endl;
	return 0;
} 
