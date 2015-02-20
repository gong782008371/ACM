//Shank's Baby-Step-Gaint-Step Algorithm
//求解a ^ x = b ( mod n )这里n为素数，无解返回-1
//复杂度sqrt(n)

int log_mod(int a, int b, int n)//相当于求loga b mod n的结果（以a为底b的对数）
{
	int m, v, e = 1, i;
	m = (int)sqrt(n + 0.5);
	v = inv(pow_mod(a, m, n), n);// pow_mod(a, b, m) a^b mod m
	map<int, int> x;
	x[1] = 0;
	for(i = 0; i < m; i ++) {
		e = mul_mod(e, a, n);//mul_mod(a, b, m)a*b % m
		if(!x.count(e)) x[e] = i;
	}
	for(i = 0; i < m; i ++) {
		if(x.count(b)) return i * m + x[b];
		b = mul_mod(b, v, n);
	}
	return -1;
}