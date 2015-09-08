/*********************************************************
  file name: bzoj2002.cpp
  author : Sakura_Mashiro
  create time:  2015年08月29日 星期六 15时17分56秒
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
const int MAXN=200000+50;
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
int n,m,op;
int d[MAXN];
struct Node{
	bool rev;
	int sz,sum;
	Node *fa,*ch[2];
}*node[MAXN],p[MAXN],*null,*tail;
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
	inline void Link(Node *x,Node *y){
		make_root(x); x->fa=y;
	}
	inline void Cut(Node *x,Node *y){
		make_root(y); Access(x); splay(x); 
		if(Ls(x)!=null)
			Ls(x)->fa=null;
		Ls(x)=null; push_up(x);
	}
	inline void push_up(Node *x){
		x->sum=Ls(x)->sum+x->sz+Rs(x)->sum;
	}
	inline void push_down(Node *x){
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
	inline void newnode(Node *&x){
		x=tail++;
		x->rev=0; x->sz=x->sum=1;
		x->fa=Ls(x)=Rs(x)=null;
	}
	inline void init(){
		tail=p;
		null=node[0]=tail++;
		null->rev=null->sz=null->sum=0;
		null->fa=Ls(null)=Rs(null)=null;
		REP(i,1,n+1)
			newnode(node[i]);
	}
	int QUERY(Node *x,Node *y){
		make_root(x); Access(y); splay(y);
		return Ls(y)->sum;
	}
}lct;
int main(){
	//freopen("in.txt","r",stdin);
	while(RD(n)){
		lct.init();
		memset(d,0,sizeof(d));
		REP(i,1,n){
			RD(d[i]);
			if(i+d[i]>n)
				d[i]=n+1-i;
			lct.Link(node[i],node[i+d[i]]);
		}
		RD(m);
		while(m--){
			RD(op);
			int now,k;
			RD(now); now++;
			if(op == 1){
				PT(lct.QUERY(node[now],node[n+1]));
				puts("");
			}
			else{
				RD(k);
				if(now+d[now] == n+1 && k>=d[now])
					continue;
				lct.Cut(node[now],node[now+d[now]]);
				d[now]=k;
				if(now+d[now]>n)
					d[now]=n+1-now;
				lct.Link(node[now],node[now+d[now]]);

			}
		}
	}
	return 0;
}
