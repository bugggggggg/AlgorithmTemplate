# ST

```c
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=5000;
int main()
{
	int N,Q;
	scanf("%d%d",&N,&Q);
	int a[maxn],f[maxn][20],g[maxn][20];
	for(int i=1;i<=N;i++)
	{
		scanf("%d",&a[i]);
		f[i][0]=a[i];g[i][0]=a[i];
	}
    //预处理恰好小于n的2的次幂为index[n]；
	int index[maxn],l=-1,two=1;
	index[0]=index[1]=0;
	for(int i=2;i<maxn;)
	{
		if(~l)two=two<<1;	
		l++;
		for(;i<maxn&&i<=(two<<1);i++)
			index[i]=l;
	}
    
	for(int i=1;i<=index[N];i++)
	{
		for(int j=1;j<=N-(1<<i)+1;j++)
		{
			f[j][i]=max(f[j][i-1],f[j+(1<<(i-1))][i-1]);
			g[j][i]=min(g[j][i-1],g[j+(1<<(i-1))][i-1]);
		}
	}
    
	while(Q--)
	{
		int p,q;
		scanf("%d%d",&p,&q);
		//if(p>q)swap(p,q);
		int ind=index[q-p+1];
		int mn1=max(f[p][ind],f[q-(1<<ind)+1][ind]);
		int mn2=min(g[p][ind],g[q-(1<<ind)+1][ind]);
		printf("%d\n",mn1-mn2);
	}
	return 0;
}
```

