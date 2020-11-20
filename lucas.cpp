#include<cstdio>
#include<algorithm>
using namespace std;
#define ll long long 
const int maxn=200006;
ll n,m,p;
ll fac[maxn];
ll qpow(ll a,ll n,ll p)
{
	ll ret=1;
	while(n)
	{
		if(n&1)ret=ret*a%p;
		a=a*a%p;
		n>>=1;
	}return ret;
}
ll C(ll n,ll m,ll p)
{
	if(m>n)return 0;
	return fac[n]*qpow(fac[m],p-2,p)%p*qpow(fac[n-m],p-2,p)%p;
}
ll lucas(ll n,ll m)
{
	if(!m)return 1;
	return C(n%p,m%p,p)*lucas(n/p,m/p)%p;
}
int main()
{
	int _;
	for(scanf("%d",&_);_;_--)
	{
		scanf("%I64d%I64d%I64d",&n,&m,&p);
		fac[0]=1;
		for(int i=1;i<=p;i++)fac[i]=fac[i-1]*(ll)i%p;
		printf("%I64d\n",lucas(n+m,m));
	}
	return 0;
}