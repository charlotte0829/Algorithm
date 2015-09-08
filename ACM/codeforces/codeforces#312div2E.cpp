/*********************************************************
  file name: codeforces#312div2E.cpp
  author : kereo
  create time:  2015年07月17日 星期五 15时54分25秒
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
#define REPF(i,n) for(int i=0;i<(int)n;i++)
#define FOR(i,v) for(__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
int n,q;
int cnt[sigma_size];
char str[MAXN];
struct node{
	int l,r;
	int num,tag;
}seg[sigma_size][MAXN<<2];
void push_down(int id,int rt){
	if(seg[id][rt].tag == -1)
		return ;
	seg[id][L(rt)].tag=seg[id][rt].tag;
	seg[id][L(rt)].num=seg[id][rt].tag*(seg[id][L(rt)].r-seg[id][L(rt)].l+1);
	seg[id][R(rt)].tag=seg[id][rt].tag;
	seg[id][R(rt)].num=seg[id][rt].tag*(seg[id][R(rt)].r-seg[id][R(rt)].l+1);
	seg[id][rt].tag=-1;
}
void push_up(int id,int rt){
	seg[id][rt].num=seg[id][L(rt)].num+seg[id][R(rt)].num;
}
void build(int id,int rt,int l,int r){
	seg[id][rt].l=l; seg[id][rt].r=r; 
	seg[id][rt].num=0; seg[id][rt].tag=-1;
	if(l == r){
		seg[id][rt].num=(str[l] == 'a'+id);
		//cout<<"id="<<id<<" rt="<<rt<<" l="<<l<<" r="<<r<<" num="<<seg[id][rt].num<<endl;
		return ;
	}
	int mid=(l+r)>>1;
	build(id,L(rt),l,mid); build(id,R(rt),mid+1,r);
	push_up(id,rt);
}
void update(int id,int rt,int l,int r,int c){
	if(seg[id][rt].l == l && seg[id][rt].r == r){
		seg[id][rt].tag=c;
		seg[id][rt].num=c*(r-l+1);
		return ;
	}
	push_down(id,rt);
	int mid=(seg[id][rt].l+seg[id][rt].r)>>1;
	if(r<=mid)
		update(id,L(rt),l,r,c);
	else if(l>mid)
		update(id,R(rt),l,r,c);
	else{
		update(id,L(rt),l,mid,c);
		update(id,R(rt),mid+1,r,c);
	}
	push_up(id,rt);
}
int query(int id,int rt,int l,int r){
	//cout<<" L="<<l<<" R="<<r<< "l="<<seg[id][rt].l<<" r="<<seg[id][rt].r<<endl;
	if(seg[id][rt].l == l && seg[id][rt].r == r)
		return seg[id][rt].num;
	push_down(id,rt);
	int mid=(seg[id][rt].l+seg[id][rt].r)>>1;
	int ans;
	if(r<=mid)
		ans=query(id,L(rt),l,r);
	else if(l>mid)
		ans=query(id,R(rt),l,r);
	else
		ans=query(id,L(rt),l,mid)+query(id,R(rt),mid+1,r);
	push_up(id,rt);
	return ans;
}
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%d%d",&n,&q)){
		scanf("%s",str+1);
		REPF(i,sigma_size)
			build(i,1,1,n);
		int kase=0;
		while(q--){
			int l,r,k;
			scanf("%d%d%d",&l,&r,&k);
			REPF(i,sigma_size)
				cnt[i]=query(i,1,l,r);
			REPF(i,sigma_size)
				update(i,1,l,r,0);
			if(k){
				int sum=0;
				REPF(i,sigma_size){
					if(cnt[i])
						update(i,1,l+sum,l+sum+cnt[i]-1,1);
					sum+=cnt[i];
				}
			}
			else{
				int sum=0;
				for(int i=sigma_size-1;i>=0;i--){
					if(cnt[i])
						update(i,1,l+sum,l+sum+cnt[i]-1,1);
					sum+=cnt[i];
				}
			}
		}
		REP(i,n){
			REPF(j,sigma_size){
				if(query(j,1,i,i)){
					printf("%c",'a'+j);
					break;
				}
			}
		}
		printf("\n");
	}
	return 0;
}
