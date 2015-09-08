/*********************************************************
  file name: codeforces#308div2D.cpp
  author : kereo
  create time:  2015年07月05日 星期日 17时25分21秒
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
const int MAXN=2000+50;
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
int n;
int x[MAXN],y[MAXN];
map<PII,int>mp;
int gcd(int a,int b){
	return b == 0 ? a : gcd(b,a%b);
}
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%d",&n)){
		mp.clear();
		REP(i,n)
			scanf("%d%d",&x[i],&y[i]);
		int ans=0;
		REP(i,n){
			for(int j=i+1;j<=n;j++){
				int dx=x[j]-x[i];
				int dy=y[j]-y[i];
				int tmp=gcd(abs(dx),abs(dy));
				dx/=tmp; dy/=tmp;
				if(dy<0)
					dx*=-1,dy*=-1;
				if(dy == 0)
					dx=1;
				if(dx == 0)
					dy=1;
				mp[make_pair(dx,dy)]++;
			}
			ans+=(n-i)*(n-i-1)/2;
			FOR(it,mp){
				int num=it->second;
				ans-=num*(num-1)/2;
			}
			mp.clear();
		}
		printf("%d\n",ans);
	}
	return 0;
}
