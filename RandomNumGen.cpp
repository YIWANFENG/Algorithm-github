#include <iostream>
#include <time.h> 

//线性同余产生伪随机数 
using namespace std;

class CRandom
{
private:
	unsigned long rand_seed; //随机数种子

public:
	CRandom(unsigned long s = 0)
	{
		if(!s) rand_seed = time(0);
		else rand_seed = s; 
	}
	
	unsigned long Random(unsigned long n) 
	{
		//0-n-1之间的随机数 
		const unsigned long multiplier = 1194211693L;
		const unsigned long adder = 15465L;
		
		rand_seed = multiplier*rand_seed + adder;
		
		return (rand_seed>>16) % n;
	} 
	
	double fRandom(void) 
	{
		//产生0-1之间的随机实数 
		const unsigned long large_number =  0x10000;
		return Random(large_number) / double(large_number);
	}
	
};

int main()
{
	CRandom rnd;
	
	int i,n=100000;
	int m[10];
	for(i=0;i<10;++i) m[i]=0;
	//查看生成随机数的分布 
	for(i=0;i<n;i++) 
		m[rnd.Random(1000)/100]++;
	for(i=0;i<10;++i)	
	 	cout<<m[i]/(double)n<<endl;
	cin.get();
	
	return 0;
}
