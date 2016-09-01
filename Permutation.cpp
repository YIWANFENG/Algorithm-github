#include <iostream>
#include <cmath>

using namespace std;

template<typename T_>
inline void Swap(T_ &a, T_ &b){
	T_ item = a;
	a = b;
	b = item;
}

template<typename T_>
void Permutation(T_ list[], int i_start, int i_end){
	if(i_start == i_end){
		for(int i=0; i<=i_end; ++i) 
			cout<<list[i]<<' ';
		cout<<endl;
	} 
	else {
		for(int i=i_start; i<=i_end; ++i){
			Swap<T_>(list[i_start], list[i]);
			Permutation<T_>(list, i_start+1, i_end);
			Swap<T_>(list[i_start], list[i]);
		}
	}
}
int main()
{
	int list[]={1,2,3,4,5};
	Permutation<int>(list, 0, 3);
} 
