//��׺����ģ�壬MANXΪ����Ĵ�С
//֧�ֵĲ����м����׺����(sa����)�� ����������Ԫ�ص������ǰ׺(height����)��ʹ��get_height();
//����������׺a, ��b�������ǰ׺������ʹ��lcp_init(),�ٵ���get_lcp(a, b)�õ�
//�����n�������ַ����ĳ���+1(n = strlen(s) + 1)�� m��ģ��ķ�Χ m=128��ʾ����ĸ�����ַ�Χ�ڣ���������Ҳ����С
//s[len] �ǲ����һ���������ַ���ҪС���ַ�
struct SufArray {
    char s[MAXN];
    int sa[MAXN], t[MAXN], t2[MAXN], c[MAXN], n, m;
    int rnk[MAXN], height[MAXN];//rnk��height����
    int mi[MAXN][20], idxK[MAXN];//���ڼ���LCP

    void init() {
        mem0(s);
        mem0(height);
    }
    //�����ַ�����Ϊ����
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
