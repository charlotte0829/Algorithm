/*********************************************************
  file name: poj3728.cpp
  author : Sakura_Mashiro
  create time:  2015年09月24日 星期四 09时07分40秒
**********************************************************
solution:
	LCA+RMQ
		分析:先求u,v的LCA,然后求u-->LCA-->v的利润最大值,由三种情况组成
			（1）最大值是u->lca的最大值
			（2）最大值是lca->v的最大值
			（3）最大值是lca->v的最大值减u->lca的最小值
			
		anc[i][j]表示结点i的2^j祖先
		up[i][j]表示结点i到结点i的2^j-1祖先获得的最大利润
		down[i][j]表示结点i的2^j-1祖先到结点i获得的最大利润
		dmax[i][j]表示由结点i到结点i的2^j-1祖先的最大值
		dmin[i][j]表示由结点i到结点i的2^j-1祖先的最小值

		转移方程:
			up[u][i]=max(max(up[u][i-1],up[x][i-1]),dmax[x][i-1]-dmin[u][i-1])
			down[u][i]=max(max(down[u][i-1],down[x][i-1]),dmax[u][i-1]-dmin[x][i-1])
			dmax[u][i]=max(dmax[u][i-1],dmax[x][i-1])
			dmin[u][i]=min(dmin[u][i-1],dmin[x][i-1])

		

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
int n,m,edge_cnt;
int head[MAXN],dep[MAXN],a[MAXN];
int anc[MAXN][20];
int down[MAXN][20],up[MAXN][20],dmax[MAXN][20],dmin[MAXN][20];  
struct Edge{
	int v,next;
}edge[MAXN<<1];
void init(){
	edge_cnt=0;
	memset(dep,0,sizeof(dep));
	memset(head,-1,sizeof(head));
}
void addedge(int u,int v){
	edge[edge_cnt].v=v;
	edge[edge_cnt].next=head[u]; head[u]=edge_cnt++;
}
void dfs(int u,int fa,int d){
	dep[u]=d; anc[u][0]=fa;
	up[u][0]=down[u][0]=0; dmax[u][0]=dmin[u][0]=a[u];
	for(int i=1;(1<<i)<=d;i++){
		anc[u][i]=anc[anc[u][i-1]][i-1];
		int x=anc[u][i-1];
		up[u][i]=max(max(up[u][i-1],up[x][i-1]),dmax[x][i-1]-dmin[u][i-1]);
		down[u][i]=max(max(down[u][i-1],down[x][i-1]),dmax[u][i-1]-dmin[x][i-1]);
		dmax[u][i]=max(dmax[u][i-1],dmax[x][i-1]);
		dmin[u][i]=min(dmin[u][i-1],dmin[x][i-1]);
	}
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v == fa)
			continue;
		dfs(v,u,d+1);
	}
}
int LCA(int u,int v){
	if(dep[u]<dep[v])
		swap(u,v);
	for(int i=0;i<15;i++)	
		if((dep[u]-dep[v]) & (1<<i)) u=anc[u][i];
	if(u == v)
		return u;
	for(int i=14;i>=0;i--)
		if(anc[u][i] != anc[v][i])
			u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}
int MIN(int u,int v){
	int k=0;
	while((1<<(k+1))<=dep[u]-dep[v]+1) k++;
	if((1<<k) == dep[u]-dep[v]+1) return dmin[u][k];
	return min(dmin[u][k],MIN(anc[u][k],v));
}
int MAX(int u,int v){
	int k=0;
	while((1<<(k+1))<=dep[u]-dep[v]+1) k++;
	if((1<<k) == dep[u]-dep[v]+1) return dmax[u][k];
	return max(dmax[u][k],MAX(anc[u][k],v));
}
int UP(int u,int v){
	int k=0;
	while((1<<(k+1))<=dep[u]-dep[v]+1) k++;
	if((1<<k) == dep[u]-dep[v]+1) return up[u][k];
	return  max(max(up[u][k],UP(anc[u][k],v)),MAX(anc[u][k],v)-dmin[u][k]);
}
int DOWN(int u,int v){
	int k=0;
	while((1<<(k+1))<=dep[u]-dep[v]+1) k++;
	if((1<<k) == dep[u]-dep[v]+1) return down[u][k];
	return max(max(down[u][k],DOWN(anc[u][k],v)),dmax[u][k]-MIN(anc[u][k],v));
}
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%d",&n)){
		init();
		REP(i,1,n)
			RD(a[i]);
		REP(i,1,n-1){
			int u,v;
			RD(u); RD(v);
			addedge(u,v); addedge(v,u);
		}
		dfs(1,1,1);
		RD(m);
		REP(i,1,m){
			int u,v;
			RD(u); RD(v);
			int lca=LCA(u,v);
			int ans=max(UP(u,lca),DOWN(v,lca));
			ans=max(MAX(v,lca)-MIN(u,lca),ans);
			printf("%d\n",ans);
		}
	}
	return 0;
}
