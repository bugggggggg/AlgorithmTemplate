struct FHQ
{
	int root[maxn],cnt,lc[maxm],rc[maxm],siz[maxm],val[maxm],fix[maxm];
	void update(int x)
	{
		siz[x]=1+siz[lc[x]]+siz[rc[x]];
	}
	int newnode(int x)
	{
		siz[++cnt]=1;val[cnt]=x;fix[cnt]=rand();return cnt;
	}
	int build(int l,int r,int*p)
	{
		if(l>r)return 0;
		int mid=(l+r)>>1;
		int ret=newnode(p[mid]);
		lc[ret]=build(l,mid-1,p);
		rc[ret]=build(mid+1,r,p);
		return ret;
	}
	int merge(int A,int B)
	{
		if(!A||!B)return A+B;
		if(fix[A]<fix[B])
		{
			rc[A]=merge(rc[A],B);update(A);
			return A;
		}
		else
		{
			lc[B]=merge(A,lc[B]);update(B);
			return B;
		}
	}
	void split_val(int now,int k,int&x,int&y)
	{
		if(!now)x=y=0;
		else
		{
			if(val[now]<=k)x=now,split_val(rc[now],k,rc[now],y);
			else y=now,split_val(lc[now],k,x,lc[now]);
			update(now);
		}
	}
	void split_siz(int now,int k,int&x,int&y)
	{
		if(!now)x=y=0;
		else
		{
			if(siz[lc[now]]+1<=k)
			{
				x=now;split_siz(rc[now],k-siz[lc[now]]-1,rc[now],y);
			}
			else y=now,split_siz(lc[now],k,x,lc[now]);
			update(now);
		}
	}
}st;