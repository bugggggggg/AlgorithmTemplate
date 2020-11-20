# 虚树

```c
int dfn[maxn],id;
int sta[maxn],top;
void dfs(int x,int fa)
{
	dfn[x]=++id;
	for(int i=head[x];i;i=edge[i].nxt)
		if(edge[i].to!=fa)dfs(edge[i].to,x);
}
bool cmp(int x,int y)
{
	return dfn[x]<dfn[y];
}
int build(int n)
{
	top=0;tot=0;
	sort(a+1,a+n+1,cmp);//按dfs序排序
	sta[++top]=a[1];//栈中维护一条从a[1]到sta[top]的链
	for(int i=2;i<=n;i++)
	{
		int x=lca(a[i],sta[top]);
		while(top>1&&d[sta[top-1]]>d[x])
			addedge(sta[top-1],sta[top]),addedge(sta[top],sta[top-1]),top--;
		if(top&&d[x]<d[sta[top]])
			addedge(x,sta[top]),addedge(sta[top],x),top--;
		if(!top||sta[top]!=x)sta[++top]=x;
		if(sta[top]!=a[i])sta[++top]=a[i];
	}
	while(top>1)addedge(sta[top-1],sta[top]),addedge(sta[top],sta[top-1]),top--;
	/*…………遍历虚树找答案…………*/
	
}
```

