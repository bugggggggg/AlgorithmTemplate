int nextt[50066];

void kmp_pre(int x[],int m,int nextt[])
{
	int i,j;
	j=-1;nextt[0]=-1;
	i=0;
	while(i<m)
	{
		while(j!=-1&&x[i]!=x[j])j=nextt[j];
		nextt[++i]=++j;
	}
}



void KMP_Count(int x[],int m,int y[],int n)
{//x 是模式串，y 是主串
	int i,j;
	int ans=0;
	kmp_pre(x,m,nextt);
	i=j=0;
	while(i<n)
	{
		while(j!=-1&&y[i]!=x[j])j=nextt[j];
		i++;j++;
		if(j>=m)
		{
			ans++;
			j=nextt[j];
		}
	}
}