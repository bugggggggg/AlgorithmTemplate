
/*
	线段树在递归过程中（修改或查询），可以维护当前
	区间关于总区间补集的相关信息。
	只需要在往左走的时候合并上右子树的信息，
	往右走的时候合并上左子树的信息。
	这里有个注意点：
		往左走的时候可能改变了左子树的值，如果还要继续往右走，
		要预存左子树的原始值。
	例如洛谷p5298。

*/

struct SegmentTree
{
	struct Node
	{
		int w,tag;
	}node[100066<<2];

	void pushup(int p)
	{
		node[p].w=node[p<<1].w+node[p<<1|1].w;
	}

	void pushdown(int p,int l,int r)
	{
		if(node[p].tag!=-1)
		{
			int mid=(l+r)>>1;
			node[p<<1].w=node[p].tag*(mid-l+1);
			node[p<<1].tag=node[p].tag;
			node[p<<1|1].w=node[p].tag*(r-mid);
			node[p<<1|1].tag=node[p].tag;
			node[p].tag=-1;
		}
	}

	void build(int p,int l,int r)
	{
		node[p].tag=-1;
		if(l==r)
		{
			node[p].w=b[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(p<<1,l,mid);
		build(p<<1|1,mid+1,r);
		pushup(p);
	}

	void update(int p,int l,int r,int ql,int qr,int w)
	{
		if(ql<=l&&r<=qr)
		{
			node[p].w=w*(r-l+1);
			node[p].tag=w;
			return ;
		}
		pushdown(p,l,r);
		int mid=(l+r)>>1;
		if(ql<=mid)update(p<<1,l,mid,ql,qr,w);
		if(mid<qr)update(p<<1|1,mid+1,r,ql,qr,w);
		pushup(p);
	}

	int query(int p,int l,int r,int ql,int qr)
	{
		if(ql<=l&&r<=qr)return node[p].w;
		pushdown(p,l,r);
		int mid=(l+r)>>1;
		int ret=0;
		if(ql<=mid)ret=query(p<<1,l,mid,ql,qr);
		if(mid<qr)ret+=query(p<<1|1,mid+1,r,ql,qr);
		return ret;
	}	
}seg;
