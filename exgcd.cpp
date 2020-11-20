/*
	解方程ax+by=gcd(a,b);
	返回gcd(a,b);
*/

//调用时a,b要为正数。
ll exgcd(ll a,ll b,ll&x,ll&y)
{
	if(b==0)
	{
		x=1;y=0;return a;
	}
	ll r=exgcd(b,a%b,x,y);
	ll tmp=y;
	y=x-(a/b)*y;
	x=tmp;
	return r;
}