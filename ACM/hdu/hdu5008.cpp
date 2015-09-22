/*********************************************************
  file name: hdu5008.cpp
  author : Sakura_Mashiro
  create time:  2015年09月22日 星期二 15时26分22秒
**********************************************************
solution:
	suffix_array+binary+rmq
	step1:
		任何一个字符串的子串一定是其某个后缀的前缀,利用后缀数组可先求得sa;设字符串长度为len,
	那么sa[i]为首的后缀会新产生len-sa[i]-height[i]个新串,且按字典序排序;用数组sum[i]记录
	sa[1]到sa[i]共产生的子串个数
	step2:
		二分第k小子串以哪个sa[i]为首,继而得到子串的长度;为找到最小的起始位置,考虑到后续sa[i]依旧可以形成
	该子串,二分最终确定可以形成该子串的sa区间,区间最小的值即可,我们通过RMQ预处理好即可
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
char s[MAXN];
int t1[MAXN],t2[MAXN],c[MAXN],sa[MAXN];
bool cmp(int *r,int a,int b,int l){
	return r[a] == r[b] && r[a+l] == r[b+l];
}
void SA(int n,int m){
	int p=0;
	int *x=t1,*y=t2;
	REP(i,0,m-1) c[i]=0;
	REP(i,0,n-1) c[x[i]=s[i]]++;
	REP(i,1,m-1) c[i]+=c[i-1];
	REPF(i,n-1,0) sa[--c[x[i]]]=i;
	for(int k=1;p<n;k<<=1,m=p){
		p=0;
		REP(i,n-k,n-1) y[p++]=i;
		REP(i,0,n-1) if(sa[i]>=k) y[p++]=sa[i]-k;
		REP(i,0,m-1) c[i]=0;
		REP(i,0,n-1) c[x[y[i]]]++;
		REP(i,1,m-1) c[i]+=c[i-1];
		REPF(i,n-1,0) sa[--c[x[y[i]]]]=y[i];
		swap(x,y); p=1; x[sa[0]]=0;
		REP(i,1,n-1)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],k) ? p - 1 : p++; 	
	}
}
int height[MAXN],ran[MAXN];
void calheight(int n){
	int k=0;
	REP(i,1,n) ran[sa[i]]=i;
	REP(i,0,n-1){
		if(k)
			k--;
		int j=sa[ran[i]-1];
		while(s[i+k] == s[j+k]) k++;
		height[ran[i]]=k;
	}
}
int dp[MAXN][20],h[MAXN][20];
void RMQ(int n){
	REP(i,1,n) dp[i][0]=sa[i],h[i][0]=height[i];
	for(int j=1;(1<<j)<=n;j++)
		for(int i=1;i+(1<<j)-1<=n;i++){
			dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
			h[i][j]=min(h[i][j-1],h[i+(1<<(j-1))][j-1]);
		}
}
int n;
int lcp(int l,int r){
	if(l == r)
		return n-sa[l];
	if(l>r)
		swap(l,r);
	l++;
	int k=0;
	while((1<<(k+1))<=r-l+1) k++;
	return min(h[l][k],h[r-(1<<k)+1][k]);
}
int query(int l,int r){
	int k=0;
	while((1<<(k+1))<=r-l+1) k++;
	return min(dp[l][k],dp[r-(1<<k)+1][k]);
}
int q;
ll sum[MAXN];
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%s",s)){
		int len=strlen(s);
		n=len;
		s[n++]=0;  sum[0]=0;
		SA(n,150); calheight(len); RMQ(len);
		REP(i,1,len)
			sum[i]=sum[i-1]+len-sa[i]-height[i];
		ll Max=sum[len];
		ll L=0,R=0;
		RD(q);
		while(q--){
			ll k; RD(k);
			k=(L^R^k)+1;
			if(k>Max){
				L=0,R=0;
				puts("0 0");
				continue;
			}
			int pos=lower_bound(sum+1,sum+len+1,k)-sum;
			int l=pos,r=len,res=pos;
			int Len=height[pos]+k-sum[pos-1];
			while(l<=r){
				int mid=(l+r)>>1;
				if(lcp(pos,mid)>=Len){
					res=mid;
					l=mid+1;
				}
				else
					r=mid-1;
			}
			L=query(pos,res); R=L+Len-1;
			L++; R++;
			printf("%lld %lld\n",L,R);
		}
	}
	return 0;
}
