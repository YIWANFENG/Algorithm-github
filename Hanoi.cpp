#include <iostream>

using namespace std;

//汉诺塔移动

void move(int a,int b) {
	cout<<"move "<<a<<" to"<<b<<endl; 
}
void move(int n,int a,int b) {
	cout<<"move "<<n<<" from "<<a<<" to "<<b<<endl; 
}
 
void hanoi(int n, int a, int b, int c) {
	if(n>0) {
		hanoi(n-1, a, c, b);
		move(a,b);
		hanoi(n-1, c, b, a);
	}
} 

void hanoi2(int n, int x, int y, int z) {
	//将塔x上按直径从大到小且自上而下编号为1-n的n个原盘按规则
	//搬到z,y辅助 
	if(n==1) move(1,x,z);
	else {
		hanoi2(n-1, x, z, y);
		move(n, x, z);
		hanoi2(n-1, y, x, z);
	}
} 
int main()
{
	int n;
	cout<<"输入塔数"<<endl;
	cin>>n;
	//hanoi(n, 1, 2, 3);	
	hanoi2(n, 1, 2, 3);
	return 0; 
} 
