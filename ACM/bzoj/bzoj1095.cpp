/*********************************************************
  file name: bzoj1095.cpp
  author : Sakura_Mashiro
  create time:  2015年10月06日 星期二 16时52分06秒
**********************************************************
solution:
	动态树分治+堆
		将每次分治的重心连成一个树,易知树的深度为logn,每次修改一个
	结点我们只需要更新从当前结点到树根的这条链
		我们对每个结点维护两个堆heap1,heap2;不妨设当前考虑的结点为u,
	fa为重心构成的树中u的父结点,那么heap1[u]存以u为根的子树中结点(off状态)
	经过u到fa的距离;heap2[u]存u的各个子树到u距离的最大值;那么一个结点的heap2
	的最大值和次大值加起来就是子树中经过这个结点的最长链,然后我们开一个全局
	的堆ans记录所有heap2中最大值与次大值的和,那么全局的堆顶就是答案	
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
int n,m;
int Log[MAXN<<1];
int edge_cnt,size,root;
int head[MAXN],dp[MAXN],sz[MAXN],vis[MAXN];
struct Edge{
	int v,next;
}edge[MAXN<<1];
int dfs_clock;
int pos[MAXN],dep[MAXN],d[MAXN<<1][N];
int anc[MAXN]; //构成重心链
struct Heap{
	priority_queue<int>que1,que2;
	inline void push(int x){
		que1.push(x);
	}
	inline void erase(int x){
		que2.push(x);
	}
	inline void pop(){
		while(que2.size() && que1.top() == que2.top())
			que1.pop(),que2.pop();
		que1.pop();
	}
	inline int top(){
		while(que2.size() && que1.top() == que2.top())
			que1.pop(),que2.pop();
		if(!que1.size())
			return 0; 
		return que1.top();
	}
	inline int size(){
		return que1.size()-que2.size();
	}
	inline int stop(){
		if(size()<2) return 0;
		int tmp=top(); pop();
		int tmp1=top(); push(tmp);
		return tmp1;
	}
}heap1[MAXN],heap2[MAXN],ans;
void init(){
	edge_cnt=dfs_clock=0;
	memset(vis,0,sizeof(vis));
	memset(head,-1,sizeof(head));
	Log[0]=-1;
	REP(i,1,MAXN*2-1)
		Log[i]=Log[i>>1]+1;
}
void addedge(int u,int v){
	edge[edge_cnt].v=v; 
	edge[edge_cnt].next=head[u]; head[u]=edge_cnt++;
}
void getroot(int u,int fa){
	sz[u]=1; dp[u]=0;
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v == fa || vis[v]) 
			continue;
		getroot(v,u);
		sz[u]+=sz[v]; dp[u]=max(dp[u],sz[v]);
	}
	dp[u]=max(dp[u],size-sz[u]);
	if(dp[u]<dp[root])
		root=u;
}
void dfs(int u,int fa,int depth){
	pos[u]=++dfs_clock; dep[u]=depth; d[dfs_clock][0]=dep[u];
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v == fa)
			continue;
		dfs(v,u,depth+1);
		d[++dfs_clock][0]=dep[u];
	}	
}
void build(int u,int fa){
	anc[u]=fa; vis[u]=1;
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v == fa || vis[v])
		   continue;
		root=0; size=sz[v]; 
		getroot(v,u); build(root,u);
	}
}
int RMQ(int u,int v){
	u=pos[u],v=pos[v];
	if(u>v)
		swap(u,v);
	int k=Log[v-u+1];
	return min(d[u][k],d[v-(1<<k)+1][k]);
}
int getdis(int u,int v){
	return dep[u]+dep[v]-2*RMQ(u,v);
}
void off(int u,int now){
	if(now == u){
		heap2[u].push(0);
		if(heap2[u].size() == 2)
			ans.push(heap2[u].top());	
	}
	int fa=anc[u];
	if(fa == -1)
		return ;
	int dis=getdis(fa,now);
	int tmp=heap1[u].top(); heap1[u].push(dis);
	if(dis>tmp){
		int tmp1=heap2[fa].top()+heap2[fa].stop(),num=heap2[fa].size();
		if(tmp) heap2[fa].erase(tmp);
		heap2[fa].push(dis);
		int tmp2=heap2[fa].top()+heap2[fa].stop();
		if(tmp2>tmp1){
			if(num>=2) ans.erase(tmp1);
			if(heap2[fa].size()>=2) ans.push(tmp2);
		}
	}
	off(fa,now);
}
void on(int u,int now){
	if(u == now){
		if(heap2[u].size() == 2) ans.erase(heap2[u].top());
		heap2[u].erase(0);
	}
	int fa=anc[u];
	if(fa == -1)
		return ;
	int dis=getdis(fa,now),tmp=heap1[u].top();
	heap1[u].erase(dis);
	if(dis == tmp){
		int tmp1=heap2[fa].top()+heap2[fa].stop(),num=heap2[fa].size();
		heap2[fa].erase(dis);
		if(heap1[u].top()) heap2[fa].push(heap1[u].top());
		int tmp2=heap2[fa].top()+heap2[fa].stop();
		if(tmp2<tmp1){
			if(num>=2) ans.erase(tmp1);
			if(heap2[fa].size()>=2) ans.push(tmp2);
		}
	}
	on(fa,now);
}
char op[2];
bool col[MAXN];
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%d",&n)){
		init();
		REP(i,1,n-1){
			int u,v; RD(u); RD(v);
			addedge(u,v); addedge(v,u);
		}
		dfs(1,-1,0);
		REP(j,1,Log[dfs_clock])
			for(int i=1;i+(1<<j)-1<=dfs_clock;i++)
				d[i][j]=min(d[i][j-1],d[i+(1<<(j-1))][j-1]);
		size=n; root=0; dp[0]=inf;
		getroot(1,-1); build(root,-1);
		REP(i,1,n)
			col[i]=true;
		int tot=n;
		REP(i,1,n)
			off(i,i);
		RD(m);
		while(m--){
			scanf("%s",op);
			if(op[0] == 'C'){
				int x;
				RD(x);
				if(col[x])
				   	on(x,x),tot--;
				else
					off(x,x),tot++;
				col[x]^=1;
			}
			else{
				if(tot<=1)
					printf("%d\n",tot-1);
				else
					printf("%d\n",ans.top());
			}
		}
	}
	return 0;
}
