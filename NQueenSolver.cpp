#include <iostream>
#include <stdlib.h>

using namespace std;

class NQueenSolver {
private:
	int n;	//皇后数量 
	int *x;	//每一行的皇后所在的列
	int sum;	//当前解的数量 
	
private:
	bool Validate(int k) {
		//验证第k行皇后位置是否合理
		for(int i=1; i<k; ++i) {
			if((k-i)==abs(x[i]-x[k]) || x[i]==x[k])
				return false;
		}
		return true;
	}
	void Backtrack(int t) {
		if(t>n) {	//到达解空间树的叶子  
			++sum;	
			if(sum==1) show_plan();
		} else {
			//遍历所有的子结点
			for(int i=1; i<=n; ++i) {
				x[t] = i;
				if(Validate(t)) 
					Backtrack(t+1);
			}
		}
	} 
	void Backtrack_Iterative() {
		int k =1 ; //处理层数
		x[1] = 0;
		while(k>0) {
			++x[k];
			//遍历所有子结点，寻找满足约束的子结点 
			while(x[k]<=n && !Validate(k)) ++x[k];
			if(x[k]<=n) { //找到满足约束的子结点 
				if(k==n) { //到达叶子结点  
					++sum;
					if(sum == 1) show_plan(); 
				} else {
					//进入下一层结点 
					++k;
					x[k] = 0; 
				}
			} else {
				//所有子结点遍历完毕，回溯 
				--k;
			}							
		}
	} 
	void show_plan() {
		for(int i=1; i<=n; ++i) {
			for(int j=1; j<=n; ++j) {
				if(x[i]==j) cout<<"Q ";
				else cout<<"* ";
			}
			cout<<endl;
		}
	}
public:
	int Solve(int num_queens) {
		//num_queens皇后数量
		//解的数量 
		n = num_queens;
		sum = 0;
		x = new int[n+1];
		Backtrack(1);
		delete []x;
		return sum;
	}
	int Solve_iterative(int num_queens) {
		//num_queens皇后数量
		//解的数量 
		n = num_queens;
		sum = 0;
		x = new int[n+1];
		Backtrack_Iterative();
		delete []x;
		return sum;
	}
};


int main()
{
	
	int num = 0,sum;
	cout<<"输入皇后数\n";
	cin >> num;
		
	NQueenSolver qs;
	sum = qs.Solve(num);
	//sum = qs.Solve_iterative(num);
	cout<<num<<"皇后问题解的数量:"<<sum<<endl; 
	
	return 0;
}
