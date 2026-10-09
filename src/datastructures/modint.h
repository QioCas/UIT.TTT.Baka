namespace md
{
    using T = ll; // T : int, long long
    T mod = 1e9 + 7; // <------------------------------------------------------------------------------------------------ Modulus Number.
    int m = -1;
    struct Modulus 
    {
        T x = T();
        inline void fix() { while(x >= mod) x -= mod; }
        Modulus(ll v = ll()) { x = v; fix(); }
        
        friend Modulus Mul(Modulus c, Modulus d); friend Modulus Pow(Modulus c, ll exp); friend Modulus Inv(Modulus c);
        Modulus operator + (const Modulus& c) { return Modulus(x + c.x); }
        Modulus operator - (const Modulus& c) { return Modulus(x - c.x + mod); }
        Modulus operator * (const Modulus& c) { return Mul(*this, c.x); }
        Modulus operator / (const Modulus& c) { return Mul(*this, Inv(c)); }
        bool operator == (const Modulus& c) { return x == c.x; }
        bool operator != (const Modulus& c) { return x != c.x; }

        friend istream& operator >> (istream& cin, Modulus &c) {
            cin >> c.x; c.x = c.x % mod + mod;
            return c.fix(), cin;
        }
        
        friend ostream& operator << (ostream& cout, const Modulus &c) {
            return cout << c.x;
        }
    };
    
    vector<Modulus> Fact, Invert;

    // [T = int] O(1) | [T == ll] O(log(exp))
    Modulus Mul(Modulus c, Modulus d) {
        ll exp = d.x;
        if(sizeof(T) == 4UL) return Modulus(c.x * exp % mod);
        Modulus res = 0;
        for(; exp > 0; exp >>= 1, c = c + c)
            if(exp & 1) res = res + c;
        return res;
    }
    
    // [T = int] O(log(exp)) | [T = ll] O(log(exp) * log(mod))
    Modulus Pow(Modulus c, ll exp) {
        Modulus res = 1;
        for(; exp > 0; exp >>= 1, c = c * c)
            if(exp & 1) res = res * c;
        return res;
    }

    // [c.x <= m] <O(m), O(1)> | <O(1), O(log(min(mod, c.x)))
    Modulus Inv(Modulus c) {
        if(c.x <= m) 
            return Mul(Invert[c.x], Fact[c.x - 1]);
        ll a = c.x, b = mod, ax = 1, bx = 0;
        while(b > 0) {
            ll q = a / b, r = a % b;
            a = b, b = r;
            r = ax - bx * q;
            ax = bx, bx = r;
        }
        if(ax < 0) ax += mod;
        return Modulus(ax);
    }

    // O(m)
    void BuildMOD(int M) {
        m = M;
        Fact = Invert = vector<Modulus>(m + 1, 0);
        Fact[0] = Invert[0] = 1;
        for(int i = 1; i <= m; ++i) 
            Fact[i] = Fact[i - 1] * i;
        Invert[m] = Pow(Fact[m], mod - 2);
        for(int i = m - 1; i >= 1; --i) 
            Invert[i] = Invert[i + 1] * ll(i + 1);
    }

    // <O(m), O(1))
    Modulus nCk(ll n, ll k) {
        Modulus res = 1;
        while(n != 0 or k != 0) {
            ll rn = n % mod, rk = k % mod;
            n /= mod, k /= mod;
            if(rn < rk) return 0;
            res = res * Fact[rn] / (Fact[rk] * Fact[rn - rk]);
        }
        return res;
    }
} // namespace md
using namespace md;
