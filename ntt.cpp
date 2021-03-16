


/*
    2,4,p^e,2*p^e有原根(p为质数，e为正整数)
    求n的原根：
    先求phi[n],
    phi[n]的质因子设为p[1],p[2].....
    枚举i:2---p-1,
    如果对任意的j:i^(phi[n]/p[j]) != 1 (mod n)
    那么i就是一个原根。

    因为原根g在模n意义下的最小循环节就是phi[n],
    所以对phi[n]的任意因子k,g^k!=1 (mod n).
    所以只要枚举最大的几个(phi[n]/p[j])就行（因为小的是循环节，它的倍数也是循环节）

*/

//新版，还没套过几个题

#define poly std::vector<int>
#define ll long long
const int mod=998244353;//如果2*mod爆int了，add和sub里加个long long
int mul(const int&a,const int&b){return 1ll*a*b%mod;}
int add(int a,const int&b){a+=b;return (a>=mod)?a-mod:a;}
int sub(int a,const int&b){a-=b;return (a<0)?a+mod:a;}
int qpow(int a,int b)
{
    int ans=1;
    while(b){if(b&1)ans=mul(ans,a);a=mul(a,a);b>>=1;}
    return ans;
}
int lim,R[1000006],t1[1000006],t2[1000006],w[1000006];
void NTT(int*a)
{
    for(int i=0;i<lim;i++)if(i<R[i])std::swap(a[i],a[R[i]]);
    for(int h=2;h<=lim;h<<=1)
    {
        int gn=qpow(3,(mod-1)/h);/////////////////////这里3是mod的原根，记得修改
        for(int j=0;j<lim;j+=h)
        {
            int g=1;
            for(int k=j;k<j+h/2;k++)
            {
                int u=a[k],t=mul(g,a[k+h/2]);
                a[k]=add(u,t);
                a[k+h/2]=sub(u,t);
                g=mul(g,gn);
            }
        }
    }
}
poly operator*(poly a,poly b)
{
    int siz=(int)a.size()+(int)b.size()-1;
    lim=1;
    while(lim<=siz)lim<<=1;
    for(int i=1;i<lim;i++)R[i]=(R[i>>1]>>1)|((i&1)?lim>>1:0);
    memset(t1,0,(lim+1)<<2);//////////////////////////如果开了long long 记得这里要改(‘<<2’ 要改)
    memset(t2,0,(lim+1)<<2);///////////////////////////
    for(int i=(int)a.size()-1;~i;--i)t1[i]=a[i];
    for(int i=(int)b.size()-1;~i;--i)t2[i]=b[i];
    NTT(t1);NTT(t2);
    for(int i=0;i<lim;i++)t1[i]=mul(t1[i],t2[i]);
    NTT(t1);
    //在快速数论逆变换的时候gn不取倒数，直接算然后这里取反
    //因为g^(p-1)=1(mod p),所以直接算i位置的得到的值就是取反后lim-i位置的值。
    std::reverse(t1+1,t1+lim);
    a.resize(siz);
    int inv=qpow(lim,mod-2);
    for(int i=0;i<siz;i++)a[i]=mul(t1[i],inv);
    return a;
}










///////////////////////////////////////////////////////

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
int lim,R[1000006],t1[1000006],t2[1000006],w[1000006];
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
    memset(t1,0,(lim+1)<<2);//////////////////////////如果开了long long 记得这里要改(‘<<2’ 要改)
    memset(t2,0,(lim+1)<<2);///////////////////////////
    for(int i=(int)a.size()-1;~i;--i)t1[i]=a[i];
    for(int i=(int)b.size()-1;~i;--i)t2[i]=b[i];
    NTT(t1);NTT(t2);
    for(int i=0;i<lim;i++)t1[i]=mul(t1[i],t2[i]);
    NTT(t1);
    std::reverse(t1+1,t1+lim);//
    a.resize(siz);
    int inv=qpow(lim,mod-2);
    for(int i=0;i<siz;i++)a[i]=mul(t1[i],inv);
    return a;
}

int main()
{
    scanf("%d",&n);
	for(int i=1;i<((n+1)<<2);i<<=1)
    {
        int wn=qpow(3,(mod-1)/(i<<1));w[i]=1;
        for(int j=1;j<i;j++)w[i+j]=mul(w[i+j-1],wn);
    }//预处理，这个3是998244353的原根

    return 0;
}
