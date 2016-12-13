#include <iostream>
#include <cmath>
#include <string.h>
#include <Windows.h>

//求解 x,y最长公共字串 

using namespace std;



const int n = 20;
const int m = 20;
//记录最长子序列 n ,m比对应字符串长度至少大1 

int c[n][m];  //记录字串长度 
int b[n][m];  //记录c[i][j]来源 




void LCSLength(int n,int m,const char *x,const char *y) {
	//n序列x字符数，m序列y字符数 
	for(int i=0;i<=n;++i) c[i][0]=0;
	for(int i=0;i<=m;++i) c[0][i]=0;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			if(x[i-1]==y[j-1]) {
				//x[i]==y[i]，才是真正的在字串中
				c[i][j]=c[i-1][j-1]+1;
				b[i][j]=1;
			} else if(c[i-1][j]>=c[i][j-1]) {
				//由上面继承 
				c[i][j]=c[i-1][j];
				b[i][j]=2;
			} else {
				//由左面继承 
				c[i][j]=c[i][j-1];
				b[i][j]=3;
			}
		}
	}
}
void LCS(int i,int j,const char *x) {
	if(i==0 || j==0) return ;
	if(b[i][j]==1) {   
		LCS(i-1,j-1,x);
		cout<<x[i-1];
	} else if(b[i][j]==2) 
		LCS(i-1,j,x);
	else 
		LCS(i,j-1,x);
}

int main(int argc,char*argv[]) {
	
	const char *x="adcd";
	const char *y="adscaxzd";
	//memset(c,0,n*m*sizeof(int));
	//memset(b,0,n*m*sizeof(int));
	LCSLength(strlen(x),strlen(y),x,y);
	for(int i=0;i<strlen(x)+1;++i) {
		for(int j=0;j<strlen(y)+1;++j) {
			cout<<c[i][j];
		}
		cout<<endl;
	} 
	LCS(strlen(x),strlen(y),x);
	
	return 0;
}
