
//定义随机测试的次数
#define Times 10

//产生[0, n-1]的一个随机数
LL random(LL n)
{
    return ((double)rand() / RAND_MAX * n + 0.5);
}
//乘法，采用加法模拟，避免中间结果超出LL
LL multi(LL a,LL b,LL mod)
{
    LL ans=0;
    while(b)
    {
        if(b & 1)
        {
            b--;
            ans=(ans+a) % mod;
        }
        else
        {
            b/=2;
            a=(2*a) % mod;
        }
    }
    return ans;
}

//快速幂，同样避免超出LL的做法
LL Pow(LL a, LL b, LL mod)
{
    LL ans=1;
    while(b)
    {
        if(b&1)
        {
            b--;
            ans=multi(ans,a,mod);
        }
        else
        {
            b/=2;
            a=multi(a,a,mod);
        }
    }
    return ans;
}

//miller_rabin的一遍探测，返回false表示是合数
bool witness(LL a,LL n)
{
    LL d=n-1;
    while( !(d&1) )
        d >>= 1;
    LL t=Pow(a, d, n);
    while(d!=n-1 && t!=1 && t!=n-1)
    {
        t=multi(t,t,n);
        d<<=1;
    }
    return t==n-1 || d&1;
}

//miller_rabin算法，返回false表示是合数，否则是素数
//返回素数出错的概率(最高)为 1 / (4 ^ times)
bool miller_rabin(LL n)
{
    if(n == 2)
        return true;
    if( n<2 || !(n&1) )
        return false;
    for(int i = 1; i <= Times ; i++ )
    {
        LL a = random(n-2) + 1;
        if( !witness(a, n) )
            return false;
    }
    return true;
}
