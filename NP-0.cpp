#include <iostream> 
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <vector>

//多机调度问题	NP 
using namespace std;

class Job{
public:
	int id;
	int time;
	operator int () const {
		return time;
	} 
	
};
class Machine{
public:
	int id;
	int avail;
	operator int () const {
		return avail;
	}
};
class cmp2{
public:
    bool operator ()(Machine a,Machine b){
        return int(a)>int(b);//优先判定 
    }
};


bool cmp (Job a,Job b){
	
	if(int(a)>int(b)) return true;
	return false;
} 


template <class T_>
void Greedy(T_ a[],int n,int m){
	//a(in) 作业序列 [1-n]
	//n(in)作业数
	//m(in)机器数  
	sort((a+1),(a+(n+1)),cmp);
	
	if(n <= m) {
		cout<<"每作业都分配一个机器\n";
		cout<<"最长用时："<<int(a[0])<<endl; 
	} else {
		//最闲机器优先队列 
		priority_queue<Machine,vector<Machine>,cmp2> q; 	//优先级队列 
		
		Machine x;
		for(int i=1;i<=m;++i) {
			x.avail = 0;
			x.id = i;
			q.push(x);
		}
		for(int i=n;i>=1;i--) {
			x = q.top();
			q.pop();
			cout<<"将机器"<<x.id<<"从"<<x.avail
				<<"到"<<(x.avail+a[i].time)<<"的时间分配给作业"
				<<a[i].id<<endl;
				x.avail+=a[i].time;
				q.push(x); 
		}
	}
	
	
} 

int main()
{
	Job a[11];
	srand(time(NULL));
	
	for(int i=1;i<=10;i++){
		a[i].id = i;
		a[i].time = rand()%5+5;
	}
	
	Greedy<Job>(a,10,4);
	
	cin.get();
	return 0;
}
