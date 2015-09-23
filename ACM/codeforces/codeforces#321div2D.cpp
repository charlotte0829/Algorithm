/*********************************************************
  file name: codeforces#321div2D.cpp
  author : Sakura_Mashiro
  create time:  2015年09月23日 星期三 10时06分46秒
**********************************************************
solution:
	bitmask+dp
		mp[i][j]记录下从i到j增加的满足度,dp[s][i]记录状态为s,刚上的dish为i的最大
	满足度,dp转移一下即可
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
const int N=20;
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
int n,m,k;
ll a[N],mp[N][N],dp[1<<N][N];
void init(){
	memset(mp,0,sizeof(mp));
	memset(dp,0,sizeof(dp));
}
int main(){
	//freopen("in.txt","r",stdin);
	RD(n); RD(m); RD(k);
	init();
	REP(i,1,n)
		RD(a[i]);
	REP(i,1,k){
		int x,y,c;
		RD(x); RD(y); RD(c);
		mp[x][y]=c;
	}
	for(int i=0;i<n;i++)
		dp[1<<i][i]=a[i+1];
	for(int s=1;s<(1<<n);s++){
		for(int i=0;i<n;i++){
			if((s & (1<<i)) == 0)
				continue;
			for(int j=0;j<n;j++){
				if((s & (1<<j)) == 0)
					continue;
				if(i == j)
					continue;
				dp[s][j]=max(dp[s][j],dp[s^(1<<j)][i]+mp[i+1][j+1]+a[j+1]);
			}
		}
	}
	ll ans=0;
	for(int s=1;s<(1<<n);s++){
		int num=0;
		for(int i=0;i<n;i++)
			if(s & (1<<i))
				num++;
		if(num == m){
			for(int i=0;i<n;i++)
				if(s & (1<<i))
					ans=max(ans,dp[s][i]);
		}
	}
	cout<<ans<<endl;
	return 0;
}
