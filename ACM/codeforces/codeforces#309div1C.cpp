/*********************************************************
  file name: codeforces#309div1C.cpp
  author : kereo
  create time:  2015年07月04日 星期六 18时24分38秒
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
int n,m;
int edge_cnt;
bool flag;
int head[MAXN],fa[MAXN],vis[MAXN];
struct Edge{
	int v,col,next;
}edge[MAXN<<1];
vector<PII>mp[2];
void init(){
	edge_cnt=0;
	memset(head,-1,sizeof(head));
	REP(i,n)
		fa[i]=i;
	mp[0].clear(); mp[1].clear();
}
int findset(int x){
	return fa[x] == x ? x : fa[x] = findset(fa[x]);
}
void addedge(int u,int v){
	//printf("%d %d\n",u,v);
	edge[edge_cnt].v=v; 
	edge[edge_cnt].next=head[u]; head[u]=edge_cnt++;
}
void dfs(int u){
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(vis[v]){
			if(vis[u] == vis[v]){
				flag=false;
				return;
			}
			continue;
		}
		vis[v]=3-vis[u];
		dfs(v);
	}
}
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%d%d",&n,&m)){
		init();
		REP(i,m){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			mp[c].push_back(mk(a,b));
		}
		FOR(it,mp[1]){
			int u=it->first,v=it->second;
			int fx=findset(u),fy=findset(v);
			if(fx == fy)
				continue;
			fa[fx]=fy;
		}
		int tag=1;
		int cnt=0;
		FOR(it,mp[0]){
			cnt++;
			int u=it->first,v=it->second;
			int fx=findset(u),fy=findset(v);
			//cout<<"u="<<fx<<" v="<<fy<<endl;	
			if(fx == fy){
				tag=0; break;
			}
			addedge(fx,fy); addedge(fy,fx);
		}
		//cout<<"cnt="<<cnt<<endl;
		//printf("gg!\n");
		if(!tag){
			printf("0\n");
			continue;
		}
		memset(vis,0,sizeof(vis));
		ll ans=(mod+1)/2; flag=1;
		REP(i,n){
			if(findset(i) == i && !vis[i]){
				vis[i]=1;
				dfs(i);
				if(flag)
					ans=ans*2%mod;
				else{
					ans=0;
					break;
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
