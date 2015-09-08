/*********************************************************
  file name: codeforces#301div2C.cpp
  author : kereo
  create time:  2015年07月19日 星期日 15时03分54秒
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
const int N=500+50;
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
int sx,sy,ex,ey;
int dx[4]={-1,0,0,1};
int dy[4]={0,-1,1,0};
char mp[N][N];
struct node{
	int x,y;
};
bool bfs(){
	node now;
	now.x=sx; now.y=sy;
	queue<node>que;
	que.push(now);
	while(!que.empty()){
		now=que.front(); que.pop();
		for(int i=0;i<4;i++){
			int nx=now.x+dx[i];
			int ny=now.y+dy[i];
			if(nx == ex && ny == ey && mp[nx][ny] == 'X')
				return true;
			if(nx<0 || nx>=n || ny<0 || ny>=m || mp[nx][ny] == 'X')
				continue;
			mp[nx][ny]='X';
			node next;
			next.x=nx; next.y=ny;
			que.push(next);
		}
	}
	return false;
}
int main(){
	//freopen("in.txt","r",stdin);
	while(~scanf("%d%d",&n,&m)){
		for(int i=0;i<n;i++)
			scanf("%s",mp[i]);
		scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
		sx--; sy--; ex--; ey--;
		if(bfs())
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
