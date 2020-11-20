# 树的直径

两次bfs

```c
#include<cstdio>
#include<cstring>
#include<queue>
#include<cstdlib>
using namespace std;
const int maxn=1000;
int main()
{
	//freopen("data.in","r",stdin); 
	int head[maxn],next[maxn];
	int u[maxn],v[maxn],p[maxn];
	memset(head,-1,sizeof(head));
	int cnt=0;
	while(~scanf("%d%d%d",&u[cnt],&v[cnt],&p[cnt]))
	{
		next[cnt]=head[u[cnt]];head[u[cnt]]=cnt;
		u[cnt+1]=v[cnt];v[cnt+1]=u[cnt];p[cnt+1]=p[cnt];
		next[cnt+1]=head[v[cnt]];head[v[cnt]]=cnt+1;
		cnt+=2;
	}
//
	queue<int>q;
	bool vis[maxn]={0};
	int d[maxn];
	d[1]=0;vis[1]=true;
	q.push(1);
	int s=1;
	while(!q.empty())
	{
		int num=q.front();q.pop();
		for(int i=head[num];~i;i=next[i])
		{
			if(vis[v[i]])continue;
			vis[v[i]]=true;
			d[v[i]]=d[num]+p[i];
			if(d[v[i]]>d[s])s=v[i];
			q.push(v[i]);
		}
	}	
	memset(vis,0,sizeof(vis));
	queue<int>q1;
	d[s]=0;vis[s]=true;
	q1.push(s);
	while(!q1.empty())
	{
		int num=q1.front();q1.pop();
		for(int i=head[num];~i;i=next[i])
		{
			if(vis[v[i]])continue;
			vis[v[i]]=true;
			d[v[i]]=d[num]+p[i];
			if(d[v[i]]>d[s])s=v[i];
			q1.push(v[i]);
		}
	}
	printf("%d",d[s]);
	return 0;
}
```

树形dp

```c
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int maxn=1000;
int u[maxn],v[maxn],p[maxn],head[maxn],next[maxn];
int d[maxn],ans=0;
bool vis[maxn]={0};
void dp(int n)
{
	vis[n]=true;
	for(int i=head[n];~i;i=next[i])
	{
		if(vis[v[i]])continue;
		dp(v[i]);
		ans=max(ans,d[n]+p[i]+d[v[i]]);
		d[n]=max(d[n],d[v[i]]+p[i]);
	}
}
int main()
{
	//freopen("data.in","r",stdin);
	memset(head,-1,sizeof(head));
	int cnt=0;
	while(~scanf("%d%d%d",&u[cnt],&v[cnt],&p[cnt]))
	{
		next[cnt]=head[u[cnt]];head[u[cnt]]=cnt;
		v[cnt+1]=u[cnt];u[cnt+1]=v[cnt];p[cnt+1]=p[cnt];
		next[cnt+1]=head[v[cnt]];head[v[cnt]]=cnt+1;
		cnt+=2;
	}
	dp(1);
	printf("%d",ans);
	return 0;
} 
```

