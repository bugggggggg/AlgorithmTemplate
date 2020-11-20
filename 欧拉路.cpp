# 欧拉路

判度数，找起点

```c
void dfs(int x)
{
	for(int i='A';i<='z';i++)//用前向星的话可以加当前弧优化
	{
		if(!vis[i][x])continue;
		vis[i][x]=vis[x][i]=0;
		dfs(i);
	}
	ans.push_back((char)x);//后序，神奇。。。。。
}
```

