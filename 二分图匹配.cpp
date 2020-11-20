# 二分图匹配

匈牙利O（n*m）点数乘边数

还以以dinic跑最大流

关于二分图中其他的性质有：

1. 二分图的最小顶点覆盖 最小顶点覆盖要求用最少的点(U或V中都行)，让每条边都至少和其中一个点关联。 Knoig定理：二分图的最小顶点覆盖数等于二分图的最大匹配数。

2. DAG图的最小路径覆盖 ：

   2.1 DAG的最小不相交路径覆盖：把原图的每个点V拆成Vx Vx和Vy Vy两个点，如果有一条有向边A->B，那么就加边Ax−>By Ax−>By。这样就得到了一个二分图。那么最小路径覆盖=原图的结点数-新图的最大匹配数

   2.2 DAG的最小可相交路径覆盖：先用floyd求出原图的传递闭包，即如果a到b有路径，那么就加边a->b。然后就转化成了最小不相交路径覆盖问题。

3. 二分图的最大独立集 在Ｎ个点的图G中选出m个点，使这m个点两两之间没有边．求m最大值。 引理：二分图的最大独立集数 = 节点数(n)—最大匹配数(m)

```c
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1005;
struct Edge
{
	int to,nxt;
}edge[maxn*maxn];
int head[maxn],tot;
void addedge(int x,int y)
{
	edge[++tot].to=y;edge[tot].nxt=head[x];head[x]=tot;
}
int n,m,e;
int match[maxn],vis[maxn];
bool dfs(int x,int ti)
{
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int y=edge[i].to;
		if(vis[y]==ti)continue;
		vis[y]=ti;
		if(!match[y]||dfs(match[y],ti))
		{
			match[y]=x;return true;
		}
	}
	return false;
}
int main()
{
	scanf("%d%d%d",&n,&m,&e);//左右点集、边数
	int x,y;
	for(int i=1;i<=e;i++)
	{
		scanf("%d%d",&x,&y);
		if(x>n||y>m)continue;
		addedge(x,y);//左往右连有向边
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		if(dfs(i,i))ans++;//寻找增广路
	printf("%d",ans);
	return 0;
}
```

