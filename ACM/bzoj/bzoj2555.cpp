/*********************************************************
  file name: bzoj2555.cpp
  author : Sakura_Mashiro
  create time:  2015年10月07日 星期三 16时14分18秒
**********************************************************
solution:
	SAM+LCT
		若当前串已建成后缀自动机,查询一个字串就是从SAM的root
	出发沿着自动机跑找到该字符串对应的结点,每个结点的right集合
	大小就是这个子串出现的次数,找不到返回0;
		每次extend的时候就将新建结点沿着parent指针到根的路径上
	经过结点的right集合+1即可
		由于字符串相当大,所以我们用LCT来维护每个结点right集合的
	大小,那么extend的复杂度可以降到logn
		总复杂度为O(nlogn)
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
const int MAXN=1500000+50;
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
namespace LCT{
	int cnt;
	struct Node{
		bool rev;
		int val,lazy;
		Node *fa,*ch[2];
	}pool[MAXN],*null;
	inline bool is_root(Node *x){
		return x->fa == null || x->fa->ch[0]!=x && x->fa->ch[1]!=x;
	}
	inline void update(Node *x,int add){
		if(x == null)
			return ;
		x->val+=add; x->lazy+=add;
	}
	inline void Reverse(Node *x){
		if(x == null)
			return ;
		x->rev^=1; swap(Ls(x),Rs(x));
	}
	inline void push_down(Node *x){
		if(x->rev){
			x->rev^=1; 
			Reverse(Ls(x)); Reverse(Rs(x));
		}
		if(x->lazy){
			update(Ls(x),x->lazy); update(Rs(x),x->lazy);
			x->lazy=0;
		}
	}
	inline void down(Node *x){
		if(!is_root(x)) down(x->fa);
		push_down(x);
	}	
	inline void rotate(Node *x,int d){
		Node *y=x->fa;
		y->ch[d^1]=x->ch[d]; 
		x->ch[d]->fa=y; x->fa=y->fa;
		if(!is_root(y)){
			int d = y->fa->ch[1] == y;
			y->fa->ch[d]=x;
		}
		y->fa=x; x->ch[d]=y;
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
	}
	inline void Access(Node *x){
		for(Node *tmp=null;x!=null;tmp=x,x=x->fa){
			splay(x); Rs(x)=tmp; 
		}
	}
	inline void make_root(Node *x){
		Access(x); splay(x); Reverse(x);
	}
	inline void cut(Node *x,Node *y){
		make_root(x); Access(y); splay(y); Ls(y)->fa=null; Ls(y)=null;
	}
	inline void link(Node *x,Node *y){
		make_root(x); x->fa=y;	
	}
	inline void newnode(Node *&x){
		x=&pool[cnt++];
		x->rev=x->val=x->lazy=0;
		x->fa=Ls(x)=Rs(x)=null;		
	}
	inline void init(){
		cnt=1;
		null=&pool[0];
		null->rev=null->val=null->lazy=0;
		null->fa=Ls(null)=Rs(null)=null;
	}
	inline void ADD(Node *x,Node *y,int add){
		make_root(x); Access(y); splay(y); update(y,add);
	}
	inline int QUERY(Node *x){
		Access(x); splay(x); 
		return x->val;
	}	
}
int cnt;
struct Node{
	int len,val;
	LCT::Node *node;
	Node *ch[sigma_size],*fail;
}pool[MAXN],*last,*root;
struct SAM{
	inline void init(){
		cnt=1;	LCT::init(); 
		last=root=&pool[0]; pool[0].fail=NULL;
		pool[0].len=pool[0].val=0; LCT::newnode(pool[0].node);
		REP(i,0,sigma_size-1)
			pool[0].ch[i]=NULL;
	}
	inline void newnode(Node *&x){
		x=&pool[cnt++]; LCT::newnode(x->node);
		x->fail=NULL; 
		REP(i,0,sigma_size-1)
			x->ch[i]=NULL;
	}
	inline void extend(int c){
		Node *p=last,*np; newnode(np);
		np->len=p->len+1; 
		for(;p && !p->ch[c];p=p->fail) p->ch[c]=np;
		if(!p){
			np->fail=root; 
			LCT::link(np->node,root->node);
		}
		else{
			if(p->ch[c]->len == p->len + 1){
				np->fail=p->ch[c];
				LCT::link(np->node,p->ch[c]->node);
			}
			else{
				Node *q=p->ch[c],*nq; newnode(nq);
				nq->fail=q->fail; nq->len=p->len+1; 
				memcpy(nq->ch,q->ch,sizeof(nq->ch));
				LCT::cut(q->node,q->fail->node);
				LCT::link(nq->node,nq->fail->node);
				LCT::link(nq->node,q->node);
				nq->node->val=q->node->val;
				LCT::link(np->node,nq->node);
				np->fail=q->fail=nq;
				for(;p && p->ch[c] == q;p=p->fail)
					p->ch[c]=nq;
			}
		}
		last=np;
		LCT::ADD(np->node,root->node,1);
	}
	inline int QUERY(char *s,int len){
		Node *p=root;
		REP(i,0,len-1){
			int c=s[i]-'A'; p=p->ch[c];
			if(p == NULL)
				return 0;
		}
		return LCT::QUERY(p->node);
	}	
}sam;
int m;
char op[10];
char s[MAXN*2];
int mask;
void Decode(char *str,int mask){
	int len=strlen(str);
	REP(i,0,len-1){
		mask=(mask*131+i)%len;
		swap(str[i],s[mask]);
	}
}
void print(){
	REP(i,1,cnt-1)
		cout<<"now = "<<i<<" fail = "<<pool[i].fail-pool<<endl;
	REP(i,1,LCT::cnt-1){
		cout<<"id = "<<pool[i-1].node-LCT::pool; if(i!=1) cout<<" fail = "<<pool[i-1].fail->node-LCT::pool<<endl;
		else
			puts("");
		cout<<" now = "<<i<<" fa = "<<LCT::pool[i].fa-LCT::pool;
		cout<<" lson = "<<LCT::pool[i].ch[0]-LCT::pool<<" rson = "<<LCT::pool[i].ch[1]-LCT::pool<<" val = "<<LCT::pool[i].val<<endl;
	}	
}
int main(){
	//freopen("in.txt","r",stdin);
	sam.init();
	RD(m); mask=0;
	scanf("%s",s);
	int len=strlen(s);
	REP(i,0,len-1)
		sam.extend(s[i]-'A');
	//print();	
	while(m--){
		scanf("%s%s",op,s);
		Decode(s,mask);
		int len=strlen(s);
		if(op[0] == 'Q'){
			int ans=sam.QUERY(s,len);
			mask^=ans;
			printf("%d\n",ans);
		}
		else{
			REP(i,0,len-1)
				sam.extend(s[i]-'A');
		}
	}
	return 0;
}
