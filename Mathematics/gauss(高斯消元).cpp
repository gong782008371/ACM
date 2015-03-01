
//��˹��Ԫ����򷽳̣�����޽ⷵ��-1���нⷵ�����ɱ�Ԫ�ĸ���
int gauss()
{
    int col = 0, k = 0 ;
    for(k = 0; k < equ && col < var ; k ++, col ++)
    {
        int r = k;
        for(r = k; r < equ && a[r][col] != 1; r ++ );
        if(r == equ)
        {
            k--;
            continue;
        }
        if(r != k)
            for(int c = col; c <= var; c ++)
                SWAP(a[r][c], a[k][c]);
        for(int r = k + 1; r < equ; r ++ )
            if(a[r][col])
                for(int c = col; c <= var; c ++ )
                    a[r][c] ^= a[k][c];
        }
        for(int r = k; r < equ; r ++ )
            if(a[r][var] != 0) return -1;
        return var - k;
}


//��˹��Ԫ�⸡����ϵ�����̣�ֻ��һ����ʱ�����������
void gauss()
{
    int col = 0;
    for(int k=0;k<cnt && col < cnt;k++, col ++)
    {
        double Max = fabs(a[k][col]);
        int  Maxr = k;
        for(int r = k + 1; r < cnt; r ++)
            if( fabs(a[r][col])  -  Max  >  eps  )
                Max  =  fabs( a[Maxr = r][col] );
        if(fabs(Max) < eps)  {  k --;  continue;  }
        for(int c = col;c<=cnt; c ++ )
            SWAP(a[Maxr][c],  a[k][c]  );
        for(int r = k + 1; r < cnt; r ++ ) if( fabs(a[r][col]) > eps  )
        {
            double tmp = a[r][col] / a[k][col];
            for(int c = col; c <= cnt; c ++ )
                a[r][c] -= tmp * a[k][c];
        }
    }
    for(int r=cnt-1;r>=0;r--)
    {
        for(int c = cnt-1;c>r;c--)
            a[r][cnt] -= a[r][c] * ans[c];
        ans[r] = a[r][cnt] / a[r][r];
    }
}


//��˹��Ԫ��ͬģ������
//�����ģΪmod��ϵ������a�����У��𰸱�����ans������

int var, equ, a[MAXN][MAXN], ans[MAXN];

//��չŷ���������Ԫ
void exgcd(int a, int b, int& x, int& y)
{
    if(!b) { x = 1; y = 0; }
    else { exgcd(b, a % b, y, x); y -= x*(a/b); }
}

int gauss()
{
    int x, y, k = 0, col = 0;
    for(k = 0; k < equ && col < var; k ++, col ++)
    {
        int Max = 0, row = -1;
        for(int r = k ; r < equ; r ++)//�ҵ�������
        {
            if( Max < abs(a[r][col]) )
                Max = abs( a[r][col] ), row = r;
        }
        if(row == -1)//���� ȫ��Ϊ0ֱ�ӿ�����һ�У��в���
        {
            k--;
            continue;
        }
        for(int c = col; c <= var; c ++)//�����б任���������У�
            SWAP(a[k][c], a[row][c]);
        for(int r = k + 1; r < equ; r ++)//���²�����в�Ϊ0��ϵ����Ϊ0
        {
            if(a[r][col])
            {
                int lcm = LCM(abs(a[k][col]), abs(a[r][col]));
                int ta = lcm / a[r][col];
                int tb = lcm / a[k][col];
                if(a[r][col] * a[k][col] < 0) tb = -tb;
                for(int c = col; c <= var; c ++ )//�����б任 r2 = a * r2 - b * r1
                {
                    a[r][c] = a[r][c] * ta - a[k][c] * tb;
                    a[r][c] = (a[r][c] % mod + mod) % mod;
                }
            }
        }
    }
    for(int r = k; r < equ; r ++)
    {
        if(a[r][var]) return -1;//Ax = B�У�����AΪ0��B��Ϊ0���У��޽�
    }
    if(k < var) return 1;//�������С�ڱ����������ж��
    //������Ψһ��
    for(int r = var - 1; r >= 0; r --)
    {
        int tmp = a[r][var];
        for(int c = var - 1; c > r; c -- )
        {
            tmp -= ans[c] * a[r][c] % 7;
        }
        tmp = (tmp % mod + mod) % mod;
        exgcd(a[r][r], mod, x, y);
        ans[r] = (tmp * x % mod + mod) % mod;
    }
    return 0;
}

