template<class Tp>
struct MergeSortTree : vector<Tp> {
    void build() {
        n = this->size();
        st.resize((n<<2) + 1, {});
        build(1, 0, n-1);
    }
    int query(int s, int t, int from, int to) {
        return query(1, 0, n-1, s, t, from, to);
    }
    void build(int id, int l, int r) {
        if(l == r) { st[id].push_back((*this)[l]); return; }
        int mid = (l+r) >> 1;
        build(id<<1, l, mid);
        build(id<<1|1, mid+1, r);
        st[id].resize(r-l+1);
        merge(st[id << 1].begin(), st[id << 1].end(),
              st[id << 1 | 1].begin(), st[id << 1 | 1].end(),
              st[id].begin());
    }
    
    int query(int id, int l, int r, int s, int t, int from, int to) {
        if(l > t || r < s) return 0;
        if(s <= l && r <= t) 
        return upper_bound(st[id].begin(), st[id].end(), to)
        -  lower_bound(st[id].begin(), st[id].end(), from);
        int mid = (l+r) >> 1;
        return query(id<<1, l, mid, s, t, from, to) + 
        query(id<<1|1, mid+1, r, s, t, from, to);
    }

    int n;
    vector<vector<Tp>> st;
};

