/*********************************************************
  file name: codeforces#321div2C.cpp
  author : Sakura_Mashiro
  create time:  2015年09月23日 星期三 09时25分12秒
**********************************************************
solution:
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
int n,m,edge_cnt,num;
int a[MAXN],son[MAXN],head[MAXN],Max[MAXN];
struct Edge{
	int v,next;
}edge[MAXN<<1];
void init(){
	edge_cnt=num=0;
	memset(Max,0,sizeof(Max));
	memset(head,-1,sizeof(head));
}
void addedge(int u,int v){
	edge[edge_cnt].v=v; 
	edge[edge_cnt].next=head[u]; head[u]=edge_cnt++;
}
void dfs(int u,int fa,int len){
	son[u]=1;
	int cnt=a[u] == 1 ? len+1 : 0;
	if(fa>0)
		Max[u]=max(cnt,Max[fa]);
	else
		Max[u]=cnt;
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].v;
		if(v == fa)
			continue;
		dfs(v,u,cnt);
		son[u]+=son[v];
	}
	if(son[u] == 1 && Max[u]<=m){
		num++;
	}
}
int main(){
	//freopen("in.txt","r",stdin);
	RD(n); RD(m); init();
	REP(i,1,n)
		RD(a[i]);
	REP(i,1,n-1){
		int u,v;
		RD(u); RD(v);
		addedge(u,v); addedge(v,u);
	}
	dfs(1,-1,0);
	cout<<num<<endl;
	return 0;
}
