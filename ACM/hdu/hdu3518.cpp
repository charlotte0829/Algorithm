/*********************************************************
  file name: hdu3518.cpp
  author : Sakura_Mashiro
  create time:  2015年09月30日 星期三 10时12分48秒
**********************************************************
solution:
	SAM 
		后缀自动机多维护l,r两个变量,l表示该状态表示的子串结束
	位置最小的位置,r为最大的位置,从parent树的叶子结点向上更新,
	统计时若p结点的r-l>p->fail->len,则该结点对答案贡献min(r-l,p->len)-p->fail->len
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
const int MAXN=2000+50;
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
int cnt;
struct Node{
	int len,l,r;
	Node *ch[sigma_size],*fail;
}pool[MAXN],*root,*last;
struct SAM{
	inline void init(){
		cnt=1;
		last=root=&pool[0]; pool[0].fail=NULL;
		pool[0].len=0; pool[0].l=inf; pool[0].r=-inf;
		REP(i,0,sigma_size-1)
			pool[0].ch[i]=NULL;
	}
	inline void newnode(Node * &x){
		x=&pool[cnt++];
		x->l=inf; x->r=-inf; x->fail=NULL;
		REP(i,0,sigma_size-1)
			x->ch[i]=NULL;
	}
	inline void extend(int c){
		Node *p=last,*np; newnode(np);
		np->len=p->len+1;
		for(;p && !p->ch[c];p=p->fail) p->ch[c]=np;
		if(!p) np->fail=root;
		else{
			if(p->ch[c]->len == p->len + 1) np->fail=p->ch[c];
			else{
				Node *q=p->ch[c],*nq; newnode(nq);
				*nq=*q;
				nq->len=p->len+1; np->fail=q->fail=nq;
				for(;p && p->ch[c] == q;p=p->fail) p->ch[c]=nq;
			}
		}
		last=np;
	} 
}sam;
char s[MAXN];
int c[MAXN],sa[MAXN];
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%s",s)){
		if(s[0] == '#')
			break;
		int len=strlen(s);
		memset(c,0,sizeof(c));
		sam.init();
		REP(i,0,len-1)
			sam.extend(s[i]-'a');
		REP(i,0,cnt-1)
			c[pool[i].len]++;
		REP(i,1,len)
			c[i]+=c[i-1];
		REPF(i,cnt-1,0)
			sa[--c[pool[i].len]]=i;
		Node *p=root;
		REP(i,0,len-1){
			int c=s[i]-'a';
			p=p->ch[c]; p->l=p->r=p->len;
		}
		REPF(i,cnt-1,0){
			Node *x=&pool[sa[i]];
			if(x->fail){
				x->fail->l=min(x->fail->l,x->l);
				x->fail->r=max(x->fail->r,x->r);
			}
		}
		ll ans=0;
		REPF(i,cnt-1,0){
			Node *x=&pool[sa[i]];
			if(x->fail && x->r-x->l>x->fail->len){
				ans+=min(x->r-x->l,x->len)-x->fail->len;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
