const int N = 200200;
const int inf = 1 << 30;
int n, m, a[N];

struct Node {
    ll sum;
    int min, max, lazy;
    Node(int u = 0): sum(u), min(u), max(u), lazy(inf) {}
    Node(ll sum, int min, int max, int lazy): sum(sum), min(min), max(max), lazy(lazy) {}
} IT[4 * N];

Node operator + (Node a, Node b) {
    return {
        a.sum + b.sum,
        min(a.min, b.min),
        max(a.max, b.max),
        inf
    };
}

#define m ((l + r) >> 1)
void Build(int id, int l, int r) {
    if(l == r) {
        IT[id] = a[l];
        return;
    }
    Build(id << 1, l, m);
    Build(id << 1 | 1, m + 1, r);
    IT[id] = IT[id << 1] + IT[id << 1 | 1];
}

void Self(int id, int l, int r, int v) {
    IT[id].max = IT[id].min = v;
    IT[id].lazy = v;
    IT[id].sum = (ll) v * (r - l + 1);
}

void Push(int id, int l, int r) {
    if(IT[id].lazy == inf || l == r) return;
    Self(id << 1, l, m, IT[id].lazy);
    Self(id << 1 | 1, m + 1, r, IT[id].lazy);
    IT[id].lazy = inf;
}

void UpdateMod(int id, int l, int r, int s, int t, int mod) {
    Push(id, l, r);
    if(l > t || r < s || IT[id].max < mod) return;
    if(s <= l && r <= t && IT[id].max == IT[id].min) {
        int v = IT[id].max % mod;
        Self(id, l, r, v);
        return;
    }
    UpdateMod(id << 1, l, m, s, t, mod);
    UpdateMod(id << 1 | 1, m + 1, r, s, t, mod);
    IT[id] = IT[id << 1] + IT[id << 1 | 1];
}

void UpdateVal(int id, int l, int r, int u, int v) {
    Push(id, l, r);
    if(l > u || r < u) return;
    if(l == r) {
        IT[id] = v;
        return;
    }
    UpdateVal(id << 1, l, m, u, v);
    UpdateVal(id << 1 | 1, m + 1, r, u, v);
    IT[id] = IT[id << 1] + IT[id << 1 | 1];
}

ll GetSum(int id, int l, int r, int s, int t) {
    Push(id, l, r);
    if(l > t || r < s) return 0;
    if(s <= l && r <= t) return IT[id].sum;
    return GetSum(id << 1, l, m, s, t) + GetSum(id << 1 | 1, m + 1, r, s, t);
}
#undef m
