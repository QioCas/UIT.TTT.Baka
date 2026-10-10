int n;
vector<int> bit1, bit2;
/*
    updateRange(l, r, v): Moi phan tu cong them v
    rangeSum(l, r): Tong cac phan tu tu l den r
*/
 

void init(int n_init) {
	n = n_init;
	bit1.assign(n+1, 0);
	bit2.assign(n+1, 0);
}

void updatePoint(vector<int> &b, int u, int v) {
    int idx = u;
    while (idx <= n) {
        b[idx] += v;
        idx += (idx & (-idx));
    }
}
 
void updateRange(int l, int r, int v) {
    updatePoint(bit1, l, (n - l + 1) * v);
    updatePoint(bit1, r + 1, -(n - r) * v);
    updatePoint(bit2, l, v);
    updatePoint(bit2, r + 1, -v);
}
 
int getSumOnBIT(vector<int> &b, int u) {
    int idx = u, ans = 0;
    while (idx > 0) {
        ans += b[idx];
        idx -= (idx & (-idx));
    }
    return ans;
}
 
int prefixSum(int u) {
    return getSumOnBIT(bit1, u) - getSumOnBIT(bit2, u) * (n - u);
}
 
int rangeSum(int l, int r) {
    return prefixSum(r) - prefixSum(l - 1);
}

// first index a[0] + ... + a[index] >= s.
int lowerBoundPrefix(long long s) {
    int idx = 0;
    long long sum1 = 0, sum2 = 0;

    int k = 1;
    while ((k << 1) <= n) k <<= 1;

    for (; k > 0; k >>= 1) {
        int nxt = idx + k;

        if (nxt <= n) {
            long long cur1 = sum1 + bit1[nxt];
            long long cur2 = sum2 + bit2[nxt];
            long long pref = cur1 - cur2 * (n - nxt);
            if (pref < s) { idx = nxt; sum1 = cur1; sum2 = cur2; }
        }
    }

	int ans = idx + 1;
	return (ans <= n) ? ans : -1;
}