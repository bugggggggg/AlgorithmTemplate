
a[1000][1000],ans[1000];

void Gauss(int n)
{
	for(int i=1;i<=n;i++)
	{
		// int p=i;
		// for(int j=i+1;j<=n;j++)
		// 	if(a[j][i]>a[p][i])p=j;
		// if(p!=i)swap(a[i],a[p]);
		for(int j=n+1;j>i;j--)a[i][j]/=a[i][i];
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
}