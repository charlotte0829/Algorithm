/*********************************************************
  file name: codeforces#313div1C.cpp
  author : kereo
  create time:  2015年07月23日 星期四 09时53分23秒
*********************************************************/
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
const int MAXN=200000+50;
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
#define REP(i,n) for(int i=1;i<=(int)n;i++)
#define FOR(i,v) for(__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
int n,m,k;
PII p[N];
ll f[MAXN],dp[N];
ll num_pow(ll a,int k){
	ll ans=1;
	a%=mod;
	while(k){
		if(k&1)
			ans=ans*a%mod;
		k>>=1;
		a=a*a%mod;
	}
	return ans;
}
ll C(int n,int m){
	return f[n]*num_pow(f[n-m]*f[m],mod-2)%mod;
}
int main(){
	f[0]=1;
	REP(i,MAXN-1)
		f[i]=f[i-1]*i%mod;
	while(~scanf("%d%d%d",&n,&m,&k)){
		REP(i,k){
			int x,y;
			scanf("%d%d",&x,&y);
			p[i]=mk(x,y);
		}
		p[0]=mk(1,1); p[++k]=mk(n,m);
		sort(p,p+k);
		dp[0]=1;
		REP(i,k){
			dp[i]=C(p[i].first+p[i].second-2,p[i].first-1);
			for(int j=1;j<i;j++){
				if(p[j].first<=p[i].first && p[j].second<=p[i].second)
					dp[i]=(dp[i]-C(p[i].first-p[j].first+p[i].second-p[j].second,p[i].first-p[j].first)*dp[j])%mod;
			}
		}
		printf("%lld\n",(dp[k]%mod+mod)%mod);
	}
	return 0;
}
