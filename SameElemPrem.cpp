#include <iostream>
#include <algorithm>


///有重复元素的全排列问题 

using namespace std;

template<typename T_>
inline void Swap(T_ &a, T_ &b){
	T_ item = a;
	a = b;
	b = item;
}

template<typename T_>
void Permutation(T_ list[], int i_start, int i_end){
	//对含重复元素的list全排列并输出 
	//需排列的数组 list
	
	if(i_start == i_end){
		for(int i=0; i<=i_end; ++i) 
			cout<<list[i]<<' ';
		cout<<endl;
	} 
	else {
		
		for(int i=i_start; i<=i_end; ++i){
			bool fg = true;
			for(int j=i_start; j<i; ++j) {
				if(list[j]==list[i]) {
					fg = false;
					break;
				}
			}
			if(!fg) continue;
			Swap<T_>(list[i_start], list[i]);
			Permutation<T_>(list, i_start+1, i_end);
			Swap<T_>(list[i_start], list[i]);
		}
	}
}
int test0()
{
	int list[]={4,4,5,6,6};
	Permutation<int>(list, 0, sizeof(list)/sizeof(int)-1);
	cout<<"键入任意键退出\n";
	getchar();
} 
/////////////////////////////////////////////////
void BySTL() {
	
	int a[]={1,1,6,7,8};
	
	while(next_permutation(a,a+5))
	{
		for(int i = 0; i < 5; i++)
			printf("%d ", a[i]);
		printf("\n");
	}
} 

int main()
{
	test0();
	//BySTL();
    return 0;
}




