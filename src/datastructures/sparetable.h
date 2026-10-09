const int N = 100100;
const int K = 22;

int n;
int a[N];
int rmq[N][K];

void build() {
    for(int i = 1; i <= n; ++i) {
        rmq[i][0] = a[i];
    }
    for(int k = 1; (1 << k) <= n; ++k) 
        for(int i = 1; i + (1 << (k - 1)) <= n; ++i) {
            rmq[i][k] = min(rmq[i][k - 1], rmq[i + (1 << (k - 1))][k - 1]);
        }
}
int get(int l, int r) {
    int pot = 31 - __builtin_clz(r - l + 1);
    return min(rmq[l][pot], rmq[r - (1 << pot) + 1][pot]);
}


