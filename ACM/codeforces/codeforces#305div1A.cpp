/*********************************************************
  file name: codeforces#305div1B.cpp
  author : kereo
  create time:  2015年08月14日 星期五 08时39分22秒
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
const int MAXN=4000+50;
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
ll C[MAXN][MAXN],B[MAXN];
int main(){
	for(int i=0;i<MAXN;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++){
			C[i][j]=C[i-1][j-1]+C[i-1][j];
			if(C[i][j]>=mod)
				C[i][j]%=mod;
		}
	}
	B[0]=B[1]=1;
	for(int i=2;i<MAXN;i++){
		for(int k=0;k<=i;k++){
			B[i]+=B[k]*C[i-1][k];
			if(B[i]>=mod)
				B[i]%=mod;
		}
	}
	while(~scanf("%d",&n)){
		ll ans=0;
		for(int i=0;i<n;i++){
			ans+=C[n][i]*B[i];
			ans%=mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
