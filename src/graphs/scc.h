int n, m;
vector<int> adj[MAX_N];
int timeIn[MAX_N], low[MAX_N];
bool deleted[MAX_N];
int dfsTime = 0;
int numStronglyConnectedComponents = 0;
int root[MAX_N];
stack<int> st;

void dfs(int u) {
    timeIn[u] = low[u] = ++dfsTime;
    st.push(u);

    for (int v : adj[u]) {
        if (deleted[v]) continue;

        if (!timeIn[v]) {
            dfs(v);
            minimize(low[u], low[v]);
        }
        else {
            minimize(low[u], timeIn[v]);
        }
    }

    if (timeIn[u] == low[u]) {
        numStronglyConnectedComponents++;
        int v;
        do {
            v = st.top();
            st.pop();
            root[v] = u;
            deleted[v] = true;
        }
        while (v != u);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m ; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
    }

    for (int i = 1; i <= n; i++) {
        if (!timeIn[i]) {
            dfs(i);
        }
    }

    cout << numStronglyConnectedComponents;

    return 0;
}