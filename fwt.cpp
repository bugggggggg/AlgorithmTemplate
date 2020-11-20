

//N是范围[0,N),
//正着opt取1，反着取-1;
int N;
void FWT_or(int *f,int opt)
{
    for(int o=2,k=1;o<=N;o<<=1,k<<=1)
        for(int i=0;i<N;i+=o)
            for(int j=0;j<k;j++)
                f[i+j+k]=(f[i+j+k]+opt*f[i+j]+mod)%mod;
}
void FWT_and(int *f,int opt)
{
    for(int o=2,k=1;o<=N;o<<=1,k<<=1)
        for(int i=0;i<N;i+=o)
            for(int j=0;j<k;j++)
                f[i+j]=(f[i+j]+mod+f[i+j+k]*opt)%mod;
}

ll inv2=powmod(2,mod-2);
void FWT_xor(int *f,int opt)
{
    for(int o=2,k=1;o<=N;o<<=1,k<<=1)
        for(int i=0;i<N;i+=o)
            for(int j=0;j<k;j++)
            {
                f[i+j]=(f[i+j]+f[i+j+k])%mod;
                f[i+j+k]=(f[i+j]+mod+mod-f[i+j+k]-f[i+j+k])%mod;
                if(opt==-1)
                {
                    f[i+j]=1ll*f[i+j]*inv2%mod;
                    f[i+j+k]=1ll*f[i+j+k]*inv2%mod;
                }
                
            }
}


FWT_or(a,1);FWT_or(aa,1);
for(int i=0;i<N;i++)a[i]=1ll*a[i]*aa[i]%mod;
FWT_or(a,-1);

FWT_and(b,1);FWT_and(bb,1);
for(int i=0;i<N;i++)b[i]=1ll*b[i]*bb[i]%mod;
FWT_and(b,-1);

FWT_xor(c,1);FWT_xor(cc,1);
for(int i=0;i<N;i++)c[i]=1ll*c[i]*cc[i]%mod;
FWT_xor(c,-1);