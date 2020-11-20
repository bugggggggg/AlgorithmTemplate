# 矩阵快速幂

```c
#include<cstdio>
#include<cstring>
using namespace std;
const int N=2;
const int mod=10000;
int tmp[N][N];
void multi(int a[][N],int b[][N],int n)//a*b,返回值在a
{
	memset(tmp,0,sizeof(tmp));
	for(int i=0;i<n;i++)
		for(int k=0;k<n;k++)
			if(a[i][k]!=0)
				for(int j=0;j<n;j++)
					tmp[i][j]=(tmp[i][j]+a[i][k]*b[k][j])%mod;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			a[i][j]=tmp[i][j]; 
}
int res[N][N];
void Pow(int a[][N],int n)
{
	memset(res,0,sizeof(res));
	for(int i=0;i<2;i++)res[i][i]=1;
	while(n)
	{
		if(n&1)multi(res,a,2);
		multi(a,a,2);
		n=n>>1;
	}
}
int main()
{
	int n;
	while(scanf("%d",&n)&&(~n))
	{
		if(!n)
		{
			printf("0\n");
			continue;
		}
		int a[N][N]={1,1,1,0};
		Pow(a,n-1); 
		printf("%d\n",res[0][0]);
	}
	return 0;
}
```

