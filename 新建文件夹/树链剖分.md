# 树链剖分

本题只有沿重链跑。对于x的子树的的操作，对区间[ id[x] , id[x] + siz[x] - 1 ]进行操作就行

```c
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn=30006;
struct Edge
{
    int to,nxt;
}edge[maxn<<1];
int head[maxn],tot;
void addedge(int x,int y)
{
    edge[++tot].to=y;edge[tot].nxt=head[x];head[x]=tot;
}

////父亲///////链顶/////深度///////重儿子////子树大小////
int fa[maxn],top[maxn],dep[maxn],son[maxn],siz[maxn];
int num,id[maxn],rk[maxn];//线段树上的编号和原编号的对应关系
int n;
void dfs1(int x,int f)
{
    dep[x]=dep[f]+1;siz[x]=1;fa[x]=f;
    for(int i=head[x];i;i=edge[i].nxt)
    {
        int y=edge[i].to;
        if(y==f)continue;
        dfs1(y,x);
        siz[x]+=siz[y];
        if(siz[y]>siz[son[x]])son[x]=y;
    }
}
void dfs2(int x,int t)
{
    top[x]=t;id[x]=++num;rk[num]=x;
    if(son[x])dfs2(son[x],t);
    for(int i=head[x];i;i=edge[i].nxt)
    {
        int y=edge[i].to;
        if(y==fa[x]||y==son[x])continue;
        dfs2(y,y);
    }
}


int w[maxn];

struct Node
{
    int sum,mx;
    Node operator +(const Node&a)
    {
        return Node{sum+a.sum,max(mx,a.mx)};
    }
}node[maxn<<2];
void pushup(int p)
{
    node[p].sum=node[p<<1].sum+node[p<<1|1].sum;
    node[p].mx=max(node[p<<1].mx,node[p<<1|1].mx);
}
void build(int p,int l,int r)
{
    if(l==r)
    {
        node[p].sum=node[p].mx=w[rk[l]];
        return;
    }
    int mid=(l+r)>>1;
    build(p<<1,l,mid);build(p<<1|1,mid+1,r);
    pushup(p);
}
void update(int p,int l,int r,int aim,int w)
{
    if(l==r)
    {
        node[p].mx=node[p].sum=w;
        return ;
    }
    int mid=(l+r)>>1;
    if(aim<=mid)update(p<<1,l,mid,aim,w);
    if(aim>mid)update(p<<1|1,mid+1,r,aim,w);
    pushup(p);
}
Node query(int p,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr)return node[p];
    int mid=(l+r)>>1;
    if(ql<=mid&&mid<qr)
        return query(p<<1,l,mid,ql,qr)+query(p<<1|1,mid+1,r,ql,qr);
    else if(ql<=mid)
        return query(p<<1,l,mid,ql,qr);
    else if(mid<qr)
        return query(p<<1|1,mid+1,r,ql,qr);
}
Node solve(int x,int y)
{
    Node ret=Node{0,(int)-1e9};
    while(top[x]!=top[y])//沿重链往上跑
    {
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        ret=ret+query(1,1,n,id[top[x]],id[x]);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    ret=ret+query(1,1,n,id[x],id[y]);
    return ret;
}
int main()
{
    scanf("%d",&n);
    int x,y;
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        addedge(x,y);addedge(y,x);
    }
    for(int i=1;i<=n;i++)scanf("%d",&w[i]);
    dfs1(1,0);dfs2(1,1);build(1,1,n);
    int _;
    scanf("%d",&_);
    char op[10];
    while(_--)
    {
        scanf("%s%d%d",op,&x,&y);
        if(op[0]=='C')update(1,1,n,id[x],y);
        else if(op[1]=='M')printf("%d\n",solve(x,y).mx);
        else printf("%d\n",solve(x,y).sum);
    }
    return 0;
}


```



