/*********************************************************
  file name: trie.cpp
  author : kereo
  create time:  2015年05月20日 星期三 16时16分27秒
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
const int MAXN=10000000+50;
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
int sz; //结点总数
struct node{
	int idx,num,tag; //idx为结点编号,num为结点经过次数,tag标记是否是某字符串最后一个字符
	node * ch[sigma_size];
}nod[MAXN],*root,*null;
struct Trie{
	void init(){
		sz=0;
		null=&nod[0];
		null->idx=null->num=null->tag=0;
		newnode(root);
	}
	void newnode(node *&x){
		x=&nod[++sz]; 
		x->idx=sz; x->num=x->tag=0;
		for(int i=0;i<sigma_size;i++)
			x->ch[i]=null;
	}
	void insert(char *str){ 
		int len=strlen(str);
		node *p=root;
		for(int i=0;i<len;i++){
			int k=str[i]-'0';
			if(p->ch[k] == null)
				newnode(p->ch[k]);
			p=p->ch[k];
			p->num++;
		}
		p->tag=1;
	}
}trie;
