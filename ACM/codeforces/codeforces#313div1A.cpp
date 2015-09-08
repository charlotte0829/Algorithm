/*********************************************************
  file name: codeforces#313div1A.cpp
  author : kereo
  create time:  2015年07月22日 星期三 21时52分25秒
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
const int N=100+50;
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
#define REP(i,n) for(int i=1;i<=(int)n;i++)
#define FOR(i,v) for(__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
ll a1,a2,a3,a4,a5,a6;
ll f(ll x){
	return x*x;
}
int main(){
	while(~scanf("%lld%lld%lld%lld%lld%lld",&a1,&a2,&a3,&a4,&a5,&a6)){
		ll ans=0;
		ll len=a1+a6+a5;
		ans+=f(len)-f(a1)-f(a5)-f(a3);
		printf("%lld\n",ans);
	}
	return 0;
}
