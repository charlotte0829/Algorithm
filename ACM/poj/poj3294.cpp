/*********************************************************
  file name: poj3294.cpp
  author : Sakura_Mashiro
  create time:  2015年09月24日 星期四 21时16分16秒
**********************************************************
solution:
	suffix_array+binary
		将n个串用各不相同的字符串在一起,后缀数组求sa,二分最长的字符长度len
	根据height数组标记当前以sa[i]为首地址长度len的子串所在第几个串,当height
	不满足时,扫一遍此时的vis数组是否有大于n/2个位置标记即可;特判下n=1的情况
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
const int MAXN=100000+150;
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
char str[MAXN];
int s[MAXN];
int t1[MAXN],t2[MAXN],sa[MAXN],c[MAXN];
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
		swap(x,y);
		p=1; x[sa[0]]=0;
		REP(i,0,n-1)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],k) ? p - 1 : p++;
	}
}
int height[MAXN],ran[MAXN];
void calheight(int n){
	int k=0;
	REP(i,1,n) ran[sa[i]]=i;
	REP(i,0,n-1){
		if(k) k--;
		int j=sa[ran[i]-1];
		while(s[i+k] == s[j+k]) k++;
		height[ran[i]]=k;
	}
}
int cnt;
int vis[N],id[MAXN],ans[MAXN];
bool judge(int n){
	int num=0;
	REP(i,1,n)
		if(vis[i])
			num++;
	return num>n/2;
}
bool ok(int len,int mid,int n){
	int flag=0,sum=0;
	memset(vis,0,sizeof(vis));
	REP(i,1,len-1){
		int idx=id[sa[i]];
		if(height[i]>=mid){
			vis[idx]=1;
			if(i == len-1){
				bool tag=judge(n);
				if(tag){
					flag=1;
					ans[sum++]=sa[i];
				}
			}
		}
		else{
			bool tag=judge(n);
			if(tag){
				flag=1;
				ans[sum++]=sa[i-1];
			}
			memset(vis,0,sizeof(vis));
			vis[idx]=1;
		}
	}
	if(flag)
		cnt=sum;
	return flag;
}
int n;
int main(){
	//freopen("in.txt","r",stdin);
	int T=0;
	while(~scanf("%d",&n) && n){
		int len=0;
		if(T)
			puts("");
		T++;
		memset(id,0,sizeof(id));
		REP(i,1,n){
			scanf("%s",str);
			int l=strlen(str);
			REP(j,0,l-1){
				id[len]=i;
				s[len++]=str[j]-'a'+100;
			}
			s[len++]=i;
		}
		s[len-1]=0;
		if(n == 1){
			printf("%s\n",str);
			continue;
		}
		SA(len,150); calheight(len-1);
		int res=0; cnt=0;
		int l=1,r=1000;
		while(l<=r){
			int mid=(l+r)>>1;
			if(ok(len,mid,n)){
				res=mid;
				l=mid+1;
			}
			else
				r=mid-1;
		}
		if(res == 0)
			puts("?");
		else{
			REP(i,0,cnt-1){
				for(int j=0;j<res;j++)
					printf("%c",s[ans[i]+j]-100+'a');
				puts("");
			}
		}
	}
	return 0;


}
