#include <iostream>
#include <cmath>
#include <cstring>
///分治

using namespace std;

// Strassen 矩阵乘法 
//适用于 n*n方阵 n为2的幂次 
// 改进方向在原数组操作？ 

//PS:下面代码大部分为数组分块拷贝，(⊙﹏⊙)b
template<class T_>
void Show(T_ *a, int row, int col) {
	for(int i=0; i<row; i++) {
		for(int j=0; j<col; ++j) {
			cout<<*(a+i*col+j)<<' '; 
		}
		cout<<endl;
	}
}

template<class T_>
void MatrixMulti(T_ *A, T_ *B, T_ *C , int row, int col) {
	///任意矩阵相乘 
	///input B , C
	///output A 
	for(int i=0; i<row; ++i) {
		for(int j=0; j<col; ++j) {
			*(A+i*col+j) = 0;
			for(int k=0; k<col; ++k) {
				*(A+i*col+j) += (*(B+col*i+k))*(*(C+row*k+j));
			}
		}
	}	
}
template<class T_>
void MatrixAdd(T_ *A, T_ *B, T_ *C , int row, int col,int type) {
	//type=1,执行+ /// type=-1,执行- 
	for(int i=0; i<row; ++i) {
		for(int j=0; j<col; ++j) {
			*(A+i*col+j) = *(B+i*col+j) + (*(C+i*col+j))*type;
		}
	}
}

template<class T_>
void Strassen(T_ *A, T_ *B, T_ *C , int n) {
	///计算2的幂次阶矩阵乘法 
	///input B , C
	///output A 
	if(n==2) {
		MatrixMulti<T_>(A, B, C, n, n);
		return;	
	}
	if(n>2) {
		Strassen(A, B, C, n/2);
		//矩阵分块 
		T_* a11 = new T_[n/2*n/2];
		for(int i=0; i<n/2; ++i) 
			memcpy(a11+i*n/2, B+n*i, sizeof(T_)*n/2);
		//Show<T_>(a11,n/2,n/2);
		
		T_* a12 = new T_[n/2*n/2];
		for(int i=0; i<n/2; ++i) 
			memcpy(a12+i*n/2, B+n/2+n*i, sizeof(T_)*n/2);
		//Show<T_>(a12,n/2,n/2);
		
		T_* a21 = new T_[n/2*n/2];
		for(int i=0; i<n/2; ++i) 
			memcpy(a21+i*n/2, B+n/2*n+n*i, sizeof(T_)*n/2);
		//Show<T_>(a21,n/2,n/2);
		
		T_* a22 = new T_[n/2*n/2];
		for(int i=0; i<n/2; ++i) 
			memcpy(a22+i*n/2, B+n/2*(n+1)+n*i, sizeof(T_)*n/2);
		//Show<T_>(a22,n/2,n/2);
		
		
		T_* b11 = new T_[n/2*n/2];
		for(int i=0; i<n/2; ++i) 
			memcpy(b11+i*n/2, C+n*i, sizeof(T_)*n/2);
		//Show<T_>(b11,n/2,n/2);
		
		T_* b12 = new T_[n/2*n/2];
		for(int i=0; i<n/2; ++i) 
			memcpy(b12+i*n/2, C+n/2+n*i, sizeof(T_)*n/2);
		//Show<T_>(b12,n/2,n/2);
		
		T_* b21 = new T_[n/2*n/2];
		for(int i=0; i<n/2; ++i) 
			memcpy(b21+i*n/2, C+n/2*n+n*i, sizeof(T_)*n/2);
		//Show<T_>(b21,n/2,n/2);
		
		T_* b22 = new T_[n/2*n/2];
		for(int i=0; i<n/2; ++i) 
			memcpy(b22+i*n/2, C+n/2*(n+1)+n*i, sizeof(T_)*n/2);
		//Show<T_>(b22,n/2,n/2);
		
		T_*c11= new T_[n/2*n/2];
		T_*c12= new T_[n/2*n/2];
		T_*c21= new T_[n/2*n/2];
		T_*c22= new T_[n/2*n/2];
		T_*tmp1 = new T_[n/2*n/2];
		T_*tmp2 = new T_[n/2*n/2];
		T_*m1 = new T_[n/2*n/2];
		T_*m2 = new T_[n/2*n/2];
		T_*m3 = new T_[n/2*n/2];
		T_*m4 = new T_[n/2*n/2];
		T_*m5 = new T_[n/2*n/2];
		T_*m6 = new T_[n/2*n/2];
		T_*m7 = new T_[n/2*n/2];
		//计算 
		MatrixAdd<T_>(tmp1, b12, b22, n/2, n/2, -1); 
		MatrixMulti<T_>(m1, a11, tmp1, n/2, n/2);
		
		MatrixAdd<T_>(tmp1, a11, a12, n/2, n/2, 1);
		MatrixMulti<T_>(m2, tmp1, b22, n/2, n/2);
		
		MatrixAdd<T_>(tmp1, a21, a22, n/2, n/2, 1);
		MatrixMulti<T_>(m3, tmp1, b11, n/2, n/2);
		
		MatrixAdd<T_>(tmp1, b21, b11, n/2, n/2, -1);
		MatrixMulti<T_>(m4, a22, tmp1, n/2, n/2);
		
		MatrixAdd<T_>(tmp1, a11, a22, n/2, n/2, 1);
		MatrixAdd<T_>(tmp2, b11, b22, n/2, n/2, 1);
		MatrixMulti<T_>(m5, tmp1, tmp2, n/2, n/2);
		
		MatrixAdd<T_>(tmp1, a12, a22, n/2, n/2, -1);
		MatrixAdd<T_>(tmp2, b21, b22, n/2, n/2, 1);
		MatrixMulti<T_>(m6, tmp1, tmp2, n/2, n/2);
		
		MatrixAdd<T_>(tmp1, a11, a21, n/2, n/2, -1);
		MatrixAdd<T_>(tmp2, b11, b12, n/2, n/2, 1);
		MatrixMulti<T_>(m7, tmp1, tmp2, n/2, n/2);
		
		MatrixAdd<T_>(tmp1, m5, m4, n/2, n/2, 1);
		MatrixAdd<T_>(tmp2, m6, m2, n/2, n/2, -1);
		MatrixAdd<T_>(c11, tmp1, tmp2, n/2, n/2, 1);
		MatrixAdd<T_>(c12, m1, m2, n/2, n/2, 1);
		MatrixAdd<T_>(c21, m3, m4, n/2, n/2, 1);
		MatrixAdd<T_>(tmp1, m5, m1, n/2, n/2, 1);
		MatrixAdd<T_>(tmp2, m7, m3, n/2, n/2, 1);
		MatrixAdd<T_>(c22, tmp1, tmp2, n/2, n/2, -1);
		
		//矩阵合并，数据拷回 
		for(int i=0; i<n/2; ++i) 
			memcpy(A+n*i, c11+i*n/2, sizeof(T_)*n/2);
		//Show<T_>(c11,n/2,n/2);
		//Show<T_>(A,n,n);
		for(int i=0; i<n/2; ++i) 
			memcpy(A+n/2+n*i, c12+i*n/2, sizeof(T_)*n/2);
		//Show<T_>(c12,n/2,n/2);
		//Show<T_>(A,n,n);
		for(int i=0; i<n/2; ++i) 
			memcpy(A+n/2*n+n*i, c21+i*n/2, sizeof(T_)*n/2);
		//Show<T_>(c21,n/2,n/2);
		//Show<T_>(A,n,n);
		for(int i=0; i<n/2; ++i) 
			memcpy(A+n/2*(n+1)+n*i, c22+i*n/2, sizeof(T_)*n/2);
		//Show<T_>(c22,n/2,n/2);
		//Show<T_>(A,n,n);
		
		
		//内存回收 
		delete []a11;
		delete []a12;
		delete []a21;
		delete []a22;
		delete []b11;
		delete []b12;
		delete []b21;
		delete []b22;
		delete []c11;
		delete []c12;
		delete []c21;
		delete []c22;
		delete []m1;
		delete []m2;
		delete []m3;
		delete []m4;
		delete []m5;
		delete []m6;
		delete []m7;
		delete []tmp1;
		delete []tmp2;
	}
	

}

int main()
{
	int col = 4, row = 4;

	int A[4][4];
	int B[4][4] = {1,2,3,4,7,8,9,10,11,12,13,14,15,16};
	int C[4][4] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	//Show<int>((int*)B,4,4);
	MatrixMulti<int>((int*)A, (int*)B, (int*)C, row, col); 
	for(int i=0; i<row; i++) {
		for(int j=0; j<col; ++j) {
			cout<<A[i][j]<<' '; 
			A[i][j] = 0;
		}
		cout<<endl;
	}
	Strassen<int> ((int*)A, (int*)B, (int*)C, row);
	for(int i=0; i<row; i++) {
		for(int j=0; j<col; ++j) {
			cout<<A[i][j]<<' '; 
		}
		cout<<endl;
	}
	return 0;
}
