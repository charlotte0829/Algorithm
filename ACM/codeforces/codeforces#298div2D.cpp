/*********************************************************
  file name: codeforces#298div2D.cpp
  author : kereo
  create time:  2015年07月20日 星期一 16时16分47秒
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
int num[MAXN],ans[MAXN];
vector<int>vec[MAXN];
int main(){
	while(~scanf("%d",&n)){
		memset(num,0,sizeof(num));
		REP(i,n){
			int x;
			scanf("%d",&x);
			vec[x].push_back(i);
			num[x]++;
		}
		int now=0;
		int cnt=0;
		while(now>=0){
			if(num[now]){
				num[now]--;
				ans[cnt++]=vec[now][num[now]];
				now++;
			}
			else
				now-=3;
		}
		int flag=1;
		for(int i=0;i<n;i++){
			if(num[i]){
				flag=0;
				break;
			}
		}
		if(!flag){
			printf("Impossible\n");
			continue;
		}
		else{
			printf("Possible\n");
			for(int i=0;i<cnt;i++){
				if(i)
					printf(" ");
				printf("%d",ans[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
