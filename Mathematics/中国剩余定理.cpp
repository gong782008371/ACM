void exgcd(LL a, LL b, LL& d, LL& x, LL& y)
{
    if(!b) { d = a; x = 1; y = 0; }
    else { gcd(b, a % b, d, y, x); y -= x*(a/b); }
}

//n个方程: x = a[i] ( mod m[i] ) 0 <= i < n
LL china(int n, int *a, int *m)
{
	LL M = 1, d, x = 0, y;
	for(int i = 0; i < n; i ++) M *= m[i];
	for(int i = 0; i < n; i ++) {
		LL w = M / m[i];
		exgcd(m[i], w, d, d, y);
		x = (x + y * w * a[i]) % M;
	}
	return (x + M) % M;
}
