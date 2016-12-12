#include <iostream>
#include <algorithm>

//工作分配问题-回溯法
//排列树 


using namespace std;

class WorkAssign{

private:
	int n;			//n个人
	int *time; 		//(n+1)*(n+1)矩阵，表示i分给j所需的费用 
	int	*best_c;	 	//最优解 
	int *curr_c;	//当前最优分配 
	int curr_t;		//当前耗费 
	int best_t;		//最优耗费 

private:
	void Backtrack(int t) 
	{
		//第i个人
		 
		if(t>n&&curr_t<best_t) {
			for(int i=0;i<=n;++i) {
				best_c[i]=curr_c[i];
				best_t = curr_t;
			}
			return ;
		}
		for(int i=t; i<=n; ++i) {
			curr_c[t] = i;
			curr_t += time[t*(n+1)+i];
			swap<int>(curr_c[t],curr_c[i]);
			Backtrack(t+1); 
			swap<int>(curr_c[t],curr_c[i]);
			curr_t -= time[t*(n+1)+i];
			curr_c[t] = 0;
		}
	}

public:
	int Solve(int n_,int *time_,int *best,int max_time)
	{
		n = n_;
		time = time_;
		best_c = best;
		curr_c = new int[(n+1)*(n+1)];
		curr_t = 0;
		best_t = max_time;
		Backtrack(1);
		
		delete []curr_c;
		return best_t;
	}


}; 
int main()
{
	int n=5;
	int time_[] = {
		0,0,0,0,0,0,
		0,1,2,3,4,5,
		0,5,1,2,3,4,
		0,4,4,1,1,4,
		0,4,2,4,1,5,
		0,5,4,2,3,1
	};
	int wu[n+1];
	WorkAssign wa;
	cout<<"最小耗费"<<wa.Solve(n,time_,wu,50)<<endl;
	cout<<"作业安排"<<endl;
	for(int i=1; i<=n; ++i) {
		cout<<wu[i]<<' ';
	}
	cin.get();
	return 0;
} 
