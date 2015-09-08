/*********************************************************
  file name: spoj375.cpp
  author : Sakura_Mashiro
  create time:  2015年08月27日 星期四 10时02分25秒
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
const int MAXN=20000+50;
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
template <class T>
inline bool RD(T &ret){
	char c;
	int sgn;
	if(c=getchar(),c == EOF) return 0;
	while(c!='-' && (c<'0' || c>'9')) c=getchar();
	sgn= (c == '-') ? -1 : 1;
	ret= (c == '-') ? 0 : (c-'0');
	while(c=getchar(),c>='0' && c<='9') ret=ret*10+(c-'0');
	ret*=sgn;
	return 1;
}
template<class T>
inline bool PT(T x){
	if(x < 0){
		putchar('-');
		x=-x;
	}
	if(x > 9) PT(x/10);
	putchar(x%10+'0');
}
int n;
char op[N];
struct Node{
	bool rev;
	int val,Max;
	Node *fa,*ch[2];
}*node[MAXN],*null,*tail,p[MAXN];
struct LCT{
	inline bool is_root(Node *x){
		return x->fa == null || x->fa->ch[0]!=x && x->fa->ch[1]!=x;
	}
	inline void rotate(Node *x,int d){
		Node *y=x->fa;
		y->ch[d^1]=x->ch[d]; 
		x->ch[d]->fa=y; x->fa=y->fa;
		if(!is_root(y)){
			int d=y->fa->ch[1] == y;
			y->fa->ch[d]=x;
		}
		x->ch[d]=y; y->fa=x;
		push_up(y);
	}
	inline void push_down(Node *x){
		if(x->rev){
			x->rev^=1;
			Ls(x)->rev^=1; Rs(x)->rev^=1;
			swap(Ls(x),Rs(x));
		}
	}
	inline void push_up(Node *x){
		x->Max=max(x->val,max(Ls(x)->Max,Rs(x)->Max));
	}
	inline void down(Node *x){
		if(!is_root(x))
			down(x->fa);
		push_down(x);
	}
	inline void splay(Node *x){
		down(x);
		while(!is_root(x)){
			Node *y=x->fa;
			if(is_root(y)){
				int d=y->ch[0] == x ? 1 : 0;
				rotate(x,d);
			}
			else{
				int d=y->fa->ch[0] == y ? 1 : 0;
				if(y->ch[d] == x)
					rotate(x,d^1);
				else
					rotate(y,d);
				rotate(x,d);
			}
		}
		push_up(x);
	}
	inline void Access(Node *x){
		for(Node *t=null;x!=null;t=x,x=x->fa){
			splay(x); Rs(x)=t; push_up(x);
		}
	}
	inline void make_root(Node *x){
		Access(x); splay(x); x->rev^=1;
	}
	inline void Link(Node *x,Node *y){
		make_root(x);  x->fa=y;
	}
	inline void newnode(Node *&x){
		x=tail++;
		x->val=x->Max=-inf;
		x->fa=Ls(x)=Rs(x)=null;
	}
	inline void init(){
		tail=p;
		null=node[0]=tail++;
		null->val=null->Max=-inf;
		Ls(null)=Rs(null)=null->fa=null;
		REP(i,1,2*n-1)
			newnode(node[i]);
	}
	inline void MODIFY(Node *x,int val){
		splay(x); x->val=val; push_up(x);
	}
	inline int QUERY(Node *x,Node *y){
		make_root(x);
		Access(y); splay(y);
		return max(y->val,Ls(y)->Max);
	}
}lct;
int main(){
//	freopen("in.txt","r",stdin);
	int T;
	RD(T);
	while(T--){
		RD(n);
		lct.init();
		REP(i,1,n-1){
			int u,v,w;
			RD(u); RD(v); RD(w);
			lct.MODIFY(node[n+i],w);
			lct.Link(node[u],node[n+i]); lct.Link(node[v],node[n+i]);
		}
		while(~scanf("%s",op)){
			if(op[0] == 'D')
				break;
			int u,v;
			RD(u); RD(v); 
			if(op[0] == 'C')
				lct.MODIFY(node[n+u],v);
			else{
				//printf("%d\n",lct.QUERY(node[u],node[v]));
				PT(lct.QUERY(node[u],node[v]));
				puts("");
			}
		}
	}
	return 0;
}
