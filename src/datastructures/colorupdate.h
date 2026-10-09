#include "bits/stdc++.h"
using namespace std;

struct ColorUpdate {
    struct Seg {
        int l, r, c; 
        Seg(int l, int r, int c): l(l), r(r), c(c) {}
        bool operator < (const Seg& other) const { return l < other.l; }
        friend ostream& operator << (ostream& cout, const Seg& val) {
            return cout << "{ [" << val.l << " " << val.r << "] " << val.c << "}";
        }
    };
    set<Seg> segs;
    void cut(int x) {
        auto it = segs.lower_bound({x, 0, 0});

        if(it == segs.begin()) return; 
        --it;

        if(it->r == x - 1) return;

        Seg s = *it;
        segs.erase(s);
        segs.insert(Seg(s.l, x - 1, s.c));
        segs.insert(Seg(x, s.r, s.c));
    }

    void add(int l, int r, int c) {
        cut(l), cut(r + 1);
        Seg s(l, r, c);
        auto it = segs.lower_bound(s);
        while(it != segs.end() && it->l <= s.r) {
            auto it2 = it++;
            segs.erase(it2);
        }
        segs.insert(s);
    }

    void remove(int l, int r) {
        cut(l), cut(r + 1);
        Seg s(l, r, 0);
        auto it = segs.lower_bound(s);
        while(it != segs.end() && it->l <= s.r) {
            auto it2 = it++;
            segs.erase(it2);
        }
    }
};


// Usage:
// add(l, r, c)
// remove(l, r, c)
// cut(x)