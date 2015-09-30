/*********************************************************
  file name: hdu4622.cpp
  author : Sakura_Mashiro
  create time:  2015年09月30日 星期三 22时16分29秒
**********************************************************
solution:
	SAM
		由于字串长度<=2000,但查询多达1e5,我们可以对以位置i开始
	的串建立后缀自动机,预处理出从i到j(i<=j<=len)的答案,每个状态
	结点对答案的贡献为它所代表的最长子串长度减去parent树父亲结点
	代表的最长子串长度
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
const int N=2000+50;
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
int cnt;
struct Node{
	int len,pos;
	Node *ch[sigma_size],*fail;
}pool[MAXN],*root,*last;
struct SAM{
	inline void init(){
		cnt=1;
		root=last=&pool[0];
		pool[0].len=0; pool[0].pos=-1; pool[0].fail=NULL;
		REP(i,0,sigma_size-1)
			pool[0].ch[i]=NULL;
	}
	inline void newnode(Node *&x){
		x=&pool[cnt++];
		x->fail=NULL;
		REP(i,0,sigma_size-1)
			x->ch[i]=NULL;
	}
	inline void extend(int c){
		Node *p=last,*np; newnode(np);
		np->len=p->len+1; np->pos=p->len;
		for(;p && !p->ch[c];p=p->fail) p->ch[c]=np;
		if(!p)
			np->fail=root;
		else{
			if(p->ch[c]->len ==  p->len + 1) 
				np->fail=p->ch[c];
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
int ans[N][N];
char s[MAXN];
int main(){
	//freopen("in.txt","r",stdin);
	int T; RD(T);
	while(T--){
		scanf("%s",s);
		memset(ans,0,sizeof(ans));
		int len=strlen(s);
		REP(i,0,len-1){
			sam.init();
			REP(j,i,len-1)
				sam.extend(s[j]-'a');
			REP(j,1,cnt-1){
				Node *x=&pool[j];
				ans[i][x->pos+i]+=x->len-x->fail->len;
			}
			REP(j,i+1,len-1)
				ans[i][j]+=ans[i][j-1];
		}
		int m; RD(m);
		while(m--){
			int l,r;
			RD(l); RD(r); 
			l--; r--;
			printf("%d\n",ans[l][r]);
		}
	}
	return 0;
}
