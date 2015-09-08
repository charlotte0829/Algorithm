/*********************************************************
  file name: codeforces#308div2C.cpp
  author : kereo
  create time:  2015年07月05日 星期日 14时41分14秒
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
int n,m;
int main(){
	while(~scanf("%d%d",&n,&m)){
		if(n == 2){
			printf("YES\n");
			continue;
		}
		bool tag=true;
		while(m){
			int x=m%n;
			if(x<=1)
				m/=n;
			else if(x == n-1)
				m=m/n+1;
			else{
				tag=false;
				break;
			}
		}
		if(tag)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
	return 0;
}
