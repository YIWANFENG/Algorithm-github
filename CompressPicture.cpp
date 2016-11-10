#include <iostream>
#include <stdlib.h>
#include <time.h>

//图像分段压缩 
using namespace std;


int Length(int i) {
	//求该像素占用几位空间 
	int k=1;
	i/=2;
	while(i>0) {
		k++;
		i/=2;
	}
	return k;
}
void Compress(int n,int p[],int s[],int L[],int b[],int bseg[])
{
	//n像素数，p[]每个像素的值
	//s以i为最后元素的所有分段的元素占用位数
	//L[i]以i为最后元素的分段与之前分段的元素数
	//b[]每像素占用的位数  
	//bseg[]以i为最后元素的分段像素最大占用位数
	 
	int Lmax = 256,header=11;
	s[0]=0;
	for(int i=1;i<=n;i++) {
		b[i]=Length(p[i]);
		int bmax = b[i];
		s[i]=s[i-1]+bmax;
		L[i]=1;
		for(int j=2;j<=i&&j<=Lmax;++j){
			if(bmax<b[i-j+1]) bmax = b[i-j+1];
			if(s[i]>s[i-j]+j*bmax) {
				s[i]= s[i-j]+j*bmax;
				L[i]=j;
				bseg[i] = bmax;
			}
		}
		s[i]+=header;		
	}	
}

void Traceback(int n,int &i,int s[],int L[]) 
{
	if(n==0) return ;
	Traceback(n-L[n],i,s,L);
	s[i++]=n-L[n]; //传出每分段开始位置 
	//cout<<s[i-1]<<endl; 
} 

void Print(int s[],int L[],int bseg[],int n)
{
	cout<<"理想值是"<<s[n]<<endl;
	int m =0;
	Traceback(n,m,s,L);
	s[m]=n;
	cout<<"分成"<<m<<"段\n" ;
	for(int j=1;j<=m;j++) {
		L[j]=L[s[j]];
		bseg[j]=bseg[s[j]];
	}
	for(int j=1;j<=m;j++) {
		cout<<"分段大小："<<L[j]<<" 该段每元素占位 "<<bseg[j]<<endl;
	}
}

int main(int argc,char *argv[]) 
{
	int p[1024+1];
	int s[1024+1];
	int L[1024+1],b[1024+1],bseg[1024+1];
	srand(time(NULL));
	for(int i=0;i<1024+1;i++){
		if(i<=100) p[i] = 3;
		if(100<i&&i<=200) p[i] = 45;
		if(200<i&&i<=300) p[i] = 125;
		if(i>300) p[i]=rand()%254+1;
	}
	Compress(350,p,s,L,b,bseg);
	Print(s,L,bseg,350);
	cin.get();
	return 0;
}
