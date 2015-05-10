/*********************************************************/
/**用于计算快速计算C(n, m)                              **/
/**复杂度O(logN)支持模   p>MAX_INT                      **/
/**                                                     **/
/*********************************************************/
LL mul_mod(LL a, LL b, LL p) {
    LL ans = 0;
    while(b) {
        if(b & 1) ans = (ans + a) % p;
        a <<= 1; a %= p;
        b >>= 1;
    }
    return ans;
}

LL exp_mod(LL a, LL b, LL p) {
    LL ans = 1;
    while(b) {
        if(b & 1) ans = mul_mod(ans, a, p);
        a = mul_mod(a, a, p);
        b >>= 1;
    }
    return ans;
}

//initial fact 在main的最开始部分使用
LL fact[MAXN];
void init_fact(int n, LL p) {
    fact[0] = 1;
    rep (i, 1, n) fact[i] = mul_mod(fact[i - 1], i, p);
}

//C(n, m) % p = n! * (m! * (n - m)!)^(p - 2) % p
LL C(LL n, LL m, LL p) {
    if(n < m) return 0;
    if(n == m) return 1;
    return mul_mod(fact[n], exp_mod(mul_mod(fact[m], fact[n - m], p), p - 2, p), p);
}

LL lucas(LL n, LL m, LL p) {
    LL ans = 1;
    while(n && m && ans) {
        ans = mul_mod(ans, C(n % p, m % p, p), p);
        n /= p;
        m /= p;
    }
    return ans;
}
