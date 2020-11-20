

//返回区间最值的下标
//调Max时，小的下标作为x则返回最左的
int mx[20][maxn],Log[maxn];
int Max(int x,int y)//相等返回x的
{
	return h[x]>=h[y]?x:y;
}
int myfind(int l,int r)
{
	int k=Log[r-l+1];
	return Max(mx[k][l],mx[k][r-(1<<k)+1]);
}
void init()
{
    Log[0]=-1;
	for(int i=1;i<=n;i++)Log[i]=Log[i>>1]+1;
	for(int i=1;i<=n;i++)mx[0][i]=i;
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)//从j到j+(1<<i)-1,所以判右端点小于n
			mx[i][j]=Max(mx[i-1][j],mx[i-1][j+(1<<(i-1))]);
}



/*
二维（n*m*logn*logm)

#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=256;
int a[maxn][maxn];
int dp[maxn][maxn][9][9];
int bp[maxn][maxn][9][9];
int n,b,k;
int Log[maxn<<1];
int query(int x,int y,int xx,int yy)
{
	int k1=Log[xx-x+1],k2=Log[yy-y+1];
	return max(max(dp[x][y][k1][k2],dp[xx-(1<<k1)+1][y][k1][k2]),
				max(dp[x][yy-(1<<k2)+1][k1][k2],dp[xx-(1<<k1)+1][yy-(1<<k2)+1][k1][k2]));
}
int query2(int x,int y,int xx,int yy)
{
	int k1=Log[xx-x+1],k2=Log[yy-y+1];
	return min(min(bp[x][y][k1][k2],bp[xx-(1<<k1)+1][y][k1][k2]),
				min(bp[x][yy-(1<<k2)+1][k1][k2],bp[xx-(1<<k1)+1][yy-(1<<k2)+1][k1][k2]));
}
int main()
{
	Log[0]=-1;
	for(int i=1;i<=300;i++)Log[i]=Log[i>>1]+1;
	scanf("%d%d%d",&n,&b,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&a[i][j]);
			dp[i][j][0][0]=a[i][j];
			bp[i][j][0][0]=a[i][j];
		}
	for(int ii=0;ii<=8;ii++)//先行后列
		for(int jj=0;jj<=8;jj++)
			if(ii+jj)
				for(int i=1;i+(1<<ii)-1<=n;i++)
					for(int j=1;j+(1<<jj)-1<=n;j++)
						if(ii)
						{
							dp[i][j][ii][jj]=max(dp[i][j][ii-1][jj],dp[i+(1<<(ii-1))][j][ii-1][jj]);
							bp[i][j][ii][jj]=min(bp[i][j][ii-1][jj],bp[i+(1<<(ii-1))][j][ii-1][jj]);
						}
						else
						{
							dp[i][j][ii][jj]=max(dp[i][j][ii][jj-1],dp[i][j+(1<<(jj-1))][ii][jj-1]);
							bp[i][j][ii][jj]=min(bp[i][j][ii][jj-1],bp[i][j+(1<<(jj-1))][ii][jj-1]);
						}
	
}
*/
/*

二维用单调队列（n*m）

先对行跑单调队列，

再对行的结果对列跑单调队列


#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=256;
int a[maxn][maxn];
int mx[maxn][maxn],mn[maxn][maxn];
int Mx[maxn][maxn],Mn[maxn][maxn];
int n,b,k;
deque<int>qmn,qmx;
int main()
{
	scanf("%d%d%d",&n,&b,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)
	{
		qmx.clear();qmn.clear();
		for(int j=1;j<=n;j++)
		{
			while(!qmx.empty()&&a[i][qmx.back()]<=a[i][j])
				qmx.pop_back();
			qmx.push_back(j);
			while(!qmx.empty()&&qmx.front()<j-b+1)qmx.pop_front();
			mx[i][j]=a[i][qmx.front()];

			while(!qmn.empty()&&a[i][qmn.back()]>=a[i][j])
				qmn.pop_back();
			qmn.push_back(j);
			while(!qmn.empty()&&qmn.front()<j-b+1)qmn.pop_front();
			mn[i][j]=a[i][qmn.front()];
		}
	}
	for(int i=b;i<=n;i++)
	{
		qmn.clear();qmx.clear();
		for(int j=1;j<=n;j++)
		{
			while(!qmx.empty()&&mx[qmx.back()][i]<=mx[j][i])
				qmx.pop_back();
			qmx.push_back(j);
			while(!qmx.empty()&&qmx.front()<j-b+1)qmx.pop_front();
			Mx[j][i]=mx[qmx.front()][i];

			while(!qmn.empty()&&mn[qmn.back()][i]>=mn[j][i])
				qmn.pop_back();
			qmn.push_back(j);
			while(!qmn.empty()&&qmn.front()<j-b+1)qmn.pop_front();
			Mn[j][i]=mn[qmn.front()][i];
		}
	}
	while(k--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",Mx[x+b-1][y+b-1]-Mn[x+b-1][y+b-1]);
	}
	return 0;
}
*/

