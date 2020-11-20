# 逆序对

```c
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=50000;
long long cnt;
int a[maxn],tmp[maxn];
void merge(int l,int r)
{
	if(l==r)return ;
	int mid=(l+r)/2;
	merge(l,mid);
	merge(mid+1,r);
	int i=l,j=mid+1;
	for(int k=l;k<=r;k++)
	{
		if(j>r||(i<=mid&&a[i]<a[j]))tmp[k]=a[i++];
		else {tmp[k]=a[j++];cnt+=(long long)(mid-i+1);}
	}
	for(int k=l;k<=r;k++)
		a[k]=tmp[k];
}
int main()
{
	int n;
	while(scanf("%d",&n)&&n)
	{
		cnt=0;
		for(int i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
		}
		merge(0,n-1);
		printf("%lld\n",cnt);
	}
	return 0;
}

```

