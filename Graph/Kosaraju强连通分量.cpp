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
