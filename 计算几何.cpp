
/*
	atan2比较在long double下是不稳定的

*/

#include<bits/stdc++.h>
using namespace std;
#define db double
const db EPS=1e-9;

inline int sign(db a){return a<-EPS?-1:a>EPS;}

inline int cmp(db a,db b){return sign(a-b);}

#define cross(p1,p2,p3) (((p2).x-(p1).x)*((p3).y-(p1).y)-((p3).x-(p1).x)*((p2).y-(p1).y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))

struct P
{
	db x,y;
	P(){}
	P(db _x,db _y):x(_x),y(_y){}
	P operator+(P p){return P(x+p.x,y+p.y);}
	P operator-(P p){return P(x-p.x,y-p.y);}
	P operator*(db d){return P(x*d,y*d);}
	P operator/(db d){return P(x/d,y/d);}
	
	bool operator<(P p)const
	{
		int c=cmp(x,p.x);
		if(c)return c==-1;
		return cmp(y,p.y)==-1;
	} 
	bool operator==(P o)const
	{
		return cmp(x,o.x)==0&&cmp(y,o.y)==0;
	}
	db dot(P p){return x*p.x+y*p.y;}
	db det(P p){return x*p.y-y*p.x;}
	
	void read(){cin>>x>>y;}
	void write(){cout<<"("<<x<<","<<y<<")"<<'\n';}
	
	db abs2(){return x*x+y*y;}
	db abs(){return sqrt(abs2());}
	
	db distTo(P p){return (*this-p).abs();}
	db alpha(){return atan2(y,x);}
	int quad()const{return sign(y)==1||(sign(y)==0&&sign(x)>=0);}//判是否在上半区 
};

bool chkLL(P p1,P p2,P q1,P q2)//判p1p2与q1q2是否平行 
{
	db a1=cross(q1,q2,p1),a2=-cross(q1,q2,p2);
	return sign(a1+a2)!=0;
}

P isLL(P p1,P p2,P q1,P q2)//p1p2与q1q2的交点 
{
	db a1=cross(q1,q2,p1),a2=-cross(q1,q2,p2);
	return (p1*a2+p2*a1)/(a1+a2);
}

//线段相交
bool intersect(db l1,db r1,db l2,db r2)//区间[l1,r1]与[l2,r2]是否交 
{
	if(l1>r1)swap(l1,r1);if(l2>r2)swap(l2,r2);
	return !(cmp(r1,l2)==-1||cmp(r2,l1)==-1);
} 
bool isSS(P p1,P p2,P q1,P q2)//非严格相交 
{
	return intersect(p1.x,p2.x,q1.x,q2.x)&&intersect(p1.y,p2.y,q1.y,q2.y)
	&&crossOp(p1,p2,q1)*crossOp(p1,p2,q2)<=0
	&&crossOp(q1,q2,p1)*crossOp(q1,q2,p2)<=0;
} 
bool isSS_strict(P p1,P p2,P q1,P q2)//严格相交 
{
	return crossOp(p1,p2,q1)*crossOp(p1,p2,q2)<0
	&&crossOp(q1,q2,p1)*crossOp(q1,q2,p2)<0;
}
//点在线段上 
bool isMiddle(db a,db m,db b)//m在[a,b]内 
{
	return sign(a-m)==0||sign(b-m)==0||(a<m!=b<m);
} 
bool isMiddle(P a,P m,P b)
{
	return isMiddle(a.x,m.x,b.x)&&isMiddle(a.y,m.y,b.y);
}
bool onSeg(P p1,P p2,P q)
{
	return crossOp(p1,p2,q)==0&&isMiddle(p1,q,p2);
}
bool onSeg_strict(P p1,P p2,P q)//?
{
	return crossOp(p1,p2,q)==0&&sign((q-p1).dot(p1-p2))*sign((q-p2).dot(p1-p2))<=0;
}
//投影/反射/最近点
P proj(P p1,P p2,P q)//q在p1p2上的投影 
{
	P dir=p2-p1;
	return p1+dir*(dir.dot(q-p1)/dir.abs2());
}
P reflect(P p1,P p2,P q)//q关于p1p2的对称点 
{
	return proj(p1,p2,q)*2-q;
}
db nearest(P p1,P p2,P q)//q到p1p2的最短距离 
{
	P h=proj(p1,p2,q);
	if(isMiddle(p1,h,p2))return q.distTo(h);
	return min(p1.distTo(q),p2.distTo(q));
}
 
db disSS(P p1,P p2,P q1,P q2)//p1p2与q1q2间最短距离 
{
	if(isSS(p1,p2,q1,q2))return 0;
	return min(min(nearest(p1,p2,q1),nearest(p1,p2,q2)),min(nearest(q1,q2,p1),nearest(q1,q2,p2)));
}

db rad(P p1,P p2)//向量p1与向量p2夹角 
{
	return atan2(p1.det(p2),p1.dot(p2));
}
 
bool PAcmp(P a,P b)//极角排序 
{
	if(a.quad()!=b.quad())return a.quad()<b.quad();
	return sign(a.det(b))>0;
} 

/*
	这种排序(-1,0)位置最小。
	按atan2角度排的，(-1,0)位置最大
*/

db area(vector<P> ps)//多边形面积 ,逆正
{
	db ret=0;int n=ps.size();
	for(int i=0;i<n;i++)ret+=ps[i].det(ps[(i+1)%n]);
	return ret/2; 
}

//点包含(点p是否在多边形内部) 
//过p作一条水平射线，并把与多边形的交点向上平移一个无穷小量
//交点为偶数在外面，奇数在内部 
int contain(vector<P>ps,P p)//2:inside,1:on_seg,0:outside 
{
	int n=ps.size(),ret=0;
	for(int i=0;i<n;i++)
	{
		P u=ps[i],v=ps[(i+1)%n];
		if(onSeg(u,v,p))return 1;
		if(cmp(u.y,v.y)<=0)swap(u,v);
		if(cmp(p.y,u.y)>0||cmp(p.y,v.y)<=0)continue;// 
		ret^=crossOp(p,u,v)>0;
	} 
	return ret*2;
} 

//凸包
vector<P> convexHull(vector<P>ps)
{
	int n=SZ(ps);if(n<=1)return ps;
	sort(all(ps));
	vector<P>qs(n*2);int k=0;
	for(int i=0;i<n;qs[k++]=ps[i++])//上半凸包
		while(k>1&&crossOp(qs[k-2],qs[k-1],ps[i])>=0)--k;
	// for(int i=0;i<k;i++)
	// 	printf("%f %f____\n",qs[i].x,qs[i].y);
	// puts("");
	for(int i=n-2,t=k;i>=0;qs[k++]=ps[i--])//下半凸包
		while(k>t&&crossOp(qs[k-2],qs[k-1],ps[i])>=0)--k;
	qs.resize(k-1);
	return qs;
}

//旋转卡壳，返回凸包的直径
//使用前保证为凸包，且逆时针（否则在det的地方加上绝对值）
db rotateCalipers(vector<P>ps)
{
	int n=SZ(ps);
	db ret=-1e9;
	int q=1;
	for(int i=0;i<n;i++)
	{
		while((ps[(i+1)%n]-ps[i]).det(ps[q]-ps[i])<(ps[(i+1)%n]-ps[i]).det(ps[(q+1)%n]-ps[i]))
			q=(q+1)%n;
		ret=max(ret,ps[i].distTo(ps[q]));
	}return ret;
}

/*
半平面交，按斜率小到大，截距大到小排序，
单调栈维护，每次判交点左右关系来出栈。

*/

