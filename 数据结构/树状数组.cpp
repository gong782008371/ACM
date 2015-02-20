int c[110000], n;

int lowbit(int x) 
{
	return x & (-x);
}

void update(int k, int val)
{
	while(k <= n) {
		c[k] += val;
		k += lowbit(k);
	}
}

int get_sum(int k) 
{
	int sum = 0;
	while(k > 0) {
		sum += c[k];
		k -= lowbit(k);
	}
	return sum;
}