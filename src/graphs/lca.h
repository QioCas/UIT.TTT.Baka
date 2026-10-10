vector<int> G[N];
int ID[N << 1], tin[N], tout[N], counter = 0;

int dep[N], par[N][LOG];

void dfs(int u, int p = 0) {
    ID[ tin[u] = ++counter ] = u;
    dep[u] = dep[p] + 1;
    par[u][0] = p;
    for(int k = 1; k < LOG; ++k)
        par[u][k] = par[par[u][k - 1]][k - 1];
    for(const int& v : G[u]) 
        if(v != p) dfs(v, u);
    ID[ tout[u] = ++counter ] = u;
}

int lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for(int k = LOG - 1; k >= 0; --k)
        if(diff & MASK(k)) u = par[u][k];
    if(u == v) return u;
    for(int k = LOG - 1; k >= 0; --k)
        if(par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
    return par[u][0];
}
