#include <iostream>
#include <algorithm> 

using namespace std;
//流水作业调度
 
class Job{
public:
	int operator() (){
		return key;
	}
	int key;
	int index;
	bool job;
}; 

bool cmp(Job a,Job b){
	if(a()>b()) return false;
	return true;
}
int FlowShop(int n,int a[],int b[],int c[]) {
	Job d[n];
	for(int i=0;i<n;i++) {
		d[i].key=a[i]>b[i]?b[i]:a[i];
		d[i].job=!(a[i]>b[i]);
		d[i].index = i;
	}
	sort(d,d+n*sizeof(Job),cmp);
	int j=0,k=n-1;
	for(int i=0; i<n; i++) {
		if(d[i].job) c[j++] = d[i].index;
		else c[k--] = d[i].index;
	}
	j = a[c[0]];
	k = j+b[c[0]];
	for(int i=1; i<n; i++) {
		j+=a[c[i]];
		k = j<k?k+b[c[i]]:j+b[c[i]];
	}
	return k;	
} 

int main(int argc,char *argv[])
{
	
	
	
	cin.get();
	return 0;
}
