/*********************************************************
  file name: poj2774.cpp
  author : Sakura_Mashiro
  create time:  2015年09月27日 星期日 08时15分53秒
**********************************************************
solution:
	SAM
		对第一个串创建后缀自动机,第二个串在后缀自动机上跑,更新
	最大值
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
	int len;
	Node *ch[sigma_size],*fail;
}pool[MAXN],*root,*last;
struct SAM{
	inline void init(){
		cnt=1;
		last=root=&pool[0];
		pool[0].len=0; pool[0].fail=NULL; 
		REP(i,0,sigma_size-1)
			pool[0].ch[i]=NULL;
	}
	inline void newnode(Node *&x){
		x=&pool[cnt++];
		x->len=0; x->fail=NULL;
		REP(i,0,sigma_size-1)
			x->ch[i]=NULL;
	}
	inline void add(int c){
		Node *p=last,*np;
		newnode(np); np->len=p->len+1;
		for(;p && !p->ch[c];p=p->fail) p->ch[c]=np;
		if(!p) np->fail=root;
		else{
			if(p->ch[c]->len == p->len+1) np->fail=p->ch[c];
			else{
				Node *q=p->ch[c],*r; newnode(r);
				*r=*q;
				r->len=p->len+1; q->fail=np->fail=r;
				for(;p && p->ch[c] == q;p=p->fail) p->ch[c]=r;
			}
		}
		last=np;
	}
}sam;
char s1[MAXN],s2[MAXN];
int main(){
	//freopen("in.txt","r",stdin);
	scanf("%s%s",s1,s2);
	int len=strlen(s1);
	sam.init();
	REP(i,0,len-1){
		int c=s1[i]-'a'; sam.add(c);
	}
	int ans=0,res=0;
	len=strlen(s2);
	Node *p=root;
	REP(i,0,len-1){
		int c=s2[i]-'a';
		if(p->ch[c])
			res++,p=p->ch[c];
		else{
			while(p && !p->ch[c]) p=p->fail;
			if(!p)
				res=0,p=root;
			else
				res=p->len+1,p=p->ch[c];

		}
		ans=max(ans,res);
	}
	printf("%d\n",ans);
	return 0;
}
