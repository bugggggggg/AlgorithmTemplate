# 快速乘

```c
//O(1)快速乘
inline LL quick_mul(LL x,LL y,LL MOD){
    x=x%MOD,y=y%MOD;
    return ((x*y-(LL)(((long double)x*y+0.5)/MOD)*MOD)%MOD+MOD)%MOD;
}

//O(log)快速乘
inline LL quick_mul(LL a,LL n,LL m)
{
    LL ans=0;
    while(n)
    {
        if(n&1) ans=(ans+a)%m;
        a=(a<<1)%m;
        n>>=1;
    }
    return ans;
}
```

