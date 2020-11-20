#include<cstdio>
#include<bitset>
using namespace std;

bitset<1006>f[1006];
int n,m;
//f[i]表示i的连通情况
int main()
{
    scanf("%d%d",&n,&m);
    int x,y;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        f[x][y]=1;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(f[j][i])f[j]|=f[i];
        }
    }
    return 0;
}
