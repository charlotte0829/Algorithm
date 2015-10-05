/*********************************************************
  file name: BubbleCup8B.cpp
  author : Sakura_Mashiro
  create time:  2015年10月05日 星期一 10时59分07秒
**********************************************************
http://codeforces.com/contest/575/problem/B
solution:
	LCA
		以1为根dfs一遍,对于有根树以下面的点代表当前的边,维护
	从下到上经过这条边的次数up和从上到下经过这条边的次数down,
	最后根据方向累加违约金额即可
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
int n,K,edge_cnt;
int head[MAXN];
int anc[MAXN][N],up[MAXN],down[MAXN],dep[MAXN],cost[MAXN*10];
struct Edge{
	int d,v,next;
}edge[MAXN<<1];
void init(){
	edge_cnt=0;
	memset(up,0,sizeof(up));
	memset(down,0,sizeof(down));
	memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int d){
	edge[edge_cnt].d=d; edge[edge_cnt].v=v;
	edge[edge_cnt].next=head[u]; head[u]=edge_cnt++;
}
void dfs(int u,int fa,int depth){
	dep[u]=depth; anc[u][0]=fa;
	REP(i,1,N-1)
		anc[u][i]=anc[anc[u][i-1]][i-1];
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v == fa)
			continue;
		dfs(v,u,depth+1);
	}
}
int LCA(int u,int v){
	if(dep[u]<dep[v])
		swap(u,v);
	REP(i,0,N-1)
		if(dep[u]-dep[v] & (1<<i)) u=anc[u][i];
	if(u == v)
		return v;
	REPF(i,N-1,0)
		if(anc[u][i]!=anc[v][i])
			u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}
int ans;
void DFS(int u,int fa){
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v == fa)
			continue;
		int d1 = edge[i].d;
		int d2 = edge[i^1].d;
		DFS(v,u);
		if(d2 == 0){
			ans+=cost[up[v]];
			if(ans>=mod)
				ans%=mod;
		}
		if(d1 == 0){
			ans+=cost[down[v]];
			if(ans>=mod)
				ans%=mod;
		}
		up[u]+=up[v]; down[u]+=down[v];
	}	
}
int main(){
	//freopen("in.txt","r",stdin);
	cost[0]=0; cost[1]=1;
	REP(i,2,10*MAXN-1)
		cost[i]=cost[i-1]*2%mod;
	REP(i,2,10*MAXN-1)
		cost[i]=(cost[i-1]+cost[i])%mod;
	while(~scanf("%d",&n)){
		init();
		REP(i,1,n-1){
			int u,v,d;
			RD(u); RD(v); RD(d);
			if(d == 1){
				addedge(u,v,1); addedge(v,u,0);
			}
			else{
				addedge(u,v,1); addedge(v,u,1);
			}
		}
		dfs(1,1,0);
		RD(K);
		int pre=1;
		while(K--){
			int now; RD(now);
			int lca=LCA(pre,now);
			up[pre]++; up[lca]--;
			down[lca]--; down[now]++;
			pre=now;
		}
		ans=0; 
		DFS(1,1);
		printf("%d\n",ans);
	}
	return 0;
}
