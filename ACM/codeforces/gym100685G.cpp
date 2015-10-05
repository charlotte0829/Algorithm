/*********************************************************
  file name: gym100685G.cpp
  author : Sakura_Mashiro
  create time:  2015年10月05日 星期一 08时19分04秒
**********************************************************
http://codeforces.com/gym/100685/problem/G
solution:
	LCA
		以1为根dfs一遍,考虑u,维护u到1的路径上有多少个方向一致
	的边数up,和1到u的路径上方向一致的边数down,对于查询的u和v,
	若up[u]+down[v]-up[lca]-down[lca] == dep[u]+dep[v]-2dep[lca]
	则Yes
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
int n,edge_cnt;
int head[MAXN];
int anc[MAXN][N],dep[MAXN],up[MAXN],down[MAXN];
struct Edge{
	int d,v,next;
}edge[MAXN<<1];
void init(){
	edge_cnt=0;
	memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int d){
	edge[edge_cnt].v=v; edge[edge_cnt].d=d; 
	edge[edge_cnt].next=head[u]; head[u]=edge_cnt++;
}
void dfs(int u,int fa,int depth,int Up,int Down){
	dep[u]=depth; anc[u][0]=fa; up[u]=Up; down[u]=Down;
	REP(i,1,N-1)
		anc[u][i]=anc[anc[u][i-1]][i-1];
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v == fa)
			continue;
		int d = edge[i].d,Up1=Up,Down1=Down;
		if(d == 0)
			Up1++;
		else 
			Down1++;
		dfs(v,u,depth+1,Up1,Down1);
	}
}
int LCA(int u,int v){
	if(dep[u]<dep[v])
		swap(u,v);
	REP(i,0,N-1)
		if(dep[u]-dep[v] & (1<<i)) u=anc[u][i];
	if(u == v)
		return u;
	REPF(i,N-1,0)
		if(anc[u][i]!=anc[v][i])
			u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}
int m;
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%d",&n)){
		init();
		REP(i,1,n-1){
			int u,v;
			RD(u); RD(v);
			addedge(u,v,1); addedge(v,u,0);
		}
		dfs(1,1,0,0,0);
		RD(m);
		while(m--){
			int u,v; 
			RD(u); RD(v);
			int lca=LCA(u,v);
			if(up[u]-up[lca]+down[v]-down[lca] == dep[u]+dep[v]-2*dep[lca])
				puts("Yes");
			else
				puts("No");
		}
	}
	return 0;
}
