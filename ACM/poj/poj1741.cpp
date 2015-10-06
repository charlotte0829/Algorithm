/*********************************************************
  file name: poj1741.cpp
  author : Sakura_Mashiro
  create time:  2015年10月06日 星期二 10时02分31秒
**********************************************************
solution:
	点分治
		dep[i]+dep[j]<=k且belong[i]!=belong[j]的(i,j)对数=
	dep[i]+dep[j]<=k的对数-dep[i]+dep[j]<=k且belong[i]=belong[j]的对数
		若考虑当前结点u,得到以u为根的dep数组,我们sort一下,利用two-point
	就可以统计出对数,这部分复杂度O(nlogn)
		总的复杂度为O(nlog^2n),分治递归深度的最坏情况为O(logn)
	不妨设根为第0层,那么第k层最多2^k个点,假如有个点叫u,那么以这个点为
	根的子树size为n/2^k,那么理论上界为nlogn+2*n/2*log(n/2)+2^2*n/(2^2)*log(n/(2^2))+...+2^k*n/(2^k)*log(n/(2^k)) (k<=logn)
	=knlogn-n(1+2+...+k)=knlogn-(1+k)*k/2*n<=nlog^2n-n*(logn+1)*(logn)/2,即O(nlog^2n)
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
int n,k,edge_cnt,size,root;
int head[MAXN],sz[MAXN],dp[MAXN],vis[MAXN];
int ans;
int d[MAXN];
vector<int>vec;
struct Edge{
	int v,w,next;
}edge[MAXN<<1];
void init(){
	edge_cnt=0;
	memset(vis,0,sizeof(vis));
	memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int w){
	edge[edge_cnt].v=v; edge[edge_cnt].w=w; 
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
void getdepth(int u,int fa,int dis){
	d[u]=dis; vec.push_back(d[u]);
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v == fa || vis[v])
		   continue;
		getdepth(v,u,dis+edge[i].w);	
	}
}
int cal(int u,int dis){
	vec.clear();
	getdepth(u,-1,dis);
	int res=0,num=vec.size();
	sort(vec.begin(),vec.end());
	for(int l=0,r=num-1;l<r;){
		if(vec[l]+vec[r]<=k)
			res+=r-l,l++;
		else
			r--;
	}
	return res;
}
void solve(int u,int fa){
	ans+=cal(u,0); vis[u]=1;
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v == fa || vis[v])
			continue;
		ans-=cal(v,edge[i].w);
		root=0; getroot(v,-1); size=sz[v];
		solve(root,-1);
	}
}
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%d%d",&n,&k) && n+k){
		init();
		REP(i,1,n-1){
			int u,v,w;
			RD(u); RD(v); RD(w); 
			addedge(u,v,w); addedge(v,u,w);
		}
		size=n; dp[root]=inf;
		getroot(1,-1); ans=0; solve(root,-1);
		cout<<ans<<endl;
	}
	return 0;
}
