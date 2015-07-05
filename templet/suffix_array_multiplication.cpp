/*********************************************************
  file name: suffix_array_multiplication.cpp
  author : kereo
  create time:  2015年05月17日 星期日 22时44分43秒
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
char str[MAXN];
int t1[MAXN],t2[MAXN],sa[MAXN],c[MAXN]; //t1[],t2[]用于交换,sa[i]记录第i小后缀第一个字符的位置,c[]用于基数排序
int cmp(int *r,int a,int b,int l){
	return r[a] == r[b] && r[a+l] == r[b+l];
}
void SA(int n,int m){ //n为字符串后添0后的长度,m是基数排序的范围
	int i,p=0; //p记录当前不同的后缀数
	int *x=t1,*y=t2;
	for(i=0;i<m;i++) c[i]=0;
	for(i=0;i<n;i++) c[x[i]=str[i]]++;
	for(i=1;i<m;i++) c[i]+=c[i-1];
	for(i=n-1;i>=0;i--) sa[--c[x[i]]]=i; //排序第一关键字
	for(int k=1;p<n;k<<=1,m=p){
		for(p=0,i=n-k;i<n;i++) y[p++]=i;
		for(i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k; //利用sa[]排序第二关键字
		for(i=0;i<m;i++) c[i]=0;
		for(i=0;i<n;i++) c[x[y[i]]]++;
		for(i=1;i<m;i++) c[i]+=c[i-1];
		for(i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		for(p=1,x[sa[0]]=0,i=1;i<n;i++)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],k) ? p-1 : p++;
	}
}
int height[MAXN],Rank[MAXN]; //height[i]记录sa[i-1]和sa[i]的LCP,Rank[i]记录suffix(i)在后缀中排第几小
//h[i]=height[rank[i]],h[i]>=h[i-1]-1
void calheight(int n){ //n为字符串本身长度
	int k=0;
	for(int i=1;i<=n;i++) Rank[sa[i]]=i;
	for(int i=0;i<n;i++){
		if(k) k--;
		int j=sa[Rank[i]-1];
		while(str[i+k] == str[j+k]) k++;
		height[Rank[i]]=k;
	}
}
