
//************************************************
//pollard_rho �㷨�����������ֽ�
//************************************************
LL factor[100];//�������ֽ������շ���ʱ������ģ�
int tol;//�������ĸ���������С���0��ʼ

LL gcd(LL a,LL b)
{
    if(a==0)return 1;//???????
    if(a<0) return gcd(-a,b);
    while(b)
    {
        LL t=a%b;
        a=b;
        b=t;
    }
    return a;
}

LL Pollard_rho(LL x, LL c)
{
    LL i=1,k=2;
    LL x0=rand()%x;
    LL y=x0;
    while(1)
    {
        i++;
        x0=(multi(x0, x0, x) + c) % x;
        LL d=gcd(y-x0,x);
        if(d!=1&&d!=x) return d;
        if(y==x0) return x;
        if(i==k){y=x0;k+=k;}
    }
}

//��n���������ӷֽ�
void findfac(LL n)
{
    if(miller_rabin(n))//����
    {
        factor[tol++]=n;
        return;
    }
    LL p=n;
    while(p>=n)
        p=Pollard_rho(p, rand()%(n-1)+1);
    findfac(p);
    findfac(n/p);
}
