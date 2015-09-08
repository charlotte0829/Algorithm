/*********************************************************
  file name: hdu5002.cpp
  author : Sakura_Mashiro
  create time:  2015年09月02日 星期三 11时35分31秒
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
struct Node{
	bool rev;
	int  add,c,sz;
	int val,max1,max2,num1,num2;
	Node *fa,*ch[2];
}*node[MAXN],*tail,p[MAXN],*null;
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
	inline void link(Node *x,Node *y){
		make_root(x); x->fa=y;
	}
	inline void cut(Node *x,Node *y){
		make_root(x); 
		Access(y); splay(y); 
		if(Ls(y)!=null)
			Ls(y)->fa=null;
		Ls(y)=null;  push_up(y);
	}
	inline void push_down(Node *x){
		if(x->rev){
			x->rev^=1;
			Ls(x)->rev^=1; Rs(x)->rev^=1;
			swap(Ls(x),Rs(x));
		}
		if(x->c!=-inf){
			if(Ls(x)!=null){
				Ls(x)->val=Ls(x)->max1=Ls(x)->c=x->c; Ls(x)->max2=-inf;
				Ls(x)->num1=Ls(x)->sz; Ls(x)->num2=0; Ls(x)->add=0;
			}
			if(Rs(x)!=null){
				Rs(x)->val=Rs(x)->max1=Rs(x)->c=x->c; Rs(x)->max2=-inf;
				Rs(x)->num1=Rs(x)->sz; Rs(x)->num2=0; Rs(x)->add=0;
			}
			x->c=-inf;
		}
		if(x->add){
			if(Ls(x)!=null){
				Ls(x)->val+=x->add; 
				Ls(x)->add+=x->add; Ls(x)->max1+=x->add; 
				if(Ls(x)->max2!=-inf)
					Ls(x)->max2+=x->add;
			}
			if(Rs(x)!=null){
				Rs(x)->val+=x->add;
			   	Rs(x)->add+=x->add;	Rs(x)->max1+=x->add; 
				if(Rs(x)->max2!=-inf)
					Rs(x)->max2+=x->add;
			}
			x->add=0;
		}
	}
	inline void down(Node *x){
		if(!is_root(x)) down(x->fa);
		push_down(x);
	}
	inline void update(Node *x,int val,int num){
		if(val == -inf) return ;
		if(val < x->max2) return ;
		if(val > x->max1){
			x->max2=x->max1; x->num2=x->num1;
			x->max1=val; x->num1=num;
		}
		else if(val == x->max1)
			x->num1+=num;
		else if(val > x->max2){
			x->max2=val; x->num2=num;
		}
		else
			x->num2+=num;
	}
	inline void push_up(Node *x){
		x->sz=Ls(x)->sz+1+Rs(x)->sz;
		x->max1=-inf; x->num1=0; x->max2=-inf; x->num2=0;
		update(x,x->val,1);
		update(x,Ls(x)->max1,Ls(x)->num1);
		update(x,Ls(x)->max2,Ls(x)->num2);
		update(x,Rs(x)->max1,Rs(x)->num1);
		update(x,Rs(x)->max2,Rs(x)->num2);
		/*printf("max1=%d num1=%d max2=%d num2=%d\n",x->max1,x->num1,x->max2,x->num2);
		puts("#################");*/

	}
	inline void init(){
		tail=p;
		null=node[0]=tail++;
		null->rev=null->num1=null->num2=null->add=null->sz=0; 
		null->val=null->max1=null->max2=null->c=-inf;
		null->fa=Ls(null)=Rs(null)=null;
		REP(i,1,n)
			newnode(node[i],-inf);
	}
	inline void newnode(Node *&x,int val){
		x=tail++;
		x->sz=1; 
		x->rev=x->add=x->num1=x->num2=0;
		x->val=x->max1=x->max2=x->c=-inf;
		x->fa=Ls(x)=Rs(x)=null;
	}
	inline void MODIFY(Node *x,int val){
		splay(x); x->val=val; push_up(x);
	}
	inline void SET(Node *x,Node *y,int c){
		make_root(x); 
		Access(y); splay(y);
		//cout<<"####now = "<<y-p<<endl;
		y->val=y->max1=y->c=c; y->num1=y->sz;
		y->max2=-inf; y->num2=0;
		//printf("max1=%d num1=%d max2=%d num2=%d\n",y->max1,y->num1,y->max2,y->num2);

	}
	inline void ADD(Node *x,Node *y,int add){
		make_root(x);
		Access(y); splay(y); 
		y->val+=add; y->max1+=add;  y->add+=add;
		if(y->max2!=-inf)
			y->max2+=add;
	}
	inline void QUERY(Node *x,Node *y){
		make_root(x);
		Access(y); splay(y);
		if(y->num2 == 0 && y->max2 == -inf){
			puts("ALL SAME");
			return ;
		}
		PT(y->max2); printf(" "); PT(y->num2); puts("");
	}

}lct;
void print(){
	REP(i,1,n){
		Node *x=node[i];
		printf("now=%d fa=%d lson=%d rson=%d\n",i,node[i]->fa-p,node[i]->ch[0]-p,node[i]->ch[1]-p);
		printf("val=%d max1=%d max2=%d num1=%d num2=%d\n",x->val,x->max1,x->max2,x->num1,x->num2);
	}
}
int op;
int main(){
	//freopen("in.txt","r",stdin);
	int T,kase=0;
	RD(T);
	while(T--){
		printf("Case #%d:\n",++kase);
		RD(n); RD(m);
		lct.init();
		REP(i,1,n){
			int w; RD(w);
			lct.MODIFY(node[i],w);
		}
		REP(i,1,n-1){
			int u,v;
			RD(u); RD(v);
			lct.link(node[u],node[v]);
		}
		//print(); //ok的
		while(m--){
			scanf("%d",&op);
			//cout<<" ^^^^^^^^^^^^^^^^^^^^^^^op = "<<op<<endl;
			if(op == 1){
				int x,y,a,b;
				RD(x); RD(y); RD(a); RD(b);
				lct.cut(node[x],node[y]); lct.link(node[a],node[b]);
			}
			if(op == 2){
				int a,b,x;
				RD(a); RD(b); RD(x);
				lct.SET(node[a],node[b],x);
			}
			if(op == 3){
				int a,b,d;
				RD(a); RD(b); RD(d);
				lct.ADD(node[a],node[b],d);
			}
			if(op == 4){
				int a,b;
				RD(a); RD(b);
				lct.QUERY(node[a],node[b]);
			}
		}
	}
	return 0;
}
