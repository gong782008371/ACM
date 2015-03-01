//DFS求图的割顶，iscut数组初始化为0，dfs_clock初始化为0

int pre[MAXN], low[MAXN], iscut[MAXN];
int dfs_clock;

int dfs(int u, int fa)//调用时fa传入一个负数
{
    int lowu = pre[u] = ++dfs_clock;
    int child = 0;
    for(int i = 0; i < G[u].size(); i ++)
    {
        int v = G[u][v];
        if(!pre[v])
        {
            child ++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if(lowv >= pre[u])
                iscut[u] = true;
        }
        else if(pre[v] < pre[u] && v != fa) {
            lowu = min(lowu, pre[v]);
        }
    }
    //如果整个连通分量只有两个节点
    if(fa < 0 && child == 1) iscut[u] = 0;
    low[u] = lowu;
    return lowu;
}
