/*********************************************************
  file name: hdu5003.cpp
  author : Sakura_Mashiro
  create time:  2015年09月22日 星期二 14时55分23秒
**********************************************************
solution:
**********************************************************/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<set>
#include<map>
#include<vector>
#include<stack>
#include<cmath>
#include<string>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int sigma_size=26;
const int N=50+5;
const int MAXN=100000+50;
const int inf=0x3fffffff;
const double eps=1e-8;
const int HASH=100007;
const int mod=1000000000+7;
#define L(x) (x<<1)
#define R(x) (x<<1|1)
#define Ls(x) (x->ch[0])
#define Rs(x) (x->ch[1])
#define PII pair<int, int>
#define mk(x,y) make_pair((x),(y))
#define REP(i,a,b) for(int i=(int)a;i<=(int)b;i++)
#define REPF(i,a,b) for(int i=(int)a;i>=(int)b;i--)
template<class T>
inline bool RD(T & res){
	char c;
	int sgn;
	if(c=getchar(),c == EOF) return 0;
	while(c!='-' && (c<'0' || c>'9')) c=getchar();
	sgn=(c == '-') ? -1 : 1;
	res=(c == '-') ? 0 : c-'0';
	while(c=getchar(),c>='0' && c<='9') res=res*10+(c-'0');
	res*=sgn;
	return 1;
}
template<class T>
inline void PT(T x){
	if(x < 0){
		putchar('-');
		x=-x;
	}
	if(x > 9) PT(x/10);
	putchar(x % 10 + '0');
}
int n;
int a[N];
double base[N];
bool cmp(int a,int b){
	return a>b;
}
int main(){
	base[0]=1.0;
	REP(i,1,N-1)
		base[i]=base[i-1]*0.95;
	int T; RD(T);
	while(T--){
		RD(n);
		REP(i,1,n)
			RD(a[i]);
		sort(a+1,a+n+1,cmp);
		double ans=0;
		REP(i,1,n)
			ans+=a[i]*base[i-1];
		printf("%.10f\n",ans);
	}
	return 0;
}
