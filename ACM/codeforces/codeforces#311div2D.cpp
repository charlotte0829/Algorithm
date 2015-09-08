/*********************************************************
 file name: codeforces#311div2D.cpp
 author : kereo
 create time: 2015年07月02日 星期四 14时50分23秒
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
#define REP(i,n) for(int i=0;i<int(n);i++)
#define FOR(i,v) for(__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
int n,m;
int flag,L,R; //标记是否存在奇环
int edge_cnt;
int head[MAXN],deg[MAXN],U[MAXN],V[MAXN],vis[MAXN];
struct Edge{
	int v,next;
}edge[MAXN<<1];
void init(){
	edge_cnt=0;
	memset(deg,0,sizeof(deg));
	memset(vis,0,sizeof(vis));
	memset(head,-1,sizeof(head));
}
void addedge(int u,int v){
	edge[edge_cnt].v=v; 
	edge[edge_cnt].next=head[u]; head[u]=edge_cnt++;
}
void dfs(int u){
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(!vis[v]){
			vis[v]=3-vis[u];
			if(vis[v] == 1)
				L++;
			else
				R++;
			dfs(v);
		}
		if(vis[v]+vis[u]!=3)
			flag=1;
	}
}
int main(){
	while(~scanf("%d%d",&n,&m)){
		init();
		REP(i,m){
			scanf("%d%d",&U[i],&V[i]);
			deg[U[i]]++; deg[V[i]]++;
			addedge(U[i],V[i]); addedge(V[i],U[i]);
		}
		if(m == 0){
			printf("3 %lld\n",(ll)n*(ll)(n-1)*(n-2)/6);
			continue;
		}
		int tag=1;
		REP(i,m){
			if(deg[U[i]] != 1 || deg[V[i]] != 1){
				tag=0; break;
			}
		}
		if(tag){
			printf("2 %lld\n",(ll)m*(ll)(n-2));
			continue;
		}
		flag=0;
		ll ans=0;
		for(int i=1;i<=n;i++){
			if(vis[i])
				continue;
			vis[i]=1;
			L=1,R=0;
			dfs(i);
			if(flag){
				printf("0 1\n");
				break;
			}
			ans+=(ll)L*(ll)(L-1)/2+(ll)R*(ll)(R-1)/2;
		}
		if(!flag)
			printf("1 %lld\n",ans);
	}
	return 0;
}
