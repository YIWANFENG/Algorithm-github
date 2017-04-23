#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const short G_N = 3;		//方形数码问题每行元素个数


class Node{
public:

	int x,y;						//0(特殊值所在位置) 
	int chest[G_N][G_N];			//此时分布状态 
	int h_value,g_value,f_value;					//股价函数值 
	Node *prior;					//父节点指针
	vector<Node*> childs;			//孩子指针 

	Node *next_open;		//用于访问open队列
	Node *prior_open;		//用于访问open队列

	Node() {
		x=y=0;
		h_value = g_value = f_value = 0;
		prior = NULL;
		next_open = prior_open =NULL;
	}
	void inherit(Node* ff) {
		//仅复制x,y,chest 
		if(!ff) return ;
		x = ff->x; y = ff->y;
		for (int i = 0; i < G_N; i++) {
			for (int j = 0; j < G_N; j++) {
				chest[i][j] = ff->chest[i][j];
			}
		}
		prior = ff;
	}

	void hn2(Node *target) {
		//启发函数 1
		//不在目标位置点数作为h_value
	    int num = 0;  
	    for(int i = 0 ; i < G_N ; i++) {  
	        for(int j = 0 ; j < G_N ; j++) {  
	            if(this->chest[i][j] != target->chest[i][j])  
	                num++;  
	        }  
	    }  
	    h_value = num;  
	}

	void hn(Node *target) {
		//启发函数 2
		class Distance {
		public:
			int operator() (int x,int y,int value,Node *target) {
				//返回(x,y)对应的值value在target中的位置与(x,y)的距离
				for (int i = 0; i < G_N; i++) 
					for (int j = 0; j < G_N; j++) 
						if (value == target->chest[i][j]) 
							return abs(x - i) + abs(y - j);
				return 1000;
			}
		} distance;
		//所有点距离目标位置和作为h_value
		int num = 0;
		for (int i = 0; i < G_N; i++) {
			for (int j = 0; j < G_N; j++) {
				num += distance(i, j, chest[i][j], target);
			}
		}
		h_value = num;
	}

	//n到目标的最短路径的启发值 
	void gn() {
		if(this->prior == NULL)  
        	this->g_value = 0;  
    	else  
        	this->g_value = this->prior->g_value + 1;  
	}
	//fn估价函数
	void fn() {
		f_value = g_value + h_value;
	} 
	
	void show() {
		for (int i = 0; i < G_N; i++) {
			for (int j = 0; j < G_N; j++) {
				cout << this->chest[i][j] << ' ';
			}
		cout << endl;
		}
	}
};

bool is_same_node(Node *a, Node *b) {
	if (a->x != b->x || a->y != b->y) return false;
	for (int i = 0; i < G_N; i++) {
		for (int j = 0; j < G_N; j++) {
			if (a->chest[i][j] != b->chest[i][j]) {
				return false;
			}
		}
	}
	return true;
}


class OpenList {
//此class用于访问在open队列
public:
	Node*  head_;
	void add_one(Node*one) {
		//list中加入one
		if(one == NULL) return ;
		one->next_open = NULL;
		Node* tmp = head_;
		if(head_ == NULL) {
			head_ = one;
			one->prior_open = NULL;
		} else {
			while(tmp->next_open!=NULL) tmp=tmp->next_open;
			tmp->next_open = one;
			one->prior_open = tmp;
			one->next_open = NULL;
		}
	}
	void delete_one(Node *one) {
		//list中删除one
		if(one->prior_open==NULL) {
			head_ = one->next_open;
			if(one->next_open)			//找了几天的bug,哎，此处之前漏写，导致链表操作失误
				one->next_open->prior_open = NULL;
		} else {
			one->prior_open->next_open = one->next_open;
			if(one->next_open != NULL) one->next_open->prior_open = one->prior_open;
		}
		one->next_open = one->prior_open = NULL;

	}
	Node* front() {
		//取出 Openlist 中 f_value最大的元素地址 
		Node *tmp = head_;
		Node *min=head_;
		while(tmp!=NULL) {
			if(tmp->f_value < min->f_value) {
				min = tmp;
			}
			tmp = tmp->next_open;
		}
		return min;
	}
	bool has_child(Node *child,Node *&who) {
		//判断OPEN表中是否含有结点child
		//并由who指出其在open中的位置
		Node *tmp = head_;
		while(tmp) {
			if(is_same_node(tmp, child)) {
				who = tmp;
				return true;	
			}
			tmp = tmp->next_open;
		}
		who = NULL;
		return false;
	}
	bool empty() {
		return (head_ == NULL);
	}
};


Node target;
//priority_queue<Node*,vector<Node*>,cmp> OPEN;		//open表，保存等待扩展的结点
vector<Node*> CLOSED;								//closed表，保存访问过的节点
OpenList open_list;									//用于访问open结点

bool is_on_closed(Node *child,Node * &who,int &who_pos) {
	
	//判断child是否在CLOSED中出现过,并由who指出其在closed中的位置
		for(who_pos=0; who_pos < CLOSED.size(); who_pos++) {
			
			if(is_same_node(child,CLOSED[who_pos])) {
				who = (CLOSED[who_pos]);
				return true;
			}
		}
		who_pos = -1;
		who = NULL;
		return false;
}

bool is_target(Node*target,Node* one) {
	//判断是否到达目标状态
	return is_same_node(target, one);
}

bool is_same_as_parent(Node *one) {
	//判断是否和其父辈相同
	Node * tmp= one->prior;
	while (tmp != NULL) {
		if (is_same_node(one, tmp)) {
			return true;
		}
		tmp = tmp->prior;
	}
	return false;
}
void calculate_g_to_update_open(Node *source,Node* child,Node *who) {
	//source 为child的父亲结点
	///***计算估值函数并修改
	//须知其父是谁,且因为待扩展，不许考虑其子 
	child->gn();
	child->fn();
	if(child->g_value < who->g_value) {
		
		who->g_value = child->g_value;
		who->f_value = child->f_value;
		who->prior = child->prior;
	}
	source->childs.push_back(who);
	delete child;
}

void calculate_g_to_update_closed(Node *source,Node* child,Node *who,int who_pos_on_closed) {
	//source 为child的父亲结点
	///***计算估值函数并修改，已扩展，需考虑其子 
	child->gn();
	child->fn();
	source->childs.push_back(who);

	if(child->g_value < who->g_value) {
		who->g_value = child->g_value;
		who->f_value = child->f_value;
		who->prior = child->prior;
		who->childs.clear();
		CLOSED.erase(CLOSED.begin() + who_pos_on_closed);
		open_list.add_one(who);
		delete child;
	}
}

void check_child(Node *source,Node *child) {
	//source --child的父节点
	//检查孩子在整个搜索图中的位置以及状态并做相应动作
	if (is_same_as_parent(child)) return;
	child->hn(&target);
	Node *who;
	int who_pos_on_closed;
	if(open_list.has_child(child,who)) {
		//cout<<"on open"<<endl;
		calculate_g_to_update_open(source,child,who);
	} else if(is_on_closed(child,who, who_pos_on_closed)) {
		//cout<<"on closed"<<endl;
		calculate_g_to_update_closed(source,child,who, who_pos_on_closed);
	} else {
		//cout<<"add open"<<endl;
		source->childs.push_back(child);
		open_list.add_one(child);
	}
}


void creat_child(Node *source) {
	//产生source结点的后继可能结点(即走一步后的状态)
	
	class Swap {
		public: 
		 void operator()(int &a, int &b) {
			int t = a; 
			a = b;
			b = t;
		}
	}swap;

	//向左交换
	if(source->y>0) {
		//cout<<"左"<<endl;
		Node *child = new Node();
		child->inherit(source);
		swap(child->chest[child->x][child->y],
			child->chest[child->x][child->y - 1]);
		child->x = source->x;
		child->y = source->y-1;
		check_child(source,child);
	}
	//向右交换
	if(source->y<G_N-1) {
		//cout<<"右"<<endl;
		Node *child = new Node();
		child->inherit(source);
		swap(child->chest[child->x][child->y],
			child->chest[child->x][child->y + 1]);
		child->x = source->x;
		child->y = source->y + 1;
		check_child(source, child);
	}
	//向上交换
	if(source->x>0) {
		//cout<<"上"<<endl;
		Node *child = new Node();
		child->inherit(source);
		swap(child->chest[child->x][child->y],
			child->chest[child->x - 1][child->y]);
		child->x = source->x - 1;
		child->y = source->y;
		check_child(source, child);	
	}
	//向下交换
	if(source->x<G_N-1) {
		//cout<<"下"<<endl;
		Node *child = new Node();
		child->inherit(source);
		swap(child->chest[child->x][child->y],
			child->chest[child->x + 1][child->y]);
		child->x = source->x + 1;
		child->y = source->y;
		check_child(source, child);

	}
}



void show_path(Node *one) {
	Node *tmp = one;
	while (tmp) {
		cout << "↑" << endl;
		tmp->show();
		tmp = tmp->prior;
	}
}

void search_Astar(Node *target, Node *init_node)
{
	
	
	//压入初始状态
	open_list.add_one(init_node);
	// 进入搜索树搜索图
	Node *tmp = NULL;
	while (!open_list.empty()) {
		//取出估价最优的元素，并从open表中除名
		tmp = open_list.front();
		open_list.delete_one(tmp);

		//检查该结点是否为目标节点
		if(is_target(target,tmp)) {
			cout<<"Yes"<<endl;
			break;
		}
			
		//有后即状态 
		if(true) {
			//产生后继状态（后继结点） 
			creat_child(tmp);
		} 
		//该点检测完毕，压入closed表
		CLOSED.push_back(tmp);

	}
	show_path(tmp);
	//搜索结束，最终结点是tmp
}

void init_node_status(Node * a, int b[])
{
	for (int i = 0; i < G_N; i++) {
		for (int j = 0; j < G_N; j++) {
			a->chest[i][j] = b[i*G_N + j];
			if (b[i*G_N + j] == 0) {
				a->x = i;
				a->y = j;
			}
		}
	}
	a->hn(&target);
	a->gn();
	a->fn();
}

int main()
{
	Node init_node;
	init_node.next_open = NULL;
	int a[] = { 2,0,3,1,8,4,7,6,5 };
	int b[] = { 1,2,3,8,0,4,7,6,5 };

	init_node_status(&target, b);
	init_node_status(&init_node, a);

	target.show();
	search_Astar(&target, &init_node);
	cout << "Waitint for input" << endl;
	cin.get();
	return 0;
}
