void ex_gcd(LL a, LL b, LL& x, LL& y)
{
    if(!b) { x = 1; y = 0; }
    else { ex_gcd(b, a % b, y, x); y -= x*(a/b); }
}

//ax=1 mod(m) ·µ»Øx
LL inv(LL a, LL m)
{
    LL x, y;
    ex_gcd(a, m, x, y);
    return (x%m + m) % m;
}
