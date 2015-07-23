/*********************************************************************

Tarjan算法，离线查询O(n + q)

*********************************************************************/


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


/*********************************************************************

ST算法，在线查询O(nlogn)预处理，O(1)查询

*********************************************************************/

struct Edge {
    int v, w;
    Edge(int _v = 0, int _w = 0) {
        v = _v; w = _w;
    }
};

struct LCA {//后面“序号”都表示dfs时的序号
    int idx[MAXN << 1]; //idx[a] = b表示序号a的节点编号为b
    int dep[MAXN << 1]; //dep[a] = b序号为a的深度（高度）为b
    int dp[MAXN << 1][20];//区间深度最小的点的序号
    int K[MAXN << 1];
    int node_cnt;//dfs结点统计
    vector<Edge>G[MAXN];//如果没有权值，可以直接用vector<int>
    int P[MAXN];//当前顶点最早出现的序号
    int dis[MAXN];//当前节点距离根结点的距离(路径权值和)

    void init(int n) {
        mem0(dep); mem0(K);
        node_cnt = 0;
        rep (i, 0, n) G[i].clear();
    }
    void add_edge(int u, int v, int w) {
        G[u].push_back(Edge(v, w));
        G[v].push_back(Edge(u, w));
    }
    void dfs(int u, int fa, int height, int dist) {
        idx[++node_cnt] = u; //记录顶点
        dep[node_cnt] = height;//记录高度
        P[u] = node_cnt;//顶点u最早出现的位置
        dis[u] = dist;//距离根节点距离
        int sz = G[u].size();
        rep (i, 0, sz - 1) {
            int v = G[u][i].v;
            if(v == fa) continue;
            dfs(v, u, height + 1, dist + G[u][i].w);
            idx[++node_cnt] = u;
            dep[node_cnt] = height;
        }
    }
    void init_st_table() {//预处理ST表
        dfs(1, -1, 0, 0);

        int n = node_cnt;
        rep (i, 1, n) {
            dp[i][0] = i;
            while((1 << (K[i] + 1)) <= i) K[i] ++;
        }
        for(int j = 1; (1 << j) <= n; j ++) {
            for(int i = 1; i + (1 << j) - 1 <= n; i ++) {
                int l_pos = dp[i][j - 1], r_pos = dp[i + (1 << (j - 1))][j - 1];
                dp[i][j] = dep[l_pos] < dep[r_pos] ? l_pos : r_pos;
            }
        }
    }
    int rmq_query(int L, int R) {//查询区间深度最小的点的序号
        if(L > R) swap(L, R);
        int len = R - L + 1, k = K[len];
        return dep[dp[L][k]] < dep[dp[R - (1 << k) + 1][k]] ? dp[L][k] : dp[R - (1 << k) + 1][k];
    }
    int lca_query(int u, int v) {//查询点u与v的lca
        int id = rmq_query(P[u], P[v]);
        return idx[id];
    }
}lca;
