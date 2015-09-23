/*********************************************************
  file name: codeforces#321div2E.cpp
  author : Sakura_Mashiro
  create time:  2015年09月23日 星期三 17时45分53秒
**********************************************************
solution:
	segtree+双hash
		线段树维护区间字符的hash值,修改为成段更新,打个懒惰标记就好;对于
	查询l,r,d,我们检查区间[l,r-d]和[l+d,r]的hash值是否相同判断是否具有
	周期性(利用错位性)
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
int n,m,k;
char s[MAXN];
struct Node{
	ll val;
	int len,tag,l,r;
};
struct Hash{
	int Mod,base;
	ll  sum[MAXN],p[MAXN];
	Node seg[MAXN<<2];
	void init(){
		p[0]=sum[0]=1;
		REP(i,1,n){
			p[i]=p[i-1]*base;
			if(p[i]>=Mod)
				p[i]%=Mod;
			sum[i]=sum[i-1]+p[i];
			if(sum[i]>=Mod)
				sum[i]%=Mod;
		}
	}
	inline void push_up(int rt){
		seg[rt].len=seg[L(rt)].len+seg[R(rt)].len;
		seg[rt].val=seg[L(rt)].val*p[seg[R(rt)].len]+seg[R(rt)].val;
		if(seg[rt].val>=Mod)
			seg[rt].val%=Mod;
	}
	inline void push_down(int rt){
		if(seg[rt].tag!=-1){
			seg[L(rt)].tag=seg[R(rt)].tag=seg[rt].tag;
			seg[L(rt)].val=seg[rt].tag*sum[seg[L(rt)].len-1];
			if(seg[L(rt)].val>=Mod)
				seg[L(rt)].val%=Mod;
			seg[R(rt)].val=seg[rt].tag*sum[seg[R(rt)].len-1];
			if(seg[R(rt)].val>=Mod)
				seg[R(rt)].val%=Mod;
			seg[rt].tag=-1;
		}
	}
	inline void build(int rt,int l,int r){
		seg[rt].tag=-1; 
		seg[rt].l=l; seg[rt].r=r; 
		if(l == r){
			seg[rt].len=1; seg[rt].val=s[l]-'0';
			return ;
		}
		int mid=(l+r)>>1;
		build(L(rt),l,mid); build(R(rt),mid+1,r);
		push_up(rt);
	}
	inline void update(int rt,int l,int r,int c){
		if(seg[rt].l == l && seg[rt].r == r){
			seg[rt].tag=c;
			seg[rt].val=sum[seg[rt].len-1]*c;
			if(seg[rt].val>=Mod)
				seg[rt].val%=Mod;
			return ;
		}
		push_down(rt);
		int mid=(seg[rt].l+seg[rt].r)>>1;
		if(r<=mid)
			update(L(rt),l,r,c);
		else if(l>mid)
			update(R(rt),l,r,c);
		else{
			update(L(rt),l,mid,c); update(R(rt),mid+1,r,c);
		}
		push_up(rt);
	}
	inline ll query(int rt,int l,int r){
		if(seg[rt].l == l && seg[rt].r == r){
			return seg[rt].val;
		}
		push_down(rt);
		int mid=(seg[rt].l+seg[rt].r)>>1;
		if(r<=mid)
			return query(L(rt),l,r);
		else if(l>mid)
			return query(R(rt),l,r);
		else{
			ll res1=query(L(rt),l,mid);
			ll res2=query(R(rt),mid+1,r);
			ll res=res1*p[r-mid]+res2;
			if(res>=Mod)
				res%=Mod;
			return res;
		}
	}
}tree1,tree2;
bool cmp(int l1,int r1,int l2,int r2){
	if(tree1.query(1,l1,r1) != tree1.query(1,l2,r2) || tree2.query(1,l1,r1) != tree2.query(1,l2,r2))
		return false;
	return true;
}
int main(){
	//freopen("in.txt","r",stdin);
	tree1.Mod=1e9+7; tree2.Mod=1e9+9;
	tree1.base=23333; tree2.base=233333;
	while(~scanf("%d%d%d",&n,&m,&k)){
	scanf("%s",s+1);
	int len=strlen(s+1);
	tree1.init(); tree2.init();
	tree1.build(1,1,len); tree2.build(1,1,len);
	int T=m+k;
	while(T--){
		int cmd,l,r,d; 
		RD(cmd); RD(l); RD(r); RD(d);
		if(cmd == 1){
			tree1.update(1,l,r,d); tree2.update(1,l,r,d);
		}
		else{
			if(r - l + 1 == d)
				puts("YES");
			else{
				int L1=l,R1=r-d;
				int L2=l+d,R2=r;
				if(cmp(L1,R1,L2,R2))
					puts("YES");
				else
					puts("NO");
			}
		}
		
	}
	}
	return 0;
}
