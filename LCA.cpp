/*********************************************************************

Tarjan�㷨�����߲�ѯO(n + q)

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

ST�㷨�����߲�ѯO(nlogn)Ԥ����O(1)��ѯ

*********************************************************************/

struct Edge {
    int v, w;
    Edge(int _v = 0, int _w = 0) {
        v = _v; w = _w;
    }
};

struct LCA {//���桰��š�����ʾdfsʱ�����
    int idx[MAXN << 1]; //idx[a] = b��ʾ���a�Ľڵ���Ϊb
    int dep[MAXN << 1]; //dep[a] = b���Ϊa����ȣ��߶ȣ�Ϊb
    int dp[MAXN << 1][20];//���������С�ĵ�����
    int K[MAXN << 1];
    int node_cnt;//dfs���ͳ��
    vector<Edge>G[MAXN];//���û��Ȩֵ������ֱ����vector<int>
    int P[MAXN];//��ǰ����������ֵ����
    int dis[MAXN];//��ǰ�ڵ��������ľ���(·��Ȩֵ��)

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
        idx[++node_cnt] = u; //��¼����
        dep[node_cnt] = height;//��¼�߶�
        P[u] = node_cnt;//����u������ֵ�λ��
        dis[u] = dist;//������ڵ����
        int sz = G[u].size();
        rep (i, 0, sz - 1) {
            int v = G[u][i].v;
            if(v == fa) continue;
            dfs(v, u, height + 1, dist + G[u][i].w);
            idx[++node_cnt] = u;
            dep[node_cnt] = height;
        }
    }
    void init_st_table() {//Ԥ����ST��
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
    int rmq_query(int L, int R) {//��ѯ���������С�ĵ�����
        if(L > R) swap(L, R);
        int len = R - L + 1, k = K[len];
        return dep[dp[L][k]] < dep[dp[R - (1 << k) + 1][k]] ? dp[L][k] : dp[R - (1 << k) + 1][k];
    }
    int lca_query(int u, int v) {//��ѯ��u��v��lca
        int id = rmq_query(P[u], P[v]);
        return idx[id];
    }
}lca;
