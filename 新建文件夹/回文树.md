# 回文树

```c
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=300005;
char s[maxn];
int n;
int fail[maxn],cnt[maxn],len[maxn],tot,last,ch[maxn][26];
inline int newnode(int x)
{
	len[++tot]=x;return tot;
}
int getfail(int x,int n)
{
	while(s[n-len[x]-1]!=s[n])x=fail[x];
	return x;
}
int main()
{
	scanf("%s",s+1);
	s[0]=-1;fail[0]=1;last=0;fail[1]=1;
	len[0]=0;len[1]=-1;tot=1;
	for(int i=1;s[i];++i)
	{
		s[i]-='a';
		int p=getfail(last,i);
		if(!ch[p][s[i]])
		{
			int q=newnode(len[p]+2);
			fail[q]=ch[getfail(fail[p],i)][s[i]];
			ch[p][s[i]]=q;
		}
		++cnt[last=ch[p][s[i]]];
	}
	long long ans=0;
	for(int i=tot;i;--i)
	{
		cnt[fail[i]]+=cnt[i];
		ans=max(ans,1ll*cnt[i]*len[i]);
	}
	printf("%lld",ans);
	return 0;
}
```

