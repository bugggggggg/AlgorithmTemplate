# spfa判负环

```c
struct Edge
{
    int to,nxt,w;
}edge[5006];
int head[1006],tot;
void addedge(int x,int y,int t)
{
    edge[++tot].to=y;edge[tot].nxt=head[x];
    edge[tot].w=t;head[x]=tot;
}

int n,m;
int cnt[1006];
bool inque[1006];
int d[1006];
queue<int>q;
bool judge()
{
    for(int i=1;i<=n;i++)
    {
        inque[i]=0;d[i]=1e9;cnt[i]=0;
    }
    cnt[1]=1;inque[1]=1;d[1]=0;
    while(!q.empty())q.pop();
    q.push(1);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        inque[x]=0;
        for(int i=head[x];i;i=edge[i].nxt)
        {
            int y=edge[i].to;
            db w=edge[i].w;
            if(d[y]>d[x]+w)
            {
                d[y]=d[x]+w;
                cnt[y]=cnt[x]+1;//记录最短路的路径长度，长度大于n时出现了负环
                if(cnt[y]>n)return true;
                if(!inque[y])
                {
                    inque[y]=1;q.push(y);
                }
            }
        }
    }return false;
}
```

