# 高斯消元

```c
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=105;
#define db double
int n;
db a[maxn][maxn],ans[maxn];
#define Abs(x) ((x)>0?(x):-(x))
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)scanf("%lf",&a[i][j]);
	for(int i=1;i<=n;i++)
	{
		int p=i;
		for(int j=i+1;j<=n;j++)
			if(a[j][i]>a[p][i])p=j;
		if(Abs(a[p][i])<1e-8)
		{
			puts("No Solution");return 0;
		}
		if(p!=i)swap(a[i],a[p]);
		for(int j=i+1;j<=n+1;j++)a[i][j]/=a[i][i];
		for(int j=i+1;j<=n;j++)
		{
			for(int k=i+1;k<=n+1;k++)
				a[j][k]-=a[j][i]*a[i][k];
		}
	}
	for(int i=n;i>0;i--)
	{
		ans[i]=a[i][n+1];
		for(int j=i+1;j<=n;j++)ans[i]-=a[i][j]*ans[j];
	}
	for(int i=1;i<=n;i++)printf("%.2lf\n",ans[i]);
	return 0;
}
```

