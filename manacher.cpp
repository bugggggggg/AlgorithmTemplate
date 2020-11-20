#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=20000;
int main()
{
    char str[maxn];
    int icase=0;
    while(scanf("%s",str)&&str[0]!='E')
    {
        int len=strlen(str);
        str[len*2+1]='#';
        str[len*2+2]='*';
        for(int i=2*len;i>0;i-=2)
        {
            str[i]=str[i/2-1];
            str[i-1]='#';
        }
        str[0]='@';
        int d[maxn],ans=-1,far=0,mid=0;
        for(int i=1;i<=2*len;i++)
        {
            if(i<far)
            {
                int tmp=2*mid-i;
                if(d[tmp]+i-1<far)
                {
                    d[i]=d[tmp];continue;
                }
                else d[i]=far-i+1;
            }
            else d[i]=1;
            while(str[i-d[i]]==str[i+d[i]])d[i]++;
            if(i+d[i]-1>far){far=i+d[i]-1;mid=i;}
            if(i^1)ans=max(ans,d[i]-1);
        }
        printf("Case %d: %d\n",++icase,ans);
    }
    return 0;
}
