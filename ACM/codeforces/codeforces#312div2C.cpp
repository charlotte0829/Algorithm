/*********************************************************
  file name: codeforces#312div2C.cpp
  author : kereo
  create time:  2015年07月17日 星期五 14时43分29秒
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
int n;
int num[MAXN],sum[MAXN];
void update(int x,int cnt){
	while(x<MAXN){
		num[x]++;
		sum[x]+=cnt; cnt++; x<<=1;
	}
}
int main(){
	while(~scanf("%d",&n)){
		memset(num,0,sizeof(num));
		memset(sum,0,sizeof(sum));
		REP(i,n){
			int x;
			scanf("%d",&x);
			int cnt=1;
			update(x,0);
			while(x){
				if((x>1) && x%2 == 1){
					x>>=1;
					update(x,cnt);
				}
				else{
					x>>=1;
					num[x]++; sum[x]+=cnt;
				}
				cnt++;
			}
		}
		int ans=sum[1];
			for(int i=2;i<MAXN;i++)
				if(num[i] == n)
					ans=min(ans,sum[i]);
		printf("%d\n",ans);
	}
	return 0;
}
