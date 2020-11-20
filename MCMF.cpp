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
        edge[++tot].to=y;edge[tot].w=w;edge[tot].cost=cost;edge[tot].nxt=head[x];head[x]=tot;
        edge[++tot].to=x;edge[tot].w=0;edge[tot].cost=-cost;edge[tot].nxt=head[y];head[y]=tot;
        //printf("%d -> %d : %d %d\n",x,y,w,cost);
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