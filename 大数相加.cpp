//字符串操作的高精度的加法a + b = ans
//字符串保存的是两个整数的正向序列,返回的是正序结果：
//      a = 123456 b = 123456 返回  ans = 246912（都是字符串）
void HIGH_ADD(char a[], char b[], char ans[])
{
        mem0(ans);
        strrev(a);strrev(b);
        int len1 = strlen(a);
        int len2 = strlen(b);
        int len = MAX(len1, len2);
        int up = 0;
        for(int i = 0; i < len; i ++ )
        {
                int tmp = 0;
                if(i < len1) tmp += a[i] - '0';
                if(i < len2) tmp += b[i] - '0';
                tmp += up;
                ans[i] = tmp % 10 + '0';
                up = tmp / 10;
        }
        if(up) ans[len++] = up + '0';
        strrev(ans);
}

