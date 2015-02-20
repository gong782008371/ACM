vector<int> G[MAXN];
int pre[MAXN], lowlink[MAXN], sccno[MAXN], dfs_clock, scc_cnt;
stack<int>S;

void dfs(int u)
{
    pre[u] = lowlink[u] = ++dfs_clock;
    S.push(u);
    for(int i = 0; i < G[u].size(); i ++)
    {
        int v = G[u][i];
        if(!pre[v]) {
            dfs(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        }
        else if(!sccno[v]) {
            lowlink[u] = min(lowlink[u], pre[v]);
        }
    }
    if(lowlink[u] == pre[u]) {
        scc_cnt++;
        for(;;) {
            int x = S.top(); S.pop();
            sccno[x] = scc_cnt;
            if(x == u) break;
        }
    }
}


void find_scc(int n)
{
    dfs_clock = scc_cnt = 0;
    mem0(sccno); mem0(pre);
    for(int i = 0; i < n; i ++ )
        if(!pre[i]) dfs(i);
}
