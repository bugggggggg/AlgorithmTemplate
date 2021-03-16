
//新版

const db PI=acos(-1.0);
#define Complex complex<db> 
#define poly vector<Complex>

int lim,R[2300066];
Complex t1[2300066],t2[2300066];

/*
 * fft
 * on==1 时是 DFT，on==-1 时是 IDFT
 */
void fft(Complex*a,int on)
{
	for(int i=0;i<lim;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(int h=2;h<=lim;h<<=1)
	{
		Complex wn(cos(on*2*PI/h),sin(on*2*PI/h));//////
		for(int j=0;j<lim;j+=h)
		{
			Complex w(1,0);
			for(int k=j;k<j+h/2;k++)
			{
				Complex u=a[k],t=w*a[k+h/2];
				a[k]=u+t;
				a[k+h/2]=u-t;
				w=w*wn;
			}
		}
	}
	if(on==-1)
		for(int i=0;i<lim;i++)
			a[i].real(a[i].real()/lim);
}

poly operator*(poly a,poly b)
{
    int siz=(int)a.size()+(int)b.size()-1;
    lim=1;
    while(lim<=siz)lim<<=1;//实际上是siz+1位，所以找第一个比siz大的。
    for(int i=1;i<lim;i++)R[i]=(R[i>>1]>>1)|((i&1)?lim>>1:0);
    memset(t1,0,(lim+1)*sizeof(Complex));
    memset(t2,0,(lim+1)*sizeof(Complex));
    for(int i=(int)a.size()-1;~i;--i)t1[i]=a[i];
    for(int i=(int)b.size()-1;~i;--i)t2[i]=b[i];
    fft(t1,1);fft(t2,1);
    for(int i=0;i<lim;i++)t1[i]=t1[i]*t2[i];
    fft(t1,-1);
    a.resize(siz);
    for(int i=0;i<siz;i++)a[i]=t1[i];
    return a;
}



///////////////////////////////////////////////////////////////////////////////////


#define db double
const db PI=acos(-1.0);

////

#define Complex complex<db>
/*
z.real(),z.imag()//取值
z.imag(99); z.real(-4.5);//赋值
*/

struct Complex
{
	db x,y;
	Complex(db _x=0.0,db _y=0.0)
	{
		x=_x;y=_y;
	} 
	Complex operator -(const Complex&b)
	{
		return Complex(x-b.x,y-b.y);
	}
	Complex operator +(const Complex&b)
	{
		return Complex(x+b.x,y+b.y);
	}
	Complex operator *(const Complex&b)
	{
		return Complex(x*b.x-y*b.y,x*b.y+y*b.x);
	}
};
//////////////////

// 同样需要保证 len 是 2 的幂
// 记 rev[i] 为 i 翻转后的值
int rev[1000066];
void change(Complex y[], int len) {
	for(int i=1;i<len;i++)rev[i]=(rev[i>>1]>>1)|((i&1)?lim>>1:0);
	for (int i = 0; i < len; ++i) {
		if (i < rev[i]) {  // 保证每对数只翻转一次
		  swap(y[i], y[rev[i]]);
		}
	}
	return;
}
/*
 * fft
 * len 必须为2^k形式
 * on==1 时是 DFT，on==-1 时是 IDFT
 */

void fft(Complex y[],int len,int on)
{
	change(y,len);
	for(int h=2;h<=len;h<<=1)
	{
		Complex wn(cos(on*2*PI/h),sin(on*2*PI/h));//////
		for(int j=0;j<len;j+=h)
		{
			Complex w(1,0);
			for(int k=j;k<j+h/2;k++)
			{
				Complex u=y[k],t=w*y[k+h/2];
				y[k]=u+t;
				y[k+h/2]=u-t;
				w=w*wn;
			}
		}
	}
	if(on==-1)
		for(int i=0;i<len;i++)
			y[i].x/=len;
}