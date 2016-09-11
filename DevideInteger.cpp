#include <iostream>
///递归 
using namespace std;

int DevideInteger(int n, int m){
	///输出组成元素不大于m的关于n的划分个数 
	if(n<1 || m<1) return 0;
	if(n==1 || m==1) return 1;
	if(n<m) return DevideInteger(n, n); 
	if(n==m) return DevideInteger(n, m-1)+1;
	return DevideInteger(n, m-1) + DevideInteger(n-m, m);
}



int Array[100];
int end_out = -1; 
void PrintDevideInteger(int n,int m){
	///输出组成元素不大于m的关于n的划分
	if(n < 1) {
		for(int i=0; i<=end_out; ++i)
			cout<<Array[i]<<' ';
		//cout<<"\nend_out:"<<end_out+1<<endl;
		cout<<endl;
	}
	else {
		for(int i=(n>m?m:n); i>0; --i) {
			++end_out;
			Array[end_out] = i;
			PrintDevideInteger(n-i, i);
			--end_out; 
		}
	}
}


int main()
{
	int n;
	cin >> n;
	cout<<"划分次数"<<DevideInteger(n, n) <<endl;
	PrintDevideInteger(n,n);
	
	cout<<end_out<<endl;
}
