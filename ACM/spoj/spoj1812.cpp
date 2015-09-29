/*********************************************************
  file name: spoj1812.cpp
  author : Sakura_Mashiro
  create time:  2015年09月28日 星期一 22时07分39秒
**********************************************************
solution:
	SAM
		对第一个字符串建立后缀自动机,自动机还需要维护Max,Min两个变量;
	Max表示当前结点代表的状态上当前考虑的字符串与第一个字符串的最大公
	共子串长度;Min表示当前结点代表的状态上当前已经考虑的所有字符串的最大
	公共子串长度
		有一点需要注意,我们需要更新parent树的父结点;考虑到如果子节点
	被匹配到,那么长度一定大于任意parent树上的祖先,在匹配过程中我们只是
	找到一个子串,可能会遗漏了祖先没有匹配到,这会导致祖先更新时出现问题,
	所以我们匹配到当前结点,同时也要将它parent树的祖先的Max置为祖先的len	
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
	int len,Max,Min;
	Node *ch[sigma_size],*fail;
}pool[MAXN],*root,*last;
struct SAM{
	inline void init(){
		cnt=1;
		last=root=&pool[0]; pool[0].fail=NULL;
		pool[0].len=pool[0].Max=pool[0].Min=0;
		REP(i,0,sigma_size-1)
			pool[0].ch[i]=NULL;
	}
	inline void newnode(Node * &x){
		x=&pool[cnt++];
		x->Max=0; x->fail=NULL;
		REP(i,0,sigma_size-1)
			x->ch[i]=NULL;
	}
	inline void extend(int c){
		Node *p=last,*np; newnode(np);
		np->len=np->Min=p->len+1; 
		for(;p && !p->ch[c];p=p->fail) p->ch[c]=np;
		if(!p) np->fail=root;
		else{
			if(p->ch[c]->len == p->len + 1) np->fail=p->ch[c];
			else{
				Node *q=p->ch[c],*nq; newnode(nq);
				*nq=*q;
				nq->len=nq->Min=p->len+1;
				q->fail=np->fail=nq;
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
	sam.init();
	scanf("%s",s);
	int len=strlen(s);
	REP(i,0,len-1)
		sam.extend(s[i]-'a');
	memset(c,0,sizeof(c));
	REP(i,0,cnt-1)
		c[pool[i].len]++;
	REP(i,1,len)
		c[i]+=c[i-1];
	REP(i,0,cnt-1)
		sa[--c[pool[i].len]]=i;
	while(~scanf("%s",s)){
		int len=strlen(s),l=0;
		Node *p=root;
		REP(i,0,len-1){
			int c=s[i]-'a';
			if(p->ch[c]){
				l++; p=p->ch[c];
			}
			else{
				while(p && !p->ch[c]) p=p->fail;
				if(!p)
					l=0,p=root;
				else
					l=p->len+1,p=p->ch[c];
			}
			p->Max=max(p->Max,l);
		}
		REPF(i,cnt-1,0){
			Node *p=&pool[sa[i]];
			p->Min=min(p->Min,p->Max);
			if(p->fail && p->Max)
				p->fail->Max=p->fail->len;
			p->Max=0;
		}
	}
	int ans=0;
	REP(i,0,cnt-1)
		ans=max(ans,pool[i].Min);
	printf("%d\n",ans);
	return 0;
}
