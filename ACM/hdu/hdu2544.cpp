/*********************************************************
  file name: hdu2544.cpp
  author : Sakura_Mashiro
  create time:  2015年08月24日 星期一 17时38分31秒
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
#define FOR(i,v) for(__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
int n,m;
int edge_cnt;
int head[MAXN],d[MAXN],inq[MAXN];
struct Edge{
	int v,w;
	int next;
}edge[MAXN<<1];
void init(){
	edge_cnt=0;
	memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int w){
	edge[edge_cnt].v=v;  edge[edge_cnt].w=w;
	edge[edge_cnt].next=head[u]; head[u]=edge_cnt++;
}
void spfa(){
	queue<int>que;
	REP(i,1,n)
		d[i]=inf;
	memset(inq,0,sizeof(inq));
	d[1]=0;
	que.push(1); inq[1]=1;
	while(!que.empty()){
		int u=que.front(); que.pop();
		inq[u]=0;
		for(int i=head[u];i!=-1;i=edge[i].next){
			int v=edge[i].v;
			if(d[u]+edge[i].w<d[v]){
				d[v]=d[u]+edge[i].w;
				if(!inq[v]){
					inq[v]=1;
					que.push(v);
				}
			}
		}
	}
}
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%d%d",&n,&m) && n+m){
		init();
		REP(i,1,m){
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			addedge(u,v,w); addedge(v,u,w);
		}
		spfa();
		printf("%d\n",d[n]);
	}
	return 0;
}
