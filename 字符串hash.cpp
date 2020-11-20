# 字符串hash

```c
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long//模2的64次，相当于自动溢出
const int maxn=10000;
const ull P=131;//把字符串看成P进制，P一般取131，13331
int main()
{
    ull f[maxn],p[maxn];
    char str[maxn];
    scanf("%s",str+1);
    p[0]=1;f[0]=0;
    int len=strlen(str+1);
    for(int i=1;i<=len;i++)
    {
        /*
        	预处理前缀hash
        */
        f[i]=f[i-1]*P+str[i]-'a'+1;//高位在str小的地方
        p[i]=p[i-1]*P;//P的次方
    }
    int m;
    scanf("%d",&m);
    while(m--)
    {
        int l1,r1,l2,r2;
        scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
        if(f[r1]-f[l1-1]*p[r1-l1+1]//l1到r1的字符串hash值
           ==f[r2]-f[l2-1]*p[r2-l2+1])
            puts("Yes");
        else puts("No");
    }
    return 0;
}

```

