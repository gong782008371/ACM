struct Edge {
    int u, v, w;
    Edge(int _u = 0, int _v = 0, int _w = 0) {
        u = _u; v = _v;  w = _w;
    }
    bool operator < (const Edge &A) const {
        return w < A.w;
    }
};
struct UnionSet {
    int fa[MAXN], n, m;
    Edge edge[MAXM];

    void reSize(int _n) {
        n = _n; m = 0;
        initFa(n);
    }
    void initFa(int n) {
        rep (i, 0, n) fa[i] = i;
    }
    void addEdge(int u, int v, int w) {
        edge[++m] = Edge(u, v, w);
    }
    int findFa(int x) {
        return x == fa[x] ? x : fa[x] = findFa(fa[x]);
    }
    int Union(int p) {
        int x = findFa(edge[p].u), y = findFa(edge[p].v);
        if(x != y) { fa[x] = y; return edge[p].w; }
        return 0;
    }
    int Union(int a, int b) {
        int x = findFa(a), y = findFa(b);
        if(x != y) { fa[x] = y; return 1; }
        return 0;
    }
    bool judgeSameSet(int a, int b) {
        return findFa(a) == findFa(b);
    }
    int countSet() {
        int ans = 0;
        rep (i, 0, n) if(findFa(i) == i) ans ++;
        return ans;
    }
    int kruskal() {
        initFa(n);
        sort(edge + 1, edge + m + 1);
        int ans = 0;
        rep (i, 1, m) ans += Union(i);
        return ans;
    }
}unionSet;
