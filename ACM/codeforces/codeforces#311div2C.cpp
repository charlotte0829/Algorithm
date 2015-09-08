/*********************************************************
 file name: codeforces#311div2C.cpp
 author : kereo
 create time: 2015年07月02日 星期四 10时55分26秒
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
const int N=200+50;
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
int n;
int cnt[N],num[MAXN],cost[MAXN];
struct node{
	int l,d;
	bool operator < (const node &rhs) const{
		return this->l<rhs.l;
	}
}p[MAXN];
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%d",&n)){
		memset(cnt,0,sizeof(cnt));
		memset(num,0,sizeof(num));
		memset(cost,0,sizeof(num));
		for(int i=0;i<n;i++){
			int l;
			scanf("%d",&l);
			num[l]++; p[i].l=l;
		}
		for(int i=0;i<n;i++){
			int d;
			scanf("%d",&d);
			p[i].d=d; cost[p[i].l]+=d;
		}
		sort(p,p+n);
		for(int i=0;i<MAXN;i++)
			num[i]+=num[i-1];
		for(int i=MAXN-2;i>=0;i--)
			cost[i]+=cost[i+1];
		int ans=inf;
		for(int i=0;i<n;){
			int l=p[i].l,res=0;
			res+=cost[l+1];
			int num1=num[l]-num[l-1],num2=min(num[l-1],max(0,num[l-1]-num1+1));
			for(int j=1;j<N;j++){
				if(cnt[j]<=num2)
					res+=cnt[j]*j,num2-=cnt[j];
				else{
					res+=num2*j;
					break;
				}
			}
			ans=min(ans,res);
			for(int j=0;j<num1;j++){
				cnt[p[i].d]++;
				i++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
