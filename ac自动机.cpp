namespace AC
{
	const int maxn=100066;
	int ch[maxn][26],fail[maxn],tot;
	int id[maxn],val[maxn];

	void insert(char*s,int len,int idx)
	{
		int u=0;
		for(int i=1;i<=len;i++)
		{
			if(!ch[u][s[i]-'a'])ch[u][s[i]-'a']=++tot;
			u=ch[u][s[i]-'a'];
		}
		id[u]=idx;
	}

	queue<int>q;
	void build()
	{
		for(int i=0;i<26;i++)
			if(ch[0][i])q.push(ch[0][i]);
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=0;i<26;i++)
			{
				if(ch[u][i])
				{
					fail[ch[u][i]]=ch[fail[u]][i];
					q.push(ch[u][i]);
				}
				else ch[u][i]=ch[fail[u]][i];
			}
		}
	}

	int query(char*s,int len)
	{
		int u=0,ret=0;
		for(int i=1;i<=len;i++)
		{
			u=ch[u][s[i]-'a'];
			for(int j=u;j;j=fail[j])
			{
			//	printf("%d__\n",j);
				val[j]++;
			}
		}
		for(int i=0;i<=tot;i++)
		{
			if(id[i])
			{
				ret=max(ret,val[i]);
				//printf("%d %d__\n",i,val[i]);
				di[id[i]]=i;
			}
		}
		return ret;
	}

	void clear()
	{
		for(int i=0;i<=tot;i++)
		{
			id[i]=val[i]=fail[i]=0;
			for(int j=0;j<26;j++)ch[i][j]=0;
		}
		tot=0;
	}
}