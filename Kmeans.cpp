#include <iostream>
#include <cmath>
#include <list>
#include <fstream>
#include <cstdlib>
//kmeans算法 
//数据预处理代码已去除 
using namespace std;

class Map{
public:
	int row,col;
	int valid;			//有效值
	float value[4];
	int which_center = -1; 
	
public:
	Map() {
		row = 0;
		col = 0;
		valid = 0;
		value[0] = value[1] =value[2] =value[3]= 0;
	}	 
	void calc_row_column(int x,int y) {
		row = x*300;
		col = y*300;
	}
	bool is_valid() {
		return (value[0]!=0||value[1]!=0||value[2]!=0||value[3]!=0);
	}
};

class vector4 {
public:
	float val[4];
	float& operator[](int n) {
		return val[n];
	}
	vector4() {
		val[0] = val[1] = val[2] = val[3] =0;
	}
};

template<typename T_>
class KCenter {
public:
	int index;		//编号 
	vector4 center;		//中心 
	int num;		//成员数 
	
	
	void set_kcenter(int index,vector4 center){
		this->index = index;
		this->center = center;
	}
	typename list<T_>::iterator is_member(T_ map) {
		for(typename list<T_>::iterator itr = member.begin(); itr!=member.end() ; itr++) {
			if(*itr == map) {
				return itr;
			}
		}
		return member.end();
	}
	void push(T_ map) {
		member.push_back(map);
		map->which_center = index;
		num ++;
	}
	void pop(T_ map) {
		typename list<T_>::iterator pos = is_member(map);
		if(pos != member.end()) {
			(*pos)->which_center = -1;
			member.erase(pos);
			num--;
		}
	}
	float distance_from_map(T_ samp) {
		//计算samp距离KCenter的距离 
		float dist  = 0;
		dist += pow( (center[0]- (samp->value)[0]), 2);
		dist += pow( (center[1]- (samp->value)[1]), 2);
		dist += pow( (center[2]- (samp->value)[2]), 2);
		dist += pow( (center[3]- (samp->value)[3]), 2);
		return sqrt(dist);
	}
	
	void adjust_center() {
		//依据成员重新调整自身中心 
		center[0] = center[1] = center[2] = center[3] = 0;
		for(typename list<T_>::iterator itr = member.begin(); itr!=member.end() ; itr++) {
			for(int j=0; j<4; j++)
				center[j] += ((*itr)->value)[j];
		}
		for(int j=0; j<4; j++)
			center[j] /= num;
	}
	
	float all_distance() {
		float dist = 0;
		for(typename list<T_>::iterator itr = member.begin(); itr!=member.end() ; itr++) {
			dist += distance_from_map(*itr);
		}
		return dist;
	}
	
private:
	list<T_> member;
	
};

const int N_K = 4; //K中心个数 
KCenter<Map*> kcenters[N_K];


//寻找初始簇的质心
void find_centers(vector4 centers[],int n,Map maps[],int n_maps) {

	//平均取样值作为簇中心 (预先计算了数据中最大147最小值0) 
	int span = 147;
	for(int i=0;i<n;i++) {
		for(int j=0;j<4;j++)
			centers[i][j] = i*span/(N_K-1);
	}
	for(int i=0;i<N_K;i++)
			cout<<"cu "<<centers[i][0]<<' '<<centers[i][1]<<' '<<centers[i][2]<<' '<<centers[i][3]<<endl; 
}

void init_centers(vector4 centers[],int n) {
	//设置初始簇的质心 
	for(int i=0; i<n; i++) {
		kcenters[i].set_kcenter(i,centers[i]);
	}
}

bool divide(Map maps[],int n) {
	//为每个样本分类 
	//并返回这次是否重新调整过的标志 
	float dist = 0;
	int num_select = 0;	
	bool is_adjust = false;
	
	for(int i=0; i<n; i++) {
		//寻找最近簇 
		dist = kcenters[0].distance_from_map(maps+i);
		num_select = 0;
		for(int j=1; j<N_K; j++) {
			if( dist > kcenters[j].distance_from_map(maps+i) ) {
				dist = kcenters[j].distance_from_map(maps+i);
				num_select = j;		
			}
		}
		if(maps[i].which_center == -1) {
			//从未分类过 
			kcenters[num_select].push(maps+i);
			is_adjust = true;
		} else if (maps[i].which_center != num_select){
			//被分到其他簇
			//从之前簇取出 
			kcenters[maps[i].which_center].pop(maps+i);
			//压入新簇 
			kcenters[num_select].push(maps+i);
			is_adjust = true;
		}
	}
	for(int i=0; i<N_K; i++)
		kcenters[i].adjust_center();
	return is_adjust;
}





/////////////	以下为获得有效数据	//////////////////////
int n_maps = -1; //有效矩阵数 
Map *maps;

int main() {

	//get_data(maps,&n_maps);//读入原始数据 maps数组保存，n_maps表示元素个数 
	vector4 centers[5];
	find_centers(centers,N_K,maps,n_maps);
	init_centers(centers,N_K);
	
	//各簇内数据不再变动作为迭代判断 
	while(divide(maps,n_maps));
	
	for(int i=0;i<N_K;i++) {
		cout<<kcenters[i].num<<' ';
		for(int j=0;j<4;j++) cout<<kcenters[i].center[j]<<' ';
		cout<<endl;
	}
	delete [] maps;
	
	return 0;
}
