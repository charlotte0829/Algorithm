/*********************************************************
  file name: codeforces#146div1C.cpp
  author : Sakura_Mashiro
  create time:  2015年09月30日 星期三 21时09分46秒
**********************************************************
problem:
		给定一个母串,每次询问一个子串或把子串前一部分移到末尾形成的
	串在母串中出现的次数
solution:
	SAM
		对母串建立后缀自动机,后缀自动机维护一个变量num,num表示结点代表
	的子串在母串中出现的次数,需要parent树从叶子结点向上更新;对于查询的
	子串(长度为len),我们复制一下并去掉最后一位接到原子串后面;
		查询时,沿着后缀自动机走,如果匹配长度>=len,沿着fail指针找到从这个
	位置往前len个字符之间的串在自动机中对应的状态结点,ans加上该状态出现的次数即可
		还有一点值得注意,因为复制后的询问串可能长度为len的子串会有相同
	会造成查询的重复累加,所以后缀自动机的每个结点要打个tag标记
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
const int MAXN=2000000+50;
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
	int len,tag,num;
	Node *ch[sigma_size],*fail;
}pool[MAXN],*root,*last;
struct SAM{
	inline void init(){
		cnt=1;
		root=last=&pool[0]; pool[0].fail=NULL;
		pool[0].len=pool[0].num=0; pool[0].tag=-1;
		REP(i,0,sigma_size-1)
			pool[0].ch[i]=NULL;
	}
	inline void newnode(Node * &x){
		x=&pool[cnt++];
		x->tag=-1; x->num=0; x->fail=NULL;
		REP(i,0,sigma_size-1)
			x->ch[i]=NULL;
	}
	inline void extend(int c){
		Node *p=last,*np; newnode(np);
		np->len	=p->len+1;
		for(;p && !p->ch[c];p=p->fail) p->ch[c]=np;
		if(!p) 
			np->fail=root;
		else{
			if(p->ch[c]->len == p->len + 1) 
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
int n;
char s[MAXN];
int c[MAXN],sa[MAXN];
int Query(char *str,int len,int L,int idx){
	int ans=0,l=0;
	Node *p=root;
	REP(i,0,len-1){
		int c=str[i]-'a';
		if(p->ch[c])
			p=p->ch[c],l++;
		else{
			while(p && !p->ch[c]) p=p->fail;
			if(!p)
				l=0,p=root;
			else
				l=p->len+1,p=p->ch[c];
		}
		if(l>=L){
			while(p->fail && p->fail->len>=L)p=p->fail;
			if(p->tag!= idx)
				p->tag=idx,ans+=p->num;
		}
	}	
	return ans;
}
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%s",s)){
		sam.init(); RD(n);
		memset(c,0,sizeof(c));
		int len=strlen(s);
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
			p=p->ch[c]; p->num=1;
		}
		REPF(i,cnt-1,0){
			Node *x=&pool[sa[i]];
			if(x->fail)
				x->fail->num+=x->num;
		}
		while(n--){
			scanf("%s",s);
			int l=strlen(s),L=l;
			REP(i,0,l-2)
				s[L++]=s[i];
			printf("%d\n",Query(s,L,l,n));
		}
	}
	return 0;
}
