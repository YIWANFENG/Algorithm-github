#include <iostream>
#include <stdlib.h>
#include <stack>
using namespace std;

template <class T_>
class MaxLoading {
private:
	// in  
	int n;
	const T_ *w; //每个集装箱重量 
	T_ c; 		 //可载重量 
	
	// out
	T_ bestw;	//当前最优载重量 
	int *bestx;	//当前最优解
	
	//interior
	int *x;		//当前解
	T_ cw;		//当前载重量 
	T_ r; 		//当前剩余物品重量
	 
	void Backtrack(int i) {
		if(i>n) {
			//到达叶子
			bestw = cw;
			for(int j=1; j<=n; ++j) bestx[j] = x[j]; 
			return ;
		}
		//更新剩余重量
		T_ r_backup = r;
		r -= w[i];
		
		//搜索左子节点 
		if(cw+w[i]<=c) {//约束函数 
			x[i] = 1;
			T_ cw_backup = cw;
			cw+=w[i];
			Backtrack(i+1);
			cw = cw_backup; 
		}
		//搜索右子结点
		if(cw+r>bestw) { //限界函数 
			x[i] = 0;
			Backtrack(i+1);
		} 
		r = r_backup;
		
	} 
	void Backtrack_Iterative(void) {
		int i = 1;
		
 		while(true) {
			//搜索左子节点 
			while(i<=n && cw+w[i]<=c) {
				r -=w[i];
				cw +=w[i];
				x[i] = 1;
				++i;
			}
			if(i>n) {
				for(int j=1; j<=n; ++j) 
					bestx[j] =x[j];
				bestw = cw;
			} else {
				//进入右子树
				r-=w[i];
				x[i] = 0;
				++i; 
			}
			//剪枝回溯 
			while( cw+r<=bestw ) {
				--i;
				while(i>0 && !x[i]) {
					//从右子树返回 
					r += w[i];
					--i; 
				}
				if(i==0)
					return ;
				//进入右子树
				x[i] = 0;
				cw -= w[i];
				++i; 
			}
		}
	}
public:
	int Solve(int n_,T_ c_,const T_ *w_,int *bestx_) {
		//n_ 物品数量
		//c_ 最大载重量
		// w_[] 物品重量表
		// bestx_[] 最优解 
		n = n_;
		c = c_;
		w = w_;
		bestx = bestx_;
		
		x =  new int[n+1];
		cw = 0;
		bestw = 0;
		
		r = 0;
		for(int i=1; i<=n; ++i) r+=w[i];
		
		Backtrack(1);
		delete [] x;
		return bestw;
	}
	int Solve_Iterative(int n_,T_ c_,const T_ *w_,int *bestx_) {
		//n_ 物品数量
		//c_ 最大载重量
		// w_[] 物品重量表
		// bestx_[] 最优解 
		n = n_;
		c = c_;
		w = w_;
		bestx = bestx_;
		
		x =  new int[n+1];
		cw = 0;
		bestw = 0;
		
		r = 0;
		for(int i=1; i<=n; ++i) r+=w[i];
		
		Backtrack_Iterative();
		delete [] x;
		return bestw;
	}
	
};


int main()
{
	
	int n = 3,sum;
	MaxLoading<float> ml;
	float w[] = {0,10,40,40};
	int x[n+1];
	//float bestw = ml.Solve(n,60.0,w,x);
	float bestw = ml.Solve_Iterative(n,60.0,w,x);
	cout<<"最优值:"<<bestw<<endl<<"装载方式:\n";
	for(int i=1; i<=n; ++i) {
		cout<<x[i]<<' ';
	}
	
	cin.get();
	return 0;
}
