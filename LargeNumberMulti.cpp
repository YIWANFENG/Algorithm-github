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

void test();
long CharToNum(char a[],int len) {
	//字符数组转long 
	long result = 0;
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

void CharNumAdd(char[] a,char b[],int len,re[]) {
	//re=a-b
	//大数相加 
}

void LargeNumberMulti(char X[], char Y[],int len,int local,char result[]) {
	long a=0, b=0, c=0, d=0, item1, item2, item3;
	if(len<4) {
		a = CharToNum(X,len);
		b = CharToNum(Y,len);
		c = a*b;
		NumToChar(c,result);
		return ;
	}
	char ac[50],bd[50],abdc[50];
	//AC
	LargeNumberMulti(X,Y,len/2,local?,ac);				
	//BD
	LargeNumberMulti(X+len/2,Y+len/2,len/2,local?,bd);	
	//A-B
	//D-C
	//Merge 
}
int main()
{
	char a[] = "1234567823131212";
	char b[40];
	for(int i=0;i<40;++i) b[i] = '0';
	b[39]='\0';
	cout<<"a[]:\n";
	for(int i=0;i<strlen(a);++i) {
		cout<<a[i];
	}
	cout<<endl<<"b[]:\n";
	for(int i=0;i<strlen(b);++i) {
		cout<<b[i];
	}
	cout<<endl;
	
	
	LargeNumberMulti(a, a, strlen(a),0,b);


	for(int i=0;i<30;++i) {
		cout<<b[i]<<' '; 
	}
	//test(); 
	system("pause");
	return 0; 
} 



///////////////////////////////////////////////////////////
///////	相同位数2^k大整数相乘						///////
///////	貌似只能进行2、4位数的计算，过大失效	 	///////
///////	思路正确，缺点在long型表示范围		 		///////
///////////////////////////////////////////////////////////
int length(long x) {
	//判断输入的数字的位数
	int i = 0; 
	do {
		++i;
		x=x/10; 
	}while(x!=0);
	return i;
}

long mult(long x,long y,int n) {
	long a,b,c,d,s,AC,BD;
	if (length(x)==1) //起初这里落了个＝号
		return x*y;
	else
	{
		a=long(x/pow(10,(n/2))); 		//取x的左半部分
		//cout<<"A"<<a<<endl;
		b=long(x%long(pow(10,(n/2))));  //取x的右半部分
		//cout<<"B"<<b<<endl;
		c=long(y/pow(10,(n/2))); 		//取y的左半部分
		d=long(y%long(pow(10,(n/2))));  //取y的右半部分
		AC = long(mult(a,c,n/2));
		BD = long(mult(b,d,n/2));
		s=AC*pow(10,n)+long(mult((a-b),(d-c),length(a-b))+AC+BD)*pow(10,n/2)+BD;//公式
		return (s);
	}
}
void test() {
	long long x,y;
	cout<<"input x,y:"<<endl;
	cin>>x>>y;
	cout<<mult(x,y,length(x))<<endl;
} 


