/*********************************************************
  file name: hdu5000.cpp
  author : Sakura_Mashiro
  create time:  2015年09月05日 星期六 18时24分41秒
**********************************************************
solution:
	由Diworth theorem知,最长反链=最小链覆盖,最小链覆盖取决
于结点最多的一行,每一行里的向量和相同，题目可转变为:
	设和为x且小于等于向量T的向量个数为cnt(x)
	那么ans=max(cnt(x),x=1..sum(Ti)),dp一下即可
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
const int N=2000+50;
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
int n,sum;
int x[N],dp[N];
int main(){
	int T;
	RD(T);
	while(T--){
		RD(n);
		memset(dp,0,sizeof(dp));
		sum=0; dp[0]=1;
		REP(i,1,n){
			RD(x[i]);
			sum+=x[i];
		}
		REP(i,1,n){
			REPF(j,sum,0){
				REP(k,1,x[i])
					if(j-k>=0){
						dp[j]=dp[j]+dp[j-k];
						if(dp[j]>=mod)
							dp[j]%=mod;
				}
			}
		}
		PT(dp[sum/2]); puts("");
	}
	return 0;
}
