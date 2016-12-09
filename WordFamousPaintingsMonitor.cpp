#include <iostream>

//世界名画排列问题
//回溯法 


//算法时间复杂度不理想啊，7*7矩阵以上复杂度陡增。 
//8*8矩阵用我这电脑跑了近50分钟 
using namespace std;

class Point{
public:
	int x,y;
	Point(int x_,int y_) {
		x=x_;y=y_;
	}
	Point() {
		x=0;y=0;
	}
};

class Monitor{
private:
	int *rooms; 	// m*n矩阵表示房间被几人监视 
	int m;			//m行 
	int n; 			//n列 
	
	bool *robot;	//m*n矩阵表示当前解的机器人安排 
	bool *result;	//返回安排结果 
	
	int bestc;		//最少机器哨位数
	int curr_c;		//当前机器哨位数
	
	int not_safe;	//当前不安全房间数 
	
	
private:
	void Change(Point &t)
	{
		//room,not_safe与 robot变动 
		//中间 
		if(t.x>0&&t.y>0&&t.x<=m&&t.y<=n) {
			robot[t.x*(n+1)+t.y] = true;
			rooms[t.x*(n+1)+t.y]++; 
			if(rooms[t.x*(n+1)+t.y]==1) not_safe--;
		} else {
			return;
		}
		
		
		//上 
		if(t.x-1>0&&t.y>0&&t.x-1<=m&&t.y<=n) { 
			rooms[(t.x-1)*(n+1)+t.y]++;
			if(rooms[(t.x-1)*(n+1)+t.y]==1) not_safe--;
		}
		//右 
		if(t.x>0&&t.y+1>0&&t.x<=m&&t.y+1<=n) { 
			rooms[t.x*(n+1)+t.y+1]++;
			if(rooms[t.x*(n+1)+t.y+1]==1) not_safe--; 
		} 
		//下
		if(t.x+1>0&&t.y>0&&t.x+1<=m&&t.y<=n) { 
			rooms[(t.x+1)*(n+1)+t.y]++;
			if(rooms[(t.x+1)*(n+1)+t.y]==1) not_safe--;
		} 
		//左
		if(t.x>0&&t.y-1>0&&t.x<=m&&t.y-1<=n) { 
			rooms[t.x*(n+1)+t.y-1]++;
			if(rooms[t.x*(n+1)+t.y-1]==1) not_safe--; 	
		}
	}
	
	void Recover(Point &t) 
	{
		//room,not_safe与 robot恢复
		if(t.x>0&&t.y>0&&t.x<=m&&t.y<=n) {
			robot[t.x*(n+1)+t.y] = false;
			rooms[t.x*(n+1)+t.y]--; 
			if(rooms[t.x*(n+1)+t.y]==0) not_safe++;
		} else {
			return;
		}
		
		//上 
		if(t.x-1>0&&t.y>0&&t.x-1<=m&&t.y<=n) {
			rooms[(t.x-1)*(n+1)+t.y]--;
			if(rooms[(t.x-1)*(n+1)+t.y]==0) not_safe++;
		}		
		//右 
		if(t.x>0&&t.y+1>0&&t.x<=m&&t.y+1<=n) {
			rooms[t.x*(n+1)+t.y+1]--;
			if(rooms[t.x*(n+1)+t.y+1]==0) not_safe++;
		} 
		//下 
		if(t.x+1>0&&t.y>0&&t.x+1<=m&&t.y<=n) {
			rooms[(t.x+1)*(n+1)+t.y]--;
			if(rooms[(t.x+1)*(n+1)+t.y]==0) not_safe++;
		}			
		//左	
		if(t.x>0&&t.y-1>0&&t.x<=m&&t.y-1<=n) {
			rooms[t.x*(n+1)+t.y-1]--;
			if(rooms[t.x*(n+1)+t.y-1]==0) not_safe++; 
		}		
	} 
	
	Point FindNotSafe(Point &t)const
	{
		//找到一个不安全房屋 
		for(int i=t.x; i<=m; ++i) {
			for(int j=1; j<=n; ++j) {
				if(i>0&&rooms[i*(n+1)+j]==0) {
					//cout<<"("<<i<<","<<j<<")"<<endl;
					return Point(i,j);
				}
			}
		}
		return Point(0,0);//超界坐标 
	}
	
	void Backtrack(Point t)
	{
		//if(not_safe<0) {
		//	cout<<"("<<t.x<<","<<t.y<<")"<<endl;
		//	cout<<"Not safe"<<not_safe<<" C "<<curr_c<<endl;
		//	return;
		//}
		
		if(not_safe==0&&curr_c<bestc) {
			for(int i=0; i<(m+1)*(n+1); ++i) {
				result[i] = robot[i];	
				
				//cout <<"#" <<result[i]<<"#"<< endl;
			}
			bestc=curr_c;
			return ;
		}
		//超界检查 
		if(t.x<=0 || t.y<=0 || t.x>m || t.y>n)
			return ;
		Point x1,x2;
		//(t.x,t.y)
		Change(t);
		curr_c++;
		x1 =  FindNotSafe(t);
		//cout << "(" << x1.x << "," << x1.y << ")" << endl;
		Backtrack(x1);
		Recover(t);
		curr_c--;
		
		//(t.x,t.y+1)
		x2.x = t.x;
		x2.y = t.y+1;
		if (x2.x > 0 && x2.y > 0 && x2.x <= m && x2.y <= n) {
			Change(x2);
			curr_c++;
			x1 = FindNotSafe(t);
			Backtrack(x1);
			Recover(x2);
			curr_c--;
		}
		
		
		//(t.x+1,t.y)
		x2.x = t.x+1;
		x2.y = t.y;
		if (x2.x > 0 && x2.y > 0 && x2.x <= m && x2.y <= n) {
			Change(x2);
			curr_c++;
			x1 = FindNotSafe(t);
			Backtrack(x1);
			Recover(x2);
			curr_c--;
		}		
	}
	
	
public:
	int Solve(int m_,int n_,bool *res) 
	{
		//m_ 行 n_列 res[] 最终安排数组 
		//返回所需最少机器人属 
		m =m_; n=n_; 
		rooms=(int*)malloc(sizeof(int)*(n+1)*(m+1));
		robot=(bool*)malloc(sizeof(bool)*(n+1)*(m+1));
		for(int i=0;i<(n+1)*(m+1);++i) {
			rooms[i] = 0;
			robot[i] = false;
		}
		result = res;
		bestc = m*n;
		curr_c = 0;
		not_safe=m*n;	//当前不安全房间数 
		Backtrack(Point(1,1)); 
		free(rooms);
		free(robot);
		return  bestc; 
	}
		
}; 

void show(int m_,int n_,bool *res) 
{
	for(int i=1; i<=m_; ++i) {
		for(int j=1; j<=n_; ++j) {
			if(res[i*(n_+1)+j]) cout<<"# ";
			else cout<<"O ";
		}
		cout<<'\n';
	}
}



int main(int argc,char *argv[])
{
	int n = 4, m = 4;
	cout << "输入房间矩阵大小行列";
	cin >> m >> n;
	Monitor sl;
	bool *res = new bool[(n+1)*(m+1)];
	cout<<"最少哨兵:"<<sl.Solve(m,n,res)<<endl;
	show(m,n,res);
	
	int aa;
	cin>>aa;
	
	return 0;
} 
