# 复数

```c
typedef long double D;

const D PI = acos(-1);

struct complex {
    D real, imag;
    complex() { real = imag = 0; }
    complex(D x): real(x), imag(0) {} 
    complex(D x, D y): real(x), imag(y) {}
    inline complex conj() { return complex(real, -imag); }
    inline complex operator+(complex rhs) const { return complex(real + rhs.real, imag + rhs.imag); }
    inline complex operator-(complex rhs) const { return complex(real - rhs.real, imag - rhs.imag); }
    inline complex operator*(complex rhs) const { return complex(real * rhs.real - imag * rhs.imag,
                                                                 imag * rhs.real + real * rhs.imag); }
    inline complex operator*=(complex rhs) { return (*this) = (*this) * rhs; }
    //(a+bi)(c+di) = (ac-bd) + (bc+ad)i
    friend inline complex operator*(D x, complex cp) { return complex(x * cp.real, x * cp.imag); }
    inline complex operator/(D x) const { return complex(real / x, imag / x); }
    inline complex operator/=(D x) { return (*this) = (*this) / x; }
    friend inline complex operator/(D x, complex cp) { return x * cp.conj() / (cp.real * cp.real - cp.imag * cp.imag); }
    inline complex operator/(complex rhs) const { 
        return (*this) * rhs.conj() / (rhs.real * rhs.real - rhs.imag * rhs.imag); 
    }
    inline complex operator/=(complex rhs) { return (*this) = (*this) / rhs; }
    inline D length() { return sqrt(real * real + imag * imag); }
};
```

