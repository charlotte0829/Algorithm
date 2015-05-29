/*********************************************************
  file name: Mobius.cpp
  author : kereo
  create time:  2015年05月29日 星期五 23时18分39秒
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
int prime[MAXN],mu[MAXN+5];
void Mobius(){ 
	int tot=0; mu[1]=1; //tot denotes the number of prime 
	memset(prime,0,sizeof(prime));
	for(int i=2;i<MAXN;i++){
		if(!prime[i]){
			mu[i]=-1; prime[tot++]=i;
		}
		for(int j=0;j<tot && prime[j]<=MAXN/i;j++){
			prime[i*prime[j]]=1;
			if(i%prime[j] == 0){
				mu[i*prime[j]]=0;
				break;
			}
			mu[i*prime[j]]=-mu[i];
		}
	}
}
