# 最小生成树

## prim

```c
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	int link[51][51];
	int n,m;
	while(scanf("%d",&n)&&n)
	{
		scanf("%d",&m);
		memset(link,0x3f,sizeof(link));
		bool vis[51]={0};
		int d[51];
		memset(d,0x3f,sizeof(d));
		int u,v,p;
		for(int i=0;i<m;i++)
		{
			scanf("%d%d%d",&u,&v,&p);
			link[u][v]=link[v][u]=min(link[u][v],p);
		}
		d[1]=0;//vis[1]=true;
		for(int i=1;i<n;i++)
		{
			int x=0;
			for(int j=1;j<=n;j++)
			{
				if(!vis[j]&&(x==0||d[j]<d[x]))x=j;
			}
			vis[x]=true;
			for(int j=1;j<=n;j++)
			{
				if(!vis[j])d[j]=min(d[j],link[x][j]);
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++)ans+=d[i];
		printf("%d\n",ans);
	}
	return 0;
}

```



## kruskal

```c
#include<cstdio>
#include<algorithm>
using namespace std;
struct Edge
{
	int s,t,value;
	bool operator <(const Edge&a)const
	{
		return value<a.value;
	}
};
int fa[30];
int myfind(int n)
{
	return fa[n]==n?n:fa[n]=myfind(fa[n]);
}
int main()
{
	int cnt,ecnt;
	Edge edge[600];
	while(scanf("%d",&cnt)&&cnt)
	{
		ecnt=0;
		for(int i=1;i<=cnt;i++)
			fa[i]=i;
		char str[2];
		int N,val;
		for(int i=1;i<cnt;i++)
		{
			scanf("%s%d",str,&N);
			while(N--)
			{
				scanf("%s%d",str,&val);
				edge[ecnt].s=i;edge[ecnt].t=str[0]-'A'+1;
				edge[ecnt].value=val;
				ecnt++;
			}
		}
		sort(edge,edge+ecnt);
		int ans=0;
		for(int i=0;i<ecnt;i++)
		{
			int p=myfind(edge[i].s),q=myfind(edge[i].t);
			if(p==q)continue;
			fa[p]=q;
			ans+=edge[i].value;
		} 
		printf("%d\n",ans);
	}
	return 0;
}
```

