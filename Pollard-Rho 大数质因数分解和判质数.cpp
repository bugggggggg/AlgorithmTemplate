#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int S=8;
ll mult_mod(ll a,ll b,ll c)
{
    ll t=a*b-(ll)((long double)a*b/c+0.5)*c;
    return t<0?t+c:t;
}
ll pow_mod(ll a,ll n,ll mod)
{
    ll ret=1;
    ll tmp=a%mod;
    while(n)
    {
        if(n&1)ret=mult_mod(ret,tmp,mod);
        tmp=mult_mod(tmp,tmp,mod);
        n>>=1;
    }
    return ret;
}
bool check(ll a,ll n,ll x,ll t)
{
    ll ret=pow_mod(a,x,n);
    ll last=ret;
    //printf("ret:%lld\n",ret);
    for(int i=1;i<=t;i++)
    {
        ret=mult_mod(ret,ret,n);
        //printf("ret:%lld\n",ret);
        if(ret==1&&last!=1&&last!=n-1)return true;
        last=ret;
    }
   // printf("!!!!%lld %lld\n",a,ret);
    if(ret!=1)return true;
    return false;
}
bool Miller_Rabin(ll n)
{
    if(n<2)return false;
    //printf("!%lld\n",n);
    if(n==2)return true;
    //printf("@%lld\n",n);
    if((n&1)==0)return false;
    ll x=n-1,t=0;
    while((x&1)==0)x>>=1,t++;
    //printf("t:%lld\n",t);
    srand(time(NULL));
    for(int i=0;i<S;i++)
    {
        ll a=rand()%(n-1)+1;
        //printf("a::%lld\n",a);
        if(check(a,n,x,t))
            return false;
    }
    return true;
}
ll ans;
#define Abs(a) ((a)>0?(a):-(a))
ll gcd(ll a,ll b)
{
    ll t;
    while(b)
    {
        t=a;a=b;b=t%b;
    }
    if(a>=0)return a;
    return -a;
}
ll pollard_rho(ll x)
{
    ll s=0,t=0,c=1ll*rand()%(x-1)+1;
    int stp=0,goal=1;
    ll val=1;
    for(goal=1;;goal<<=1,s=t,val=1)
    {
        for(stp=1;stp<=goal;++stp)
        {
            t=(mult_mod(t,t,x)+c)%x;
            val=mult_mod(val,Abs(t-s),x);
            if(stp%127==0)
            {
                ll d=gcd(val,x);
                if(d>1)return d;
            }
        }
        ll d=gcd(val,x);
        if(d>1)return d;
    }
}
void findfac(ll n,int k)
{
    if(n==1||n<=ans)return;
    if(Miller_Rabin(n))
    {
        ans=max(ans,n);///////////////////////////////////////////////////////////////质数在这里
        return ;
    }
    ll p=n;
    int c=k;
    while(p>=n)p=pollard_rho(n);
    findfac(p,k);
    while(n%p==0)n/=p;
    findfac(n,k);
}
int main()
{
    //for(int i=1;i<=100;i++)printf("%d\n",rand());
    int T;
    scanf("%d",&T);
    ll n;
    while(T--)
    {
        scanf("%lld",&n);
        if(Miller_Rabin(n))printf("Prime\n");
        else
        {
            ans=-1;
            findfac(n,107);
            printf("%lld\n",ans);
        }
        //printf("%d\n",Miller_Rabin(n));
    }
    return 0;
}
