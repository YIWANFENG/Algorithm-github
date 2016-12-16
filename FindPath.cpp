#include <iostream>
#include <queue>
#include <vector>

//布线问题 --简单分支限界 
using namespace std;


class Point{
public:
	int x,y;
	Point *parent;
	int level;
	int cost; 
	Point(int x_,int y_)) {
		x = x_; y = y_;
	}
};

class FindPath {
private:
	int n,			//n行 
		m;			//m列
	bool *a;		//可行矩阵
	Point end;
	Point start; 
	int cc;			//目前步数 
	int bestc;		//最优步数 
	Point *best;
private:
	
	
public:
	int Find(bool *a_,int n_,int m_,Point s,Point e,Point *re);
	{
		//a_可行矩阵，s开始位置,e目标位置，re返回路径坐标数组 
		//n_  a_的行，m_ a_的列    返回所需步数
		a = a_;
		n = n_;
		m = m_;
		start = s; 
		end = e;
		queue<Point*> q,recl;
		int dx[] = {-1,0,1,0};
		int dy[] = {0,1,0,-1};
		Point * E = new Point();
		E->x = s.x;
		E->y = s.y;
		E.level = 1;
		E.parent = NULL;
		recl.push(E);
		while(true) {
			//达到，且所走步数优 
			if(E->x==e.x&&E->y==e.y && E->level<bestc) {
				bestc = E->level;
				best = E;
				break;
			}
			for(int i=0;i<4;++i) {
				//该节点可走 
				if( (E->x+dx[i])>0 && (E->x+dx[i])<=n && 
					E->y+dy[i]<=m && E->y+dy[i]>0 &&
					a[(E->x+dx[i])*(m+1)+E->y+dy[i]]!=false) {
					Node *N =  new Node();
					N->level = E->level+1;
					N->x = E->x+dx[i];
					N->y = E->y+dy[i];
					N->parent = E;
					a[(N->x)*(m+1)+N->y] = false;		//成为一次扩展结点即可 
					q.push(N);
					recl.push(N);
				}
			}
			if(q.empty()) break;
			E = q.front();
			q.pop();
		}
		re = new Point[best->level];
		int ii=0;
		while(best) {
			re[best->level-ii].x = best->x ;
			re[best->level-ii].y = best->y ;
			ii++;
			best=best->parent;
		}
		while(recl.empty()) {
			delete recl.front();
			recl.pop();
		}
		return bestc; 
	}
	
};


int main()
{
	int n = 7,m=7;
	bool a[(n+1)*(m+1)];
	for(int i=0;i<(n+1)*(m+1);++i) a[i]= true;
	a[1*(n+1)+3] =a[2*(n+1)+3] = a[3*(n+1)+5] = a[4*(n+1)+4] = a[4*(n+1)+5]
	=a[5*(n+1)+5] = a[5*(n+1)+1] = a[6*(n+1)+2] =a[6*(n+1)+3] = a[7*(n+1)+3] = false;
	
	Point *re;
	int n_re = 0;
	FindPath fp;
	n_re = fp.Find(a,n,m,Point(3,2),Point(4,6))
	
	return 0;
}
