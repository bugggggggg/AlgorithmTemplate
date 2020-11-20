# trie

```c
#include<bits/stdc++.h>
using namespace std;
const int maxn=10000;
struct Node
{
    Node*next[26];
    int cnt;
    Node()
    {
        for(int i=0;i<26;i++)next[i]=NULL;
        cnt=0;
    }
};
Node*root;
int N,M;
void Insert(string a)
{
    Node*p=root;
    int len=a.length(),tmp;
    for(int i=0;i<len;i++)
    {
        tmp=a[i]-'a';
        if(p->next[tmp]==NULL)p->next[tmp]=new Node();
        p=p->next[tmp];
    }
    p->cnt++;
}
int query(string a)
{
    int ret=0,tmp,len=a.length();
    Node *p=root;
    for(int i=0;i<len;i++)
    {
        tmp=a[i]-'a';
        if(p->next[tmp]==NULL)return ret;
        p=p->next[tmp];
        ret+=p->cnt;
    }
    return ret;
}
int main()
{
    scanf("%d%d",&N,&M);
    getchar();
    root=new Node();
    string str;
    while(N--)
    {
        cin>>str;
        Insert(str);
    }
    while(M--)
    {
        cin>>str;
        printf("%d\n",query(str));
    }
    return 0;
}
```

