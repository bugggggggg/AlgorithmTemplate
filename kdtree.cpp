

曼哈顿最小距离
#include<cstdio>
#include<algorithm>

using namespace std;

const int inf=1e9;
int n,m,root,D;
struct P
{
    int d[2],mn[2],mx[2],l,r;
    int& operator[](int x){return d[x];}//
    P(int x=0,int y=0)
    {
        l=0,r=0;d[0]=x;d[1]=y;
    }
}p[500006];
bool operator<(P a,P b)
{
    return a[D]<b[D];
}//按第D维比较
#define Abs(x) ((x)>0?(x):-(x))
int dis(P a,P b)
{
    return Abs(a[0]-b[0])+Abs(a[1]-b[1]);
}//返回曼哈顿距离
struct kdtree
{
    int ans;
    P t[1000005],T;
    void update(int k)
    {
        P l=t[t[k].l],r=t[t[k].r];
        for(int i=0;i<2;i++)
        {
            if(t[k].l)t[k].mn[i]=min(t[k].mn[i],l.mn[i]),t[k].mx[i]=max(t[k].mx[i],l.mx[i]);
            if(t[k].r)t[k].mn[i]=min(t[k].mn[i],r.mn[i]),t[k].mx[i]=max(t[k].mx[i],r.mx[i]);
        }
    }//更新区域t[k]的范围
    int build(int l,int r,int now)
    {
        D=now;
        int mid=(l+r)>>1;
        nth_element(p+l,p+mid,p+r+1);//取中位数划分空间
        t[mid]=p[mid];
        for(int i=0;i<2;i++)
            t[mid].mn[i]=t[mid].mx[i]=t[mid][i];
        if(l<mid)t[mid].l=build(l,mid-1,now^1);
        if(mid<r)t[mid].r=build(mid+1,r,now^1);
        update(mid);
        return mid;
    }
    int get(int k,P p)
    {
        int tmp=0;
        for(int i=0;i<2;i++)
            tmp+=max(0,t[k].mn[i]-p[i]);
        for(int i=0;i<2;i++)
            tmp+=max(0,p[i]-t[k].mx[i]);
        return tmp;
    }//点p与矩形区域t[k]的最小曼哈顿距离，用于剪枝
    void insert(int k,int now)
    {
        if(T[now]>=t[k][now])
        {
            if(t[k].r)insert(t[k].r,now^1);
            else
            {
                t[k].r=++n;t[n]=T;
                for(int i=0;i<2;i++)
                    t[n].mn[i]=t[n].mx[i]=T[i];
            }
        }
        else
        {
            if(t[k].l)insert(t[k].l,now^1);
            else
            {
                t[k].l=++n;t[n]=T;
                for(int i=0;i<2;i++)
                    t[n].mn[i]=t[n].mx[i]=T[i];
            }
        }
        update(k);
    }
    void query(int k,int now)
    {
        int d,dl=inf,dr=inf;
        d=dis(t[k],T);
        ans=min(ans,d);
        if(t[k].l)dl=get(t[k].l,T);
        if(t[k].r)dr=get(t[k].r,T);
        if(dl<dr)
        {
            if(dl<ans)query(t[k].l,now^1);//最小距离大于ans就不用跑
            if(dr<ans)query(t[k].r,now^1);
        }
        else
        {
            if(dr<ans)query(t[k].r,now^1);
            if(dl<ans)query(t[k].l,now^1);
        }
    }
    int query(P p)
    {
        ans=inf;T=p;query(root,0);
        return ans;
    }
    void insert(P p)
    {
        T=p;insert(root,0);
    }
}kd;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d%d",&p[i][0],&p[i][1]);
    root=kd.build(1,n,0);
    while(m--)
    {
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if(op==1)kd.insert(P(x,y));
        else printf("%d\n",kd.query(P(x,y)));
    }
    return 0;
}





/*
    欧几里得最小、最大距离。
    给定n个点，没有插入操作时，把答案作为全局。
*/
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef long long ll;
typedef double db;
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef pair<long long,int> PLI;
const ll mod=1000000007;
//mt19937_64 mrand(random_device{}()); 
//int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) {return b?gcd(b,a%b):a;}

int n,root,D;

struct P
{
    db d[2];
    db mn[2],mx[2];//维护一个矩形区域
    int ls,rs;
    db& operator[](int x){return d[x];}
    P(db x=0,db y=0)
    {
        ls=rs=0;d[0]=x;d[1]=y;
    }
}node[100066];

bool operator<(P&a,P&b)
{
    return a[D]<b[D];
}

#define Abs(x) ((x)>0?(x):-(x))

db dis2(P a,P b)
{
    db dx=a[0]-b[0],dy=a[1]-b[1];
    return dx*dx+dy*dy;
}
int tot=1;


db ans_mn,ans_mx;

struct kdtree
{
    
    P t[200066],T;
    void update(int k)
    {
        P l=t[t[k].ls],r=t[t[k].rs];
        for(int i=0;i<2;i++)
        {
            if(t[k].ls)t[k].mn[i]=min(t[k].mn[i],l.mn[i]),t[k].mx[i]=max(t[k].mx[i],l.mx[i]);
            if(t[k].rs)t[k].mn[i]=min(t[k].mn[i],r.mn[i]),t[k].mx[i]=max(t[k].mx[i],r.mx[i]);
        }
    }

    int build(int l,int r,int now)
    {
        D=now;
        int mid=(l+r)>>1;
        nth_element(node+1,node+mid,node+r+1);
        t[mid]=node[mid];
        for(int i=0;i<2;i++)
            t[mid].mn[i]=t[mid].mx[i]=t[mid][i];
        if(l<mid)t[mid].ls=build(l,mid-1,now^1);
        if(mid<r)t[mid].rs=build(mid+1,r,now^1);
        update(mid);
        return mid;
    }
    db get_mn(int k,P p)
    {
        db ret;
        db tmp1=max(0.0,t[k].mn[0]-p[0])+max(0.0,p[0]-t[k].mx[0]);
        db tmp2=max(0.0,t[k].mn[1]-p[1])+max(0.0,p[1]-t[k].mx[1]);
        ret=tmp1*tmp1+tmp2*tmp2;///////////////////别写错了
        return ret;
    }//点p与矩形区域的最小可能距离。
    db get_mx(int k,P p)
    {
        db ret=0;
        ret=max(ret,dis2(p,P(t[k].mn[0],t[k].mn[1])));
        ret=max(ret,dis2(p,P(t[k].mx[0],t[k].mx[1])));
        ret=max(ret,dis2(p,P(t[k].mn[0],t[k].mx[1])));
        ret=max(ret,dis2(p,P(t[k].mx[0],t[k].mn[1])));
        return ret;
    }//点p与矩形区域的最大可能面积。

    void insert(int k,int now)
    {
        if(T[now]>=t[k][now])
        {
            if(t[k].rs)insert(t[k].rs,now^1);
            else
            {
                t[k].rs=++tot;t[tot]=T;
                for(int i=0;i<2;i++)
                    t[tot].mn[i]=t[tot].mx[i]=T[i];
            }
        }
        else
        {
            if(t[k].ls)insert(t[k].ls,now^1);
            else
            {
                t[k].ls=++tot;t[tot]=T;
                for(int i=0;i<2;i++)
                    t[tot].mn[i]=t[tot].mx[i]=T[i];
            }
        }
        update(k);
    }

    void query_mn(int k,int now)
    {
        db d,dl=2e18,dr=2e18;
        d=dis2(t[k],T);
        ans_mn=min(ans_mn,d);   
        if(t[k].ls)dl=get_mn(t[k].ls,T);
        if(t[k].rs)dr=get_mn(t[k].rs,T);
        if(dl<dr)
        {
            if(dl<ans_mn)query_mn(t[k].ls,now^1);
            if(dr<ans_mn)query_mn(t[k].rs,now^1);
        }
        else 
        {
            if(dr<ans_mn)query_mn(t[k].rs,now^1);
            if(dl<ans_mn)query_mn(t[k].ls,now^1);
        }

    }
    void query_mx(int k,int now)
    {
        db d,dl=0,dr=0;
        d=dis2(t[k],T);
        ans_mx=max(ans_mx,d);
        if(t[k].ls)dl=get_mx(t[k].ls,T);
        if(t[k].rs)dr=get_mx(t[k].rs,T);
        if(dl<dr)
        {
            if(dr>ans_mx)query_mx(t[k].rs,now^1);
            if(dl>ans_mx)query_mx(t[k].ls,now^1);
        }
        else
        {
            if(dl>ans_mx)query_mx(t[k].ls,now^1);
            if(dr>ans_mx)query_mx(t[k].rs,now^1);
        }
    }
    db query_mx(P p)
    {
        //ans_mx=0;
        T=p;query_mx(root,0);
        return ans_mx;
    }
    db query_mn(P p)
    {
        //ans_mn=2e18;
        T=p;query_mn(root,0);
        return ans_mn;
    }
    void insert(P p)
    {
        T=p;insert(root,0);
    }
}kd;

int main()
{
   
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lf%lf",&node[i][0],&node[i][1]);
    }
    random_shuffle(node+1,node+n+1);///////////////////////////////////////
    
    root=kd.build(1,1,0);
    ans_mx=0,ans_mn=2e18;
    for(int i=2;i<=n;i++)
    {
        kd.query_mn(node[i]);
        kd.query_mx(node[i]);
        kd.insert(node[i]);
    }
    printf("%.3f %.3f\n",sqrt(ans_mn),sqrt(ans_mx));
    return 0;
}

