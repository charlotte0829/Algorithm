/*********************************************************
  file name: hdu5001.cpp
  author : Sakura_Mashiro
  create time:  2015年09月05日 星期六 19时57分03秒
**********************************************************
solution:
	设dp[i][j]表示经过j步当前在i点的概率
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
const int N=50+10;
const int MAXN=10000+50;
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
int n,m,d;
double dp[N][MAXN];
vector<int>mp[N];
void init(){
	REP(i,0,n)
		mp[i].clear();
}
double solve(int u){
	memset(dp,0,sizeof(dp));
	double ans=0.0;
	dp[0][0]=1.0; 
	REP(i,0,d){
		REP(j,0,n){
			if(u == j)
				continue;
			int sz=mp[j].size();
			for(int k=0;k<sz;k++){
				int v=mp[j][k];
				dp[v][i+1]+=dp[j][i]*1.0/sz;
			}
		}
		ans+=dp[u][i+1];
	}
	return 1-ans;
}
int main(){
	//freopen("in.txt","r",stdin);
	int T;
	RD(T);
	while(T--){
		RD(n); RD(m); RD(d);
		init();
		REP(i,1,m){
			int u,v;
			RD(u); RD(v);
			mp[u].push_back(v); mp[v].push_back(u);
		}
		REP(i,1,n)
			mp[0].push_back(i);
		REP(i,1,n)
			printf("%.10lf\n",solve(i));
	}
	return 0;
}
