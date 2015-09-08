/*********************************************************
  file name: codeforces#301div2D.cpp
  author : kereo
  create time:  2015年07月19日 星期日 18时52分55秒
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
#define REP(i,n) for(int i=1;i<=(int)n;i++)
#define FOR(i,v) for(__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
int r,s,p;
double dp[N][N][N]; //dp[i][j][k]表示当rock为i个,scissor为j个,paper为k个的概率
int main(){
	while(~scanf("%d%d%d",&r,&s,&p)){
		memset(dp,0,sizeof(dp));
		dp[r][s][p]=1.0;
		for(int i=r;i>=0;i--)
			for(int j=s;j>=0;j--)
				for(int k=p;k>=0;k--){
					int sum=i*j+i*k+j*k;
					if(i>=1 && j>=1)
						dp[i][j-1][k]+=1.0*i*j/sum*dp[i][j][k];
					if(j>=1 && k>=1)
						dp[i][j][k-1]+=1.0*j*k/sum*dp[i][j][k];
					if(k>=1 && i>=1)
						dp[i-1][j][k]+=1.0*i*k/sum*dp[i][j][k];
				}
		double ans1=0,ans2=0,ans3=0;
		REP(i,r)
			ans1+=dp[i][0][0];
		REP(i,s)
			ans2+=dp[0][i][0];
		REP(i,p)
			ans3+=dp[0][0][i];
		printf("%.12f %.12f %.12f\n",ans1,ans2,ans3);
	}
	return 0;
}
