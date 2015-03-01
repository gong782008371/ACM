//Tarjan求电双连通分量，最后的结果剩下bcc_cnt个电双连通分量
//原图中每个点所在的连通分量为bccno数组所标示

int pre[MAXN], iscut[MAXN], bccno[MAXN], dfs_clock, bcc_cnt;
vector<int>G[MAXN], bcc[MAXN];

stack<Edge>s;

int dfs(int u, int fa)
{
    int lowu = pre[u] = ++dfs_clock;
    int child = 0;
    for(int i = 0; i < G[u].size(); i ++)
    {
        int v = G[u][i];
        Edge e = Edge(u, v);
        if(!pre[v])
        {
            s.push(e);
            child ++;
            int lowv = dfs(v, u);
            lowu = min(lowv, lowu);
            if(lowv >= pre[u])
            {
                iscut[u] = true;
                bcc_cnt++; bcc[bcc_cnt].clear();
                for(;;)
                {
                    //注意最后分量的下标是从1开始的
                    Edge x = s.top(); s.pop();
                    if(bccno[x.u] != bcc_cnt) { bcc[bcc_cnt].push_back(x.u); bccno[x.u] = bcc_cnt; }
                    if(bccno[x.v] != bcc_cnt) { bcc[bcc_cnt].push_back(x.v); bccno[x.v] = bcc_cnt; }
                    if(x.u == u && x.v == v) break;
                }
            }
        }
        else if(pre[v] < pre[u] && v != fa) {
            s.push(e);
            lowu = min(lowu, pre[v]);
        }
    }
    if(fa < 0 && child == 1) iscut[u] = 0;
    return lowu;
}


void find_bcc(int n)
{
    //调用结束后s保证为空，所以不需要清空
    mem0(pre); mem0(iscut); mem0(bccno);
    dfs_clock = bcc_cnt = 0;
    for(int i = 0; i < n; i ++)
        if(!pre[i]) dfs(i, -1);
}
