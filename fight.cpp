#include <iostream>
#include <queue>
#include <cstring>
#include <assert.h>
//MIN_MAX搜索，无Alpha与beta剪枝 
using namespace std;

const int MAX_INT = 65535;
const int MIN_INT = -65535;

class ChessBoard{
	
	short *ptr;
	
	int how_win(int maxplayer) {
		//空白全下，可胜局数 
		ChessBoard *tmp =new ChessBoard();
		(*tmp) = (*this);
		int re=0;
		for(int i=0;i<cols*rows;i++) if(tmp->ptr[i]==0) tmp->ptr[i] = maxplayer;
		int sum = 0;
		for(int i=0;i<rows;i++) {
			sum = 0;
			for(int j=0;j<cols;j++) sum+=tmp->ptr[i*cols+j];
			if(maxplayer==1&&sum==3) re++;
			if(maxplayer==-1&&sum==-3) re++;
		}
		for(int i=0;i<cols;i++) {
			sum = 0;
			for(int j=0;j<rows;j++) sum+=tmp->ptr[j*cols+i];
			if(maxplayer==1&&sum==3) re++;
			if(maxplayer==-1&&sum==-3) re++;
		}
		sum = 0;
		for(int i=0;i<rows;i++) 
			sum +=tmp->ptr[i*cols+i];
		if(maxplayer==1&&sum==3) re++;
		if(maxplayer==-1&&sum==-3) re++;
		sum = 0;
		for(int i=0,j=2;i<rows;i++,j--) 
			sum +=tmp->ptr[i*cols+j];
		if(maxplayer==1&&sum==3) re++;
		if(maxplayer==-1&&sum==-3) re++;
		delete tmp;
		return re;
	}
	
	
public:
	//井子棋 3*3 
	bool max_player;						//max选手的棋局
	int rows,cols;
	ChessBoard *childs;
	ChessBoard *next_borther;
	ChessBoard *father;
	int value;						//评估值 
	ChessBoard(int rows=3,int cols=3) {
		this->rows = rows;
		this->cols = cols;
		ptr = new short[rows*cols]; 
		for(int i=0;i<rows*cols;i++) ptr[i] = 0;
		next_borther = childs = NULL; 
	}
	~ChessBoard() {
		this->rows = 0;
		this->cols = 0;
		if(ptr) delete [] ptr;
		ptr = NULL;
	}
	void operator = (ChessBoard &other) {
		//复制棋盘 
		if(this->rows!=other.rows || this->cols != other.cols ) return ;
		for(int i=0;i<rows*cols;i++) ptr[i] = other.ptr[i];
	}
	short& operator [] (int n) {
		return ptr[n];
	}
	void put(int row,int col,bool max_player) {
		//假设坐标合理输入 
		if(ptr[row*cols+col]==0) {
			ptr[row*cols+col] = max_player?1:-1;
			this->max_player = !max_player;
		}
	}
	void put_child(ChessBoard *child) {
		child->next_borther = childs;
		childs = child;
	}
	int where_is_void(int where[]) {
		//查看now中空白位置，并返回数量n以及位置where = i*cols+j
		int n=0;
		for(int i=0;i<rows*cols;i++) {
			if(ptr[i] == 0) where[n++] = i;
		}
		return n;
	}
	
	void show() {
		//cout<<"++++"<<endl;
		for(int i=0;i<rows;i++) {
			for(int j=0;j<cols;j++) {
				char c = '-';
				if(ptr[i*cols+j]==1) c = 'o';
				if(ptr[i*cols+j]==-1) c = 'x'; 
				cout<<c;
			}
			cout<<endl;
		}
		cout<<"++++"<<endl;
	}
	int who_win() {
		int sum = 0;
		for(int i=0;i<rows;i++) {
			sum = 0;
			for(int j=0;j<cols;j++) sum+=ptr[i*cols+j];
			if(sum==3) return 1;
			if(sum==-3) return -1;
		}
		for(int i=0;i<cols;i++) {
			sum = 0;
			for(int j=0;j<rows;j++) sum+=ptr[i+cols*j];
			if(sum==3) return 1;
			if(sum==-3) return -1;
		}
		sum = 0;
		for(int i=0;i<rows;i++) 
			sum +=ptr[i*cols+i];
		if(sum==3) return 1;
		if(sum==-3) return -1;
		sum = 0;
		for(int i=0,j=2;i<rows;i++,j--) 
			sum +=ptr[i*cols+j];
		if(sum==3) return 1;
		if(sum==-3) return -1;
		return 0;//平局 
	}
	int evaluate() {
		//关键
		if(who_win()==1) return MAX_INT;
		else if(who_win()==-1) return MIN_INT;
		return (how_win(1) - how_win(-1));
	} 

}; 



void creat_Tree(queue<ChessBoard*> &qu_chess,ChessBoard &now,int layer=4) {
	//广度优先生成树  
	int size = now.rows*now.cols;
	int where[size];						//row = where/(cols);col = where%(cols) 
	
	qu_chess.push(&now); 
	qu_chess.push(NULL);					//第一层结束标志 
	
	while(!qu_chess.empty()) {
		ChessBoard *live = qu_chess.front();	//取出一节点作为扩展节点
		qu_chess.pop(); 
		if(!live) {
			layer--; 
			if(0==layer) break;			  	//生成layer层后退出 
			qu_chess.push(NULL);		  	//作为一层结束标志 
			live = qu_chess.front();		
			qu_chess.pop();
		}			  
		int n = live->where_is_void(where);		  	//可放棋子位置与个数 
		for(int j=0;j<n;j++) {
			ChessBoard *child = new ChessBoard();
			(*child) = (*live);
			child->put(where[j]/(child->cols),where[j]%(child->cols),(live->max_player));
			child->father = live;			
			live->put_child(child);		
			qu_chess.push(child);			//孩子待扩展  
		}
	}
}

void dispose_tree(ChessBoard *node) {
	//释放node的搜索树 (except node )
	if(node->childs == NULL) return ;
	else {
		ChessBoard *next,*tmp = node->childs;
		while(tmp) {
			dispose_tree(tmp);
			next = tmp->next_borther;
			delete tmp;
			tmp = next;
		}
	}
}

int minmax_recu(ChessBoard *node,int depth,bool max_player) {
	//递归极大极小判断 
	if(depth==0 || node->childs==NULL) {		//到达指定深度或者节点不可扩展 
		return node->evaluate();	
	}
	
	if(max_player) {						   	//此次操作为MAX 
		int bestval = MIN_INT;
		ChessBoard *tmp = node->childs;
		while(tmp) {						   	//所有孩子取最大 
			tmp->value = minmax_recu(tmp,depth-1,false);
			bestval = max<int>(bestval,tmp->value);
			tmp = tmp->next_borther;
		}
		return bestval;
	} else {									//此次操作为MIN
		int bestval = MAX_INT;							  
		ChessBoard *tmp = node->childs;
		while(tmp) {						   //所有孩子取最小 
			tmp->value = minmax_recu(tmp,depth-1,true);
			bestval = min<int>(bestval,tmp->value);
			tmp = tmp->next_borther;
		}
		return bestval;
	}
} 

void MAX_MIN_search(ChessBoard &now_node,int &row,int &col) {
	//极大极小搜索
	//给出初始局面，计算四步推算下一步走法(row,col) 
	
	queue<ChessBoard*> qu_chess;
	//生成2层搜索树
	creat_Tree(qu_chess,now_node,2);	
	
	//反向极大极小推理，得到目标步骤 
	now_node.value = minmax_recu(&now_node,2,now_node.max_player);
	ChessBoard *tmp = now_node.childs->childs;
	
	tmp = now_node.childs;
	while(tmp && tmp->value!=now_node.value) {
		tmp = tmp->next_borther;
	}
	for(int i=0;i<now_node.rows*now_node.cols;i++) 
		if(now_node[i]!=(*tmp)[i]) {
			row = i/(now_node.cols);col = i%(now_node.cols);
		}
	
	//销毁搜索树 
	dispose_tree(&now_node);
	
} 




int main() {
	//这里只做了一步预测
	//实际模拟可以实例化两个CHessBoard,分别作为对手
	//各自都以自己为MAX来完成自行对弈 
	//其次，在搜索中若一定会出现平局或者最终根本赢不了时, 
	//这里给出的中间步骤无参考性。 
	ChessBoard p;
	int next_row=0,next_col=0;
	//设置初态 

	p.put(2,2,true);
	p.put(0,2,false);


	MAX_MIN_search(p,next_row,next_col);
	p.put(next_row,next_col,true);
	p.show();
	
	return 0;
}
