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
const ll mod=1000000009;
//mt19937_64 mrand(random_device{}()); 
//int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) {return b?gcd(b,a%b):a;}

int ctz(int x){return __builtin_popcount(x);}

int N;
void FWT_or(int *f,int opt)
{
	for(int o=2,k=1;o<=N;o<<=1,k<<=1)
		for(int i=0;i<N;i+=o)
			for(int j=0;j<k;j++)
				f[i+j+k]=(f[i+j+k]+opt*f[i+j]+mod)%mod;
}

int h[21][1100000],f[21][1100000],g[21][1100000];

int main()
{
	int n;
	scanf("%d",&n);
	N=1<<n;
	int x;
	for(int i=0;i<N;i++)
	{
		scanf("%d",&x);
		f[ctz(i)][i]=x;
	}
	for(int i=0;i<N;i++)
	{
		scanf("%d",&x);
		g[ctz(i)][i]=x;
	}
	for(int i=0;i<=n;i++)
	{
		FWT_or(f[i],1);FWT_or(g[i],1);
	}
	for(int i=0;i<=n;i++)//有等号
	{
		for(int j=0;j<=i;j++)
		{
			for(int k=0;k<N;k++)
				h[i][k]=(h[i][k]+1ll*f[j][k]*g[i-j][k])%mod;
		}
	}
	for(int i=0;i<=n;i++)FWT_or(h[i],-1);
	for(int i=0;i<N;i++)printf("%d ",h[ctz(i)][i]);
	puts("");	
	return 0;
}

/*
求h[i]=Σf[j]*g[k]  (j|k=i,j&k=0)

计p[i]为i中1的个数。
则h[i]=Σf[j]*g[k]  (j|k=i,p[j]+p[k]=p[i])
考虑增加一维，h[p[i]][i]=h[i],其余为0
f,g同h扩展，
此时h[p[i]][i]=Σf[p[j]][j]*g[p[k]][k]  (j|k=i,p[j]+p[k]=p[i])

可以先固定第一维，对每一维跑一次fwt，然后根据fwt的可加性，
固定第二位，h[i][k]=Σf[j][k]*g[i-j][k]。
最后h的每一维再跑一次ifwt还原。
h[p[i]][i]就是原本的h[i].

*/