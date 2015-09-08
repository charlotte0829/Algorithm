/*********************************************************
  file name: codeforces#313div1B.cpp
  author : kereo
  create time:  2015年07月22日 星期三 23时08分12秒
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
char s1[MAXN],s2[MAXN];
bool cmp(char *s1,char *s2,int len){
	for(int i=0;i<len;i++)
		if(s1[i]!=s2[i])
			return false;
	return true;
}
bool dfs(char *s1,char *s2,int len){
	if(cmp(s1,s2,len))
		return true;
	if(len&1)
		return false;
	len>>=1;
	if((dfs(s1,s2+len,len) && dfs(s1+len,s2,len)) ||(dfs(s1,s2,len) && dfs(s1+len,s2+len,len))) 
	  return true;
	return false;	
}
int main(){
	while(~scanf("%s%s",s1,s2)){
		int len=strlen(s1);
		if(dfs(s1,s2,len))
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
