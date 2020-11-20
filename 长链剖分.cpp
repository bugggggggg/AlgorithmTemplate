# 长链剖分

线性处理深度相关信息

```c
#include<cstdio>
#include<algorithm>
using namespace std;

struct Edge
{
    int to,nxt;
}edge[2000006];
int head[1000006],tot;
void addedge(int x,int y)
{
    edge[++tot].to=y;edge[tot].nxt=head[x];head[x]=tot;
}

const int maxn=1000006;
int son[maxn],len[maxn];
void dfs1(int x,int fa)
{
    for(int i=head[x];i;i=edge[i].nxt)
    {
        int y=edge[i].to;
        if(y==fa)continue;
        dfs1(y,x);
        if(len[y]>len[son[x]])son[x]=y;
    }
    len[x]=len[son[x]]+1;
}//预处理最深的儿子

int n;
int tmp[maxn],*id=tmp,ans[maxn],*f[maxn];
void dfs2(int x,int fa)
{
    f[x][0]=1;
    if(son[x])
    {
        //开辟重儿子信息存储空间
        f[son[x]]=f[x]+1;dfs2(son[x],x);ans[x]=ans[son[x]]+1;
    }//O(1)继承重儿子信息
    for(int i=head[x];i;i=edge[i].nxt)
    {
        int y=edge[i].to;
        if(y==fa||y==son[x])continue;
        f[y]=id;id+=len[y];dfs2(y,x);
        for(int j=1;j<=len[y];j++)
        {
            f[x][j]+=f[y][j-1];
            if(f[x][j]>f[x][ans[x]]||(f[x][j]==f[x][ans[x]]&&j<ans[x]))
                ans[x]=j;
        }
    }//暴力继承其他儿子信息
    if(f[x][ans[x]]==1)ans[x]=0;
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
    dfs1(1,0);
    f[1]=id;id+=len[1];//开辟空间
    dfs2(1,0);
    for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
    return 0;
}

```

