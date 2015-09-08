/*********************************************************
  file name: codeforces#301div2E.cpp
  author : kereo
  create time:  2015年07月19日 星期日 15时26分08秒
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
#define REP(i,n) for(int i=1;i<=(int)n;i++)
#define FOR(i,v) for(__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
int n;
map<int,int>mp,mp1; //mp存位置对应的值,mp1存值对应的位置
int a[MAXN],x[MAXN],c[MAXN];
int lowbit(int x){
	return x&(-x);
}
void add(int x,int d){
	while(x<MAXN){
		c[x]+=d;
		x+=lowbit(x);
	}
}
int  query(int x){
	int res=0;
	while(x){
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
}
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%d",&n)){
		mp.clear();mp1.clear(); 
		memset(c,0,sizeof(c));
		REP(i,n){
			int u,v;
			scanf("%d%d",&u,&v);
			if(!mp.count(u))
				mp[u]=u;
			if(!mp.count(v))
				mp[v]=v;
			mp1[mp[u]]=v; mp1[mp[v]]=u;
			swap(mp[u],mp[v]);
		}
		int cnt=0;
		FOR(it,mp){
			x[cnt]=a[cnt]=it->second;
			cnt++;
			//printf("pos=%d val=%d\n",it->first,it->second);
		}
		/*cout<<"cnt="<<cnt<<endl;
		for(int i=0;i<cnt;i++)
			printf("%d ",x[i]);
		printf("\n");*/
		sort(a,a+cnt);
		ll ans=0;
		for(int i=0;i<cnt;i++){
			int val=lower_bound(a,a+cnt,x[i])-a+1;
			//cout<<"x[i]="<<x[i]<<" val="<<val<<" query="<<query(val)<<endl;
			ans+=val-1-query(val);
			add(val,1);
		}
	//	cout<<"ans="<<ans<<endl;
		for(int i=0;i<cnt;i++){
			int l=mp1[x[i]],r=x[i];
			if(l>r)
				swap(l,r);
			ans+=r-l+1;
			int L=lower_bound(a,a+cnt,l)-a;
			int R=lower_bound(a,a+cnt,r)-a;
			if(r == a[R])
				R++;
			ans-=R-L;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
