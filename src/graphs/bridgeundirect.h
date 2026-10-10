int n, m;
vector<int> adj[MAX_N];
int low[MAX_N], timeIn[MAX_N];
int dfsTime;
vector<pii> edge;
bool used[MAX_N];
int numCau, numKhop;
 
void dfs(int u) {
    timeIn[u] = low[u] = ++dfsTime; 
 
    bool isKhop = false;
    int cnt = 0;
 
    for (int id : adj[u]) {
        if (used[id]) continue;
        used[id] = true;
        int v = edge[id].fi ^ edge[id].se ^ u;
        if (!timeIn[v]) {
            dfs(v);
            cnt++;
            minimize(low[u], low[v]);
            numCau += (low[v] > timeIn[u]);
            isKhop |= (low[v] >= timeIn[u]);
        }
        else {
            minimize(low[u], timeIn[v]);
        }
    }
 
    if (timeIn[u] > 1) {
        numKhop += isKhop;
    }
    else {
        numKhop += (cnt > 1);
    }
}

signed main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb((int) edge.size());
        adj[v].pb((int) edge.size());
        edge.pb({u, v});
    }
 
    for (int i = 1; i <= n; i++) {
        if (!timeIn[i]) {
            dfsTime = 0;
            dfs(i);
        }
    }
 
    cout << numKhop << ' ' << numCau;
 
    return 0;
}
