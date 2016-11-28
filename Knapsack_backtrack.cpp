#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class Object {
public:
	int ID; 	//原始编号 
	float d; 	//单位重量的价值
	
	bool operator< (const Object & a) const {
		return d>=a.d;
	}
	
};


template <class T_,class W_>
class Knapsack {
private:
	// in  
	int n;
	T_ *w; //每个物品重量 
	W_ *p; //每个物品价值 ,需要从大到小排序 
	T_ c; 		 //背包可载重量 
	
	// out
	W_ bestp;	//当前最优载价值 
	int *bestx;	//当前最优解
	
	//interior
	int *x;		//当前解
	T_ cw;		//当前载重量 
	W_ cp; 		//当前价值 


private:
	W_ Bound(int i) { //计算上界 
		T_ c_left = c- cw;
		W_ b = cp;
		while(i<=n && w[i]<=c_left)   {
			c_left -= w[i];
			b+=p[i];
			++i;
		}
		if(i<=n) b+=p[i]*c_left/w[i];
		return b;
	}	 
	void Backtrack(int i) {
		if(i>n) {
			//到达叶子
			bestp = cp;
			for(int j=1; j<=n; ++j) bestx[j] = x[j]; 
			return ;
		}

		//搜索左子节点 
		if(cw+w[i]<=c) {//约束函数 
			x[i] = 1;
			T_ cw_backup = cw;
			W_ cp_backup = cp; 
			cw+=w[i];
			cp+=p[i];
			Backtrack(i+1);
			cw = cw_backup; 
			cp = cp_backup;
		}
		//搜索右子结点
		if(Bound(i+1)>bestp) { //限界函数 
			x[i] = 0;
			Backtrack(i+1);
		} 	
	} 
	/*void Backtrack_Iterative(int i) {
		//
		int k = 1;
		bool flag = true;
		while(k>0) {
			//左子树
			if(flag && cw+w[k]<=c) {//约束函数 
				x[k] = 1;
				T_ cw_backup = cw;
				cw+=w[i];
				Backtrack(i+1);
				cw = cw_backup; 
			}
			
			
			
			//右子树  
			if(flag && cw+r>bestw) { //限界函数 
				x[i] = 0;
				Backtrack(i+1);
			} 
			
		}
	
	
	}*/
public:
	W_ Solve(int n_,T_ c_,const T_ *w_,const W_ *p_,int *bestx_) {
		//n_ 物品数量
		//c_ 背包最大载重量
		// w_[] 物品重量表
		// p_[] 物品价值 
		// bestx_[] 最优解 
		//返回最优价值 
		n = n_;
		c = c_;
		w = new T_[n+1];
		p = new W_[n+1]; 
		bestx = bestx_;
		
		x =  new int[n+1];
		cw = 0;
		cp = 0;
		bestp = 0;
		Object *Q = new Object[n];
		T_ w_total = 0; //总重量
		W_ p_total = 0; //总价值 
		
		for(int i=1; i<=n; i++) {
			Q[i-1].ID = i;
			Q[i-1].d = p_[i]/(float)w_[i]; ////!!!
			w_total += w_[i]; 
			p_total += p_[i];
		}
		//检查是否全可装下 
		if(w_total < c) {
			delete [] Q;
			for(int i=1; i<=n; ++i) x[i] = 1;
			return p_total; 
		}
		
		sort(Q,Q+n); //物品按单位价值从大到小排序 ,以便Bound() 
		//一般情况 
		for(int i=1; i<=n; ++i) {
			p[i] = p_[ Q[i-1].ID ];
			w[i] = w_[ Q[i-1].ID ]; 
		}
		Backtrack(1);
		
		//最优解 
		for(int i=1; i<=n; ++i) 
			x[Q[i-1].ID] = bestx[i];
		for(int i=1; i<=n; ++i) 
			x[i] = bestx[i];
			
		delete [] p;
		delete [] w;
		delete [] x;
		return bestp;
	}
	
};



int main()
{
	
	int n = 4,sum;
	Knapsack<int,float> ml;
	int w[] = {0,3,5,2,1};
	float p[] = {0,9,10,7,4};
	int x[n+1];
	float bestp = ml.Solve(n,7,w,p,x);
	
	cout<<"最优值:"<<bestp<<endl<<"装载方式:\n";
	for(int i=1; i<=n; ++i) {
		cout<<x[i]<<' ';
	}
	
	cin.get();
	return 0;
}
