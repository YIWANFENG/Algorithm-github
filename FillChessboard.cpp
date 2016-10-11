#include <iostream>
#include <cmath>
//分治

using namespace std;
const int n = 8;
int Board[n][n];
int tile=1;
void FillChessBoard(int tr, int tc, int dr, int dc, int size) {
	/// tr,tc 左上角行列号 
	/// dr, dc 特殊方格行列号
	/// size = 2^k 
	
	if(size == 1) return;
	int t = tile++;//L形骨牌号
	int s = size/2;//分割棋盘
	
	//填充左上角子棋盘
	if(dr<tr+s && dc<tc+s)
		FillChessBoard(tr,tc,dr,dc,s);//特殊方格在此
	else {
		Board[tr+s-1][tc+s-1] = t;//骨牌填充右下角
		FillChessBoard(tr,tc,tr+s-1,tc+s-1,s);//骨牌填充左下角 
	} 
	
	//填充右上角子棋盘
	if(dr<tr+s && dc>=tc+s) 
		FillChessBoard(tr,tc+s,dr,dc,s);//特殊方格在此
	else {
		Board[tr+s-1][tc+s] = t;//骨牌填充左下角
		FillChessBoard(tr,tc+s,tr+s-1,tc+s,s); //骨牌填充左下角
	}
	
	//填充左下角
	if(dr>=tr+s && dc<tc+s)
		FillChessBoard(tr+s,tc,dr,dc,s);//特殊方格在此
	else {
		Board[tr+s][tc+s-1] = t;//骨牌填充右上角
		FillChessBoard(tr+s,tc,tr+s,tc+s-1,s); 
	}
	
	//填充右下角
	if(dr>=tr+s && dc>=tc+s)
		FillChessBoard(tr+s,tc+s,dr,dc,s);//特殊方格在此
	else {
		Board[tr+s][tc+s] = t;//骨牌填充右上角
		FillChessBoard(tr+s,tc+s,tr+s,tc+s,s); 
	}
	
} 

int main() 
{
	FillChessBoard(0,0,4,4,8);
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout<<Board[i][j]<<'\t';
		}
		cout<<endl;
	}
	system("pause"); 
	return 0; 
}
