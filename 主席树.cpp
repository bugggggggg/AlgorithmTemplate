# 主席树

```c
#include<cstdio>
#include<algorithm>
#include<set>
#include<iterator>
#include<map>
using namespace std;
const int maxn=200010;
int n,m;
struct Node
{
	int id,w;
	int lc,rc;
}node[maxn*20];
int tot;
int a[maxn],b[maxn];
set<int>st;
set<int>::iterator it;
map<int,int>mp;
int root[maxn];
void build(int&p,int l,int r)
{
	p=++tot;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(node[p].lc,l,mid);
	build(node[p].rc,mid+1,r);
}
void insert(int&p,int q,int l,int r,int x)
{
	p=++tot;
	node[p]=node[q];
	//node[p].w=node[q].w;node[p].lc=node[q].lc;node[p].rc=node[q].rc;
	node[p].w++;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(x<=mid)insert(node[p].lc,node[q].lc,l,mid,x);
	else insert(node[p].rc,node[q].rc,mid+1,r,x);
}
int query(int x,int y,int l,int r,int k)
{
	if(l==r)return b[l];
	int mid=(l+r)>>1;
	int tmp=node[node[x].lc].w-node[node[y].lc].w;
	if(tmp>=k)
		return query(node[x].lc,node[y].lc,l,mid,k);
	else 
		return query(node[x].rc,node[y].rc,mid+1,r,k-tmp);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),st.insert(a[i]);
	int p=0;
	for(it=st.begin();it!=st.end();++it)
	{
		b[++p]=(*it);mp[(*it)]=p;
	}
	for(int i=1;i<=n;i++)a[i]=mp[a[i]];
	//printf("$");
	build(root[0],1,p);
	//printf("#");
	for(int i=1;i<=n;i++)insert(root[i],root[i-1],1,p,a[i]);
	//printf("@");
	int l,r,k;
	while(m--)
	{
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",query(root[r],root[l-1],1,p,k));
	}
	return 0;
}
```

