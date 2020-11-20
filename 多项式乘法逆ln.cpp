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
const ll mod=998244353;
//mt19937_64 mrand(random_device{}()); 
//int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) {return b?gcd(b,a%b):a;}

const db PI=acos(-1.0);
const int N=1000006;

struct Complex
{
	db rl,im;
	Complex(){rl=im=0;}
	Complex(db x,db y){rl=x,im=y;}
	Complex conj(){return Complex(rl,-im);}
	Complex operator+(Complex b){return Complex(rl+b.rl,im+b.im);}
	Complex operator-(Complex b){return Complex(rl-b.rl,im-b.im);}
	Complex operator*(Complex b){return Complex(rl*b.rl-im*b.im,rl*b.im+im*b.rl);}
}w[N],s1[N],s2[N],s3[N],s4[N],s5[N],s6[N];

int n,rev[N],f[N];

void fft(Complex*P,int len)
{
	for(int i=0;i<len;i++)if(i<rev[i])swap(P[i],P[rev[i]]);
	for(int i=1;i<len;i<<=1)
		for(int p=i<<1,j=0;j<len;j+=p)
			for(int k=0;k<i;k++)
			{
				Complex x=P[j+k],y=w[len/i*k]*P[j+k+i];
				P[j+k]=x+y;P[j+k+i]=x-y;
			}
}


void mul(int*a,int*b,int*c,int len)
{
	int len2=len;len<<=1;
	int l=0;while((1<<l)<len)++l;--l;
	for(int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
	for(int i=0;i<len;i++)w[i]=Complex(cos(PI*i/len),sin(PI*i/len));
	for(int i=0;i<len2;i++)s1[i]=(Complex){db(a[i]&32767),db(a[i]>>15)};
	for(int i=0;i<len2;i++)s2[i]=(Complex){db(b[i]&32767),db(b[i]>>15)};
	for(int i=len2;i<len;i++)s1[i]=s2[i]=Complex(0,0);
	fft(s1,len),fft(s2,len);
	for(int i=0;i<len;i++)
	{
		int j=(len-i)&(len-1);
		Complex da=(s1[i]+s1[j].conj())*Complex(0.5,0);
		Complex db=(s1[i]-s1[j].conj())*Complex(0,-0.5);
		Complex dc=(s2[i]+s2[j].conj())*Complex(0.5,0);
		Complex dd=(s2[i]-s2[j].conj())*Complex(0,-0.5);
		s3[j]=da*dc;s4[j]=da*dd;s5[j]=db*dc;s6[j]=db*dd;
	}
	for(int i=0;i<len;i++)s1[i]=s3[i]+s4[i]*Complex(0,1);
	for(int i=0;i<len;i++)s2[i]=s5[i]+s6[i]*Complex(0,1);
	fft(s1,len);fft(s2,len);
	for(int i=0;i<len2;i++)
	{
		int da=(ll)(s1[i].rl/len+0.5)%mod;
		int db=(ll)(s1[i].im/len+0.5)%mod;
		int dc=(ll)(s2[i].rl/len+0.5)%mod;
		int dd=(ll)(s2[i].im/len+0.5)%mod;
		c[i]=(da+((ll)(db+dc)<<15)+((ll)dd<<30))%mod;
	}
	for(int i=len2;i<len;i++)c[i]=0;
}

int tmp[N];
void getinv(int *a,int *b,int len)
{
	if(len==1){b[0]=powmod(a[0],mod-2);return;}
	getinv(a,b,len>>1);mul(a,b,tmp,len);
	for(int i=0;i<len;i++)tmp[i]=mod-tmp[i];tmp[0]+=2;
	mul(tmp,b,b,len);
}
int d[N],inv[N];
void getln(int *a,int*b,int len)
{
	for(int i=1;i<len;i++)d[i-1]=1ll*i*a[i]%mod;
	getinv(a,inv,len);mul(d,inv,b,len);
	for(int i=len-1;i;i--)b[i]=1ll*b[i-1]*powmod(i,mod-2)%mod;
}


int main()
{
	int n;
	scanf("%d",&n);
	//长度要是大于n的2的次幂
	int len=1;while(len<=n)len<<=1;


	for(int i=1;i<=n;i++)scanf("%d",&f[i]);
	f[0]=1;
	getln(f,f,len);


	return 0;
}

