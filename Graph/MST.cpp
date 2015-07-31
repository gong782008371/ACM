struct Edge {
    int from, to, dis;
    Edge(int _from = 0, int _to = 0, int _dis = 0): from(_from), to(_to), dis(_dis){}
    bool operator < (const Edge &A) const {
        return dis < A.dis;
    }
};
struct MST {
    int n, m, fa[MAXN];
    Edge edge[MAXM];
    void init(int _n) { n = _n; m = 0; }
    void addEdge(int u, int v, int dis) {
        edge[++m].from = u; edge[m].to = v; edge[m].dis = dis;
    }
    int findFa(int x) {
        return x == fa[x] ? x : fa[x] = findFa(fa[x]);
    }
    int findAns() {
        sort(edge + 1, edge + m + 1);
        rep (i, 0, n) fa[i] = i;
        int ans = 0;
        rep (i, 1, m) {
            int u = edge[i].from, v = edge[i].to, w = edge[i].dis;
            int x = findFa(u), y = findFa(v);
            if(x != y) {
                fa[x] = y;
                ans += w;
            }
        }
        return ans;
    }
}mst;
