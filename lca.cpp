# LCA

VI e[100066];
int dp[100066][20],dep[100066];

void dfs(int x,int fa)
{
	dp[x][0]=fa;
	for(int i=1;i<=18;i++)//18要根据点数修改
		dp[x][i]=dp[dp[x][i-1]][i-1];
	dep[x]=dep[fa]+1;
	for(auto y:e[x])
	{
		if(y==fa)continue;
		dfs(y,x);
	}
}

int lca(int x,int y)
{
	if(dep[x]>dep[y])swap(x,y);
	for(int i=18;i>=0;i--)//18要根据点数修改
		if(dep[dp[y][i]]>=dep[x])y=dp[y][i];
	if(x==y)return x;
	for(int i=18;i>=0;i--)//18要根据点数修改
		if(dp[x][i]!=dp[y][i])x=dp[x][i],y=dp[y][i];
	return dp[x][0];
}

