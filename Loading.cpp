#include <iostream>
#include <queue>

//最优装载 -- 分支限界 
using namespace std;

///普通队列 
class QNode
{
public:
	QNode *parent;		//指向父结点的指针 
	bool LChild;		//左孩子 
	float weight;		//载重量 
	
};

void EnQueue(queue<QNode*> &q, float wt, int i,int n,float bestw, 
			QNode *E,QNode *&bestE,int bestx[],bool ch ,queue<QNode*> &q2)
{
	//将活结点加入到队列q中 
	//q 指向队列的指针 	//wt 当前载重量 		//i 当前子集树的层数
	// n 集装箱总数量   // bestw 当前最优值  	//E	 当前扩展节点 
	//bestE 最优值对应的结点 //bestx 最优解  	//ch 左孩子标志    //q2垃圾回收用 
	if(i==n) {
		if(wt==bestw) {
			bestE = E;
			bestx[n] = ch?1:0;	
		}
 		return ;
	}
	
	QNode *b = new QNode;
	b->weight = wt;
	b->parent = E;
	b->LChild = ch;
	q.push(b);
	q2.push(b);	
}

float MaxLoading(float w[], float c,int n,int bestx[]) 
{
	//w[] 集装箱重量  //c 轮船载重量 
	//n 集装箱数量    //bestx[] 最优解 
	//返回最优值
	queue<QNode*> q,q2;
	q.push(NULL);
	int i=1;			//当前层 
    float bestw = 0; 	//最优载重量 
    float Ew = 0;		//当前载重量	
    float r = 0;		//剩余载重量 
	for(int j=2;j<=n;j++) r+=w[j];
	QNode *E = NULL,	//当前扩展结点 
		  *bestE; 		//最优解对应的结点 
		  
	while(true)  {
		float wt = Ew+w[i];
		//检查左孩子 
		if(wt <= c) {
			if(wt>bestw) bestw=wt;	//提前更新最优解 
			EnQueue(q,wt,i,n,bestw,E,bestE,bestx,true,q2); 
		}
		//右孩子 
		if(Ew+r>=bestw) {
			EnQueue(q,Ew,i,n,bestw,E,bestE,bestx,false,q2); 
		}
		E = q.front();
		q.pop();
		if(!E) {
			//遇到层的结尾标志 
			if(q.empty()) break;
			q.push(NULL);	//加入当前层结尾标志 
			E = q.front();
			q.pop();
			++i;			//增加层数
			r -= w[i]; 		//更新剩余集装箱重量 
		}
		Ew = E->weight; //更新当前载重量 
	}
	for(int j=n-1;j>0;--j) {
		bestx[j] = (bestE->LChild)?1:0;
		bestE = bestE->parent;
	}
	while(q2.empty()) {
		delete q2.front();
		q2.pop();
	}
	return bestw;
}






int main()
{
	int n = 3,sum; 
 	float w[] = {0,10,40,40}; 
 	int x[n+1]; 
 	//float bestw = ml.Solve(n,60.0,w,x); 
 	float bestw = MaxLoading(w,60.0,n,x); 
 	cout<<"最优值:"<<bestw<<endl<<"装载方式:\n"; 
 	for(int i=1; i<=n; ++i) { 
 		cout<<x[i]<<' '; 
 	} 
 	cin.get(); 
	
	return 0;
}

////优先队列 
class QNode
{
public:
	QNode *parent;		//指向父结点的指针 
	bool LChild;		//左孩子 
	float uweight;		//载重量上界 
	int level;			//所在层数  

};

class mycmp{
public:
	bool operator() (const QNode* a1,const QNode* a2) const
	{
		if( (a1->uweight) < (a2->uweight) ) return true;
		return false;
	}
};

void EnLiveQueue(priority_queue<QNode*,vector<QNode*>,mycmp > &q,  
			QNode *E,float wt, bool ch ,int i,queue<QNode*> &q2)
{
	//将活结点加入到队列q中 
	//q 指向队列的指针 	//wt 当前载重量 		//i 当前子集树的层数
	//E	 当前扩展节点 
	//ch 左孩子标志    //q2垃圾回收用 
		
	QNode *b = new QNode;
	b->parent =E;
	b->LChild = ch;
	b->level = i;
	b->uweight = wt;
	
	q.push(b);
	q2.push(b);	
}

float MaxLoading(float w[], float c,int n,int bestx[]) 
{
	//w[] 集装箱重量  //c 轮船载重量 
	//n 集装箱数量    //bestx[] 最优解 
	//返回最优值
	queue<QNode*> q2;
	priority_queue<QNode*,vector<QNode*>,mycmp > q;
	int i=1;			//当前层 
    float Ew = 0;		//当前载重量	
    float r[n+1];		//剩余载重量 
    r[n] = 0;
	for(int j=n-1;j>0;j--) r[j]=r[j+1]+w[j+1];
	QNode *E = NULL;	//当前扩展结点 
		  
	while(i!=n+1)  {
		float wt = Ew+w[i];
		//检查左孩子 
		if(wt <= c) {
			EnLiveQueue(q,E,wt+r[i],true,i+1,q2); 
		}
		//右孩子 
		EnLiveQueue(q,E,Ew+r[i],false,i+1,q2);
		E = q.top();
		q.pop();
		i = E->level;
		Ew = E->uweight-r[i-1];
	}
	for(int j=n;j>0;--j) {
		bestx[j] = (E->LChild)?1:0;
		E = E->parent;
	}
	while(q2.empty()) {
		delete q2.front();
		q2.pop();
	}
	return Ew;
}
