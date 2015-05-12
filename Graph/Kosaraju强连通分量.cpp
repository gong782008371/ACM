//Kosaraju�㷨������ͼ��ǿ˫��ͨ����
//G��ԭͼ��G2��Gת�ú��ͼ�������б߶�����
//���scc_cnt��ǿ��ͨ�����ĸ��������Ϊi�Ķ�������sccno[i]���������

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

�����ǲ��ýṹ��ķ�ʽ����
    ���𰸵�i���㴦�ڵ�sccno[i]���ֿ��
    ǿ��ͨ�ֿ�ı��[1, scc.scc_cnt]
    ��i��ǿ��ͨ�ֿ��ﱣ��ĵ���scc.scc[i]

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
