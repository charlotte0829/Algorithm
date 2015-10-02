/*********************************************************
  file name: spoj6779.cpp
  author : Sakura_Mashiro
  create time:  2015年10月02日 星期五 17时13分04秒
**********************************************************
solution:
	Link-Cut-Tree
		LCT结点要维护mx,lmx,rmx,sum;mx表示结点所在子树最大连续和,
	lmx表示从低往右的最大连续和,rmx为从低往左的最大连续和,sum表示
	子树和;
		注意push_down和push_up的维护
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
struct Node{
	bool rev;
	int lazy,sz;
	int val,mx,lmx,rmx,sum;
	Node *fa,*ch[2];
}pool[MAXN],*tail,*null,*node[MAXN];
struct LCT{
	inline bool is_root(Node *x){
		return x->fa == null || x->fa->ch[0] !=x && x->fa->ch[1] !=x;
	}
	inline void rotate(Node *x,int d){
		Node *y=x->fa;
		y->ch[d^1]=x->ch[d]; 
		x->ch[d]->fa=y; x->fa=y->fa;
		if(!is_root(y)){
			int d = y->fa->ch[1] == y;
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
				int d = y->ch[0] == x ? 1 : 0;
				rotate(x,d);
			}
			else{
				int d = y->fa->ch[0] == y ? 1 : 0;
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
	inline void reverse(Node *x){
		if(x == null)
			return ;
		x->rev^=1; 
		swap(x->lmx,x->rmx); swap(Ls(x),Rs(x));
	}
	inline void modify(Node *x,int val){
		if(x == null)
			return ;
		x->val=x->lazy=val; x->sum=x->sz*val;
		x->mx=x->lmx=x->rmx=max(0,x->sz*val);
	}
	inline void make_root(Node *x){
		Access(x); splay(x); reverse(x);
	}
	inline void down(Node *x){
		if(!is_root(x)) down(x->fa);
		push_down(x);
	}
	inline void init(){
		tail=pool;
		null=node[0]=tail++;
		null->fa=Ls(null)=Rs(null)=null;
		null->rev=null->sz=0; null->lazy=-inf;
		null->val=null->sum=null->lmx=null->rmx=null->mx=0;
	}
	inline void newnode(Node *&x,int val){
		x=tail++;
		x->fa=Ls(x)=Rs(x)=null;
		x->val=x->sum=val; x->lazy=-inf; 
		x->rev=0; x->sz=1; x->mx=x->lmx=x->rmx=max(0,val);
	}
	inline void link(Node *x,Node *y){
		make_root(x); x->fa=y;
	}
	inline void push_down(Node *x){
		if(x->rev){
			x->rev^=1;
			reverse(Ls(x)); reverse(Rs(x));
		}
		if(x->lazy!=-inf){
			modify(Ls(x),x->lazy);
			modify(Rs(x),x->lazy);
			x->lazy=-inf;
		}
	}
	inline void push_up(Node *x){
		x->sz=Ls(x)->sz+Rs(x)->sz+1;
		x->sum=Ls(x)->sum+x->val+Rs(x)->sum;
		x->mx=max(max(Ls(x)->mx,Rs(x)->mx),Ls(x)->rmx+x->val+Rs(x)->lmx);
		x->lmx=max(Ls(x)->lmx,Ls(x)->sum+x->val+Rs(x)->lmx);
		x->rmx=max(Rs(x)->rmx,Rs(x)->sum+x->val+Ls(x)->rmx);
	}
	inline void MODIFY(Node *x,Node *y,int c){
		make_root(x); Access(y); splay(y); modify(y,c);
	}
	inline int QUERY(Node *x,Node *y){
		make_root(x); Access(y); splay(y); 
		return y->mx;
	}
}lct;
int n,m;
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%d",&n)){
		lct.init();
		REP(i,1,n){
			int w; RD(w);
			lct.newnode(node[i],w);
		}
		REP(i,1,n-1){
			int u,v;
			RD(u); RD(v);
			lct.link(node[u],node[v]);
		}
		RD(m);
		int op,u,v,w;
		while(m--){
			RD(op); RD(u); RD(v);
			if(op == 2){
				RD(w);
				lct.MODIFY(node[u],node[v],w);
			}
			else{
				printf("%d\n",lct.QUERY(node[u],node[v]));
			}
		}
	}
	return 0;
}
