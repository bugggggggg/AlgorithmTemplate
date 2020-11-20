# 快读快写

```c
inline void read(int &x)
{
    x=0;
    static int p;p=1;
    static char c;c=getchar();
    while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
    x*=p;   
}
inline void print(long long x)
{
    static int cnt;
    static int a[15];
    cnt=0;
    do
    {
        a[++cnt]=x%10;
        x/=10;
    }while(x);
    for(int i=cnt;i>=1;i--)putchar(a[i]+'0');
    puts("");
}
```

