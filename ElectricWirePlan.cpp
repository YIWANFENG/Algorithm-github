#include <iostream> 
using namespace std; 

const int N = 10;
//懒得看了，题目表述令人难受 


void MNS(int C[],int n,int **size)
{
	//C[i] = Pi(i) i对应的下接线柱 
	//n 上接线柱个数
	//size[][] 保存 最大不相交子集的元素数  
	for(int j=0;j<C[1];j++)
		size[1][j]=0;

	for(int j=C[1]; j<=n; j++)
		size[1][j]=1;

	for(int i=2; i<n; i++)	{
		for(int j=0; j<C[i]; j++)
			size[i][j]=size[i-1][j];//当i<c[i]的情形
		for(int j=C[i]; j<=n; j++)
			//当j>=c[i]时，考虑(i，c[i])是否属于MNS(i,j)的两种情况
			size[i][j]=size[i-1][j]>(size[i-1][C[i]-1]+1)?size[i-1][j]:(size[i-1][C[i]-1]+1);
	}
	size[n][n]=max(size[n-1][n],size[n-1][C[n]-1]+1);
}

void Traceback(int C[],int **size,int n,int Net[],int& m)
{
	//C[i] = Pi(i) i对应的下接线柱 
	//n 上接线柱个数
	//size[][] 保存 最大不相交子集的元素数
	//Net 结果 
	// m 连线数 
	int j=n;
	m=0;
	for(int i=n;i>1;i--) {
		if(size[i][j]!=size[i-1][j]) { //此时，(i,c[i])是最大不相交子集的一条边
			Net[m++]=i;
			j=C[i]-1;//更新扩展连线柱区间
		}
	}
	if(j>=C[1]) {	//处理i=1的情形
		Net[m++]=1;
	}
}


int main()
{
	int c[] = {0,8,7,4,2,5,1,9,3,10,6};//下标从1开始
	
	int **size = new int *[N+1];
	for(int i=0; i<=N; i++) {
		size[i] = new int[N+1];
	}

	MNS(c,N,size);

	cout<<"电路布线最大不相交连线数目为："<<size[N][N]<<endl;

	int Net[N],m;
	Traceback(c,size,N,Net,m);

	cout<<"最大不相交连线分别为："<<endl;
	for(int i=m-1; i>=0; i--) {
		cout<<"("<<Net[i]<<","<<c[Net[i]]<<") ";
	}
	cout<<endl;
	cin.get();
	return 0;
}
