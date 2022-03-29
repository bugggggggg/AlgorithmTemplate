#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define eb emplace_back
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
typedef pair<long long,long long> PLL;
const ll mod=998244353;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l, int r) {uniform_int_distribution<int> uni(l, r);return uni(rng);}
//__builtin_popcount(n)
//getline(cin,s);
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}




/*


*/