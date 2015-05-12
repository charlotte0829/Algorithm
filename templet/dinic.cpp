/*********************************************************
  file name: dinic.cpp
  author : kereo
  create time:  2015年05月12日 星期二 15时49分07秒
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
int edge_cnt;
bool vis[MAXN];
int head[MAXN],cur[MAXN],d[MAXN]; 
struct Edge{
	int v,cap,flow,next;
}edge[MAXN<<1];
void init(){
	edge_cnt=0;
	memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int cap){
	edge[edge_cnt].v=v; edge[edge_cnt].cap=cap; 
	edge[edge_cnt].flow=0; edge[edge_cnt].next=head[u]; head[u]=edge_cnt++;	
	edge[edge_cnt].v=u; edge[edge_cnt].cap=0;
	edge[edge_cnt].flow=0; edge[edge_cnt].next=head[v]; head[v]=edge_cnt++;
}
bool bfs(int st,int ed){ //bfs构造分层网络
	queue<int>que;
	memset(d,-1,sizeof(d));
	memset(vis,false,sizeof(vis));
	d[st]=0; vis[st]=true; que.push(st);
	while(!que.empty()){
		int u=que.front(); que.pop();
		for(int i=head[u];i!=-1;i=edge[i].next){
			int v=edge[i].v;
			if(!vis[v] && edge[i].cap>edge[i].flow){
				vis[v]=true;
				d[v]=d[u]+1; que.push(v);
			}
		}
	}
	return vis[ed];
}
int dfs(int u,int ed,int low){ //dfs沿阻塞流增广
	if(u == ed || low == 0)  //low表示从源点到当前结点u为止所有弧的最小残量,low == 0及时剪枝
		return low;
	int flow=0,f;
	for(int& i=cur[u];i!=-1;i=edge[i].next){ //cur[]记录当前结点上次考虑的弧
		int v=edge[i].v;
		if(d[v] == d[u]+1 && (f=dfs(v,ed,min(low,edge[i].cap-edge[i].flow)))>0){
			edge[i].flow+=f; 
			edge[i^1].flow-=f;
			flow+=f; low-=f;
			if(low == 0)
				break;
		}
	}
	return flow;
}
int dinic(int st,int ed){
	int flow=0;
	while(bfs(st,ed)){
		memcpy(cur,head,sizeof(cur));
		flow+=dfs(st,ed,inf);
	}
	return flow;
}
