const int N = 100100;

vector<int> G[N];

int timer = 0;
int tin[N], tout[N], ord[N], sz[N];

void dfs_tour(int u, int p = -1) {
    tin[u] = ++timer;
    ord[timer] = u;
    sz[u] = 1;
    for(const int& v : G[u]) 
        if(v != p) {
            dfs_tour(v, u);
            sz[u] += sz[v];
        }
    tout[u] = timer;
}

void DFS(int u, int p = -1, bool keep = false) {
    int heavy = -1;
    for(const int& v : G[u]) 
        if(v != p) {
            if(heavy == -1 || sz[heavy] < sz[v])
                heavy = v;
        }

    for(const int& v : G[u]) if(v != p && v != heavy) DFS(v, u, 0);

    if(~heavy) DFS(heavy, u, 1);

    for(const int& v : G[u]) if(v != p && v != heavy) {
        for(int i = tin[v]; i <= tout[v]; ++i) {
            // Insert(ord[i]);
        }
    }

    // Insert(u);

        
    if(!keep) {
        for(int i = tin[u]; i <= tout[u]; ++i) {
            // Remove(ord[i]);
        }
    }
}

