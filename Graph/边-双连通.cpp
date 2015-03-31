//两次dfs求边双连通分量，并且还包括连通分量连边

struct Edge {
    int v, id;
    Edge(int _v = 0, int _id = 0) {
        v = _v; id = _id;
    }
    bool operator < (const Edge& A) const {
        return v < A.v;
    }
};

int pre[MAXN], bccno[MAXN];//初始化为0
bool isB[MAXM], vis[MAXM];//清空,isB=isBridge   vis用于标记是不是重边
int dfs_clock, bcc_cnt;//需要初始化为0,bcc_cnt用于记录连通分量的个数，下标为[1, bcc_cnt]
vector<Edge>G[MAXN], G2[MAXN];//初始化清空，原图、缩点后的图
vector<int>bcc[MAXN];//需清空，每个连通分量所包含的顶点集合

//第一次dfs，找出所有的桥
int dfs(int u, int fa)
{
    int lowu = pre[u] = ++dfs_clock;
    int si = G[u].size();
    for(int i = 0; i < si; i ++) {
        int v = G[u][i].v, id = G[u][i].id;
        if(!pre[v]) {
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if(lowv > pre[u]) isB[id] = !vis[id];//是桥
        }
        else if(pre[v] < pre[u] && v != fa) {
            lowu = min(lowu, pre[v]);
        }
    }
    return lowu;
}

//标记所有的重边,重边不可能是桥，只要是有重边一定要保留这个
void getVis(int n)
{
    mem0(vis);
    for (int i = 0; i < n; i ++) { //下标从0 ~ n - 1
        sort(G[i].begin(), G[i].end());
        int si = G[i].size();
        for (int j = 1; j < si; j ++) if(G[i][j].v == G[i][j - 1].v) {
            vis[G[i][j - 1].id] = vis[G[i][j].id] = 1;
        }
    }
}

void dfs2(int u) {//第二次dfs，用于找出所有的bcc
    if(vis[u]) return ;
    vis[u] = 1;
    bccno[u] = bcc_cnt; bcc[bcc_cnt].push_back(u);
    int si = G[u].size();
    for(int i = 0; i < si; i ++) if(!isB[G[u][i].id]) {
        dfs2(G[u][i].v);
    }
}

void init(int n) { //数据初始化
    dfs_clock = bcc_cnt = 0;
    mem0(pre); mem0(bccno); mem0(isB);
    for(int i = 0; i < n; i ++) {
        G2[i].clear(); bcc[i].clear();
    }
}

void find_bcc(int n)
{
    init(n);
    getVis(n); //将重边标记为不可能是桥
    for(int i = 0; i < n; i ++) {//找到所有的桥，由isB标记
        if(!pre[i]) dfs(i, -1);
    }
    mem0(vis);
    for(int i = 0; i < n; i ++) if(!vis[i]) {//找到bcc，bcc的下标从1开始
        bcc_cnt ++;  dfs2(i);
    }
}

void find_bcc_edge(int n) {//给新的连通图（缩点后的图）连上边
    for(int u = 0; u < n; u ++) {
        int si = G[u].size();
        for(int i = 0; i < si; i ++) {
            int v = G[u][i].v, id = G[u][i].id;
            if(bccno[u] != bccno[v]) {
                G2[bccno[u]].push_back(Edge(bccno[v], id));
                G2[bccno[v]].push_back(Edge(bccno[u], id));//如果是有向边不要这一句
            }
        }
    }
}
