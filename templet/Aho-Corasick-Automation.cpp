/*********************************************************
  file name: Aho-Corasick-Automation.cpp
  author : kereo
  create time:  2015年05月21日 星期四 17时01分53秒
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
int sz,head,tail; //sz为结点总数
struct node{
	int idx,num,tag; //idx为结点编号,num为结点经过次数,tag标记是否是某字符串最后一个字符
	node *ch[sigma_size],*fail;
}nod[MAXN],*que[MAXN],*root,*null;
struct AC{
	void init(){
		sz=0;
		head=tail=0; null=&nod[0];
		null->idx=null->num=null->tag=0; null->fail=null;
		newnode(root);
	}
	void newnode(node *&x){
		x=&nod[sz];
		x->idx=sz++; x->num=x->tag=0; x->fail=null;
		for(int i=0;i<sigma_size;i++)
			x->ch[i]=null;
	}
	void insert(char *str){
		node *p=root;
		int len=strlen(str);
		for(int i=0;i<sigma_size;i++){
			int k=str[i]-'a';
			if(p->ch[k] == null)
				newnode(p->ch[k]);
			p=p->ch[k]; p->num++;
		}
		p->tag=1;
	}
	void get_fail(){
		que[tail++]=root;
		while(head<tail){
			node *p=que[head++];
			for(int k=0;k<sigma_size;k++){
				if(p->ch[k] == null){
					if(p == root)
						p->ch[k]=root;
					else
						p->ch[k]=p->fail->ch[k];
				}
				else{
					if(p == root)
						p->ch[k]->fail=root;
					else
						p->ch[k]->fail=p->fail->ch[k];
					que[tail++]=p->ch[k];
				}
			}
		}
	}
}ac;
int main(){
	return 0;
}
