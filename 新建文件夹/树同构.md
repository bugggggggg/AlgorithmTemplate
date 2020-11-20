# 树同构



树根固定时，树的最小表示法与树的形态一一对应

根不固定时，考虑重心，

如果它是唯一的，可以以它为根求最小表示法

否则，一定是两棵大小为n/2的树中间连一条边，对两边的树分别求最小表示法（这时根是固定的了）

最小表示法：对dfs序的01串用trie进行排序

时间复杂度O(m*n^2)//m树的棵树，n树的节点数

```c
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=56;

struct Trie
{
	int ch[2],w,siz;
	void init()
	{
		ch[0]=ch[1]=w=siz=0;
	}
}node[10000];
int TOT;
void add(char*s,int len)
{
	int now=0,i=0;
	while(i<len)
	{
		if(!node[now].ch[s[i]-'0'])
		{
			node[now].ch[s[i]-'0']=++TOT;
			node[TOT].init();
		}
		now=node[now].ch[s[i]-'0'];
		node[now].siz++;
		i++;
	}
	node[now].w++;
}
/*
	用trie对01串进行排序
	siz记录该点被经过的次数
*/
void paixu(char*s,int len)
{
	if(len==0)return;
	int cnt=0,llen=0;
	for(int i=0;i<len;i++)
	{
		if(s[i]=='0')cnt++;
		else cnt--;
		llen++;
		if(!cnt)
		{
			paixu(s+i+1-llen+1,llen-2);//递归子树
			llen=0;
		}
	}
	llen=0;
	TOT=0;node[0].init();
	for(int i=0;i<len;i++)
	{
		if(s[i]=='0')cnt++;
		else cnt--;
		llen++;
		if(!cnt)
		{
			add(s+i+1-llen,llen);
			llen=0;
		}
	}
	int p=0,now=0;
	while(p<len)
	{
		if(node[now].ch[0]&&node[node[now].ch[0]].siz)
		{
			s[p++]='0';now=node[now].ch[0];
		}
		else s[p++]='1',now=node[now].ch[1];
		node[now].siz--;
		if(node[now].w)node[now].w--,now=0;//直接回根
	}
}

//把01串加到trie里判断重合
int solve(char*s,int len,int id)
{
	int now=0,i=0;
	while(i<len)
	{
		if(!node[now].ch[s[i]-'0'])
		{
			node[now].ch[s[i]-'0']=++TOT;
			node[TOT].init();
		}
		now=node[now].ch[s[i]-'0'];
		i++;
	}
	if(!node[now].w)node[now].w=id;
	return node[now].w;
}

struct Edge
{
	int to,nxt;
}edge[maxn<<1];
int head[maxn],tot;
void addedge(int x,int y)
{
	edge[++tot].to=y;edge[tot].nxt=head[x];head[x]=tot;
}
int M,n;
int siz[maxn];
void dfs(int x,int fa)
{
	siz[x]=1;
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int y=edge[i].to;
		if(y==fa)continue;
		dfs(y,x);siz[x]+=siz[y];
	}return ;
}
int findroot(int x,int fa,int S)
{
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int y=edge[i].to;
		if(y==fa||siz[y]<=S)continue;
		return findroot(y,x,S);
	}return x;
}
char s[maxn][maxn<<1];
int L[maxn];
void dfs2(int x,int fa,int id)
{
	s[id][L[id]++]='0';
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int y=edge[i].to;
		if(y==fa)continue;
		dfs2(y,x,id);
	}s[id][L[id]++]='1';
}
int main()
{
	scanf("%d",&M);
	for(int _=1;_<=M;_++)
	{
		scanf("%d",&n);
		int x;
		for(int i=1;i<=n;i++)head[i]=0;
		tot=0;
		int root;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&x);
			if(x==0){root=i;continue;}
			addedge(x,i);addedge(i,x);
		}
		dfs(root,0);
		int rt1=findroot(root,0,n>>1),rt2=0;
		for(int i=head[rt1];i;i=edge[i].nxt)
		{
			int y=edge[i].to;
			if((siz[y]<<1)==n){rt2=y;break;}
		}
		dfs2(rt1,rt2,_);
		if(rt2)dfs2(rt2,rt1,_);
		paixu(s[_],L[_]);
	}
	TOT=0;node[0].init();
	for(int _=1;_<=M;_++)
	{
		printf("%d\n",solve(s[_],L[_],_));
	}
	return 0;
}
```



