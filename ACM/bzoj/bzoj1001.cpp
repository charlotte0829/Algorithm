/*********************************************************
  file name: bzoj1001.cpp
  author : Sakura_Mashiro
  create time:  2015年08月28日 星期五 17时19分24秒
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
const int MAXN=2000000+50;
const int inf=0x3f3f3f3f;
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
int S,T,edge_cnt=0;
int head[MAXN];
struct Edge{
	int v,w;
	int next;
}edge[MAXN*3];
void addedge(int u,int v,int w){
	edge[edge_cnt].v=v; edge[edge_cnt].w=w;
	edge[edge_cnt].next=head[u]; head[u]=edge_cnt++;
}
void init(){
	edge_cnt=0;
	memset(head,-1,sizeof(head));
}
bool vis[MAXN];
int d[MAXN];
struct HeapNode{
	int u,d;
	bool operator < (const HeapNode &rhs) const{
		return d>rhs.d;
	}
};
void Dijistra(){
	priority_queue<HeapNode>que;
	memset(vis,0,sizeof(vis));
	memset(d,0x3f,sizeof(d));
	d[S]=0;  
	que.push((HeapNode){S,0});
	while(!que.empty()){
		HeapNode now=que.top(); que.pop();
		int u=now.u; vis[u]=1;
		if(u == T)
			return ;
		for(int i=head[u];i!=-1;i=edge[i].next){
			int v=edge[i].v;
			if(vis[v])
				continue;
			if(d[v]>d[u]+edge[i].w){
				d[v]=d[u]+edge[i].w;
				que.push((HeapNode){v,d[v]});
			}
		}
	}
}
int n,m;
int main(){
	//freopen("in.txt","r",stdin);
	RD(n),RD(m);
	init();
	S=0; T=(n-1)*(m-1)*2+1;
	REP(i,1,n){
		REP(j,1,m-1){
			int w;
			RD(w);
			int u=(i-1)*(m-1)*2+j;
			int v=(i-1)*(m-1)*2+j-(m-1);
			if(i == 1)
				v=T;
			if(i == n)
				u=S;
			addedge(u,v,w); addedge(v,u,w);
		}
	}
	REP(i,1,n-1){
		REP(j,1,m){
			int w;
			RD(w);
			int u=(i-1)*(m-1)*2+j-1;
			int v=(i-1)*(m-1)*2+(m-1)+j;
			if(j == 1)
				u=S;
			if(j == m)
				v=T;
			addedge(u,v,w); addedge(v,u,w);
		}
	}
	REP(i,1,n-1){
		REP(j,1,m-1){
			int w;
			RD(w);
			int u=(i-1)*(m-1)*2+(m-1)+j;
			int v=(i-1)*(m-1)*2+j;
			addedge(u,v,w); addedge(v,u,w);
		}
	}
	Dijistra();
	if(d[T] == inf)
		d[T]=0;
	PT(d[T]); puts("");
	return 0;
}
