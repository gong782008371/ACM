/**************************************************
反素数：
    设g(i)为i的约数的个数，若对于任意的j<i，有
    g(j) < g(i)，则称i为反素数
    下面代码在NlogN的时间内求出N以内的反素数Max[N]，
    即N以内约数最多的数为Max[N]
    D[N]为N的约数的个数：
        D[N] = D[N / a] * (b + 1) / b
    其中a为N的一个素因子，b为a的幂，即
    GCD( N/(a^b), a ) = 1
**************************************************/

int isp[MAXN], yue[MAXN], D[MAXN], Max[MAXN];
void init()
{
    mem1(isp);yue[1] = 1;
    for(int i=2;i<MAXN;i++) if(isp[i])
    {
        for(int j=2*i;j<MAXN;j+=i)
        {
            isp[j] = 0;
            yue[j] = i;
        }
    }
    D[1] = Max[1] = 1;
    for(int i=2;i<MAXN;i++)
    {
        if(isp[i]) D[i] = 2;
        else
        {
            int last = i / yue[i];
            int b = 0, n = i;
            while(n % yue[i] == 0) b ++, n /= yue[i];
            D[i] = D[last] * (b+1) / b;
        }
        if(D[i] > D[Max[i-1]]) Max[i] = i;
        else Max[i] = Max[i-1];
    }
}
