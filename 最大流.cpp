
//整型版
namespace Dinic
{
	const int inf=1e9;
    struct Edge
    {
        int to,nxt,w;
    }edge[10066];
    int head[1066],tot;
    void addedge(int x,int y,int w)
    {
        edge[++tot].to=y;edge[tot].w=w;edge[tot].nxt=head[x];head[x]=tot;
        edge[++tot].to=x;edge[tot].w=0;edge[tot].nxt=head[y];head[y]=tot;
        // printf("%d -> %d : %d\n",x,y,w);
    }
    queue<int>q;
    int d[1066],s,t;
    void init(int S,int T){s=S,t=T,tot=1;}
    bool bfs()
    {
        for(int i=0;i<=t;i++)d[i]=0;
        while(!q.empty())q.pop();
        d[s]=1;q.push(s);
        while(!q.empty())
        {
            int x=q.front();q.pop();
            for(int i=head[x];i;i=edge[i].nxt)
            {
                int y=edge[i].to;
                if(d[y]||edge[i].w==0)continue;
                d[y]=d[x]+1;q.push(y);
                if(y==t)return true;
            }
        }return false;
    }
    int dinic(int x,int flow)
    {
        if(x==t)return flow;
        int rest=flow;
        for(int i=head[x];i&&rest;i=edge[i].nxt)
        {
            int y=edge[i].to;
            if(edge[i].w==0||d[y]!=d[x]+1)continue;
            int k=dinic(y,min(rest,edge[i].w));
            if(!k)d[y]=0;
            edge[i].w-=k;edge[i^1].w+=k;rest-=k;
        }return flow-rest;
    }

    /*
    //跑double的时候用加精度高于减
    db dinic(int x,db flow)
    {
        if(x==t)return flow;
        db ret=0;
        for(int i=head[x];i;i=edge[i].nxt){
            int y=edge[i].to;
            if(d[y]==d[x]+1&&edge[i].w>eps){
                db k=dinic(y,min(edge[i].w,flow));
                if(k<0)continue;
                edge[i].w-=k;
                edge[i^1].w+=k;
                ret+=k;
                flow-=k;
                if(flow<eps)break;
            }
        }
        if(ret<eps)d[x]=-1;
        return ret;
        
    }
    */



    int solve()
    {
        int maxflow=0,flow;
        while(bfs())
            while(flow=dinic(s,inf))maxflow+=flow;
        return maxflow;
    }
}


//double版
const db eps=1e-9;

namespace Dinic
{
    const int inf=1e9;
    struct Edge
    {
        int to,nxt;
        db w;
    }edge[100660];
    int head[20660],tot;
    void addedge(int x,int y,db w)
    {
        edge[++tot].to=y;edge[tot].w=w;edge[tot].nxt=head[x];head[x]=tot;
        edge[++tot].to=x;edge[tot].w=0;edge[tot].nxt=head[y];head[y]=tot;
        // printf("%d -> %d : %d\n",x,y,w);
    }
    queue<int>q;
    int d[20660],s,t;
    void init(int S,int T){
        s=S,t=T,tot=1;
        for(int i=0;i<=T;i++)head[i]=0;
    }
    bool bfs()
    {
        for(int i=0;i<=t;i++)d[i]=0;
        while(!q.empty())q.pop();
        d[s]=1;q.push(s);
        while(!q.empty())
        {
            int x=q.front();q.pop();
            for(int i=head[x];i;i=edge[i].nxt)
            {
                int y=edge[i].to;
                if(d[y]||edge[i].w<eps)continue;
                d[y]=d[x]+1;q.push(y);
                if(y==t)return true;
            }
        }return false;
    }
    db dinic(int x,db flow)
    {
        if(x==t)return flow;
        db ret=0;
        for(int i=head[x];i;i=edge[i].nxt){
            int y=edge[i].to;
            if(d[y]==d[x]+1&&edge[i].w>eps){
                db k=dinic(y,min(edge[i].w,flow));
                if(k<0)continue;
                edge[i].w-=k;
                edge[i^1].w+=k;
                ret+=k;
                flow-=k;
                if(flow<eps)break;
            }
        }
        if(ret<eps)d[x]=-1;
        return ret;
    }
    db solve()
    {
        db maxflow=0,flow;
        while(bfs())
            while(flow=dinic(s,inf))maxflow+=flow;
        return maxflow;
    }

}

/*

EK

#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=10010,maxm=100010;
struct Edge
{
    int to,w,nxt;
}edge[maxm*2];
int head[maxn],tot=1;
void addedge(int x,int y,int w)
{
    ++tot;edge[tot].to=y;edge[tot].w=w;edge[tot].nxt=head[x];head[x]=tot;
    ++tot;edge[tot].to=x;edge[tot].w=0;edge[tot].nxt=head[y];head[y]=tot;
}
int n,m,s,t;
bool vis[maxn];
queue<int>q;
int incf[maxn],pre[maxn];
int maxflow;
bool bfs()
{
    memset(vis,0,sizeof(vis));
    while(!q.empty())q.pop();
    q.push(s);vis[s]=1;
    incf[s]=1<<29;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=edge[i].nxt)
        {
            if(edge[i].w==0)continue;
            int y=edge[i].to;
            if(vis[y])continue;
            incf[y]=min(incf[x],edge[i].w);
            pre[y]=i;
            q.push(y);vis[y]=1;
            if(y==t)return true;
        }   
    } 
    return false;
} 
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
    maxflow+=incf[t];
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    int x,y,w;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&w);
        addedge(x,y,w);
    }
    while(bfs())update();
    printf("%d",maxflow);
    return 0;
}

*/

/*
    ISAP
    对d[]数组往大走的个人感觉;

    初始bfs分层的时候同时考虑了正反边，所以每个点的深度是考虑正反边的
    相对汇点t的最小值，也就是整个图的深度是最接近汇点t的。所以当一个点x在
    当前d[x]对后续点无法继续做贡献时（rest！=0），d[x]要增大
    （步步增大，以找到能流过的所有流）

    #include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
const int maxn=1210,maxm=120010;
struct Edge
{
    int to,nxt,w;
}edge[maxm*2];
int head[maxn],cur[maxn],tot;
void addedge(int x,int y,int w)
{
    edge[++tot].to=y;edge[tot].w=w;edge[tot].nxt=head[x];head[x]=tot;
    edge[++tot].to=x;edge[tot].w=0;edge[tot].nxt=head[y];head[y]=tot;
}
int dep[maxm],gap[maxm];
int n,m,s,t;
queue<int>q;
void bfs()
{
    dep[t]=1;gap[1]=1;
    q.push(t);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=edge[i].nxt)
        {
            int y=edge[i].to;
            if(dep[y])continue;
            q.push(y);dep[y]=dep[x]+1;
            gap[dep[y]]++;
        } 
    } 
}//初始化，从t到s搜出每个点的初始深度
int maxflow;
int dfs(int x,int flow)
{
    if(x==t)
    {
        maxflow+=flow;
        return flow;
    }
    int rest=flow;
    for(int i=cur[x];i&&rest;i=edge[i].nxt)
    {
        cur[x]=i;
        if(edge[i].w==0)continue;
        int y=edge[i].to;
        if(dep[y]!=dep[x]-1)continue;
        int k=dfs(y,min(rest,edge[i].w));
        if(k)
        {
            edge[i].w-=k;
            edge[i^1].w+=k;
            rest-=k;
        }
    }
    if(!rest)return flow;
    gap[dep[x]]--;
    if(!gap[dep[x]])dep[s]=n+2;//这里不能随意赋很大的值，gap会越界
    dep[x]++;gap[dep[x]]++;
    return flow-rest;
}
int ISAP()
{
    maxflow=0;
    bfs();
    while(dep[s]<=n+1)
    {
        memcpy(cur,head,sizeof(head));//当前弧优化
        dfs(s,(1<<30));
    }
    return maxflow;
} 
int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    int x,y,w;
    tot=1;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&w);
        addedge(x,y,w);
    }
    printf("%d",ISAP());
    return 0;
}

*/

/*
    hlpp

#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int inf=1<<30;
const int maxn=12100;
struct Edge
{
    int to,w,nxt;
} edge[400010];
int tot=1,head[maxn];
void addedge(int x,int y,int w)
{
    edge[++tot].to=y;edge[tot].w=w;edge[tot].nxt=head[x];head[x]=tot;
    edge[++tot].to=x;edge[tot].w=0;edge[tot].nxt=head[y];head[y]=tot;
}
int n,m,s,t;
int e[maxn],h[maxn],cnth[maxn*2];
struct cmp
{
    bool operator () (int a,int b)const
    {
        return h[a]<h[b];
    }
};
bool inque[maxn];
queue<int>q;
void bfs()
{
    memset(h,0x3f,sizeof(h));
    h[t]=0;
    q.push(t);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        inque[x]=0;
        for(int i=head[x];i;i=edge[i].nxt)
        {
            int y=edge[i].to;
            if(edge[i^1].w&&h[y]>h[x]+1)//fan pao
            {
                h[y]=h[x]+1;
                if(!inque[y])
                {
                    q.push(y);inque[y]=1;
                }
            }
        }
    }
}
priority_queue<int,vector<int>,cmp>pq;
void push_(int x)
{
    for(int i=head[x];i;i=edge[i].nxt)
    {
        int y=edge[i].to;
        if(edge[i].w&&h[y]+1==h[x])
        {
            int mn=min(edge[i].w,e[x]);
            edge[i].w-=mn;edge[i^1].w+=mn;
            e[x]-=mn;e[y]+=mn;
            if(!inque[y]&&y!=s&&y!=t)
            {
                pq.push(y);inque[y]=1;
            }
            if(!e[x])return;
        }
    }
}
void relabel(int x)
{
    h[x]=inf;
    for(int i=head[x];i;i=edge[i].nxt)
    {
        int y=edge[i].to;
        if(edge[i].w&&h[y]+1<h[x])h[x]=h[y]+1;
    }
}
int hlpp()
{
    bfs();
    if(h[s]==0x3f3f3f3f)return 0;
    h[s]=n;
    for(int i=1;i<=n;i++)
        if(h[i]<0x3f3f3f3f)cnth[h[i]]++;
    for(int i=head[s];i;i=edge[i].nxt)
    {
        int y=edge[i].to,w=edge[i].w;
        if(w)
        {
            e[s]-=w;e[y]+=w;
            edge[i].w-=w;edge[i^1].w+=w;
            if(y!=s&&y!=t&&!inque[y])
            {
                pq.push(y);inque[y]=true;
            }
        }
    }
    while(!pq.empty())
    {
        int x=pq.top();pq.pop();
        inque[x]=false;
        push_(x);
        if(e[x])
        {
            cnth[h[x]]--;
            if(cnth[h[x]]==0)
            {
                for(int i=1;i<=n;i++)
                {
                    if(i!=s&&i!=t&&h[i]>h[x]&&h[i]<n+1)
                    {
                        h[i]=n+1;
                    }
                }
            }
            relabel(x);
            cnth[h[x]]++;
            pq.push(x);inque[x]=true;
        }
    }
    return e[t];
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    int x,y,w;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&w);
        addedge(x,y,w);
    }
    printf("%d",hlpp());
    return 0;
}


*/