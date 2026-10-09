int dep[N], parent[N], sz[N];
int head[N], tin[N], tout[N], idx[N], cnt = 0;

void dfs(int u) {
    sz[u] = 1;
    for(int& v : G[u]) {
        parent[v] = u;
        dep[v] = dep[u] + 1;
        G[v].erase(find(all(G[v]), u));
        dfs(v); 
        sz[u] += sz[v];
        if(sz[G[u][0]] < sz[v]) swap(G[u][0], v);
    }
}

void hld(int u, int h) {
    idx[tin[u] = ++cnt] = u;
    head[u] = h;
    for(const int& v : G[u]) 
        hld(v, G[u][0] == v ? h : v);
    tout[u] = cnt;
}

void hld_update(int u, int v, int w) {
    for(; head[u] != head[v]; v = parent[head[v]]) {
        if(dep[head[u]] > dep[head[v]]) swap(u, v);
        // update(tin[head[v]], tin[v], w);
    }
    if(dep[u] > dep[v]) swap(u, v);
    // update(tin[u], tin[v], w)
}

int hld_prod(int u, int v) {
    int ret = ?;

    for(; head[u] != head[v]; v = parent[head[v]]) {
        if(dep[head[u]] > dep[head[v]]) swap(u, v);
        // ret = op(ret, prod(tin[head[v]], tin[v]));
    }
    if(dep[u] > dep[v]) swap(u, v);
    // ret = op(ret, prod(tin[u], tin[v]))
    return ret;
}
