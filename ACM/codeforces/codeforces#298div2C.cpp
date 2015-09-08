/*********************************************************
  file name: codeforces#298div2C.cpp
  author : kereo
  create time:  2015年07月20日 星期一 15时40分08秒
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
int a[MAXN];
ll m,sum;
int main(){
	while(~scanf("%d%lld",&n,&m)){
		sum=0;
		REP(i,n){
			scanf("%d",&a[i]);
			sum+=a[i];
		}
		REP(i,n){
			int ans=0;
			ans+=max(0LL,a[i]-max(1LL,m-n+2)+1);
			ans+=max(0LL,min(m-sum+a[i]-1,(ll)a[i]));
			if(i!=1)
				printf(" ");
			printf("%d",ans);
		}
		printf("\n");
	}
	return 0;
}
