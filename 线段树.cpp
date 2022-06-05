struct SegmentTree
{
	#define ls p << 1
	#define rs ls | 1
	int sum[100066 * 16];
	int w[100066 * 16];

	void build(int p, int l, int r) {
		if (l == r) {
			sum[p] = vec[l - 1].first;
			w[p] = 1;
			return ;
		}
		int mid = (l + r) >> 1;
		build(ls, l, mid);
		build(rs, mid + 1, r);
		sum[p] = sum[ls] + sum[rs];
		w[p] = w[ls] + w[rs];
	}

	void pushdown(int p) {

	}

	void upd(int p, int l, int r, int aim) {
		if (l == r) {
			sum[p] = w[p] = 0;
			return ;
		}
		pushdown(p);
		int mid = (l + r) >> 1;
		if (aim <= mid) upd(ls, l, mid, aim);
		else upd(rs, mid + 1, r, aim);
		sum[p] = sum[ls] + sum[rs];
		w[p] = w[ls] + w[rs];
	}

	int ask_sum(int p, int l, int r, int w) {
		if (l == r) {
			if (sum[p] == w) return l + 1;
			return l;
		}
		pushdown(p);
		int mid = (l + r) >> 1;
		if (sum[ls] >= w) return ask_sum(ls, l, mid, w);
		return ask_sum(rs, mid + 1, r, w - sum[ls]);
	}

	int ask_w(int p, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return w[p];
		pushdown(p);
		int mid = (l + r) >> 1;
		int ret = 0;
		if (ql <= mid) ret = ask_w(ls, l, mid, ql, qr);
		if (mid < qr) ret += ask_w(rs, mid + 1, r, ql, qr);
		return ret;
	}
}seg;
