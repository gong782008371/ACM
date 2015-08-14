
#define root 1, 1, n
#define middle ((L + R) >> 1)
#define lson k << 1, L, middle
#define rson k << 1 | 1, middle + 1, R

struct SegTree {
    int t[MAXN << 2];

    void push_up(int k, int L, int R) {}

    void push_down(int k, int L, int R){}

    void build(int k, int L, int R) {
        t[k] = 0;
        if(L == R) return ;
        build(lson); build(rson);
    }

    void update(int k, int L, int R, int p, int v){}

    int query(int k, int L, int R, int l, int r){}
};
