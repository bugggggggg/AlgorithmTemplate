struct Fraction
{
	ll num,den;
	Fraction(ll n=0,ll d=1):num(n),den(d)
	{
		d=__gcd(num,den),num/=d,den/=d;
		if(den<0)num=-num,den=-den;
	}
	friend Fraction operator+(const Fraction& A,const Fraction& B)
	{
		ll d=__gcd(A.den,B.den);
		return Fraction(B.den/d*A.num+A.den/d*B.num,A.den/d*B.den);
	}
	Fraction& operator+=(const Fraction &c)
	{
		return *this=*this+c;
	}
	Fraction operator-()const
	{
		Fraction r(*this);
		return r.num=-r.num,r;
	}
	friend Fraction operator-(const Fraction &a,const Fraction &c)
	{
		return -c+a;
	}
	Fraction& operator-=(const Fraction &c)
	{
		return *this=*this-c;
	}
	friend Fraction operator*(const Fraction& A,const Fraction& B)
	{
		return Fraction(A.num*B.num,A.den*B.den);
	}
	Fraction& operator*=(const Fraction &c)
	{
		return *this=*this*c;
	}
	friend Fraction operator/(const Fraction& A,const Fraction& B)
	{
		return Fraction(A.num*B.den,A.den*B.num);
	}
	Fraction& operator/=(const Fraction &c)
	{
		return *this=*this/c;
	}
	friend Fraction operator%(const Fraction &a,const Fraction &c)
	{
		return Fraction(a.num*c.den%(c.num*a.den),a.den*c.den);
	}
	Fraction& operator%=(const Fraction &c)
	{
		return *this=*this%c;
	}
	friend bool operator==(const Fraction &a,const Fraction &b)
	{
		return a.num*b.den==a.den*b.num;
	}
	friend bool operator!=(const Fraction &a,const Fraction &b)
	{
		return !(a==b);
	}
	friend bool operator<(const Fraction &a,const Fraction &b)
	{
		return a.num*b.den<a.den*b.num;
	}
	friend bool operator>(const Fraction &a,const Fraction &b)
	{
		return b<a;
	}
	friend bool operator<=(const Fraction &a,const Fraction &b)
	{
		return !(a>b);
	}
	friend bool operator>=(const Fraction &a,const Fraction &b)
	{
		return !(a<b);
	}
	friend Fraction abs(Fraction f)
	{
		if(f.num<0)f.num=-f.num;
		return f;
	}
	friend ostream& operator<<(ostream &os,const Fraction &f)
	{
		return !f.num?os<<0:
		       f.den==1?os<<f.num:
		       os<<f.num<<'/'<<f.den;
	}
};