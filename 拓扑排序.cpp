# 拓扑排序

```c
/*
	对有向无环图的topsort
	deg记录每个节点的入度
*/
void topsort()
{
	queue<int>q;
	for(int i=1;i<=n;i++)//初始入度为0的入队
		if(!deg[i])q.push(i);
	while(!q.empty())
	{
		int num=q.front();q.pop();
		a[cnt++]=num;
		for(int i=head[num];~i;i=edge[i].next)//从该点能到的点的入度减1
		{
			int to=edge[i].to;
			deg[to]--;
			if(!deg[to])q.push(to);//入度为0，入队
		}
	}
}
```

对有向无环图进行topsort后，再按拓扑序遍历，可以保证处理该节点前，能到该节点的点都已经被处理了。