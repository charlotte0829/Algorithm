/*********************************************************
  file name: codeforces#309div1A.cpp
  author : kereo
  create time:  2015年07月04日 星期六 13时41分52秒
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
const int MAXN=1000+50;
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
int n;
ll C[MAXN][MAXN];
ll dp[MAXN];
int main(){
	for(int i=0;i<MAXN;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++){
			C[i][j]=C[i-1][j-1]+C[i-1][j];
			if(C[i][j]>=mod)
				C[i][j]-=mod;
		}
	}
	while(~scanf("%d",&n)){
		int num=0; 
		memset(dp,0,sizeof(dp)); 
		dp[0]=1;
		for(int i=1;i<=n;i++){
			int m;
			scanf("%d",&m);
			num+=m;
			dp[i]=C[num-1][m-1]*dp[i-1]%mod;
		}
		printf("%lld\n",dp[n]);
	}
	return 0;
}
