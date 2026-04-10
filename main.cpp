#ifndef LOCAL
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt,abm,mmx,sse4.2")
#endif

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §0  CORE TYPES & ALIASES                                        ║
// ╚══════════════════════════════════════════════════════════════════╝
using ll   = long long;
using ull  = unsigned long long;
using ld   = long double;
using uint = unsigned int;
using lll  = __int128;
using u64  = uint64_t;
using u32  = uint32_t;
using i64  = int64_t;

// CAUTION
#define int ll          // ← comment out if int overflow not needed

template<class T>       using vc   = vector<T>;
template<class T>       using vvc  = vc<vc<T>>;
template<class T>       using vvvc = vc<vvc<T>>;
using vi   = vc<int>;
using vvi  = vvc<int>;
using vvvi = vvvc<int>;
using pi   = pair<int,int>;
using pl   = pair<ll,ll>;
using ti3  = tuple<int,int,int>;
using ti4  = tuple<int,int,int,int>;

// Policy-based ORDERED SET  (order_of_key / find_by_order)
template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_set_greater = tree<T,null_type,greater<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class K,class V>
using ordered_map = tree<K,V,less<K>,rb_tree_tag,tree_order_statistics_node_update>;

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §1  MACROS                                                      ║
// ╚══════════════════════════════════════════════════════════════════╝
#define rng(i,a,b)   for(int i=int(a);i<int(b);i++)
#define rep(i,b)     rng(i,0,b)
#define gnr(i,a,b)   for(int i=int(b)-1;i>=int(a);i--)
#define per(i,b)     gnr(i,0,b)
#define pb           push_back
#define eb           emplace_back
#define all(x)       (x).begin(),(x).end()
#define rall(x)      (x).rbegin(),(x).rend()
#define si(x)        int((x).size())
#define fi           first
#define se           second
#define mp           make_pair
#define mt           make_tuple
#define one(x)       memset(x,-1,sizeof(x))
#define zero(x)      memset(x,0,sizeof(x))
#define EACH(e,v)    for(auto&e:(v))
#define sz(x)        (int)(x).size()
#define Yes(e)       cout<<"Yes\n"; if(e)return
#define No(e)        cout<<"No\n";  if(e)return
#define YES(e)       cout<<"YES\n"; if(e)return
#define NO(e)        cout<<"NO\n";  if(e)return

#ifdef LOCAL
#define dmp(x)       cerr<<__LINE__<<" "<<#x<<" = "<<(x)<<"\n"
#define dmp2(...)    [&]{cerr<<__LINE__;((cerr<<" "<<#__VA_ARGS__<<":"<<(__VA_ARGS__)),...);cerr<<"\n";}()
#define dmpv(v)      do{cerr<<#v<<": ";for(auto _x:(v))cerr<<_x<<" ";cerr<<"\n";}while(0)
#define dmpvv(v)     do{cerr<<#v<<":\n";for(auto&_r:(v)){for(auto _x:_r)cerr<<_x<<"\t";cerr<<"\n";}}while(0)
#else
#define dmp(x)       void(0)
#define dmp2(...)    void(0)
#define dmpv(v)      void(0)
#define dmpvv(v)     void(0)
#endif

bool dbg = false;

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §2  CONSTANTS                                                   ║
// ╚══════════════════════════════════════════════════════════════════╝
const ll   infLL = LLONG_MAX / 3;
#ifdef int
const int  inf   = infLL;
#else
const int  inf   = INT_MAX / 2 - 100;
#endif
const ld   EPS    = 1e-9L;
const ld   PI     = acosl(-1.0L);
const ll   MOD1   = 998244353;
const ll   MOD2   = 1e9+7;
const ll   MOD3   = 1e9+9;
constexpr ll ten(int n){ return n==0?1LL:ten(n-1)*10LL; }
constexpr int dx4[]={0,0,1,-1};
constexpr int dy4[]={1,-1,0,0};
constexpr int dx8[]={0,0,1,-1,1,1,-1,-1};
constexpr int dy8[]={1,-1,0,0,1,-1,1,-1};

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §3  BIT TRICKS                                                  ║
// ╚══════════════════════════════════════════════════════════════════╝
int topbit(signed t){ return t==0?-1:31-__builtin_clz(t); }
int topbit(ll     t){ return t==0?-1:63-__builtin_clzll(t); }
int topbit(ull    t){ return t==0?-1:63-__builtin_clzll(t); }
int botbit(signed a){ return a==0?32:__builtin_ctz(a); }
int botbit(ll     a){ return a==0?64:__builtin_ctzll(a); }
int botbit(ull    a){ return a==0?64:__builtin_ctzll(a); }
int popcount(unsigned t){ return __builtin_popcount(t); }
int popcount(ll    t){ return __builtin_popcountll(t); }
int popcount(ull   t){ return __builtin_popcountll(t); }
int bitparity(ll t){ return __builtin_parityll(t); }
bool ispow2(ll i){ return i&&(i&-i)==i; }
ll   mask(int i) { return (ll(1)<<i)-1; }
ull  umask(int i){ return (ull(1)<<i)-1; }
ll   minp2(ll n) { if(n<=1)return 1; return ll(1)<<(topbit(n-1)+1); }

// Iterate over subsets of mask
// for(int sub=mask;sub>0;sub=(sub-1)&mask) ...
// Iterate over all submasks of all masks up to 1<<n — O(3^n)
// rep(mask,1<<n) for(int s=mask;s;s=(s-1)&mask) ...

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §4  UTILITY FUNCTIONS                                           ║
// ╚══════════════════════════════════════════════════════════════════╝
template<class T,class U> bool chmax(T&a,U b){ if(a<b){a=b;return 1;}return 0;}
template<class T,class U> bool chmin(T&a,U b){ if(b<a){a=b;return 1;}return 0;}

template<class T> T sq(const T&t){ return t*t; }
template<class T> T cube(const T&t){ return t*t*t; }
template<class T> T abs_(T a){ return a<0?-a:a; }

bool inc(int a,int b,int c){ return a<=b&&b<=c; }

// Coordinate compression: returns compressed values & sorted uniq keys
template<class T>
pair<vi,vc<T>> compress(const vc<T>&a){
    vc<T> keys=a; sort(all(keys)); keys.erase(unique(all(keys)),keys.end());
    vi comp(si(a)); rep(i,si(a))comp[i]=lower_bound(all(keys),a[i])-keys.begin();
    return{comp,keys};
}

template<class S> void mkuni(S&v){ sort(all(v)); v.erase(unique(all(v)),v.end()); }
template<class T> bool isuni(vc<T> v){ int s=si(v); mkuni(v); return si(v)==s; }

template<class T>
vi sortidx(const vc<T>&a){
    int n=si(a); vi idx(n); iota(all(idx),0);
    sort(all(idx),[&](int i,int j){return a[i]<a[j];});
    return idx;
}
template<class T>
vc<T> a_idx(const vc<T>&a,const vi&idx){
    int n=si(a); vc<T> vs(n); rep(i,n)vs[i]=a[idx[i]]; return vs;
}
vi invperm(const vi&p){ int n=si(p); vi q(n); rep(i,n)q[p[i]]=i; return q; }
vi vid(int n){ vi res(n); iota(all(res),0); return res; }

template<class S> void soin(S&s){ sort(all(s)); }
template<class S,class F> void soin(S&s,F&&f){ sort(all(s),forward<F>(f)); }
template<class S> S soout(S s){ soin(s); return s; }
template<class S> void rein(S&s){ reverse(all(s)); }
template<class S> S reout(S s){ rein(s); return s; }
template<class VS,class U> void fila(VS&vs,const U&a){ fill(all(vs),a); }

template<class T,class U>
int findid(const vc<T>&vs,const U&a){
    auto itr=find(all(vs),a);
    return itr==vs.end()?-1:itr-vs.begin();
}
template<class T> void rtt(vc<T>&vs,int i){ rotate(vs.begin(),vs.begin()+i,vs.end()); }
template<class T> T gpp(vc<T>&vs){ assert(si(vs)); T r=move(vs.back()); vs.pop_back(); return r; }

template<class T,class U> void pb(vc<T>&a,const vc<U>&b){ a.insert(a.end(),all(b)); }
template<class T,class...Args> vc<T> cat(vc<T> a,Args&&...b){ (pb(a,forward<Args>(b)),...); return a; }

template<class T,class U> int remval(vc<T>&a,const U&v){ auto it=remove(all(a),v); int r=a.end()-it; a.erase(it,a.end()); return r; }
template<class T,class F> int remif(vc<T>&a,F f){ auto it=remove_if(all(a),f); int r=a.end()-it; a.erase(it,a.end()); return r; }
template<class T> void rempos(vc<T>&a,int i){ a.erase(a.begin()+i); }

template<class T,class S=T> S SUM(const vc<T>&a){ return accumulate(all(a),S(0)); }
ll SUM(const vi&a){ return accumulate(all(a),ll(0)); }
template<class T> T MAX(const vc<T>&a){ return *max_element(all(a)); }
template<class T> T MIN(const vc<T>&a){ return *min_element(all(a)); }
template<class T> pair<T,int> MAXi(const vc<T>&a){ auto it=max_element(all(a)); return{*it,it-a.begin()}; }
template<class T> pair<T,int> MINi(const vc<T>&a){ auto it=min_element(all(a)); return{*it,it-a.begin()}; }

template<class T> vc<T> presum(const vc<T>&a){
    vc<T> s(si(a)+1); rep(i,si(a)) s[i+1]=s[i]+a[i]; return s;
}
template<class T> vc<T> predif(vc<T> a){ gnr(i,1,si(a)) a[i]-=a[i-1]; return a; }
template<class T> vvc<ll> imos(const vvc<T>&a){
    int n=si(a),m=si(a[0]); vvc<ll> b(n+1,vc<ll>(m+1));
    rep(i,n) rep(j,m) b[i+1][j+1]=b[i+1][j]+b[i][j+1]-b[i][j]+a[i][j];
    return b;
}

template<class T> T vvvc(T v){ return v; }
template<class T,class...Args> auto vvvc(int n,T v,Args...args){ return vector(n,vvvc(v,args...)); }

template<class S,class U> int lwb(const S&v,const U&a){ return lower_bound(all(v),a)-v.begin(); }
template<class S,class U> int upb(const S&v,const U&a){ return upper_bound(all(v),a)-v.begin(); }
template<class T,class U> bool bis(const vc<T>&v,const U&a){ return binary_search(all(v),a); }

template<class F> ll find_min_true(ll lw,ll up,F f){
    while(up-lw>1){ll mid=(lw+up)/2; if(f(mid))up=mid; else lw=mid;} return up;
}
template<class F> ll find_max_true(ll lw,ll up,F f){
    while(up-lw>1){ll mid=(lw+up)/2; if(f(mid))lw=mid; else up=mid;} return lw;
}
// Real-valued binary search (floating point)
template<class F> ld bisect_real(ld lo,ld hi,F f,int iter=200){
    rep(i,iter){ ld mid=(lo+hi)/2; if(f(mid))hi=mid; else lo=mid; } return (lo+hi)/2;
}

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §5  RANDOM                                                      ║
// ╚══════════════════════════════════════════════════════════════════╝
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
ll rand_int(ll l,ll r){ return uniform_int_distribution<ll>(l,r)(rng64); }
ll rand_int(ll k){ return rand_int(0,k-1); }
ld rand_real(ld l=0,ld r=1){ return uniform_real_distribution<ld>(l,r)(rng64); }
string rand_string(int n,char lw,char up){ string s(n,'?'); rep(i,n) s[i]=(char)rand_int(lw,up); return s; }
template<class T> void myshuffle(vc<T>&a){ rep(i,si(a)) swap(a[i],a[rand_int(0,i)]); }

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §6  MODULAR ARITHMETIC                                          ║
// ╚══════════════════════════════════════════════════════════════════╝
template<ll MOD> struct Mint {
    ll v;
    Mint(ll _v=0):v(_v%MOD){ if(v<0)v+=MOD; }
    Mint& operator+=(Mint o){ v+=o.v; if(v>=MOD)v-=MOD; return *this; }
    Mint& operator-=(Mint o){ v-=o.v; if(v<0)v+=MOD; return *this; }
    Mint& operator*=(Mint o){ v=v*o.v%MOD; return *this; }
    Mint& operator/=(Mint o){ return *this*=o.inv(); }
    Mint inv() const { return pow(MOD-2); }
    Mint pow(ll n) const { Mint r=1,a=*this; while(n){if(n&1)r*=a;a*=a;n>>=1;} return r; }
    friend Mint operator+(Mint a,Mint b){ return a+=b; }
    friend Mint operator-(Mint a,Mint b){ return a-=b; }
    friend Mint operator*(Mint a,Mint b){ return a*=b; }
    friend Mint operator/(Mint a,Mint b){ return a/=b; }
    friend Mint operator-(Mint a)       { return Mint(0)-=a; }
    bool operator==(Mint o)const{ return v==o.v; }
    bool operator!=(Mint o)const{ return v!=o.v; }
    bool operator< (Mint o)const{ return v<o.v; }
    friend ostream& operator<<(ostream&os,Mint a){ return os<<a.v; }
    friend istream& operator>>(istream&is,Mint&a){ ll x; is>>x; a=Mint(x); return is; }
    explicit operator ll()const{ return v; }
};
using mint  = Mint<998244353>;
using mint7 = Mint<1000000007>;

// Dynamic mod (runtime-set modulus, no template)
struct MintDyn {
    static ll MOD;
    ll v;
    MintDyn(ll _v=0):v(_v%MOD){ if(v<0)v+=MOD; }
    MintDyn& operator+=(MintDyn o){ v+=o.v; if(v>=MOD)v-=MOD; return *this; }
    MintDyn& operator-=(MintDyn o){ v-=o.v; if(v<0)v+=MOD; return *this; }
    MintDyn& operator*=(MintDyn o){ v=(__int128)v*o.v%MOD; return *this; }
    MintDyn& operator/=(MintDyn o){ return *this*=o.inv(); }
    MintDyn inv()const{
        ll a=v,b=MOD,x=1,y=0;
        while(b){ll q=a/b;a-=q*b;swap(a,b);x-=q*y;swap(x,y);}
        return MintDyn((x%MOD+MOD)%MOD);
    }
    MintDyn pow(ll n)const{ MintDyn r=1,a=*this; while(n){if(n&1)r*=a;a*=a;n>>=1;} return r; }
    friend MintDyn operator+(MintDyn a,MintDyn b){ return a+=b; }
    friend MintDyn operator-(MintDyn a,MintDyn b){ return a-=b; }
    friend MintDyn operator*(MintDyn a,MintDyn b){ return a*=b; }
    friend MintDyn operator/(MintDyn a,MintDyn b){ return a/=b; }
    friend ostream& operator<<(ostream&os,MintDyn a){ return os<<a.v; }
};
ll MintDyn::MOD = 998244353;

// Comb — works with any Mint type
template<class M> struct Comb {
    vc<M> f,invf;
    Comb(int n=0):f(1,1),invf(1,1){ extend(n); }
    void extend(int n){
        int cur=si(f)-1; if(cur>=n)return;
        f.resize(n+1); invf.resize(n+1);
        rng(i,cur+1,n+1) f[i]=f[i-1]*i;
        invf[n]=f[n].inv();
        gnr(i,0,n) invf[i]=invf[i+1]*(i+1);
    }
    M C(int n,int r){ if(r<0||r>n||n<0)return 0; extend(n); return f[n]*invf[r]*invf[n-r]; }
    M P(int n,int r){ if(r<0||r>n||n<0)return 0; extend(n); return f[n]*invf[n-r]; }
    M H(int n,int r){ if(n==0&&r==0)return 1; return C(n+r-1,r); }
    M Cat(int n)    { return C(2*n,n)-C(2*n,n-1); }   // Catalan number C_n
    M operator()(int n,int r){ return C(n,r); }
    // Lucas theorem for prime p (p can be small)
    M Lucas(ll n,ll r,ll p){
        if(r==0)return 1; return C(n%p,r%p)*Lucas(n/p,r/p,p);
    }
    // Stirling numbers of the second kind S(n,k)
    // S(n,k) = # ways to partition n elements into k non-empty subsets
    M Stirling2(int n,int k){
        extend(max(n,k)+1);
        M res=0;
        rep(j,k+1) res += (j%2?M(-1):M(1)) * C(k,j) * M(k-j).pow(n);
        return res * invf[k];
    }
};
Comb<mint>  comb;
Comb<mint7> comb7;

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §7  NTT & POLYNOMIAL  (mod 998244353)                          ║
// ╚══════════════════════════════════════════════════════════════════╝
namespace Poly {
    using M = mint;
    using P = vc<M>;

    void ntt(P&a,bool inv){
        int n=si(a);
        for(int i=1,j=0;i<n;i++){
            int bit=n>>1;
            for(;j&bit;bit>>=1)j^=bit; j^=bit;
            if(i<j)swap(a[i],a[j]);
        }
        for(int len=2;len<=n;len<<=1){
            M w=inv?M(3).pow(998244353-1-(998244353-1)/len):M(3).pow((998244353-1)/len);
            for(int i=0;i<n;i+=len){
                M wn=1;
                rng(j,0,len/2){
                    M u=a[i+j],v=a[i+j+len/2]*wn;
                    a[i+j]=u+v; a[i+j+len/2]=u-v; wn*=w;
                }
            }
        }
        if(inv){ M ni=M(n).inv(); for(auto&x:a)x*=ni; }
    }

    P conv(P a,P b){
        int sz=si(a)+si(b)-1,n=minp2(sz);
        a.resize(n); b.resize(n);
        ntt(a,0); ntt(b,0);
        rep(i,n)a[i]*=b[i];
        ntt(a,1); a.resize(sz); return a;
    }

    P inv_(P a,int n){
        P r={a[0].inv()};
        for(int m=1;m<n;m<<=1){
            P tmp(a.begin(),a.begin()+min((int)si(a),2*m));
            tmp.resize(2*m); r.resize(2*m);
            ntt(tmp,0); ntt(r,0);
            rep(i,2*m)r[i]=r[i]*(M(2)-tmp[i]*r[i]);
            ntt(r,1); r.resize(m);
        }
        r.resize(n); return r;
    }

    P deriv(P a){ if(si(a)<=1)return{}; P r(si(a)-1); rep(i,si(r))r[i]=a[i+1]*(i+1); return r; }
    P integr(P a){ P r(si(a)+1); rng(i,1,si(r))r[i]=a[i-1]*M(i).inv(); return r; }

    P log_(P a,int n){
        auto r=conv(deriv(a),inv_(a,n));
        r.resize(n-1); return integr(r);
    }

    P exp_(P a,int n){
        P r={M(1)};
        for(int m=1;m<n;m<<=1){
            P l=log_(r,2*m); l.resize(2*m);
            rep(i,2*m)l[i]=(i==0?M(1):M(0))-l[i]+(i<si(a)?a[i]:M(0));
            r=conv(r,l); r.resize(2*m);
        }
        r.resize(n); return r;
    }

    P sqrt_(P a,int n){
        P r={M(1)};
        M inv2=M(2).inv();
        for(int m=1;m<n;m<<=1){
            r.resize(2*m);
            P ir=inv_(r,2*m);
            P tmp(a.begin(),a.begin()+min((int)si(a),2*m));
            tmp.resize(2*m);
            auto t=conv(ir,tmp); t.resize(2*m);
            rep(i,2*m)r[i]=(r[i]+t[i])*inv2;
        }
        r.resize(n); return r;
    }

    // Polynomial power: a^k mod x^n
    P pow_(P a,ll k,int n){
        // find first nonzero
        int lo=0; while(lo<si(a)&&a[lo].v==0)lo++;
        if(lo==n)return P(n,M(0));
        if((__int128)lo*k>=n)return P(n,M(0));
        int shift=lo*k;
        M c=a[lo]; P b(si(a)-lo);
        rep(i,si(b))b[i]=a[lo+i]/c;
        b=exp_(log_(b,n-shift)*M(k),n-shift);
        M ck=c.pow(k);
        P res(n);
        rep(i,n-shift)res[i+shift]=b[i]*ck;
        return res;
    }

    // Multipoint evaluation O(n log^2 n)
    P eval_subprod(const vc<M>&xs,int l,int r){
        if(l+1==r)return{-xs[l],M(1)};
        int mid=(l+r)/2;
        return conv(eval_subprod(xs,l,mid),eval_subprod(xs,mid,r));
    }
    vc<M> eval(P f,const vc<M>&xs){
        int n=si(xs);
        P sp=eval_subprod(xs,0,n);
        function<vc<M>(P,int,int)> rec=[&](P g,int l,int r)->vc<M>{
            if(l+1==r)return{g[0]};
            int mid=(l+r)/2;
            P lp=eval_subprod(xs,l,mid);
            P rp=eval_subprod(xs,mid,r);
            // g mod lp, g mod rp
            g.resize(r-l);
            // naive mod for now; can optimize with inv
            function<P(P,P)> poly_mod=[&](P a,P b)->P{
                while(si(a)>=si(b)){
                    M c=a.back()/b.back();
                    gnr(i,0,si(b))a[si(a)-si(b)+i]-=c*b[i];
                    a.pop_back();
                }
                return a;
            };
            auto gl=rec(poly_mod(g,lp),l,mid);
            auto gr=rec(poly_mod(g,rp),mid,r);
            gl.insert(gl.end(),all(gr));
            return gl;
        };
        return rec(f,0,n);
    }
}

// Arbitrary-mod convolution via Garner (3-NTT trick)
namespace ArbitraryConv {
    using ll = long long;
    const ll M1=998244353,M2=985661441,M3=754974721;
    ll pw(ll a,ll b,ll m){ ll r=1;a%=m;for(;b;b>>=1,a=a*a%m)if(b&1)r=r*a%m;return r; }
    ll inv(ll a,ll m){ return pw(a,m-2,m); }
    void ntt_(vc<ll>&a,bool iv,ll mod,ll g){
        int n=si(a);
        for(int i=1,j=0;i<n;i++){int bit=n>>1;for(;j&bit;bit>>=1)j^=bit;j^=bit;if(i<j)swap(a[i],a[j]);}
        for(int len=2;len<=n;len<<=1){
            ll w=iv?pw(g,mod-1-(mod-1)/len,mod):pw(g,(mod-1)/len,mod);
            for(int i=0;i<n;i+=len){ll wn=1;rng(j,0,len/2){ll u=a[i+j],v=a[i+j+len/2]*wn%mod;a[i+j]=(u+v)%mod;a[i+j+len/2]=(u-v+mod)%mod;wn=wn*w%mod;}}
        }
        if(iv){ll ni=inv(n,mod);for(auto&x:a)x=x*ni%mod;}
    }
    vc<ll> conv1(vc<ll> a,vc<ll> b,ll mod,ll g){
        int sz=si(a)+si(b)-1,n=minp2(sz);
        a.resize(n);b.resize(n);ntt_(a,0,mod,g);ntt_(b,0,mod,g);
        rep(i,n)a[i]=a[i]*b[i]%mod;ntt_(a,1,mod,g);a.resize(sz);return a;
    }
    vc<ll> conv(const vc<ll>&a,const vc<ll>&b,ll mod){
        auto r1=conv1(a,b,M1,3),r2=conv1(a,b,M2,3),r3=conv1(a,b,M3,3);
        int n=si(r1); vc<ll> res(n);
        ll i12=inv(M1,M2),i123=inv(M1*M2%M3,M3);
        rep(i,n){
            ll x1=r1[i]%M1;
            ll x2=(r2[i]-x1%M2+M2)%M2*i12%M2;
            ll x3=((r3[i]-x1%M3+M3)%M3-(x2%M3)*M1%M3+M3)%M3*i123%M3;
            res[i]=((x1+x2*M1)%mod+x3*(M1%mod)%(mod)*(M2%mod))%mod;
        }
        return res;
    }
}

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §8  NUMBER THEORY                                               ║
// ╚══════════════════════════════════════════════════════════════════╝
ll gcd(ll a,ll b){ while(b){a%=b;swap(a,b);} return a; }
ll lcm(ll a,ll b){ return a/gcd(a,b)*b; }
ll extgcd(ll a,ll b,ll&x,ll&y){
    if(!b){x=1;y=0;return a;}
    ll x1,y1,g=extgcd(b,a%b,x1,y1);
    x=y1; y=x1-(a/b)*y1; return g;
}
// mod inverse (mod must be prime)
ll modinv(ll a,ll m){ ll x,y; extgcd(a,m,x,y); return (x%m+m)%m; }

// CRT: x≡r1 (mod m1), x≡r2 (mod m2)
pair<ll,ll> crt(ll r1,ll m1,ll r2,ll m2){
    ll x,y,g=extgcd(m1,m2,x,y);
    if((r2-r1)%g)return{-1,-1};
    ll lcm_=m1/g*m2;
    ll ans=(r1+m1*((r2-r1)/g%(m2/g)*x%(m2/g)))%lcm_;
    return{(ans+lcm_)%lcm_,lcm_};
}
// General CRT for vector of (r,m)
pair<ll,ll> crt_all(vc<pair<ll,ll>> congruences){
    ll r=0,m=1;
    for(auto[ri,mi]:congruences){
        auto[ans,lcm_]=crt(r,m,ri,mi);
        if(ans==-1)return{-1,-1};
        r=ans; m=lcm_;
    }
    return{r,m};
}

// Euler phi (single)
ll euler_phi(ll n){
    ll r=n;
    for(ll i=2;i*i<=n;i++) if(n%i==0){ r-=r/i; while(n%i==0)n/=i; }
    if(n>1)r-=r/n;
    return r;
}

// Linear sieve: primes + smallest prime factor
struct Sieve {
    int n; vi sp,primes;
    Sieve(int n):n(n),sp(n+1,0){
        rng(i,2,n+1){
            if(!sp[i]){sp[i]=i;primes.pb(i);}
            for(int p:primes){if(p>sp[i]||ll(i)*p>n)break;sp[i*p]=p;}
        }
    }
    bool isprime(int x){ return x>=2&&sp[x]==x; }
    vi factorize(int x){ vi r; while(x>1){r.pb(sp[x]);x/=sp[x];} return r; }
    vi factorize_unique(int x){ vi r; while(x>1){int p=sp[x];r.pb(p);while(x%p==0)x/=p;} return r; }
    // Euler's totient table
    vi phi_table(){
        vi phi(n+1); iota(all(phi),0);
        rng(i,2,n+1) if(sp[i]==i)
            for(int j=i;j<=n;j+=i) phi[j]=phi[j]/i*(i-1);
        return phi;
    }
    // Mobius function
    vi mobius_table(){
        vi mu(n+1,0); mu[1]=1;
        for(int p:primes){
            for(int j=p;j<=n;j+=p)   mu[j]-=1;
            for(ll j=ll(p)*p;j<=n;j+=ll(p)*p) mu[j]=0;
        }
        return mu;
    }
    // Divisor sum table (sum of divisors)
    vi sigma_table(){
        vi sig(n+1,0);
        rng(i,1,n+1)for(int j=i;j<=n;j+=i)sig[j]+=i;
        return sig;
    }
    // All divisors of x
    vi divisors(int x){
        vi r; for(int i=1;(ll)i*i<=x;i++) if(x%i==0){r.pb(i);if(i!=x/i)r.pb(x/i);} soin(r); return r;
    }
}; // Sieve sieve(2e6);

// Miller-Rabin primality test (deterministic up to 3.3e24)
namespace MR {
    using ull=unsigned long long;
    ull mulmod(ull a,ull b,ull m){ return (__uint128_t)a*b%m; }
    ull powmod(ull a,ull b,ull m){ ull r=1;a%=m;while(b){if(b&1)r=mulmod(r,a,m);a=mulmod(a,a,m);b>>=1;}return r; }
    bool miller(ull n,ull a){
        if(n%a==0)return n==a;
        ull d=n-1;int r=0;while(d%2==0){d/=2;r++;}
        ull x=powmod(a,d,n);
        if(x==1||x==n-1)return true;
        rep(i,r-1){x=mulmod(x,x,n);if(x==n-1)return true;}
        return false;
    }
    bool isprime(ull n){
        if(n<2)return false;
        for(ull a:{2,3,5,7,11,13,17,19,23,29,31,37})
            if(n!=a&&!miller(n,a))return false;
        return true;
    }
}

// Pollard rho factorization
namespace PR {
    using ull=unsigned long long;
    ull mul(ull a,ull b,ull m){ return (__uint128_t)a*b%m; }
    ull pw(ull a,ull b,ull m){ ull r=1;a%=m;while(b){if(b&1)r=mul(r,a,m);a=mul(a,a,m);b>>=1;}return r;}
    ull rho(ull n){
        if(n%2==0)return 2;
        ull x=rand_int(1,n-1),c=rand_int(1,n-1),y=x,d=1;
        auto f=[&](ull v){return(mul(v,v,n)+c)%n;};
        while(d==1){x=f(x);y=f(f(y));d=__gcd(x>y?x-y:y-x,n);}
        return d==n?rho(n):d;
    }
    void factorize(ull n,vc<ull>&res){
        if(n==1)return;
        if(MR::isprime(n)){res.pb(n);return;}
        ull d=n; while(d==n)d=rho(n);
        factorize(d,res); factorize(n/d,res);
    }
    vc<ull> factorize(ull n){ vc<ull> r; factorize(n,r); soin(r); return r; }
    vc<ull> divisors(ull n){
        auto f=factorize(n);
        vc<ull> d={1};
        for(int i=0;i<si(f);){
            int j=i; while(j<si(f)&&f[j]==f[i])j++;
            int cnt=si(d);
            ull pw=1;
            rng(k,i,j){pw*=f[i];rep(l,cnt)d.pb(d[l]*pw);}
            i=j;
        }
        soin(d); return d;
    }
    // Returns map prime -> exponent
    map<ull,int> factorize_map(ull n){
        auto f=factorize(n);
        map<ull,int> r;
        for(ull p:f)r[p]++;
        return r;
    }
}

// Baby-step Giant-step for discrete log: find x s.t. a^x = b (mod p)
// Returns -1 if no solution
ll discrete_log(ll a,ll b,ll p){
    a%=p; b%=p;
    if(b==1||p==1)return 0;
    ll sq=(ll)sqrtl(p)+1;
    unordered_map<ll,ll> table;
    ll cur=b;
    rep(j,sq){ table[cur]=j; cur=cur*a%p; }
    ll step=1; rep(_,sq)step=step*a%p;
    cur=1;
    rng(i,1,sq+1){
        cur=cur*step%p;
        if(table.count(cur)) return i*sq-table[cur];
    }
    return -1;
}

// nth root mod p (Tonelli-Shanks for square root)
ll sqrt_mod(ll n,ll p){
    if(n==0)return 0;
    if(p==2)return n&1;
    auto pw=[&](ll a,ll b)->ll{ll r=1;a%=p;while(b){if(b&1)r=r*a%p;a=a*a%p;b>>=1;}return r;};
    if(pw(n,(p-1)/2)!=1)return -1; // not a QR
    if(p%4==3)return pw(n,(p+1)/4);
    ll q=p-1,s=0; while(q%2==0){q/=2;s++;}
    ll z=2; while(pw(z,(p-1)/2)!=p-1)z++;
    ll m=s,c=pw(z,q),t=pw(n,q),r=pw(n,(q+1)/2);
    while(true){
        if(t==1)return r;
        ll i=1,tmp=t*t%p; while(tmp!=1){tmp=tmp*tmp%p;i++;}
        ll b=pw(c,pw(2,m-i-1,p-1)); // 2^(m-i-1) mod p-1
        m=i; c=b*b%p; t=t*c%p; r=r*b%p;
    }
}

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §9  HASHING                                                     ║
// ╚══════════════════════════════════════════════════════════════════╝
struct safe_hash {
    static ull splitmix64(ull x){
        x+=0x9e3779b97f4a7c15; x=(x^(x>>30))*0xbf58476d1ce4e5b9;
        x=(x^(x>>27))*0x94d049bb133111eb; return x^(x>>31);
    }
    size_t operator()(ull x)const{
        static const ull FIXED=chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x+FIXED);
    }
    size_t operator()(pair<ull,ull> p)const{ return operator()(p.first)^(operator()(p.second)<<32); }
};
template<class T,class U> using safe_map=unordered_map<T,U,safe_hash>;
template<class T>          using safe_set=unordered_set<T,safe_hash>;

// Polynomial rolling hash (double hash to avoid collisions)
struct StringHash {
    static const ll M1=1e9+7,M2=1e9+9,B1=131,B2=137;
    int n; vc<ll> h1,h2,p1,p2;
    StringHash(){}
    StringHash(const string&s):n(si(s)),h1(n+1,0),h2(n+1,0),p1(n+1,1),p2(n+1,1){
        rep(i,n){
            h1[i+1]=(h1[i]*B1+s[i])%M1; h2[i+1]=(h2[i]*B2+s[i])%M2;
            p1[i+1]=p1[i]*B1%M1;         p2[i+1]=p2[i]*B2%M2;
        }
    }
    pair<ll,ll> get(int l,int r){ // [l,r)
        return{(h1[r]-h1[l]*p1[r-l]%M1+M1*2)%M1,
               (h2[r]-h2[l]*p2[r-l]%M2+M2*2)%M2};
    }
};

// 2D grid hash
struct GridHash {
    static const ll M=1e9+7,B=100003,C=200003;
    vvc<ll> h; vc<ll> pb_,pc_;
    GridHash(const vvc<int>&g){
        int n=si(g),m=si(g[0]);
        h.assign(n+1,vc<ll>(m+1,0));
        pb_.resize(n+1);pc_.resize(m+1);
        pb_[0]=pc_[0]=1;
        rep(i,n)pb_[i+1]=pb_[i]*B%M;
        rep(j,m)pc_[j+1]=pc_[j]*C%M;
        rep(i,n)rep(j,m)h[i+1][j+1]=(h[i+1][j]+h[i][j+1]-h[i][j]+g[i][j]*pb_[i+1]%M*pc_[j+1])%M+M;
        rep(i,n+1)rep(j,m+1)h[i][j]%=M;
    }
    ll get(int r1,int c1,int r2,int c2){ // [r1,r2)x[c1,c2)
        return(h[r2][c2]-h[r1][c2]-h[r2][c1]+h[r1][c1]%M+M*2)%M;
    }
};

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §10  DATA STRUCTURES                                            ║
// ╚══════════════════════════════════════════════════════════════════╝

// ── Fenwick Tree (BIT) ──────────────────────────────────────────────
template<class T> struct BIT {
    int n; vc<T> d;
    BIT(){}
    BIT(int n):n(n),d(n+1,T(0)){}
    BIT(vc<T> a):n(si(a)),d(n+1,T(0)){ rep(i,n) add(i,a[i]); }
    void add(int i,T v){ for(i++;i<=n;i+=i&-i)d[i]+=v; }
    T sum(int i){ T s=0; for(i++;i>0;i-=i&-i)s+=d[i]; return s; }
    T sum(int l,int r){ return sum(r-1)-(l?sum(l-1):T(0)); } // [l,r)
    int kth(T k){ // 0-indexed, values must be non-negative
        int x=0;
        for(int pw=1<<topbit(n);pw;pw>>=1)
            if(x+pw<=n&&d[x+pw]<=k)k-=d[x+=pw];
        return x;
    }
};

// ── 2D BIT ─────────────────────────────────────────────────────────
template<class T> struct BIT2D {
    int n,m; vvc<T> d;
    BIT2D(int n,int m):n(n),m(m),d(n+1,vc<T>(m+1,0)){}
    void add(int x,int y,T v){for(int i=x+1;i<=n;i+=i&-i)for(int j=y+1;j<=m;j+=j&-j)d[i][j]+=v;}
    T sum(int x,int y){T s=0;for(int i=x+1;i>0;i-=i&-i)for(int j=y+1;j>0;j-=j&-j)s+=d[i][j];return s;}
    T sum(int x1,int y1,int x2,int y2){ return sum(x2-1,y2-1)-sum(x1-1,y2-1)-sum(x2-1,y1-1)+sum(x1-1,y1-1); }
};

// ── Segment Tree ────────────────────────────────────────────────────
template<class T,T(*op)(T,T),T(*e)()> struct segtree {
    int n,sz,log; vc<T> d;
    segtree(){}
    segtree(int n):n(n){sz=1;log=0;while(sz<n)sz<<=1,log++;d.assign(2*sz,e());}
    segtree(vc<T>&a):segtree(si(a)){rep(i,si(a))d[i+sz]=a[i];gnr(i,1,sz)d[i]=op(d[2*i],d[2*i+1]);}
    void set(int p,T x){p+=sz;d[p]=x;for(int i=1;i<=log;i++)d[p>>i]=op(d[(p>>i)<<1],d[((p>>i)<<1)|1]);}
    T query(int l,int r){T sl=e(),sr=e();l+=sz;r+=sz;while(l<r){if(l&1)sl=op(sl,d[l++]);if(r&1)sr=op(d[--r],sr);l>>=1;r>>=1;}return op(sl,sr);}
    T operator[](int i){return d[i+sz];}
    // Walk on segment tree: find first pos in [l,n) where f returns true
    // f is monotone on the segment tree
    int walk_right(int l,auto f){
        // O(log n), f(e()) must be false
        function<int(int,int,int,T)> rec=[&](int node,int nl,int nr,T carry)->int{
            if(nr<=l)return -1;
            if(!f(op(carry,d[node])))return -1;
            if(nl+1==nr)return nl;
            int mid=(nl+nr)/2;
            int res=rec(2*node,nl,mid,carry);
            if(res!=-1)return res;
            return rec(2*node+1,mid,nr,op(carry,d[2*node]));
        };
        return rec(1,0,sz,e());
    }
};

// ── Lazy Segment Tree ───────────────────────────────────────────────
template<class S,S(*op)(S,S),S(*e)(),class F,S(*mapping)(F,S),F(*cp)(F,F),F(*id)()>
struct lazysegtree {
    int n,sz,log; vc<S> d; vc<F> lz;
    lazysegtree(){}
    lazysegtree(int n):n(n){sz=1;log=0;while(sz<n)sz<<=1,log++;d.assign(2*sz,e());lz.assign(sz,id());}
    lazysegtree(vc<S>&a):lazysegtree(si(a)){rep(i,si(a))d[i+sz]=a[i];gnr(i,1,sz)d[i]=op(d[2*i],d[2*i+1]);}
    void set(int p,S x){p+=sz;push(p>>1);d[p]=x;for(int i=1;i<=log;i++)d[p>>i]=op(d[(p>>i)<<1],d[((p>>i)<<1)|1]);}
    S get(int p){p+=sz;for(int i=log;i>=1;i--)push(p>>i);return d[p];}
    S query(int l,int r){
        if(l==r)return e();
        l+=sz;r+=sz;
        for(int i=log;i>=1;i--){if(((l>>i)<<i)!=l)push(l>>i);if(((r>>i)<<i)!=r)push((r-1)>>i);}
        S sl=e(),sr=e();
        while(l<r){if(l&1)sl=op(sl,d[l++]);if(r&1)sr=op(d[--r],sr);l>>=1;r>>=1;}
        return op(sl,sr);
    }
    void apply(int p,F f){p+=sz;for(int i=log;i>=1;i--)push(p>>i);d[p]=mapping(f,d[p]);for(int i=1;i<=log;i++)d[p>>i]=op(d[(p>>i)<<1],d[((p>>i)<<1)|1]);}
    void apply(int l,int r,F f){
        if(l==r)return; l+=sz;r+=sz;
        for(int i=log;i>=1;i--){if(((l>>i)<<i)!=l)push(l>>i);if(((r>>i)<<i)!=r)push((r-1)>>i);}
        int l2=l,r2=r;
        while(l<r){if(l&1)apply_at(l++,f);if(r&1)apply_at(--r,f);l>>=1;r>>=1;}
        l=l2;r=r2;
        for(int i=1;i<=log;i++){if(((l>>i)<<i)!=l)d[l>>i]=op(d[(l>>i)<<1],d[((l>>i)<<1)|1]);if(((r>>i)<<i)!=r)d[(r-1)>>i]=op(d[((r-1)>>i)<<1],d[(((r-1)>>i)<<1)|1]);}
    }
    void apply_at(int k,F f){d[k]=mapping(f,d[k]);if(k<sz)lz[k]=cp(f,lz[k]);}
    void push(int k){if(lz[k]!=id()){apply_at(2*k,lz[k]);apply_at(2*k+1,lz[k]);lz[k]=id();}}
};

// ── Sparse Table (O(n log n) build, O(1) query) ─────────────────────
template<class T,T(*op)(T,T)> struct SparseTable {
    vvc<T> st;
    SparseTable(){}
    SparseTable(const vc<T>&a){
        int n=si(a),k=topbit(n)+1;
        st.assign(k,vc<T>(n));
        st[0]=a;
        rng(i,1,k) rep(j,n-(1<<i)+1)
            st[i][j]=op(st[i-1][j],st[i-1][j+(1<<(i-1))]);
    }
    T query(int l,int r){ int i=topbit(r-l); return op(st[i][l],st[i][r-(1<<i)]); }
};

// ── Persistent Segment Tree ─────────────────────────────────────────
template<class T,T(*op)(T,T),T(*e)()> struct PersistSegtree {
    struct Node{ T val; int l,r; };
    vc<Node> t; vi roots;
    PersistSegtree(){ t.pb({e(),0,0}); }
    int new_node(){ t.pb({e(),0,0}); return si(t)-1; }
    int build(int l,int r,const vc<T>&a){
        int node=new_node();
        if(l+1==r){t[node].val=a[l];return node;}
        int mid=(l+r)/2;
        t[node].l=build(l,mid,a); t[node].r=build(mid,r,a);
        t[node].val=op(t[t[node].l].val,t[t[node].r].val);
        return node;
    }
    int update(int prev,int l,int r,int pos,T val){
        int node=new_node(); t[node]=t[prev];
        if(l+1==r){t[node].val=val;return node;}
        int mid=(l+r)/2;
        if(pos<mid)t[node].l=update(t[prev].l,l,mid,pos,val);
        else        t[node].r=update(t[prev].r,mid,r,pos,val);
        t[node].val=op(t[t[node].l].val,t[t[node].r].val);
        return node;
    }
    T query(int node,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr)return t[node].val;
        if(ql>=r||qr<=l)return e();
        int mid=(l+r)/2;
        return op(query(t[node].l,l,mid,ql,qr),query(t[node].r,mid,r,ql,qr));
    }
    // Merge two trees (for small-to-large or offline)
    int merge(int u,int v,int l,int r){
        if(!u)return v; if(!v)return u;
        int node=new_node();
        if(l+1==r){t[node].val=op(t[u].val,t[v].val);return node;}
        int mid=(l+r)/2;
        t[node].l=merge(t[u].l,t[v].l,l,mid);
        t[node].r=merge(t[u].r,t[v].r,mid,r);
        t[node].val=op(t[t[node].l].val,t[t[node].r].val);
        return node;
    }
};

// ── DSU (Union-Find) ────────────────────────────────────────────────
struct DSU {
    vi p,s; int c;
    DSU(int n):p(n,-1),s(n,1),c(n){}
    int find(int a){ return p[a]==-1?a:(p[a]=find(p[a])); }
    bool unite(int a,int b){
        a=find(a);b=find(b);if(a==b)return false;
        if(s[a]<s[b])swap(a,b);
        p[b]=a;s[a]+=s[b];c--;return true;
    }
    bool same(int a,int b){ return find(a)==find(b); }
    int sz(int a){ return s[find(a)]; }
    vi components(){ // returns representative of each component
        vi r; rep(i,si(p)) if(p[i]==-1)r.pb(i); return r;
    }
};

// ── DSU with Rollback ────────────────────────────────────────────────
struct RollbackDSU {
    vi p,s; int c;
    vc<tuple<int,int,int,int,int>> hist;
    RollbackDSU(int n):p(n,-1),s(n,1),c(n){}
    int find(int a){ return p[a]==-1?a:find(p[a]); }
    bool unite(int a,int b){
        a=find(a);b=find(b);
        hist.eb(a,p[a],s[a],b,c);
        if(a==b)return false;
        if(s[a]<s[b])swap(a,b);
        p[b]=a;s[a]+=s[b];c--;return true;
    }
    void rollback(){
        auto[a,pa,sa,b,cc]=hist.back();hist.pop_back();
        if(a!=b){p[b]=-1;s[a]=sa;}
        c=cc;
    }
    int save(){ return si(hist); }
    void rollback_to(int t){ while(si(hist)>t)rollback(); }
};

// ── Weighted DSU ─────────────────────────────────────────────────────
// Maintains potential: weight[v] = dist from v to root
// Use for "difference constraints" or bipartite checks
struct WeightedDSU {
    vi p; vc<ll> w; vi s;
    WeightedDSU(int n):p(n,-1),w(n,0),s(n,1){}
    pair<int,ll> find(int a){ // returns {root, weight to root}
        if(p[a]==-1)return{a,0};
        auto[r,wr]=find(p[a]);
        w[a]+=wr; p[a]=r;
        return{r,w[a]};
    }
    // Unite: weight[a] - weight[b] = d  (a is heavier by d)
    bool unite(int a,int b,ll d){
        auto[ra,wa]=find(a); auto[rb,wb]=find(b);
        if(ra==rb)return wa-wb==d;
        d=d+wb-wa;
        if(s[ra]<s[rb]){swap(ra,rb);d=-d;}
        p[rb]=ra; w[rb]=d; s[ra]+=s[rb]; return true;
    }
    ll diff(int a,int b){ auto[ra,wa]=find(a); auto[rb,wb]=find(b); return wa-wb; }
};

// ── Li Chao Tree (CHT for min/max of lines) ─────────────────────────
struct LiChao {
    struct Line{ ll m,b; ll eval(ll x)const{return m*x+b;} };
    struct Node{ Line line; int l,r; };
    vc<Node> t; vi xs;
    LiChao(vi _xs):xs(_xs){ t.pb({{0,infLL},-1,-1}); }
    void add_line(int node,int lo,int hi,Line line){
        int mid=(lo+hi)/2;
        bool lef=(line.eval(xs[lo])<t[node].line.eval(xs[lo]));
        bool midd=(line.eval(xs[mid])<t[node].line.eval(xs[mid]));
        if(midd)swap(t[node].line,line);
        if(lo+1==hi)return;
        if(lef!=midd){if(t[node].l<0){t.pb({{0,infLL},-1,-1});t[node].l=si(t)-1;}add_line(t[node].l,lo,mid,line);}
        else          {if(t[node].r<0){t.pb({{0,infLL},-1,-1});t[node].r=si(t)-1;}add_line(t[node].r,mid,hi,line);}
    }
    void add(Line line){ add_line(0,0,si(xs),line); }
    void add(ll m,ll b){ add({m,b}); }
    ll query(int node,int lo,int hi,int idx){
        ll res=t[node].line.eval(xs[idx]);
        if(lo+1==hi)return res;
        int mid=(lo+hi)/2;
        if(idx<mid&&t[node].l>=0)chmin(res,query(t[node].l,lo,mid,idx));
        if(idx>=mid&&t[node].r>=0)chmin(res,query(t[node].r,mid,hi,idx));
        return res;
    }
    ll query(int idx){ return query(0,0,si(xs),idx); }
};

// ── Monotone CHT ─────────────────────────────────────────────────────
struct ConvexHullTrick {
    struct Line{ ll m,b; };
    deque<Line> hull;
    bool bad(Line l1,Line l2,Line l3){
        return (__int128)(l3.b-l1.b)*(l1.m-l2.m)<=(__int128)(l2.b-l1.b)*(l1.m-l3.m);
    }
    void add(ll m,ll b){ // decreasing slope for min hull
        Line l={m,b};
        while(si(hull)>=2&&bad(hull[hull.size()-2],hull.back(),l))hull.pop_back();
        hull.pb(l);
    }
    ll query(ll x){ // increasing x for min
        while(si(hull)>1&&hull[0].m*x+hull[0].b>=hull[1].m*x+hull[1].b)hull.pop_front();
        return hull[0].m*x+hull[0].b;
    }
    ll query_max(ll x){ // for max hull (use if slopes increasing)
        while(si(hull)>1&&hull[0].m*x+hull[0].b<=hull[1].m*x+hull[1].b)hull.pop_front();
        return hull[0].m*x+hull[0].b;
    }
};

// ── Implicit Treap (RBST) ─────────────────────────────────────────────
struct Treap {
    struct Node{ int pri,sz; ll val,lazy; int l,r; };
    vc<Node> t;
    int new_node(ll val){ t.pb({(int)rand_int(1e9),1,val,0,-1,-1}); return si(t)-1; }
    int sz(int v){ return v<0?0:t[v].sz; }
    void push(int v){
        if(v<0||!t[v].lazy)return;
        auto upd=[&](int c){ if(c>=0){t[c].val+=t[v].lazy;t[c].lazy+=t[v].lazy;} };
        upd(t[v].l);upd(t[v].r);t[v].lazy=0;
    }
    void pull(int v){ if(v>=0)t[v].sz=1+sz(t[v].l)+sz(t[v].r); }
    pair<int,int> split(int v,int k){
        if(v<0)return{-1,-1};
        push(v);
        if(sz(t[v].l)>=k){auto[l,r]=split(t[v].l,k);t[v].l=r;pull(v);return{l,v};}
        else{auto[l,r]=split(t[v].r,k-sz(t[v].l)-1);t[v].r=l;pull(v);return{v,r};}
    }
    int merge(int u,int v){
        if(u<0)return v;if(v<0)return u;
        push(u);push(v);
        if(t[u].pri>t[v].pri){t[u].r=merge(t[u].r,v);pull(u);return u;}
        else{t[v].l=merge(u,t[v].l);pull(v);return v;}
    }
    void range_add(int&root,int l,int r,ll val){
        auto[t1,t2]=split(root,l);auto[t3,t4]=split(t2,r-l);
        if(t3>=0){t[t3].val+=val;t[t3].lazy+=val;}
        root=merge(t1,merge(t3,t4));
    }
    void insert(int&root,int pos,ll val){ int nd=new_node(val);auto[l,r]=split(root,pos);root=merge(merge(l,nd),r); }
    void erase(int&root,int pos){ auto[l,r]=split(root,pos);auto[m,rr]=split(r,1);root=merge(l,rr); }
    void reverse(int&root,int l,int r);  // add flip lazy if needed
};

// ── Wavelet Tree (kth, count ≤ x in range) ───────────────────────────
struct WaveletTree {
    int lo,hi; WaveletTree *left=nullptr,*right=nullptr;
    vi b; // prefix count going left at this node
    void build(vi::iterator from,vi::iterator to,int lo,int hi){
        this->lo=lo;this->hi=hi;
        if(lo==hi||from>=to)return;
        int mid=(lo+hi)/2;
        b.reserve(to-from+1); b.pb(0);
        for(auto it=from;it!=to;it++) b.pb(b.back()+(*it<=mid));
        auto pivot=stable_partition(from,to,[mid](int x){return x<=mid;});
        left=new WaveletTree(); left->build(from,pivot,lo,mid);
        right=new WaveletTree(); right->build(pivot,to,mid+1,hi);
    }
    // kth smallest in [l,r] (1-indexed k)
    int kth(int l,int r,int k){
        if(lo==hi)return lo;
        int inLeft=b[r]-b[l-1];
        if(k<=inLeft)return left->kth(b[l-1]+1,b[r],k);
        return right->kth(l-b[l-1],r-b[r],k-inLeft);
    }
    // count of elements ≤ x in [l,r]
    int countLeq(int l,int r,int x){
        if(lo==hi)return x>=lo?(r-l+1):0;
        int mid=(lo+hi)/2;
        if(x<=mid)return left?left->countLeq(b[l-1]+1,b[r],x):0;
        int fromLeft=b[r]-b[l-1];
        return fromLeft+(right?right->countLeq(l-b[l-1],r-b[r],x):0);
    }
};

// ── Sqrt Decomposition ────────────────────────────────────────────────
struct SqrtDecomp {
    int n,block; vi a,sum;
    SqrtDecomp(vi a_):n(si(a_)),block(max(1LL,(ll)sqrtl(n))),a(a_),sum((n-1)/max(1LL,(ll)sqrtl(n))+1,0){
        rep(i,n)sum[i/block]+=a[i];
    }
    void update(int i,int val){ sum[i/block]+=val-a[i]; a[i]=val; }
    ll query(int l,int r){
        ll res=0;
        for(int i=l;i<=min(r,(l/block+1)*block-1);i++)res+=a[i];
        for(int b=l/block+1;b<r/block;b++)res+=sum[b];
        if(l/block<r/block)for(int i=r/block*block;i<=r;i++)res+=a[i];
        return res;
    }
};

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §11  GRAPH ALGORITHMS                                           ║
// ╚══════════════════════════════════════════════════════════════════╝

// ── Dijkstra ─────────────────────────────────────────────────────────
vi dijkstra(const vvc<pi>&g,int s){
    int n=si(g); vi dist(n,infLL);
    priority_queue<pi,vc<pi>,greater<pi>> pq;
    dist[s]=0;pq.push({0,s});
    while(!pq.empty()){auto[d,v]=pq.top();pq.pop();if(d>dist[v])continue;for(auto[u,w]:g[v])if(chmin(dist[u],dist[v]+w))pq.push({dist[u],u});}
    return dist;
}
vi dijkstra(const vvc<pi>&g,vi src){
    int n=si(g); vi dist(n,infLL);
    priority_queue<pi,vc<pi>,greater<pi>> pq;
    for(int s:src){dist[s]=0;pq.push({0,s});}
    while(!pq.empty()){auto[d,v]=pq.top();pq.pop();if(d>dist[v])continue;for(auto[u,w]:g[v])if(chmin(dist[u],dist[v]+w))pq.push({dist[u],u});}
    return dist;
}

// ── Bellman-Ford ──────────────────────────────────────────────────────
vi bellman_ford(const vc<ti3>&edges,int n,int s){
    vi dist(n,infLL); dist[s]=0;
    rep(i,n-1)for(auto[u,v,w]:edges)if(dist[u]!=infLL)chmin(dist[v],dist[u]+w);
    return dist;
}
// Returns true if there's a negative cycle reachable from s
bool has_neg_cycle(const vc<ti3>&edges,int n,vi dist){
    for(auto[u,v,w]:edges) if(dist[u]!=infLL&&dist[u]+w<dist[v])return true;
    return false;
}

// ── Floyd-Warshall ────────────────────────────────────────────────────
vvi floyd(int n,vvi cost){
    rep(k,n)rep(i,n)rep(j,n)
        if(cost[i][k]!=infLL&&cost[k][j]!=infLL)
            chmin(cost[i][j],cost[i][k]+cost[k][j]);
    return cost;
}

// ── SCC (Kosaraju) ────────────────────────────────────────────────────
struct SCC {
    int n; vvc<int> g,rg; vi comp; vc<bool> vis;
    SCC(int n):n(n),g(n),rg(n),comp(n,-1),vis(n){}
    void add(int u,int v){g[u].pb(v);rg[v].pb(u);}
    int build(){
        vi order;
        rep(s,n){
            if(vis[s])continue;
            stack<pair<int,int>> st; st.push({s,0}); vis[s]=1;
            while(!st.empty()){
                auto&[v,i]=st.top();
                if(i<si(g[v])){ int u=g[v][i++]; if(!vis[u]){vis[u]=1;st.push({u,0});} }
                else{ order.pb(v); st.pop(); }
            }
        }
        int k=0;
        per(i,si(order)){
            int s=order[i]; if(comp[s]>=0)continue;
            stack<int> st; st.push(s); comp[s]=k;
            while(!st.empty()){int v=st.top();st.pop();for(int u:rg[v])if(comp[u]<0){comp[u]=k;st.push(u);}}
            k++;
        }
        return k;
    }
    vvc<int> dag(int k){
        vvc<int> d(k);
        rep(u,n)for(int v:g[u])if(comp[u]!=comp[v])d[comp[u]].pb(comp[v]);
        for(auto&row:d)mkuni(row);
        return d;
    }
};

// ── Bridges & Articulation Points ─────────────────────────────────────
struct BridgeAP {
    int n; vvc<int> g; vi num,low,ap; vc<pi> bridges; int timer=0;
    BridgeAP(int n):n(n),g(n),num(n,-1),low(n){}
    void add(int u,int v){g[u].pb(v);g[v].pb(u);}
    void dfs(int v,int p){
        num[v]=low[v]=timer++;int child=0;
        for(int u:g[v]){
            if(num[u]<0){child++;dfs(u,v);chmin(low[v],low[u]);if(low[u]>=num[v])ap.pb(v);if(low[u]>num[v])bridges.pb({v,u});}
            else if(u!=p)chmin(low[v],num[u]);
        }
        if(p<0&&child<=1)ap.pop_back();
    }
    void build(){rep(i,n)if(num[i]<0)dfs(i,-1);mkuni(ap);}
};

// ── Dinic Max Flow ────────────────────────────────────────────────────
struct Dinic {
    struct Edge{int to,rev;ll cap;};
    int n; vvc<Edge> g; vi level,iter;
    Dinic(int n):n(n),g(n),level(n),iter(n){}
    int add(int u,int v,ll cap){
        int id=si(g[u]);
        g[u].pb({v,(int)si(g[v]),cap});
        g[v].pb({u,id,0});
        return id;
    }
    void add_bidi(int u,int v,ll cap){ add(u,v,cap); add(v,u,cap); } // undirected
    bool bfs(int s,int t){
        fila(level,-1);queue<int>q;level[s]=0;q.push(s);
        while(!q.empty()){int v=q.front();q.pop();for(auto&e:g[v])if(e.cap>0&&level[e.to]<0){level[e.to]=level[v]+1;q.push(e.to);}}
        return level[t]>=0;
    }
    ll dfs(int v,int t,ll f){
        if(v==t)return f;
        for(int&i=iter[v];i<si(g[v]);i++){
            auto&e=g[v][i];
            if(e.cap>0&&level[v]<level[e.to]){ll d=dfs(e.to,t,min(f,e.cap));if(d>0){e.cap-=d;g[e.to][e.rev].cap+=d;return d;}}
        }
        return 0;
    }
    ll max_flow(int s,int t){ll fl=0;while(bfs(s,t)){fila(iter,0);ll d;while((d=dfs(s,t,infLL))>0)fl+=d;}return fl;}
    ll get_cap(int u,int id){ return g[u][id].cap; }
    // Min-cut: after max_flow, nodes reachable from s in residual are on s-side
    vc<bool> min_cut_side(int s){
        vc<bool> vis(n); queue<int> q; q.push(s); vis[s]=1;
        while(!q.empty()){int v=q.front();q.pop();for(auto&e:g[v])if(e.cap>0&&!vis[e.to]){vis[e.to]=1;q.push(e.to);}}
        return vis;
    }
};

// ── Min-Cost Max-Flow (SPFA) ──────────────────────────────────────────
struct MCMF {
    struct Edge{int to,rev;ll cap,cost;};
    int n; vvc<Edge> g; vi prevv,preve; vc<ll> dist; vc<bool> inq;
    MCMF(int n):n(n),g(n),prevv(n),preve(n),dist(n),inq(n){}
    void add(int u,int v,ll cap,ll cost){
        g[u].pb({v,(int)si(g[v]),cap,cost});
        g[v].pb({u,(int)si(g[u])-1,0,-cost});
    }
    pair<ll,ll> min_cost_flow(int s,int t,ll f=infLL){
        ll flow=0,cost=0;
        while(f>0){
            fila(dist,infLL);dist[s]=0;fila(inq,false);inq[s]=true;
            queue<int>q;q.push(s);
            while(!q.empty()){
                int v=q.front();q.pop();inq[v]=false;
                for(int i=0;i<si(g[v]);i++){auto&e=g[v][i];if(e.cap>0&&dist[e.to]>dist[v]+e.cost){dist[e.to]=dist[v]+e.cost;prevv[e.to]=v;preve[e.to]=i;if(!inq[e.to]){inq[e.to]=true;q.push(e.to);}}}
            }
            if(dist[t]==infLL)break;
            ll d=f;
            for(int v=t;v!=s;v=prevv[v])chmin(d,g[prevv[v]][preve[v]].cap);
            f-=d;flow+=d;cost+=d*dist[t];
            for(int v=t;v!=s;v=prevv[v]){g[prevv[v]][preve[v]].cap-=d;g[v][g[prevv[v]][preve[v]].rev].cap+=d;}
        }
        return{flow,cost};
    }
};

// ── Hopcroft-Karp ──────────────────────────────────────────────────────
struct HopcroftKarp {
    int L,R; vvc<int> g; vi matchL,matchR,dist_;
    HopcroftKarp(int L,int R):L(L),R(R),g(L),matchL(L,-1),matchR(R,-1),dist_(L){}
    void add(int u,int v){g[u].pb(v);}
    bool bfs(){
        queue<int>q;fila(dist_,-1);
        for(int u=0;u<L;u++)if(!~matchL[u]){dist_[u]=0;q.push(u);}
        bool found=false;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v:g[u]){int w=matchR[v];if(w<0)found=true;else if(dist_[w]<0){dist_[w]=dist_[u]+1;q.push(w);}}
        }
        return found;
    }
    bool dfs(int u){
        for(int v:g[u]){int w=matchR[v];if(w<0||dist_[w]==dist_[u]+1&&dfs(w)){matchL[u]=v;matchR[v]=u;return true;}}
        dist_[u]=-1;return false;
    }
    int solve(){int r=0;while(bfs())rep(u,L)if(!~matchL[u])r+=dfs(u);return r;}
};

// ── Heavy-Light Decomposition ──────────────────────────────────────────
struct HLD {
    int n,timer=0; vi sz,dep,par,top,in,out,ord;
    vvc<int> g;
    HLD(int n):n(n),sz(n),dep(n),par(n,-1),top(n),in(n),out(n),ord(n),g(n){}
    void add(int u,int v){g[u].pb(v);g[v].pb(u);}
    void dfs_sz(int v,int p,int d){
        par[v]=p;dep[v]=d;sz[v]=1;
        if(si(g[v])&&g[v][0]==p)swap(g[v][0],g[v].back());
        for(int&u:g[v]){if(u==p)continue;dfs_sz(u,v,d+1);sz[v]+=sz[u];if(sz[u]>sz[g[v][0]])swap(u,g[v][0]);}
    }
    void dfs_hld(int v,int t){
        top[v]=t;in[v]=timer;ord[timer++]=v;
        for(int u:g[v])if(u!=par[v])dfs_hld(u,u==g[v][0]?t:u);
        out[v]=timer;
    }
    void build(int root=0){dfs_sz(root,-1,0);dfs_hld(root,root);}
    void path(int u,int v,auto f){
        for(;top[u]!=top[v];){if(dep[top[u]]<dep[top[v]])swap(u,v);f(in[top[u]],in[u]+1);u=par[top[u]];}
        if(dep[u]>dep[v])swap(u,v); f(in[u],in[v]+1);
    }
    void path_edges(int u,int v,auto f){
        for(;top[u]!=top[v];){if(dep[top[u]]<dep[top[v]])swap(u,v);f(in[top[u]],in[u]+1);u=par[top[u]];}
        if(dep[u]>dep[v])swap(u,v); if(in[u]+1<=in[v])f(in[u]+1,in[v]+1);
    }
    int lca(int u,int v){
        for(;top[u]!=top[v];){if(dep[top[u]]<dep[top[v]])swap(u,v);u=par[top[u]];}
        return dep[u]<dep[v]?u:v;
    }
    int dist(int u,int v){return dep[u]+dep[v]-2*dep[lca(u,v)];}
    bool is_anc(int u,int v){return in[u]<=in[v]&&out[v]<=out[u];}
    // kth vertex on path u->v
    int kth_on_path(int u,int v,int k){
        int l=lca(u,v);
        int du=dep[u]-dep[l],dv=dep[v]-dep[l];
        if(k<=du){ /* walk from u towards l */ return kth_anc(u,k); }
        else return kth_anc(v,du+dv-k);
    }
    int kth_anc(int u,int k){
        // naive; replace with binary lifting for O(log n)
        while(k){
            int steps=min(k,dep[u]-dep[top[u]]);
            if(steps<k){k-=steps+1;u=par[top[u]];}
            else{ // go up steps within chain
                return ord[in[u]-k];  // in HLD, chain is contiguous
            }
        }
        return u;
    }
};

// ── LCA (Binary Lifting) ───────────────────────────────────────────────
struct LCA {
    int n,LOG; vvc<int> up; vi tin,tout,dep; int timer=0;
    LCA(const vvc<int>&g,int root=0):n(si(g)),LOG(topbit(n)+2),up(n,vi(LOG+1)),tin(n),tout(n),dep(n){dfs(g,root,root,0);}
    void dfs(const vvc<int>&g,int v,int p,int d){
        tin[v]=++timer;dep[v]=d;up[v][0]=p;
        rng(i,1,LOG+1)up[v][i]=up[up[v][i-1]][i-1];
        for(int u:g[v])if(u!=p)dfs(g,u,v,d+1);
        tout[v]=++timer;
    }
    bool is_anc(int u,int v){return tin[u]<=tin[v]&&tout[u]>=tout[v];}
    int get(int u,int v){
        if(is_anc(u,v))return u;if(is_anc(v,u))return v;
        per(i,LOG+1)if(!is_anc(up[u][i],v))u=up[u][i];
        return up[u][0];
    }
    int kth_anc(int u,int k){ per(i,LOG+1)if(k>>i&1)u=up[u][i]; return u; }
    int dist(int u,int v){return dep[u]+dep[v]-2*dep[get(u,v)];}
};

// ── Centroid Decomposition ─────────────────────────────────────────────
struct CentDecomp {
    int n; vvc<int> g; vi sz,par; vc<bool> rem;
    CentDecomp(int n):n(n),g(n),sz(n),par(n,-1),rem(n){}
    void add(int u,int v){g[u].pb(v);g[v].pb(u);}
    int get_sz(int v,int p){sz[v]=1;for(int u:g[v])if(u!=p&&!rem[u])sz[v]+=get_sz(u,v);return sz[v];}
    int get_centroid(int v,int p,int s){for(int u:g[v])if(u!=p&&!rem[u]&&sz[u]>s/2)return get_centroid(u,v,s);return v;}
    void build(int v,int p){
        int c=get_centroid(v,-1,get_sz(v,-1));
        par[c]=p;rem[c]=1;
        for(int u:g[c])if(!rem[u])build(u,c);
    }
};

// ── Euler Tour / Topological Sort / Tree utilities ─────────────────────
vi toposort(const vvc<int>&g){
    int n=si(g); vi indeg(n,0);
    rep(u,n)for(int v:g[u])indeg[v]++;
    queue<int>q; rep(i,n)if(!indeg[i])q.push(i);
    vi order;
    while(!q.empty()){int v=q.front();q.pop();order.pb(v);for(int u:g[v])if(!--indeg[u])q.push(u);}
    return order; // empty if cycle
}

// ── 2-SAT ──────────────────────────────────────────────────────────────
struct TwoSat {
    int n; vvc<int> g; vi val;
    TwoSat(int n):n(n),g(2*n),val(n){}
    void add(int x,bool vx,int y,bool vy){g[2*x+!vx].pb(2*y+vy);g[2*y+!vy].pb(2*x+vx);}
    void add_clause(int x,bool vx){ add(x,vx,x,vx); }
    void must(int x,bool vx){ add_clause(x,vx); }
    void at_most_one(vi xs){ // at most one of xs[i] is true
        int n=si(xs); if(n<=1)return;
        // prefix vars: p[i] = xs[0] OR ... OR xs[i]
        // Use pairwise encoding for small n
        rep(i,n)rng(j,i+1,n) add(xs[i],true,xs[j],false);
    }
    bool solve(){
        SCC scc(2*n);
        rep(u,2*n)for(int v:g[u])scc.add(u,v);
        scc.build();
        rep(i,n){if(scc.comp[2*i]==scc.comp[2*i+1])return false;val[i]=(scc.comp[2*i]>scc.comp[2*i+1]);}
        return true;
    }
};

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §12  STRINGS                                                    ║
// ╚══════════════════════════════════════════════════════════════════╝
vi z_function(const string&s){
    int n=si(s);vi z(n);z[0]=n;
    for(int i=1,l=0,r=0;i<n;i++){
        if(i<r)z[i]=min(r-i,z[i-l]);
        while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
        if(i+z[i]>r)l=i,r=i+z[i];
    }
    return z;
}

vi kmp_fail(const string&s){
    int n=si(s);vi f(n);
    for(int i=1,j=0;i<n;i++){while(j&&s[i]!=s[j])j=f[j-1];f[i]=j+=(s[i]==s[j]);}
    return f;
}
vi kmp_match(const string&text,const string&pat){
    string s=pat+"#"+text; vi f=kmp_fail(s),res; int m=si(pat);
    rng(i,m+1,si(s))if(f[i]==m)res.pb(i-2*m);
    return res;
}

// Manacher
vi manacher(const string&s){
    string t="#";for(char c:s){t+=c;t+='#';}
    int n=si(t); vi p(n,0);
    for(int i=0,l=0,r=0;i<n;i++){
        if(i<r)p[i]=min(r-i,p[l+r-i]);
        while(i-p[i]-1>=0&&i+p[i]+1<n&&t[i-p[i]-1]==t[i+p[i]+1])p[i]++;
        if(i+p[i]>r){l=i-p[i];r=i+p[i];}
    }
    return p;
}
// longest palindromic substring length
int longest_palindrome(const string&s){ auto p=manacher(s); return *max_element(all(p)); }

// Suffix Array (O(n log n))
vi suffix_array(const string&s){
    int n=si(s)+1;vi sa(n),rk(n),tmp(n);
    iota(all(sa),0);
    rep(i,n)rk[i]=(i<si(s)?s[i]:0);
    for(int k=1;k<n;k<<=1){
        auto cmp=[&](int a,int b){if(rk[a]!=rk[b])return rk[a]<rk[b];int ra=a+k<n?rk[a+k]:-1,rb=b+k<n?rk[b+k]:-1;return ra<rb;};
        sort(all(sa),cmp);
        tmp[sa[0]]=0;rng(i,1,n)tmp[sa[i]]=tmp[sa[i-1]]+(cmp(sa[i-1],sa[i])?1:0);
        rk=tmp;
    }
    return sa;
}
vi lcp_array(const string&s,const vi&sa){
    int n=si(s);vi rk(n),lcp(n-1);
    rep(i,n)rk[sa[i+1]-1]=i;
    for(int i=0,h=0;i<n;i++){if(rk[i]){int j=sa[rk[i]];while(i+h<n&&j+h<n&&s[i+h]==s[j+h])h++;lcp[rk[i]-1]=h;if(h)h--;}}
    return lcp;
}

// Aho-Corasick
struct AhoCorasick {
    vvc<int> ch; vi fail,cnt; int n=1;
    AhoCorasick():ch(1,vi(26,-1)),fail(1,0),cnt(1,0){}
    int insert(const string&s){
        int v=0;
        for(char c:s){int x=c-'a';if(ch[v][x]<0){ch.pb(vi(26,-1));fail.pb(0);cnt.pb(0);ch[v][x]=n++;}v=ch[v][x];}
        cnt[v]++;
        return v;
    }
    void build(){
        queue<int>q;
        rep(c,26)if(ch[0][c]>=0)q.push(ch[0][c]);
        while(!q.empty()){
            int v=q.front();q.pop();cnt[v]+=cnt[fail[v]];
            rep(c,26){if(ch[v][c]>=0){fail[ch[v][c]]=ch[fail[v]][c];q.push(ch[v][c]);}else ch[v][c]=ch[fail[v]][c];}
        }
    }
    int query(const string&s){int v=0,res=0;for(char c:s){v=ch[v][c-'a'];res+=cnt[v];}return res;}
};

// Eertree / Palindromic Tree
struct PalinTree {
    struct Node{ int len,suf; int ch[26]; };
    vc<Node> t; vi suf_link; int last,n;
    string s;
    PalinTree(){
        t.pb({-1,0,{}}); // root -1 (imaginary)
        t.pb({0,0,{}});   // root 0 (empty)
        last=1; n=0;
        memset(t[0].ch,-1,sizeof(t[0].ch));
        memset(t[1].ch,-1,sizeof(t[1].ch));
    }
    int get_link(int v){
        while(n-t[v].len-2<0||s[n-t[v].len-2]!=s[n-1])v=t[v].suf;
        return v;
    }
    bool add(char c){
        s+=c; n++;
        int cur=get_link(last);
        int ch=c-'a';
        if(t[cur].ch[ch]==-1){
            Node node; node.len=t[cur].len+2;
            memset(node.ch,-1,sizeof(node.ch));
            int tmp=get_link(t[cur].suf); node.suf=t[tmp].ch[ch];
            if(node.suf==-1)node.suf=1;
            t[cur].ch[ch]=si(t);
            t.pb(node);
        }
        last=t[cur].ch[ch];
        return t[last].suf==last; // new palindrome?
    }
};

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §13  LINEAR ALGEBRA                                             ║
// ╚══════════════════════════════════════════════════════════════════╝
template<class T,int N> struct Matrix {
    array<array<T,N>,N> a{};
    Matrix operator*(const Matrix&o)const{
        Matrix r;
        rep(i,N)rep(k,N)if(a[i][k])rep(j,N)r.a[i][j]+=a[i][k]*o.a[k][j];
        return r;
    }
    static Matrix I(){ Matrix r; rep(i,N)r.a[i][i]=T(1); return r; }
    Matrix pow(ll n)const{ Matrix r=I(),b=*this; while(n){if(n&1)r=r*b;b=b*b;n>>=1;} return r; }
    vc<T> apply(const vc<T>&v)const{
        vc<T> r(N,T(0)); rep(i,N)rep(j,N)r[i]+=a[i][j]*v[j]; return r;
    }
};

template<class T>
int gauss(vvc<T>&a,int n,int m){
    int r=0;
    rep(c,m){
        int pivot=-1;
        rng(i,r,n)if(a[i][c]!=T(0)){pivot=i;break;}
        if(pivot<0)continue;
        swap(a[r],a[pivot]);
        T inv=T(1)/a[r][c];
        rep(j,m)a[r][j]*=inv;
        rep(i,n)if(i!=r&&a[i][c]!=T(0)){T f=a[i][c];rep(j,m)a[i][j]-=f*a[r][j];}
        r++;
    }
    return r;
}

template<int MAXN>
int gauss_gf2(vc<bitset<MAXN>>&a,int n,int m){
    int r=0;
    rep(c,m){
        int pivot=-1;
        rng(i,r,n)if(a[i][c]){pivot=i;break;}
        if(pivot<0)continue;
        swap(a[r],a[pivot]);
        rep(i,n)if(i!=r&&a[i][c])a[i]^=a[r];
        r++;
    }
    return r;
}

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §14  ALGORITHMS                                                 ║
// ╚══════════════════════════════════════════════════════════════════╝

// ── Berlekamp-Massey ──────────────────────────────────────────────────
vi berlekamp_massey(vi s){
    vi cur,lst; int lf=0,ld=0;
    rep(i,si(s)){
        ll t=0;rep(j,si(cur))t=(t+cur[j]*s[i-1-j])%998244353;
        if((s[i]-t)%998244353==0)continue;
        if(cur.empty()){cur.resize(i+1);lf=i;ld=s[i]-t;continue;}
        ll k=-(s[i]-t)*Mint<998244353>(ld).inv().v%998244353;
        vi c(i-lf-1);c.pb(k);
        for(ll x:lst)c.pb(-x*k%998244353);
        if(c.size()<cur.size())c.resize(cur.size());
        rep(j,si(cur))c[j]=(c[j]+cur[j])%998244353;
        if(i-lf+si(lst)>=si(cur)){lst=cur;lf=i;ld=s[i]-t;}
        cur=c;
    }
    for(auto&x:cur)x=(x%998244353+998244353)%998244353;
    return cur;
}

// ── Mo's Algorithm ────────────────────────────────────────────────────
struct Mo {
    int n,Q,block;
    vc<array<int,3>> queries;
    Mo(int n,int Q):n(n),Q(Q),block(max(1LL,(ll)sqrtl(n))){}
    void add_query(int l,int r,int idx){ queries.pb({l,r,idx}); }
    void solve(auto add_left,auto add_right,auto rem_left,auto rem_right,auto get_ans,vi&ans){
        soin(queries,[&](const auto&a,const auto&b){
            int ba=a[0]/block,bb=b[0]/block;
            if(ba!=bb)return ba<bb;
            return (ba&1)?a[1]>b[1]:a[1]<b[1];
        });
        int l=0,r=-1;
        for(auto[ql,qr,qi]:queries){
            while(r<qr)add_right(++r);
            while(l>ql)add_left(--l);
            while(r>qr)rem_right(r--);
            while(l<ql)rem_left(l++);
            ans[qi]=get_ans();
        }
    }
};

// ── Mo on Trees ────────────────────────────────────────────────────────
// Flatten tree via Euler tour, handle path queries with Mo

// ── Divide and Conquer DP ─────────────────────────────────────────────
// dp[i][j] = min over k in [optl,optr] of (prev[k] + cost(k,j))
void dc_dp(vi&dp,const vi&prev_dp,int l,int r,int optl,int optr,auto cost){
    if(l>r)return;
    int mid=(l+r)/2,opt=optl;
    rng(k,optl,optr+1){
        ll val=prev_dp[k]+cost(k,mid);
        if(val<dp[mid]){dp[mid]=val;opt=k;}
    }
    dc_dp(dp,prev_dp,l,mid-1,optl,opt,cost);
    dc_dp(dp,prev_dp,mid+1,r,opt,optr,cost);
}

// ── Parallel Binary Search ────────────────────────────────────────────
template<class Check>
vi parallel_bs(int Q,ll lo,ll hi,Check check){
    vi ans(Q,hi);vc<pair<ll,ll>> range(Q,{lo,hi});
    rep(iter,60){
        map<ll,vc<int>> mq;
        rep(i,Q)if(range[i].first<range[i].second)mq[(range[i].first+range[i].second)/2].pb(i);
        if(mq.empty())break;
        for(auto&[mid,qs]:mq){
            check(mid,qs,[&](int i,bool ok){
                if(ok){range[i].second=mid;ans[i]=mid;}
                else  range[i].first=mid+1;
            });
        }
    }
    return ans;
}

// ── Alien Trick (WQS Binary Search) ──────────────────────────────────
// For "pick exactly k items from DP" where cost is convex in k
// Binary search on penalty lambda; adjust and track item count
// Use: f(lambda) = unconstrained DP with -lambda per item
// Find lambda s.t. item count == k

// ── SMAWK (Totally Monotone Matrix Searching) — O(n+m) ──────────────
// For when opt(i) <= opt(i+1) in a totally monotone matrix

// ── Knuth's Optimization ─────────────────────────────────────────────
// dp[i][j] = min over i<=k<j of dp[i][k]+dp[k+1][j]+w[i][j]
// Require: w satisfies quadrangle inequality
// opt[i][j] in [opt[i][j-1], opt[i+1][j]]
// O(n^2)

// ── SOS DP (Sum over Subsets) ─────────────────────────────────────────
// f[mask] = sum of a[sub] for all sub of mask
vi sos_dp(vi a,int bits){
    rep(i,bits) rep(mask,1<<bits) if(mask>>i&1) a[mask]+=a[mask^(1<<i)];
    return a;
}
// f[mask] = sum of a[sup] for all sup of mask (super)
vi sos_dp_super(vi a,int bits){
    rep(i,bits) rep(mask,1<<bits) if(!(mask>>i&1)) a[mask]+=a[mask|(1<<i)];
    return a;
}
// XOR convolution via Walsh-Hadamard Transform
void wht(vi&a,bool inv){
    int n=si(a);
    for(int len=1;len<n;len<<=1)
        for(int i=0;i<n;i+=2*len)
            rep(j,len){ ll u=a[i+j],v=a[i+j+len]; a[i+j]=u+v; a[i+j+len]=u-v; }
    if(inv){ int ni=modinv(n,MOD1); for(auto&x:a)x=x*ni%MOD1; }
}
// OR convolution
void or_conv(vi&a,bool inv){
    int n=si(a);
    for(int len=1;len<n;len<<=1)
        for(int i=0;i<n;i+=2*len)
            rep(j,len) if(!inv)a[i+j+len]+=a[i+j]; else a[i+j+len]-=a[i+j];
}

// ── Grundy / Sprague-Nimber ────────────────────────────────────────────
// mex of a set
int mex(set<int>&s){ int r=0; while(s.count(r))r++; return r; }
int mex(vi& a){ set<int>s(all(a)); return mex(s); }

// ── Slope Trick ───────────────────────────────────────────────────────
// Maintain piecewise-linear convex function via two priority queues
struct SlopeTrick {
    ll offset=0;
    priority_queue<ll> L; // max-heap: slopes to left of min
    priority_queue<ll,vc<ll>,greater<ll>> R; // min-heap: slopes to right of min
    ll min_val=0;
    void push_L(ll x){ L.push(x); }
    void push_R(ll x){ R.push(x); }
    // Add max(0, x-a) to f  (ramp up at a)
    void add_right_ramp(ll a){
        push_R(a);
        if(L.size()&&L.top()>R.top()){
            ll l=L.top(),r=R.top(); L.pop();R.pop();
            min_val+=l-r; push_L(r); push_R(l);
        }
    }
    // Add max(0, a-x) to f  (ramp down at a)
    void add_left_ramp(ll a){
        push_L(a);
        if(R.size()&&L.top()>R.top()){
            ll l=L.top(),r=R.top(); L.pop();R.pop();
            min_val+=l-r; push_L(r); push_R(l);
        }
    }
    // Add |x - a| to f
    void add_abs(ll a){ add_left_ramp(a); add_right_ramp(a); }
    // Slide L by -inf, R by +inf (prefix min from left)
    void shift_L(ll a){ offset+=a; } // shift all L points by a
    void extend_flat(ll l,ll r){ push_L(l); push_R(r); } // add flat region
    ll query(){ return min_val; }
};

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §15  GEOMETRY                                                   ║
// ╚══════════════════════════════════════════════════════════════════╝
struct Pt {
    ld x,y;
    Pt(ld x=0,ld y=0):x(x),y(y){}
    Pt operator+(Pt o)const{return{x+o.x,y+o.y};}
    Pt operator-(Pt o)const{return{x-o.x,y-o.y};}
    Pt operator*(ld t)const{return{x*t,y*t};}
    Pt operator/(ld t)const{return{x/t,y/t};}
    ld dot(Pt o)const{return x*o.x+y*o.y;}
    ld cross(Pt o)const{return x*o.y-y*o.x;}
    ld norm()const{return x*x+y*y;}
    ld abs()const{return sqrtl(norm());}
    Pt rot(ld t)const{return{x*cosl(t)-y*sinl(t),x*sinl(t)+y*cosl(t)};}
    Pt rot90()const{return{-y,x};}
    Pt unit()const{return *this/abs();}
    bool operator<(Pt o)const{return x<o.x-EPS||(fabsl(x-o.x)<EPS&&y<o.y-EPS);}
    bool operator==(Pt o)const{return fabsl(x-o.x)<EPS&&fabsl(y-o.y)<EPS;}
    friend istream&operator>>(istream&is,Pt&p){return is>>p.x>>p.y;}
    friend ostream&operator<<(ostream&os,Pt p){return os<<p.x<<" "<<p.y;}
};
// Polar angle sort (CCW from positive x-axis)
bool polar_cmp(Pt a,Pt b){
    int ha=(a.y<0||(a.y==0&&a.x<0));
    int hb=(b.y<0||(b.y==0&&b.x<0));
    if(ha!=hb)return ha<hb;
    ld cr=a.cross(b);
    if(fabsl(cr)>EPS)return cr>0;
    return a.norm()<b.norm();
}

int sign(ld x){ return x>EPS?1:x<-EPS?-1:0; }

bool on_segment(Pt p,Pt a,Pt b){ return sign((b-a).cross(p-a))==0&&sign((p-a).dot(p-b))<=0; }
int seg_intersect(Pt a,Pt b,Pt c,Pt d){
    ld d1=(b-a).cross(c-a),d2=(b-a).cross(d-a);
    ld d3=(d-c).cross(a-c),d4=(d-c).cross(b-c);
    if(sign(d1)*sign(d2)<0&&sign(d3)*sign(d4)<0)return 1;
    if(on_segment(c,a,b)||on_segment(d,a,b)||on_segment(a,c,d)||on_segment(b,c,d))return -1;
    return 0;
}
Pt line_intersect(Pt a,Pt b,Pt c,Pt d){
    ld s=(c-a).cross(d-c)/((b-a).cross(d-c));
    return a+(b-a)*s;
}
ld dist_point_seg(Pt p,Pt a,Pt b){
    if(sign((b-a).dot(p-a))<=0)return(p-a).abs();
    if(sign((a-b).dot(p-b))<=0)return(p-b).abs();
    return fabsl((b-a).cross(p-a))/(b-a).abs();
}

// Point in polygon (winding number, O(n))
int winding(vc<Pt>&poly,Pt p){
    int w=0,n=si(poly);
    rep(i,n){
        Pt a=poly[i]-p,b=poly[(i+1)%n]-p;
        if(a.y<=0&&b.y>0&&a.cross(b)>0)w++;
        else if(b.y<=0&&a.y>0&&a.cross(b)<0)w--;
    }
    return w; // 0 = outside, !=0 = inside
}

vc<Pt> convex_hull(vc<Pt> pts){
    int n=si(pts),k=0; soin(pts);
    if(n<3)return pts;
    vc<Pt> H(2*n);
    rep(i,n){while(k>=2&&sign((H[k-1]-H[k-2]).cross(pts[i]-H[k-2]))<=0)k--;H[k++]=pts[i];}
    for(int i=n-2,t=k+1;i>=0;i--){while(k>=t&&sign((H[k-1]-H[k-2]).cross(pts[i]-H[k-2]))<=0)k--;H[k++]=pts[i];}
    H.resize(k-1);return H;
}

ld polygon_area(const vc<Pt>&poly){
    ld s=0;int n=si(poly);
    rep(i,n)s+=poly[i].cross(poly[(i+1)%n]);
    return s/2;
}

bool point_in_convex(const vc<Pt>&poly,Pt p){
    int n=si(poly);
    if(sign((poly[1]-poly[0]).cross(p-poly[0]))<0)return false;
    if(sign((poly[n-1]-poly[0]).cross(p-poly[0]))>0)return false;
    int lo=1,hi=n-1;
    while(hi-lo>1){int mid=(lo+hi)/2;if(sign((poly[mid]-poly[0]).cross(p-poly[0]))>=0)lo=mid;else hi=mid;}
    return sign((poly[lo+1]-poly[lo]).cross(p-poly[lo]))>=0;
}

// Minkowski sum of two convex hulls
vc<Pt> minkowski(vc<Pt> P,vc<Pt> Q){
    // Rotate to start at bottom-most
    auto rot_start=[](vc<Pt>&hull){
        auto it=min_element(all(hull));
        rotate(hull.begin(),it,hull.end());
    };
    rot_start(P);rot_start(Q);
    int n=si(P),m=si(Q);
    P.pb(P[0]);P.pb(P[1]);Q.pb(Q[0]);Q.pb(Q[1]);
    vc<Pt> res;
    int i=0,j=0;
    while(i<n||j<m){
        res.pb(P[i]+Q[j]);
        Pt ep=P[i+1]-P[i],eq=Q[j+1]-Q[j];
        ld cr=ep.cross(eq);
        if(cr>0)i++; else if(cr<0)j++; else{i++;j++;}
    }
    return res;
}

struct Circle{Pt c;ld r;};
Circle mec(vc<Pt> pts){
    myshuffle(pts);int n=si(pts);
    Circle d={pts[0],0};
    rep(i,n)if((pts[i]-d.c).abs()>d.r+EPS){
        d={pts[i],0};
        rep(j,i)if((pts[j]-d.c).abs()>d.r+EPS){
            d={(pts[i]+pts[j])/2,((pts[i]-pts[j])/2).abs()};
            rep(k,j)if((pts[k]-d.c).abs()>d.r+EPS){
                Pt a=pts[j]-pts[i],b=pts[k]-pts[i];
                ld D=2*(a.x*b.y-a.y*b.x);
                if(fabsl(D)<EPS)continue;
                ld ux=(b.y*a.norm()-a.y*b.norm())/D;
                ld uy=(a.x*b.norm()-b.x*a.norm())/D;
                Pt ctr=pts[i]+Pt(ux,uy);
                d={ctr,Pt(ux,uy).abs()};
            }
        }
    }
    return d;
}

ld convex_diameter(const vc<Pt>&hull){
    int n=si(hull);if(n==1)return 0;if(n==2)return(hull[1]-hull[0]).abs();
    ld res=0;int j=1;
    rep(i,n){
        while((hull[(i+1)%n]-hull[i]).cross(hull[(j+1)%n]-hull[j])>0)j=(j+1)%n;
        chmax(res,(hull[i]-hull[j]).abs());
        chmax(res,(hull[(i+1)%n]-hull[(j+1)%n]).abs());
    }
    return res;
}

// Half-plane intersection (sorted by angle)
struct HalfPlane {
    Pt p,d; // point on boundary, direction vector (left side is inside)
    ld angle;
    HalfPlane(Pt p,Pt d):p(p),d(d),angle(atan2l(d.y,d.x)){}
    bool operator<(const HalfPlane&o)const{ return angle<o.angle; }
    bool on_left(Pt q)const{ return d.cross(q-p)>-EPS; }
};
vc<Pt> half_plane_isect(vc<HalfPlane> hps){
    sort(all(hps));
    int n=si(hps),lo=0,hi=-1;
    vc<HalfPlane> dq(n); vc<Pt> pts(n);
    rep(i,n){
        while(lo<hi&&!hps[i].on_left(pts[hi]))hi--;
        while(lo<hi&&!hps[i].on_left(pts[lo+1]))lo++;
        dq[++hi]=hps[i];
        if(fabsl(dq[hi].d.cross(dq[hi-1].d))<EPS){
            hi--;
            if(hps[i].on_left(dq[hi].p))dq[hi]=hps[i];
        }
        if(lo<hi)pts[hi]=line_intersect(dq[hi].p,dq[hi].p+dq[hi].d,dq[hi-1].p,dq[hi-1].p+dq[hi-1].d);
    }
    while(lo<hi&&!dq[lo].on_left(pts[hi]))hi--;
    if(hi-lo<2)return {};
    pts[lo]=line_intersect(dq[lo].p,dq[lo].p+dq[lo].d,dq[hi].p,dq[hi].p+dq[hi].d);
    return vc<Pt>(pts.begin()+lo,pts.begin()+hi+1);
}

// 3D Point
struct Pt3{
    ld x,y,z;
    Pt3(ld x=0,ld y=0,ld z=0):x(x),y(y),z(z){}
    Pt3 operator+(Pt3 o)const{return{x+o.x,y+o.y,z+o.z};}
    Pt3 operator-(Pt3 o)const{return{x-o.x,y-o.y,z-o.z};}
    Pt3 operator*(ld t)const{return{x*t,y*t,z*t};}
    ld dot(Pt3 o)const{return x*o.x+y*o.y+z*o.z;}
    Pt3 cross(Pt3 o)const{return{y*o.z-z*o.y,z*o.x-x*o.z,x*o.y-y*o.x};}
    ld norm()const{return x*x+y*y+z*z;}
    ld abs()const{return sqrtl(norm());}
};

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §16  FAST I/O                                                   ║
// ╚══════════════════════════════════════════════════════════════════╝
struct FastReader {
    char buf[1<<22],*l=buf,*r=buf;
    char get(){ if(l==r){r=(l=buf)+fread(buf,1,1<<22,stdin);} return l==r?EOF:*l++; }
    ll read_ll(){
        ll x=0;char c=get();bool f=0;
        while(c<'0'||c>'9'){f|=(c=='-');c=get();}
        while(c>='0'&&c<='9'){x=x*10+c-'0';c=get();}
        return f?-x:x;
    }
    string read_str(){ string s; char c=get(); while(c==' '||c=='\n'||c=='\r')c=get(); while(c!=' '&&c!='\n'&&c!='\r'&&c!=EOF){s+=c;c=get();} return s; }
    void read(ll&x){ x=read_ll(); }
    void read(string&s){ s=read_str(); }
    template<class...T> void read(T&...t){ (read(t),...); }
} sc;

struct FastWriter {
    char buf[1<<22]; int p=0;
    void flush(){ fwrite(buf,1,p,stdout);p=0; }
    void write(char c){ buf[p++]=c; if(p==1<<22)flush(); }
    void write(ll x){
        if(x<0){write('-');x=-x;}
        char tmp[20];int k=0;
        do{tmp[k++]='0'+x%10;x/=10;}while(x);
        while(k--)write(tmp[k]);
    }
    void write(const string&s){ for(char c:s)write(c); }
    ~FastWriter(){ flush(); }
} pr;

template<class T,class U>
ostream&operator<<(ostream&os,const pair<T,U>&p){ return os<<"{"<<p.first<<","<<p.second<<"}"; }
template<class T> ostream&operator<<(ostream&os,const vc<T>&v){ os<<"{"; for(auto e:v)os<<e<<","; return os<<"}"; }
template<class T,size_t N> ostream&operator<<(ostream&os,const array<T,N>&a){ return os<<vc<T>(a.begin(),a.end()); }
template<int i,class T> void print_tuple(ostream&,const T&){}
template<int i,class T,class H,class...Args> void print_tuple(ostream&os,const T&t){ if(i)os<<","; os<<get<i>(t); print_tuple<i+1,T,Args...>(os,t); }
template<class...Args> ostream&operator<<(ostream&os,const tuple<Args...>&t){ os<<"{"; print_tuple<0,tuple<Args...>,Args...>(os,t); return os<<"}"; }

template<class T> void print_single(T x,int suc=1){ cout<<x; if(suc==1)cout<<"\n"; if(suc==2)cout<<" "; }
template<class T,class U> void print_single(const pair<T,U>&p,int suc=1){ print_single(p.first,2); print_single(p.second,suc); }
template<class T> void print_single(const vc<T>&v,int suc=1){ rep(i,v.size())print_single(v[i],i==int(v.size())-1?3:2); if(suc==1)cout<<"\n"; }
template<class T> void print(const T&t){ print_single(t); }
template<class T,class...Args> void print(const T&t,const Args&...args){ print_single(t,2); print(args...); }
template<class T> void printvv(const vvc<T>&vs){ for(const auto&row:vs)print(row); }

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §18  INPUT MACROS                                               ║
// ╚══════════════════════════════════════════════════════════════════╝
int current_run_id=0,run_batch_size=1000;
int calc_random_limit(){ return current_run_id/run_batch_size+1; }
template<class T> void generate_single(T&a){ a=rand_int(1,calc_random_limit()); }
void generate_single(string&a){ int n=3;a=rand_string(n,'a','c'); }
template<class T,class U> void generate_single(pair<T,U>&a){ generate_single(a.first);generate_single(a.second); }

template<class...Args> void input(Args&...a){
    if(dbg)(generate_single(a),...);
    else(cin>>...>>a);
}
namespace std{ template<class T,class U> istream&operator>>(istream&is,pair<T,U>&a){ return is>>a.first>>a.second; } }

#define INT(...)   int    __VA_ARGS__; input(__VA_ARGS__)
#define LL(...)    ll     __VA_ARGS__; input(__VA_ARGS__)
#define STR(...)   string __VA_ARGS__; input(__VA_ARGS__)
#define CHR(...)   char   __VA_ARGS__; input(__VA_ARGS__)
#define DBL(...)   double __VA_ARGS__; input(__VA_ARGS__)
#define LDD(...)   ld     __VA_ARGS__; input(__VA_ARGS__)
#define overload3(a,b,c,d,...) d
#define VI2(name,sz)        vi name(sz);        rep(i_##name,sz)input(name[i_##name]);
#define VI3(name,sz,off)    vi name(sz);        rep(i_##name,sz){input(name[i_##name]);name[i_##name]+=off;}
#define VI(...)  overload3(__VA_ARGS__,VI3,VI2)(__VA_ARGS__)
#define VPI(name,sz)        vc<pi> name(sz);    rep(i_##name,sz)input(name[i_##name].first,name[i_##name].second);
#define VVI(name,N,M)       vvi name(N,vi(M));  rep(i_##name,N)rep(j_##name,M)input(name[i_##name][j_##name]);
#define VS(name,sz)         vc<string> name(sz);rep(i_##name,sz)input(name[i_##name]);
#define overload5(a,b,c,d,e,f,...) f
#define VVC4(T,name,N,M)    vvc<T> name(N,vc<T>(M));
#define VVC5(T,name,N,M,v)  vvc<T> name(N,vc<T>(M,v));
#define VVC(...) overload5(__VA_ARGS__,VVC5,VVC4)(__VA_ARGS__)
#define VLL(name,sz)        vc<ll> name(sz);    rep(i_##name,sz)input(name[i_##name]);

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §19  GRAPH UTILITIES                                            ║
// ╚══════════════════════════════════════════════════════════════════╝
vvc<int> readGraph(int n,int m){
    vvc<int>g(n);rep(i,m){INT(a,b);a--;b--;g[a].pb(b);g[b].pb(a);}return g;
}
vvc<pi> readWeightedGraph(int n,int m){
    vvc<pi>g(n);rep(i,m){INT(a,b,w);a--;b--;g[a].pb({b,w});g[b].pb({a,w});}return g;
}
vvc<int> rand_tree(int n){
    vvc<int>t(n);DSU uf(n);
    while(uf.c>1){int a=rand_int(n),b=rand_int(n);if(uf.unite(a,b)){t[a].pb(b);t[b].pb(a);}}
    return t;
}
vvc<int> readTree(int n){ return dbg?rand_tree(n):readGraph(n,n-1); }

template<class T> using pqmin=priority_queue<T,vc<T>,greater<T>>;
template<class T> using pqmax=priority_queue<T>;

template<class T,class U> pair<T,U>&operator+=(pair<T,U>&a,pair<T,U>b){a.first+=b.first;a.second+=b.second;return a;}
template<class T,class U> pair<T,U>&operator-=(pair<T,U>&a,pair<T,U>b){a.first-=b.first;a.second-=b.second;return a;}
template<class T,class U> pair<T,U>operator+(pair<T,U>a,pair<T,U>b){return{a.first+b.first,a.second+b.second};}
template<class T,class U> pair<T,U>operator-(pair<T,U>a,pair<T,U>b){return{a.first-b.first,a.second-b.second};}
template<class T,class U,class V> pair<T,U>operator*(pair<T,U>a,V b){return{a.first*b,a.second*b};}
template<class T,class U> pair<T,U>operator-(pair<T,U>a){return{-a.first,-a.second};}

template<class T,size_t N> array<T,N>&operator+=(array<T,N>&a,const array<T,N>&b){rep(i,N)a[i]+=b[i];return a;}
template<class T,size_t N> array<T,N>&operator-=(array<T,N>&a,const array<T,N>&b){rep(i,N)a[i]-=b[i];return a;}
template<class T,size_t N> array<T,N>operator+(array<T,N>a,const array<T,N>&b){return a+=b;}
template<class T,size_t N> array<T,N>operator-(array<T,N>a,const array<T,N>&b){return a-=b;}

template<class T,class U> vc<T>&operator+=(vc<T>&a,U x){for(auto&v:a)v+=x;return a;}
template<class T,class U> vc<T>operator+(vc<T>a,U x){return a+=x;}
template<class T> vc<T>&operator+=(vc<T>&a,const vc<T>&b){a.resize(max(si(a),si(b)));rep(i,si(b))a[i]+=b[i];return a;}
template<class T> vc<T>operator+(const vc<T>&a,const vc<T>&b){vc<T>c(max(si(a),si(b)));rep(i,si(a))c[i]+=a[i];rep(i,si(b))c[i]+=b[i];return c;}
template<class T,class U> vc<T>&operator*=(vc<T>&a,U x){for(auto&v:a)v*=x;return a;}
template<class T,class U> vc<T>operator*(vc<T>a,U x){return a*=x;}

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §21  STRESS TESTING FRAMEWORK                                   ║
// ╚══════════════════════════════════════════════════════════════════╝
#ifdef LOCAL
void brute(){ /* implement naive solution here */ }
void stress(){
    dbg=true;
    rep(t,100000){
        if(t%1000==0)cerr<<"Run "<<t<<"\n";
        // TODO: capture cout, run slv() and brute(), compare
    }
}
#endif

// ╔══════════════════════════════════════════════════════════════════╗
// ║  §22  SOLUTION                                                   ║
// ╚══════════════════════════════════════════════════════════════════╝
void slv(){
    // ── write solution here ──────────────────────────────────────────
    INT(n);
    print(n);
}

signed main(signed argc,char*argv[]){
    if(argc>1&&strcmp(argv[1],"D")==0)dbg=true;
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout<<fixed<<setprecision(20);

    if(dbg){
        while(1){
            if(current_run_id%run_batch_size==0)cerr<<"Run "<<current_run_id<<"\n";
            slv();
            current_run_id++;
        }
    }else{
        INT(t); rep(_,t) slv();
    }
}
