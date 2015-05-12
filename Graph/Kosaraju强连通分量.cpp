//Kosaraju算法求有向图的强双连通分量
//G是原图，G2是G转置后的图（即所有边都反向）
//最后scc_cnt是强连通分量的个数，编号为i的顶点属于sccno[i]这个分量中

vector<int>G[MAXN], G2[MAXN];
vector<int>S;
int vis[MAXN], sccno[MAXN], scc_cnt;

void dfs1(int u)
{
    if(vis[u]) return ;
    vis[u] = 1;
    for(int i = 0; i < G[u].size(); i ++)
        dfs1(G[u][i]);
    S.push_back(u);
}

void dfs2(int u)
{
    if(sccno[u]) return ;
    sccno[u] = scc_cnt;
    for(int i = 0; i < G2[u].size(); i ++)
        dfs2(G2[u][i]);
}

void find_scc(int n)
{
    scc_cnt = 0;
    S.clear();
    mem0(sccno); mem0(vis);
    for(int i = 0; i < n; i ++) dfs1(i);
    for(int i = n-1; i >= 0; i --)
    if(!sccno[S[i]]) { scc_cnt++; dfs2(S[i]); }
}



/*********************************************************

以下是采用结构体的方式计算
    最后答案第i个点处于第sccno[i]个分块里，
    强连通分块的编号[1, scc.scc_cnt]
    第i个强连通分块里保存的点是scc.scc[i]

*********************************************************/
struct SCC {
    vector<int>G1[MAXN], G2[MAXN], S;
    vector<int>scc[MAXN];
    int sccno[MAXN], scc_cnt, n;
    bool vis[MAXN];

    void init(int _n) {
        n = _n;
        mem0(sccno); mem0(vis); scc_cnt = 0; S.clear();
        rep (i, 0, n) G1[i].clear(), G2[i].clear(), scc[i].clear();
    }

    void add_edge(int u, int v) {
        G1[u].push_back(v);
        G2[v].push_back(u);
    }

    void dfs1(int u) {
        if(vis[u]) return ;
        vis[u] = 1;
        int si = G1[u].size();
        rep (i, 0, si - 1) dfs1(G1[u][i]);
        S.push_back(u);
    }

    void dfs2(int u) {
        if(sccno[u]) return ;
        sccno[u] = scc_cnt;
        scc[scc_cnt].push_back(u);
        int si = G2[u].size();
        rep (i, 0, si - 1) dfs2(G2[u][i]);
    }

    int find_scc(int n) {
        rep (i, 0, n - 1) dfs1(i);
        dec (i, n - 1, 0) if(!sccno[S[i]]) {
            scc_cnt ++;
            dfs2(S[i]);
        }
        return scc_cnt;
    }

}scc;
