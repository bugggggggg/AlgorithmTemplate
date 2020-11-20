# 后缀数组

```c
#include<bits/stdc++.h>
using namespace std;
const int maxn=10000;
char s[maxn];
/*
	（从小到大）
	rak[i]:从i开始的后缀的排名
	sa[i]:排名为i的后缀开始的位置
	tax:基数排序时的辅助数组，tax[i]表示排名为i的有多少个，算前缀和后表示排名为i的应该排的位置区间
	tp[i]:与sa对应，第二关键字排名为i的后缀开始的位置
	N:字符串数组长度（1开始）
*/
int N,M,rak[maxn],sa[maxn],tax[maxn],tp[maxn];
void Sort()//基数排序
{
    for(int i=0;i<=M;i++)tax[i]=0;
    for(int i=1;i<=N;i++)tax[rak[i]]++;
    for(int i=1;i<=M;i++)tax[i]+=tax[i-1];
    for(int i=N;i>=1;i--)sa[tax[rak[tp[i]]]--]=tp[i];
}
void Suffix()
{
    //当M很大时，第一步可用快排代替（几千都不算大）
   	/*
   	struct Node//定义在全局
	{
        int index,data;
		bool operator <(const Node&a)const
		{
			return data<a.data||(data==a.data&&index<a.index);
		}
	}node[maxn];
	
	sort(node+1,node+1+N);
	node[0].data=-1;
	M=0;
	for(int i=1;i<=N;i++)
	{
		if(node[i].data!=node[i-1].data)
		{
			rak[node[i].index]=++M;	
			sa[i]=node[i].index;
		}
		else
		{
			rak[node[i].index]=M;
			sa[i]=node[i].index;
		}	
	}
   	*/
    M=80;//初始的基数的大小（字符acsii的最大值）
    for(int i=1;i<=N;i++)rak[i]=s[i]-'0'+1,tp[i]=i;
    Sort();
    
    for(int w=1,p=0;p<N;M=p,w<<=1)//当N个后缀的排名均不同时退出
    {
        p=0;//计数
        for(int i=1;i<=w;i++)tp[++p]=N-w+i;//没有第二关键字的放前面（排名小于又第二关键字的/并												//且内部排名不变）
        for(int i=1;i<=N;i++)//从i开始的2w的后缀的第二关键字的排名等于从i+w开始的长w的后缀的排名
            				//即上一次的sa[i+w]
            if(sa[i]>w)tp[++p]=sa[i]-w;
        Sort();
        //两句都行，把上一次的排名拷到暂时没用的tp数组
        swap(tp,rak);//memcpy(tp,rak,sizeof(rak));
        rak[sa[1]]=p=1;
        for(int i=2;i<=N;i++)
            rak[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+w]==tp[sa[i]+w])?p:++p;
        //判断两个长为2*w的后缀是否相等（上一次长w相等，并且从w+1出到2*w也相等）
    }
}
int main()
{
    scanf("%s",s+1);
    N=strlen(s+1);
    Suffix();
    for(int i=1;i<=N;i++)printf("%d ",sa[i]);
    return 0;
}
```



```c
/*
	Height记录排名为i和i-1的后缀的最长公共前缀的长度
	因为从i开始后缀与排在它前一个的后缀的最长公共前缀H[i]：
		满足H[i]>=H[i-1]-1(因此按这个顺序计算可以线性)
*/
int Height[maxn];
void GetHeight()
{
    int k=0;
    for(int i=1;i<=N;i++)
    {
        if(k)k--;
        int j=sa[rak[i]-1];
        while(s[j+k]==s[i+k])k++;
        Height[rak[i]]=k;
    }
}
```

