/*********************************************************
  file name: hdu4010.cpp
  author : Sakura_Mashiro
  create time:  2015年09月01日 星期二 09时24分53秒
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
const int MAXN=300000+50;
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
int op;
struct Node{
	bool rev;
	int add;
	ll val,Max;
	Node *fa,*ch[2];
}*node[MAXN],p[MAXN],*tail,*null;
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
	inline Node * findroot(Node *x){
		Access(x); splay(x); 
		while(Ls(x)!=null)
			x=Ls(x);
		return x;
	}
	inline void link(Node *x,Node *y){
		make_root(x); x->fa=y; 
	}
	inline void cut(Node *x,Node *y){
		make_root(x); Access(y); splay(y);
		if(Ls(y)!=null)
			Ls(y)->fa=null;
		Ls(y)=null; push_up(y);
	}
	inline void init(){
		tail=p;
		null=node[0]=tail++;
		null->rev=null->add=0; null->val=null->Max=-inf;
		null->fa=Ls(null)=Rs(null)=null;
		REP(i,1,n)
			newnode(node[i],-inf);
	}
	inline void newnode(Node *&x,int val){
		x=tail++;
		x->rev=x->add=0; x->val=x->Max=val;
		x->fa=Ls(x)=Rs(x)=null;
	}
	inline void push_up(Node *x){
		x->Max=max(x->val,max(Ls(x)->Max,Rs(x)->Max));
	}
	inline void push_down(Node *x){
		if(x->add){
			if(Ls(x)!=null)
				Ls(x)->val+=x->add,Ls(x)->Max+=x->add,Ls(x)->add+=x->add;
			if(Rs(x)!=null)
				Rs(x)->val+=x->add,Rs(x)->Max+=x->add,Rs(x)->add+=x->add;
			x->add=0;
		}
		if(x->rev){
			x->rev^=1; 
			Ls(x)->rev^=1; Rs(x)->rev^=1;
			swap(Ls(x),Rs(x));
		}
	}
	inline void down(Node *x){
		if(!is_root(x)) down(x->fa);
		push_down(x);
	}
	void MODIFY(Node *x,int val){
		splay(x); x->val=x->Max=val; push_up(x);
	}
	void SOLVE(Node *x,Node *y){
		make_root(x); Access(y); splay(y);
		Node *t=Ls(y);
		while(Rs(t)!=null)
			t=Rs(t);
		if(t!=null)
			cut(t,y);
	}
	void ADD(Node *x,Node *y,int val){
		make_root(x); Access(y); splay(y);
		y->val+=val; y->Max+=val; y->add+=val;
	}
	ll QUERY(Node *x,Node *y){
		make_root(x); Access(y); splay(y);
		return max(y->val,Ls(y)->Max);
	}
}lct;
int main(){
	//freopen("in.txt","r",stdin);
	while(RD(n)){
		lct.init();
		REP(i,1,n-1){
			int u,v;
			RD(u); RD(v);
			lct.link(node[u],node[v]);
		}
		REP(i,1,n){
			int w;
			RD(w);
			lct.MODIFY(node[i],w);
		}
		RD(m);
		while(m--){
			int x,y,w;
			RD(op);
			if(op == 1){
				RD(x); RD(y);
				if(lct.findroot(node[x]) == lct.findroot(node[y])){
					PT(-1); puts("");
					continue;
				}
				lct.link(node[x],node[y]);
			}
			if(op == 2){
				RD(x); RD(y);
				if(x == y || lct.findroot(node[x])!=lct.findroot(node[y])){
					PT(-1); puts("");
					continue;
				}
				lct.SOLVE(node[x],node[y]);
			}
			if(op == 3){
				RD(w); RD(x); RD(y);
				if(lct.findroot(node[x])!=lct.findroot(node[y])){
					PT(-1); puts("");
					continue;
				}
				lct.ADD(node[x],node[y],w);
			}
			if(op == 4){
				RD(x); RD(y);
				if(lct.findroot(node[x])!=lct.findroot(node[y])){
					PT(-1); puts("");
					continue;
				}
				PT(lct.QUERY(node[x],node[y])); puts("");
			}		
		}
		puts("");
	}
	return 0;
}
