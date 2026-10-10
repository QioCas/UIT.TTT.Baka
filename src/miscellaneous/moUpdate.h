// for(int i = 1; i <= n; ++i)
//     Bucket[i] = i / SIZE_BLOCK;

// SIZE_BLOCK = pow(n, 0.71);
// UPDATE_BLOCK = max(1.00, pow(C2, 0.71));

int P[N], Bucket[N], SIZE_BLOCK = 0, UPDATE_BLOCK = 0;
Query Q[N];
Update Q2[N];

struct Query {
    int data, l, r, t;
    tuple<int, int, int> mo() {
        return {t / UPDATE_BLOCK, ((t / UPDATE_BLOCK) & 1 ? 1 : -1) * Bucket[l], Bucket[l] & 1 ? r : -r};
    }
};

struct Update {
    int i, bef, now;
};

// iota(P + 1, P + num_q + 1, 1);
// sort(P + 1, P + num_q + 1, [&] (int u, int v) { return Q[u].mo() < Q[v].mo(); });

for(int i = 1; i <= num_q; ++i) {
    int id = P[i];

    while(timer < Q[id].t) {
        ++timer;
        update(Q2[timer].i, Q2[timer].now);
    }

    while(timer > Q[id].t) {
        update(Q2[timer].i, Q2[timer].bef);
        --timer;
    }
    while(l > Q[id].l) adding(ID[--l]);
    while(r < Q[id].r) adding(ID[++r]);
    while(l < Q[id].l) erase(ID[l++]);
    while(r > Q[id].r) erase(ID[r--]);
}