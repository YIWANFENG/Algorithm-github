#include <iostream>
#include <cmath> 
#include <cstring>
///分治

using namespace std;

//大数相乘  PS:关注于思想而非实现，so 程序含错。 
//  X = [AB]    Y = [CD]
//  X = A*2^n+B    Y = C*2^n+D
//  XY = (A*2^n+B)(C*2^n+D) = AC*2^n + (AD+BC)*2^n + BD
//  XY =  AC*2^n + ((A-B)(D-C)+AC+BD)*2^n + BD


long long CharToNum(char a[],int len) {
	//字符数组转long long 
	long long result = 0;
	if(len==0) return result; 
	if(a[0] == '-') {
		for(int i=1; i<len; ++i){
			result = result*10+(a[i]-'0'+0); 
		}
		return -result;
	} 
	else {
		for(int i=0; i<len; ++i){
			result = result*10+(a[i]-'0'+0); 
		}
		return result;
	}
}

void NumToChar(long long a, char re[]) {
	char it[20];
	int i=0,k=0;
	while(a!=0) {
		it[i++] = (a%10)+'0';
		a /= 10;
	}
	it[i] = '\0';
	for(int j=strlen(it)-1; j>=0; --j) {
		re[k++] = it[j];
		//cout<<it[j]<<' ';
	}
	//cout<<strlen(it)<<'$'<<k<<endl;
	re[k] = '\0';
}


void LargeNumberMulti(char X[], char Y[],int len,char result[]) {
	//可计算16以下位数的乘法 
	long long a=0, b=0, c=0, d=0, item1, item2, item3;
	a = CharToNum(X,len/2);
	b = CharToNum(X+len/2,len/2);
	c = CharToNum(Y,len/2);
	d = CharToNum(Y+len/2,len/2);
	//cout<<a<<endl<<b<<endl<<c<<endl<<d<<endl;
	
	item1 = a*c;
	item2 = ((a-b)*(d-c)+a*c+b*d);
	item3 = b*d;
	cout<<item1<<endl<<item2<<endl<<item3<<endl;
	
	/*
	//移位部分未做 
	char it1[20], it2[20], it3[20];
	NumToChar(item1,it1);
	NumToChar(item2,it2);
	NumToChar(item3,it3);
	//cout<<it1<<endl<<it2<<endl<<it3<<endl; 
	//ERROR
	strcpy(result,it1);
	result[strlen(it1)] = '0';
	strcpy(result+len/2,it2);
	result[strlen(it2)] = '0';
	strcpy(result+len/2+len,it3);
	*/
}
int main() 
{
	char a[] = "12345678";
	char b[40];
	for(int i=0;i<40;++i) b[i] = '0';
	
	LargeNumberMulti(a, a, strlen(a),b);
	
	for(int i=0;i<30;++i) {
		cout<<b[i]<<' '; 
	}
	//cout<<b<<endl;
	return 0; 
} 
