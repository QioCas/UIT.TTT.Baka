template<typename T> vector<T> berlekampMassey(const vector<T> &sequence) {
    int n = (int)sequence.size(), len = 0, m = 1;
    vector<T> prevBest(n), coefficients(n);
    T prevDelta = prevBest[0] = coefficients[0] = 1;
    for (int i = 0; i < n; i++, m++) {
        T delta = sequence[i];
        for (int j = 1; j <= len; j++) delta += coefficients[j] * sequence[i - j];
        if ((long long)delta == 0) continue;
        vector<T> temp = coefficients;
        T coef = delta / prevDelta;
        for (int j = m; j < n; j++) coefficients[j] -= coef * prevBest[j - m];
        if ((len << 1) <= i) 
            len = i + 1 - len, prevBest = temp, prevDelta = delta, m = 0;
    }
    coefficients.resize(len + 1);
    coefficients.erase(coefficients.begin());
    for (T &x : coefficients) x = -x;
    return coefficients;
}

template<typename T> T calcKthTerm(
    const vector<T> &coefficients, const vector<T> &sequence, long long k
) {
    assert(coefficients.size() <= sequence.size());
    int n = (int)coefficients.size();

    auto mul = [&](const vector<T> &a, const vector<T> &b) {
        vector<T> res(a.size() + b.size() - 1u);
        for (int i = 0; i < (int)a.size(); i++)
            for (int j = 0; j < (int)b.size(); j++)
                res[i + j] += a[i] * b[j];
        for (int i = (int)res.size() - 1; i >= n; i--)
            for (int j = n - 1; j >= 0; j--)    
                res[i - j - 1] += res[i] * coefficients[j];
        res.resize(min((int)res.size(), n));
        return res;
    };

    vector<T> a = (n == 1 ? vector<T>{coefficients[0]} : vector<T>{0, 1}), x{1};
    for (; k; k >>= 1) {
        if (k & 1) x = mul(x, a);
        a = mul(a, a);
    }
    x.resize(n);
    T res = 0;
    for (int i = 0; i < n; i++) res += x[i] * sequence[i];
    return res;
}

// Usual: cout << calcKthTerm(berlekampMassey(ans), ans, n) << "\n";