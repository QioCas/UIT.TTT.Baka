template<class Tp, class Index> struct FenwickTree2D : vector<pair<Index, Index>> {
    void build() {
        for(const auto&[u, v] : (*this)) {
            cx.push_back(u); cy.push_back(v);
        } cx.build(); cy.build();
        nodes.assign(int(cx.size()), vector<int>{});
        bit.assign(int(cx.size()), vector<int>{});
        for(const auto&[u, v] : (*this)) {
            fake_update(u, v);
        }
        for(int i = 0; i < int(cx.size()); ++i) {
            nodes[i].build();
            bit[i].assign(int(nodes[i].size()), 0);
        }
    }

    void add(int u, int v, Tp val) {
        assert(~u && ~v);
        for(int x = u + 1; x <= int(cx.size()); x += (x & -x)) 
            for(int y = lower_bound(begin(nodes[x - 1]), end(nodes[x - 1]), v) - begin(nodes[x - 1]) + 1; y <= int(nodes[x - 1].size()); y += (y & -y))
                bit[x - 1][y - 1] += val;
    }

    void cadd(Index u, Index v, Tp val) {
        add(cx.prod(u), cy.prod(v), val);
    }

    Tp csum(Index u, Index v) {
        return sum(cx.prod(u), cy.prod(v));
    }

    Tp csum(Index x, Index y, Index u, Index v) {
        return sum(cx.prod(x), cy.prod(y), cx.prod(u), cy.prod(v));
    }

    Tp sum(int u, int v) {
        Tp ret {};
        for(int x = u + 1; x > 0; x -= (x & -x)) 
            for(int y = upper_bound(begin(nodes[x - 1]), end(nodes[x - 1]), v) - begin(nodes[x - 1]); y > 0; y -= (y & -y))
                ret += bit[x - 1][y - 1];
        print("%d %d = %d", u, v, ret);
        return ret;
    }

    Tp sum(int x, int y, int u, int v) {
        return sum(u, v) + sum(x-1, y-1) - sum(u, y-1) - sum(x-1, v);
    }

    void fake_update(Index u, Index v) {
        u = cx.prod(u); v = cy.prod(v);
        for(++u; u <= int(cx.size()); u += (u & -u))
            nodes[u - 1].push_back(v);
    }
    vector<vector<Tp>> bit;
    Compress<Tp> cx, cy;
    vector<Compress<Tp>> nodes;
};

// Usage:
// push_back({x, y}) 
// add(x, y) cadd(x, y)
// sum(u, v) csum(u, v)
// sum(x, y, u, v) csum(x, y, u, v)