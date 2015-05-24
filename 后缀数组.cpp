//后缀数组模板，MANX为数组的大小
//支持的操作有计算后缀数组(sa数组)， 计算相邻两元素的最长公共前缀(height数组)，使用get_height();
//计算两个后缀a, 和b的最长公共前缀，请先使用lcp_init(),再调用get_lcp(a, b)得到
//下面的n是输入字符串的长度+1(n = strlen(s) + 1)， m是模板的范围 m=128表示在字母，数字范围内，可以扩大也可缩小
//s[len] 是插入的一个比输入字符都要小的字符
struct SufArray {
    char s[MAXN];
    int sa[MAXN], t[MAXN], t2[MAXN], c[MAXN], n, m;
    int rnk[MAXN], height[MAXN];//rnk和height数组
    int mi[MAXN][20], idxK[MAXN];//用于计算LCP

    void init() {
        mem0(s);
        mem0(height);
    }
    //读入字符串作为输入
    void read_str() {
        gets(s);
        m = 128;
        n = strlen(s);
        s[n++] = ' ';
    }
    void build_sa() {
        int *x = t, *y = t2;
        rep (i, 0, m - 1) c[i] = 0;
        rep (i, 0, n - 1) c[x[i] = s[i]] ++;
        rep (i, 1, m - 1) c[i] += c[i - 1];
        dec (i, n - 1, 0) sa[--c[x[i]]] = i;
        for(int k = 1; k <= n; k <<= 1) {
            int p = 0;
            rep (i, n - k, n - 1) y[p++] = i;
            rep (i, 0, n - 1) if(sa[i] >= k) y[p++] = sa[i] - k;
            rep (i, 0, m - 1) c[i] = 0;
            rep (i, 0, n - 1) c[x[y[i]]] ++;
            rep (i, 0, m - 1) c[i] += c[i - 1];
            dec (i, n - 1, 0) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            rep (i, 1, n - 1) {
                x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
            }
            if(p >= n) break;
            m = p;
        }
    }
    void get_height() {
        int k = 0;
        rep (i, 0, n - 1) rnk[sa[i]] = i;
        rep (i, 0, n - 1) {
            if(k) k --;
            int j = sa[rnk[i] - 1];
            while(s[i + k] == s[j + k]) k ++;
            height[rnk[i]] = k;
        }
    }
    void rmq_init(int *a, int n) {
        rep (i, 0, n - 1) mi[i][0] = a[i];
        for(int j = 1; (1 << j) <= n; j ++) {
            for(int i = 0; i + (1<<j) - 1 < n; i ++) {
                mi[i][j] = min(mi[i][j - 1], mi[i + (1 << (j - 1))][j - 1]);
            }
        }
        rep (len, 1, n) {
            idxK[len] = 0;
            while((1 << (idxK[len] + 1)) <= len) idxK[len] ++;
        }
    }
    int rmq_min(int l, int r) {
        int len = r - l + 1, k = idxK[len];
        return min(mi[l][k], mi[r - (1 << k) + 1][k]);
    }
    void lcp_init() {
        get_height();
        rmq_init(height, n);
    }
    int get_lcp(int a, int b) {
        if(a == b) return n - a - 1;
        return rmq_min(min(rnk[a], rnk[b]) + 1, max(rnk[a], rnk[b]));
    }
    void solve() {
    }
};
