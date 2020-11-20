
//bfs O(n^3) n=max(cntx,cnty);
namespace KM
{
	const int inf=1e9+10;
	const int maxn=306;
	int mp[maxn][maxn],link_x[maxn],link_y[maxn],n;
	bool visx[maxn],visy[maxn];
	int q[maxn<<1],top,tail,pre[maxn];
	int hx[maxn],hy[maxn],slk[maxn];

	int check(int i)
	{
		visx[i]=true;
		if(link_x[i])
		{
			q[tail++]=link_x[i];
			return visy[link_x[i]]=true;
		}
		while(i)
		{
			link_x[i]=pre[i];
			swap(i,link_y[pre[i]]);
		}
		return false;
	}

	void bfs(int S)
	{
		for(int i=1;i<=n;i++)slk[i]=inf,visx[i]=visy[i]=false;
		top=0;tail=1;
		q[0]=S;visy[S]=true;
		while(true)
		{
			int d;
			while(top<tail)
			{
				for(int i=1,j=q[top++];i<=n;i++)
				{
					if(!visx[i]&&slk[i]>=(d=hx[i]+hy[j]-mp[i][j]))
					{
						pre[i]=j;
						if(d)slk[i]=d;
						else if(!check(i))return;
					}
				}
			}
			d=inf;
			for(int i=1;i<=n;i++)
				if(!visx[i])d=min(d,slk[i]);
			for(int i=1;i<=n;i++)
			{
				if(visx[i])hx[i]+=d;
				else slk[i]-=d;
				if(visy[i])hy[i]-=d;
			}
			for(int i=1;i<=n;i++)
				if(!visx[i]&&!slk[i]&&!check(i))return;
		}
	}

	void init()
	{
		for(int i=1;i<=n;i++)
		{
			link_x[i]=link_y[i]=0;hy[i]=0;
			visy[i]=false;pre[i]=0;
		}
		for(int i=1;i<=n;i++)
		{
			hx[i]=mp[i][1];
			for(int j=2;j<=n;j++)
				hx[i]=max(hx[i],mp[i][j]);
		}
	}
	int solve()
	{
		init();
		int ret=0;
		for(int i=1;i<=n;i++)bfs(i);
		for(int i=1;i<=n;i++)ret+=mp[i][link_x[i]];
		return ret;
	}
}


//dfs O(n^4) ng去匹配nb，要保证ng<=nb。
namespace KM
{
	const int inf=1e9+10;
	const int maxn=406;
	int love[maxn][maxn],ex_girl[maxn],ex_boy[maxn];
	bool vis_girl[maxn],vis_boy[maxn];
	int match[maxn],slack[maxn];
	int ng,nb;

	bool dfs(int x)
	{
		vis_girl[x]=true;
		for(int y=1;y<=nb;y++)
		{
			if(vis_boy[y])continue;
			int gap=ex_girl[x]+ex_boy[y]-love[x][y];
			if(!gap)
			{
				vis_boy[y]=true;
				if(!match[y]||dfs(match[y]))
				{
					match[y]=x;return true;
				}
			}
			else slack[y]=min(slack[y],gap);
		}return false;
	}

	ll KM()
	{
		for(int i=1;i<=nb;i++)
			match[i]=ex_boy[i]=0;
		
		for(int i=1;i<=ng;i++)
		{
			ex_girl[i]=love[i][1];
			for(int j=2;j<=nb;j++)
				ex_girl[i]=max(ex_girl[i],love[i][j]);
		}

		for(int i=1;i<=ng;i++)
		{
			fill(slack+1,slack+nb+1,inf);
			while(1)
			{
				memset(vis_girl,0,sizeof(vis_girl));
				memset(vis_boy,0,sizeof(vis_boy));
				if(dfs(i))break;
				int d=inf;
				for(int j=1;j<=nb;j++)
					if(!vis_boy[j])d=min(d,slack[j]);
				for(int j=1;j<=ng;j++)
				{
					if(vis_girl[j])ex_girl[j]-=d;
				}
				for(int j=1;j<=nb;j++)
				{
					if(vis_boy[j])ex_boy[j]+=d;
					else slack[j]-=d;
				}
			}
		}
		ll ret=0;
		for(int i=1;i<=nb;i++)ret+=love[match[i]][i];
		return ret;
	}
}
