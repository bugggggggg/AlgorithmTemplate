# 斐波那契树

左子树为Tn-1，右子树为Tn-2。

每次对重心删除一半，经过n次才能到一个点

```c++
#include<bits/stdc++.h>
using namespace std;

struct Edge
{
    int to,nxt;
}edge[100000];
int head[100000],tot;
void addedge(int x,int y)
{
    edge[++tot].to=y;edge[tot].nxt=head[x];head[x]=tot;
}
int cnt=1;
int aim=0;
void solve(int rt,int n)
{
    if(n<=1)
    {
        if(!aim)aim=rt;
        return ;
    }
    ++cnt;
    addedge(rt,cnt);
    solve(cnt,n-1);
    ++cnt;
    addedge(rt,cnt);
    solve(cnt,n-2);
}

int main()
{
    //freopen("in.txt","w",stdout);
    solve(1,22);
    printf("%d %d\n",cnt,aim);
    for(int i=1;i<=cnt;i++)
    {
        for(int j=head[i];j;j=edge[j].nxt)
        {
            printf("%d %d\n",i,edge[j].to);
        }
    }
    return 0;
}

```

