# 杜教筛


	g(1)S(n)=(求和(i:1--n):(f*g)(i))-(求和(i:2--n):g(i)S(n/i))
	S(n)是f的前缀和，
	f*g的前缀和要能快速求。
	这里的*代表迪利克雷卷积，别和乘法弄混了
```c
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
const int maxn=5000000;
bool vis[maxn+5];
int prim[maxn],cnt;
#define LL long long
#define ULL unsigned long long
LL mu[maxn+66],phi[maxn+66];
map<int,LL>ansmu,ansphi;
void init()
{
	mu[1]=phi[1]=1;
	for(int i=2;i<=maxn;++i)
	{
		if(!vis[i])
		{
			prim[++cnt]=i;mu[i]=-1;phi[i]=i-1;
		}
		for(int j=1;j<=cnt&&prim[j]*i<=maxn;++j)
		{
			vis[i*prim[j]]=1;
			if(i%prim[j]==0)
			{
				phi[i*prim[j]]=phi[i]*prim[j];
				break;
			}
			else
			{
				mu[i*prim[j]]=-mu[i];
				phi[i*prim[j]]=phi[i]*phi[prim[j]];
			}
		}
	}
	for(int i=1;i<=maxn;i++)mu[i]+=mu[i-1],phi[i]+=phi[i-1];
}
LL S_phi(int n)
{
	if(n<=maxn)return phi[n];
	if(ansphi[n])return ansphi[n];
	LL ans=0;
	for(int l=2,r;r<2147483647&&l<=n;l=r+1)
	{
		r=n/(n/l);
		ans+=(r-l+1)*S_phi(n/l);
	}
	return ansphi[n]=(ULL)n*(n+1ll)/2ll-ans;
}
LL S_mu(int n)
{
	if(n<=maxn)return mu[n];
	if(ansmu[n])return ansmu[n];
	LL ans=0;
	for(int l=2,r;r<2147483647&&l<=n;l=r+1)
	{
		r=n/(n/l);
		ans+=(r-l+1)*S_mu(n/l);
	} 
	return ansmu[n]=1ll-ans;
}
int main()
{
	int _;
	init();
	for(scanf("%d",&_);_;_--)
	{
		int n;
		scanf("%d",&n);
		printf("%lld %lld\n",S_phi(n),S_mu(n));
	}
	return 0;
}
```

