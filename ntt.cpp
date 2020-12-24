#include<cstdio>
#include<algorithm>
#include<map>
#include<cstring>
#include<vector>
#include<iterator>
//using namespace std;
#define poly std::vector<int>
#define ll long long
const int mod=998244353;
int mul(const int&a,const int&b){return 1ll*a*b%mod;}
int add(int a,const int&b){a+=b;return (a>=mod)?a-mod:a;}
int sub(int a,const int&b){a-=b;return (a<0)?a+mod:a;}
int qpow(int a,int b)
{
    int ans=1;
    while(b){if(b&1)ans=mul(ans,a);a=mul(a,a);b>>=1;}
    return ans;
}
int lim,R[1000006],t1[1000006],t2[1000006],w[1000006],a[200006];
int n;
void NTT(int*a)
{
    for(int i=0;i<lim;i++)if(i<R[i])std::swap(a[i],a[R[i]]);
    for(int i=1;i<lim;i<<=1)
        for(int j=0;j<lim;j+=(i<<1))
            for(int k=0;k<i;k++)
            {
                const int tmp=mul(a[i+j+k],w[i+k]);
                a[i+j+k]=sub(a[j+k],tmp);
                a[j+k]=add(a[j+k],tmp);
            }
}
poly operator*(poly a,poly b)
{
    int siz=(int)a.size()+(int)b.size()-1;
    lim=1;
    while(lim<=siz)lim<<=1;
    for(int i=1;i<lim;i++)R[i]=(R[i>>1]>>1)|((i&1)?lim>>1:0);
    memset(t1,0,(lim+1)<<2);
    memset(t2,0,(lim+1)<<2);
    for(int i=(int)a.size()-1;~i;--i)t1[i]=a[i];
    for(int i=(int)b.size()-1;~i;--i)t2[i]=b[i];
    NTT(t1);NTT(t2);
    for(int i=0;i<lim;i++)t1[i]=mul(t1[i],t2[i]);
    NTT(t1);
    std::reverse(t1+1,t1+lim);
    a.resize(siz);
    int inv=qpow(lim,mod-2);
    for(int i=0;i<siz;i++)a[i]=mul(t1[i],inv);
    return a;
}
poly solve(int l,int r)
{
    if(l==r)return poly(a[l]+1,1);
    int mid=(l+r)>>1;
    return solve(l,mid)*solve(mid+1,r);
}//分治NTT
std::map<int,int>Map;
int main()
{
    scanf("%d",&n);
    {
    	for(int i=1;i<((n+1)<<2);i<<=1)
        {
            int wn=qpow(3,(mod-1)/(i<<1));w[i]=1;
            for(int j=1;j<i;j++)w[i+j]=mul(w[i+j-1],wn);
        }//预处理，这个3是998244353的原根
	}
    for(int i=1,x;i<=n;i++)scanf("%d",&x),Map[x]++;
    int tot=0;
    for(std::map<int,int>::iterator it=Map.begin();it!=Map.end();++it)a[++tot]=it->second;
    n>>=1;
    printf("%d",solve(1,tot)[n]);
    return 0;
}
