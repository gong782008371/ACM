
//高斯消元解异或方程，如果无解返回-1，有解返回自由变元的个数
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


//高斯消元解浮点数系数方程，只有一个解时，返回这个解
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


//高斯消元解同模方程组
//下面的模为mod，系数存在a数组中，答案保存在ans数组中

int var, equ, a[MAXN][MAXN], ans[MAXN];

//扩展欧几里得求逆元
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
        for(int r = k ; r < equ; r ++)//找到最大的行
        {
            if( Max < abs(a[r][col]) )
                Max = abs( a[r][col] ), row = r;
        }
        if(row == -1)//此行 全部为0直接考虑下一列，行不变
        {
            k--;
            continue;
        }
        for(int c = col; c <= var; c ++)//初等行变换（交换两行）
            SWAP(a[k][c], a[row][c]);
        for(int r = k + 1; r < equ; r ++)//将下侧的所有不为0的系数化为0
        {
            if(a[r][col])
            {
                int lcm = LCM(abs(a[k][col]), abs(a[r][col]));
                int ta = lcm / a[r][col];
                int tb = lcm / a[k][col];
                if(a[r][col] * a[k][col] < 0) tb = -tb;
                for(int c = col; c <= var; c ++ )//初等行变换 r2 = a * r2 - b * r1
                {
                    a[r][c] = a[r][c] * ta - a[k][c] * tb;
                    a[r][c] = (a[r][c] % mod + mod) % mod;
                }
            }
        }
    }
    for(int r = k; r < equ; r ++)
    {
        if(a[r][var]) return -1;//Ax = B中，含有A为0，B不为0的行，无解
    }
    if(k < var) return 1;//矩阵的秩小于变量个数，有多解
    //否则有唯一解
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

