/*
	快速求积性函数F[x]前缀和，F[P^K]，P属于质数要能快速求值。

	v[i]是i的最小质因数，p[j]是第j小的质数。



	先求g(n,j)=ΣF[i][i是质数 或者 v[i]>p[j] ]
	1.  p[j]*p[j]>n  g(n,j)=g(n,j-1)
	2.  p[j]*p[j]<=n  g(n,j)=g(n,j-1)-F[p[j]]*( g(n/p[j],j-1)-g(p[j]-1,j-1) )
	其中g(p[j],j)=ΣF[p[j]]
	g在过程中可以压缩第二维；
	g的初值：
	g(n,0)=ΣF[i],这里把i都当作质数来做（比如f[p]=p-1,那么F[i]都当作i-1来算）
	这样做导致g的中间值是虚假的，但是因为最后只要质数的值，而非质数的值会消去，
	所以没问题。

	g(n,j)可以理解成在埃式筛法过程中，筛去了p[1]到P[j]后，剩下的位置的F的和。


	然后求S(n,j)=ΣF[i][v[i]>=p[j]]
	S(n,j)=g(n,|P|)-Σ(i:1 to j-1)F[P[i]] + ΣΣ(F[p[k]^e]*S(n/(P[k]^e),k+1)+F(P[k]^(e+1)))
											k: j+1----tot; e:1-----
	即枚举最小质因子展开。


	求的过程中,S和g的第一维只会取到2sqrt(n)个值：
	根据根号分块，n/i 只有2*sqrt(n)个取值。
	所以可以提前处理出来。



*/
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef long long ll;
typedef double db;
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef pair<long long,int> PLI;
const ll mod=1000000007;
//mt19937_64 mrand(random_device{}()); 
//int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) {return b?gcd(b,a%b):a;}

ll id1[200066],id2[200066];
ll w[200066];
ll g[200066],h[200066];//去掉取模，g[id2[1]]是1--n的质数和，h[id2[1]]是1---n的质数个数
ll SQR;
ll n;

int tot,prime[200066];
ll sp[200066];
int v[200066];
void init(int n)
{
	for(int i=2;i<=n;i++)
	{
		if(!v[i])
		{
			v[i]=i;prime[++tot]=i;sp[tot]=(sp[tot-1]+i)%mod;
		}
		for(int j=1;j<=tot;j++)
		{
			if(prime[j]>v[i]||i>n/prime[j])break;
			v[i*prime[j]]=prime[j];
		}
	}
}

ll inv2=powmod(2,mod-2);

ll S(ll x,int y)
{
	if(x<=1||prime[y]>x)return 0;
	int k=(x<=SQR)?id1[x]:id2[n/x];
	ll ret=g[k]-sp[y-1]-(h[k]-y+1);
	if(y==1)ret+=2;
	ret=(ret%mod+mod)%mod;
	for(int i=y;i<=tot&&1ll*prime[i]*prime[i]<=x;i++)
	{
		ll s=prime[i];
		ll t=s*s;
		for(int e=1;t<=x;s=t,t*=prime[i],e++)
		{
			
			ret=(ret+1ll*(prime[i]^e)*S(x/s,i+1)+(prime[i]^(e+1)))%mod;
		}
	}return ret;
}

int main()
{
	scanf("%lld",&n);SQR=sqrt(n);
	init(SQR);
	//for(int i=1;i<=tot;i++)printf("%d__%lld\n",prime[i],sp[i]);
	//printf("%d\n",tot);
	int p=0;
	for(ll i=1,r;i<=n;i=r+1)
	{
		r=n/(n/i);w[++p]=n/i;
		h[p]=(w[p]-1)%mod;
		g[p]=1ll*(w[p]+1)%mod*(w[p]%mod)%mod*inv2%mod;//这里w[p]很大，要取mod后再乘
		g[p]=(g[p]-1+mod)%mod;
		if(w[p]<=SQR)id1[w[p]]=p;
		else id2[r]=p;
	}
	
	for(int i=1;i<=tot;i++)
	{
		for(int j=1;j<=p&&1ll*prime[i]*prime[i]<=w[j];j++)
		{
			int k=(w[j]/prime[i]<=SQR)?id1[w[j]/prime[i]]:id2[n/(w[j]/prime[i])];
			g[j]=(g[j]+mod-1ll*(g[k]-sp[i-1]+mod)%mod*prime[i]%mod)%mod;
			h[j]=(h[j]+mod-(h[k]-i+1))%mod;
		}
	}
	ll ans=S(n,1)+1;
	ans%=mod;
	printf("%lld\n",ans);
	return 0;
}