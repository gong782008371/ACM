struct Query {
    int v, id;
    Query(int _v = 0, int _id = 0) {
        id = _id; v = _v;
    }
};

struct LCA {
    bool vis[MAXN];
    int anc[MAXN], ans[MAXM];
    vector<Query>q[MAXN];
    vector<int>G[MAXN];

    int init(int n) {
        mem0(vis);
        rep (i, 0, n) q[i].clear(), G[i].clear();
    }

    void add_query(int id, int u, int v) {
        q[u].push_back(Query(v, id));
        q[v].push_back(Query(u, id));
    }

    void add_edge(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int getFa(int x) {
        return x == anc[x] ? anc[x] : anc[x] = getFa(anc[x]);
    }

    void dfs(int u, int p) {
        anc[u] = u;
        int sz = G[u].size();
        rep (i, 0, sz - 1) if(G[u][i] != p) {
            dfs(G[u][i], u);
        }
        sz = q[u].size();
        rep (i, 0, sz - 1) if(vis[q[u][i].v]) {
            ans[q[u][i].id] = getFa(q[u][i].v);
        }
        anc[u] = p;
        vis[u] = 1;
    }
};
