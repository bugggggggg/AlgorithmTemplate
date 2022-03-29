# 费用流

## （ek+spfa）

```c

namespace MCMF
{
    const int inf=1e9;
    struct Edge
    {
        int to,nxt,w,cost;
    }edge[20066];
    int head[1066],tot;
    void addedge(int x,int y,int w,int cost)
    {
        //printf("%d ->%d :%d %d \n",x,y,w,cost);
        edge[++tot].to=y;edge[tot].w=w;edge[tot].cost=cost;edge[tot].nxt=head[x];head[x]=tot;
        edge[++tot].to=x;edge[tot].w=0;edge[tot].cost=-cost;edge[tot].nxt=head[y];head[y]=tot;
    }
    queue<int>q;
    int d[1066],pre[1066],incf[1066];
    bool inque[1066];
    int s,t;
    void init(int S,int T){s=S,t=T,tot=1;}
    bool spfa()
    {
        for(int i=0;i<=t;i++)d[i]=inf,inque[i]=0;
        d[s]=0;q.push(s);incf[s]=inf;
        while(!q.empty())
        {
            int x=q.front();q.pop();inque[x]=0;
            for(int i=head[x];i;i=edge[i].nxt)
            {
                int y=edge[i].to;
                if(edge[i].w==0)continue;
                if(d[y]>d[x]+edge[i].cost)
                {
                    d[y]=d[x]+edge[i].cost;
                    pre[y]=i;incf[y]=min(incf[x],edge[i].w);
                    if(!inque[y])q.push(y),inque[y]=1;
                }
            }
        }
        if(d[t]==inf)return false;
        return true;
    }
    int mincost;
    void update()
    {
        int x=t;
        while(x!=s)
        {
            int i=pre[x];
            edge[i].w-=incf[t];edge[i^1].w+=incf[t];
            x=edge[i^1].to;
        }
        mincost+=incf[t]*d[t];
    }
    int solve()
    {
        mincost=0;
        while(spfa())update();
        return mincost;
    }
}
```



## ek+dijk

只有在初始边权均为正的时候，下面的板子才对。
初始有负边权的情况要先想办法初始化数组h,即源点s到每个点的最短路
（比如dag上跑dp），然后再跑。

对初始边权均为正。引进“势”，即h函数，保证权值为正。

```c
#include<cstdio>
#include<algorithm>
#include<queue>
#include<utility>
#include<functional>
#include<vector>
using namespace std;

struct Edge
{
    int to,nxt,w,cost;
}edge[100666];
int head[5066],tot;
void addedge(int x,int y,int w,int cost)
{
    edge[++tot].to=y;edge[tot].w=w;edge[tot].cost=cost;
    edge[tot].nxt=head[x];head[x]=tot;
    edge[++tot].to=x;edge[tot].w=0;edge[tot].cost=-cost;
    edge[tot].nxt=head[y];head[y]=tot;
}

int n,m,s,t;
bool vis[5066];
int d[5066],h[5066],pre[5066],incf[5066];
#define pii pair<int,int>
priority_queue<pii,vector<pii>,greater<pii> >pq;
bool dijk()
{
    for(int i=1;i<=n;i++)vis[i]=0,d[i]=1e9;
    pq.push(pii(0,s));d[s]=0;incf[s]=1e9;
    while(!pq.empty())
    {
        int x=pq.top().second;pq.pop();
        if(vis[x])continue;
        vis[x]=1;
        for(int i=head[x];i;i=edge[i].nxt)
        {
            if(edge[i].w==0)continue;
            int y=edge[i].to;
            if(vis[y])continue;
            if(d[y]>d[x]+edge[i].cost+h[x]-h[y])
            {
                d[y]=d[x]+edge[i].cost+h[x]-h[y];
                pq.push(pii(d[y],y));
                pre[y]=i;
                incf[y]=min(incf[x],edge[i].w);
            }
        }
    }return d[t]!=1e9;
}
int maxflow,mincost;
void update()
{
    int x=t;
    while(x!=s)
    {
        int i=pre[x];
        edge[i].w-=incf[t];
        edge[i^1].w+=incf[t];
        x=edge[i^1].to;
    }
    maxflow+=incf[t];mincost+=incf[t]*(d[t]-h[s]+h[t]);
    for(int i=1;i<=n;i++)h[i]+=d[i];
}

int main()
{
    freopen("P3381_8.in","r",stdin);
    scanf("%d%d%d%d",&n,&m,&s,&t);
    int x,y,w,cost;
    tot=1;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&x,&y,&w,&cost);
        addedge(x,y,w,cost);
    }
    while(dijk())update();
    printf("%d %d",maxflow,mincost);
    return 0;
}

```

