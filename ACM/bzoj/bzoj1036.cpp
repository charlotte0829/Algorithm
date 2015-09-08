/*********************************************************
  file name: bzoj1036.cpp
  author : Sakura_Mashiro
  create time:  2015年08月24日 星期一 19时09分35秒
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
const int MAXN=30000+50;
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
struct Node{
	int Max,val;
	ll sum;
	bool rev;
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
		y->fa=x; x->ch[d]=y;
		push_up(y); 
	}
	inline void splay(Node *x){
		down(x);
		print();
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
	void print(){
		/*printf("###this is print-function#####\n");
		REP(i,1,4){
			Node *pos=node[i];
			printf("ID=%d\n",i);
			printf("rev=%d val=%d Max=%d sum=%lld\n",pos->rev,pos->val,pos->Max,pos->sum);
			printf("fa=%d lson=%d rson=%d\n",pos->fa-p,Ls(pos)-p,Rs(pos)-p);
		}
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n")	;*/
	}
	inline void Access(Node *x){
		for(Node *t=null;x!=null;t=x,x=x->fa){
			splay(x); Rs(x)=t; push_up(x); 
		}
	}
	inline void make_root(Node *x){
		Access(x); 
		splay(x); x->rev^=1;
	}
	inline void Cut(Node *x,Node *y){
		make_root(x); 
		print();
		Access(y); 
		print();
		//cout<<"*************************************************************shit!"<<endl;
		splay(y);
		print();
	}
	inline void Link(Node *x,Node *y){
		make_root(x); x->fa=y;
		print();
	}
	inline void push_up(Node *x){
		x->sum=Ls(x)->sum+x->val+Rs(x)->sum;
		x->Max=max(x->val,max(Ls(x)->Max,Rs(x)->Max));
	}
	inline void push_down(Node *x){
		if(x->rev){
			x->rev^=1;
			Ls(x)->rev^=1; Rs(x)->rev^=1;
			swap(Ls(x),Rs(x));
		}
	}
	inline void down(Node *x){
		if(is_root(x)){
			push_down(x);
			return ;
		}
		down(x->fa); push_down(x);
	}
	inline void init(){
		tail=p;
		null=node[0]=tail++;
		null->sum=0; null->val=null->Max=-inf;
		null->fa=Ls(null)=Rs(null)=null;
	}
	inline void newnode(Node *&x,int val){
		x=tail++; x->rev=0;
		x->val=x->Max=x->sum=val;
		x->fa=Ls(x)=Rs(x)=null;
	}
}lct;
int n,m;
char op[N];
int U[MAXN],V[MAXN];
int main(){
	freopen("in.txt","r",stdin);
	while(~scanf("%d",&n)){
		lct.init();
		REP(i,1,n-1)
			scanf("%d%d",&U[i],&V[i]);
		REP(i,1,n){
			int w;
			scanf("%d",&w);
			lct.newnode(node[i],w);
		}
		/*REP(i,1,n){
			printf("pos=%d val=%d Max=%d sum=%lld\n",i,p[i].val,p[i].Max,p[i].sum);
		}*/
		REP(i,1,n-1){
			//printf("u=%d v=%d\n",U[i],V[i]);
			lct.Link(node[U[i]],node[V[i]]);
		}
		scanf("%d",&m);
		while(m--){
			scanf("%s",op);
			int u,v;
			scanf("%d%d",&u,&v);
			//printf("op=%s u=%d v=%d\n",op,u,v);
			if(op[1] == 'H'){
				lct.splay(node[u]); node[u]->val=v; lct.push_up(node[u]);
			}
			if(op[1] == 'M'){
				lct.Cut(node[u],node[v]);
				printf("%d\n",node[v]->Max);
			}
			if(op[1] == 'S'){
				lct.Cut(node[u],node[v]);
				printf("%lld\n",node[v]->sum);
			}
		//	printf("---------------------------------\n");
		}
	}
	return 0;
}
