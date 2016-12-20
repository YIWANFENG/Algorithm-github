#include <time.h> 
#include <stdlib.h>
#include <math.h>
#include <iostream>


//nqueue - Las Vegas
 
using namespace std;

class NQueue_Las_Vegas
{
private:
	int *y;  //当前行上皇后可放置的位置
	
	bool Place(int k)		
	{ 
 		//验证第k行皇后位置是否合理 
 		for(int i=1; i<k; ++i) { 
 			if((k-i)==abs(x[i]-x[k]) || x[i]==x[k]) 
 				return false; 
 		} 
 		return true; 
 	} 

	
	bool Backtrack(int t)	
	{
		//回溯法
		if(t>n) return true;
		else {
			for(int i=1;i<=n;++i)
			{
				x[t] = i;
				if(Place(t) && Backtrack(t+1))
					return true;
			}
		}
		return false;
	}
	
	bool QueuesLV(int m)	
	{
		//随机放置m个皇后的Las Vegas算法
		int k = 1;
		int count = 1;
		while(k<=m && count>0) {
			count=0;
			for(int i=1;i<=n;++i) {
				x[k]=i;
				if(Place(k)) y[count++] = i;
			}
			if(count>0) 
				x[k++] = y[rand()%count];
			
		}
		return count>0;
	}
	
public:
	int n;
	int *x;
	
	void Solve(int num_loops)
	{
		y = new int[n+1];
		int m = 5;
		if(n>15) m = n-15;
		bool found = false;
		for(int i=1;i<num_loops;++i) {
			if(QueuesLV(m)) {
				if(Backtrack(m+1)) {
					found = true;
					break;
				}
			}
		}
		if(found) {
			for(int i=1;i<=n;++i) 
				cout<<x[i]<<' ';
			cout<<endl;
		} else {
			cout<<"No Answer"<<endl;
		}
		delete [] y;
	}
};


int main()
{
	NQueue_Las_Vegas nq;
	nq.n = 8;
	nq.x = new int[nq.n+1];
	for(int i=0;i<20;++i)
		nq.Solve(10) ;
		
	cin.get();
	delete [] nq.x;
	return 0;
}
