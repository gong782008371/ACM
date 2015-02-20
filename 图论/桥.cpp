//DFS求图的桥，dfs_clock初始化为0, cut_cnt初始化为0，pre数组初始化为0，low同上
//最后的所有的桥边保存在cut数组中，可以按题目要求更改保存方式

struct Edge{
    int u, v;
    Edge(){}
    Edge(int _u, int _v){
        u = _u; v = _v;
    }
}cut[MAXM];
int pre[MAXN], low[MAXN];
int dfs_clock, cut_cnt;

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
            if(lowv > pre[u])//这里是>号，没有=
                cut[++cut_cnt] = Edge(u, v);
        }
        else if(pre[v] < pre[u] && v != fa) {
            lowu = min(lowu, pre[v]);
        }
    }
    return low[u] = lowu;;
}
