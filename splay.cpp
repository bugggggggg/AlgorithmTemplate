const int maxn=1100066;


struct Splay
{
	int rt,tot,fa[maxn],ch[maxn][2],val[maxn],cnt[maxn],siz[maxn];

	void maintain(int x){siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+cnt[x];}

	bool get(int x){return x==ch[fa[x]][1];}

	void clear(int x)
	{
		ch[x][0]=ch[x][1]=fa[x]=val[x]=siz[x]=cnt[x]=0;
	}

	void pushdown(int x)
	{
		// if(x&&)
		// {

		// }
	}

	void rotate(int x)
	{
		int y=fa[x],z=fa[y];

		//pushdown(y);
		//pushdown(x);

		//先向下传标记再计算chk。
		int chk=get(x);
		ch[y][chk]=ch[x][chk^1];
		if(ch[x][chk^1])fa[ch[x][chk^1]]=y;
		ch[x][chk^1]=y;
		fa[y]=x;
		fa[x]=z;
		if(z)ch[z][y==ch[z][1]]=x;
		maintain(y);
		maintain(x);
	}

	void splay(int x,int S=0)
	{
		for(int f=fa[x];f!=S;f=fa[x])
		{
			if(fa[f]!=S)rotate(get(x)==get(f)?f:x);
			rotate(x);
		}
		if(!S)rt=x;
	}

	void insert(int k)
	{
		if(!rt)
		{
			val[++tot]=k;
			cnt[tot]++;
			rt=tot;
			maintain(rt);
			return ;
		}
		int cur=rt,f=0;
		while(1)
		{
			//pushdown(cur);

			if(val[cur]==k)
			{
				cnt[cur]++;
				maintain(cur);
				maintain(f);
				splay(cur);
				break;
			}
			f=cur;
			cur=ch[cur][val[cur]<k];
			if(!cur)
			{
				val[++tot]=k;cnt[tot]++;fa[tot]=f;
				ch[f][val[f]<k]=tot;
				maintain(tot);maintain(f);
				splay(tot);
				break;
			}
		}
	}

	int rk(int k)
	{
		int res=0,cur=rt;
		while(cur)
		{
			//pushdown(cur);

			if(k<val[cur])cur=ch[cur][0];
			else 
			{
				res+=siz[ch[cur][0]];
				if(k==val[cur])
				{
					splay(cur);
					return res+1;
				}
				res+=cnt[cur];
				cur=ch[cur][1];
			}
		}
		return res+1;
	}//k的排名（小于k的个数加1）


	int kth(int k)
	{
		int cur=rt;
		while(1)
		{
			//pushdown(cur);

			if(ch[cur][0]&&k<=siz[ch[cur][0]])cur=ch[cur][0];
			else
			{
				k-=(cnt[cur]+siz[ch[cur][0]]);
				if(k<=0)
				{
					splay(cur);
					return cur;
				}
				cur=ch[cur][1];
			}
		}
	}//值排名为k的节点编号
	//节点的父亲及父亲左儿子子树和为k-1。

	int pre()
	{
		//pushdown(rt);

		int cur=ch[rt][0];
		if(!cur)return 0;//不存在
		while(ch[cur][1])
		{
			//pushdown(cur);
			cur=ch[cur][1];
		}
		splay(cur);
		return cur;
	}//返回根节点的值的前驱的节点编号（是严格小于的）

	int nxt()
	{
		//pushdown(rt);
		int cur=ch[rt][1];
		if(!cur)return 0;
		while(ch[cur][0])
		{
			//pushdown(cur);
			cur=ch[cur][0];
		}
		splay(cur);
		return cur;
	}

	void del(int k)
	{
		rk(k);
		if(cnt[rt]>1)
		{
			cnt[rt]--;
			maintain(rt);
			return ;
		}
		if(!ch[rt][0]&&!ch[rt][1])
		{
			clear(rt);
			rt=0;
			return ;
		}
		if(!ch[rt][0])
		{
			int cur=rt;
			rt=ch[rt][1];
			fa[rt]=0;
			clear(cur);
			return ;
		}
		if(!ch[rt][1])
		{
			int cur=rt;
			rt=ch[rt][0];
			fa[rt]=0;
			clear(cur);
			return ;
		}
		int cur=rt;
		int x=pre();////////////////////////
		fa[ch[cur][1]]=x;
		ch[x][1]=ch[cur][1];
		clear(cur);
		maintain(rt);

	}
}splay;
