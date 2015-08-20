/******************************************************************************

莫队算法，使用曼哈顿距离最小生成树实现
用法：
    modui(m);
    int root = kruskal(m);
    dfs(root, -1, 1, 0);

******************************************************************************/

int ans[MAXM];//用于记录答案,ans[i]表示第i个查询的答案
vector<int>G[MAXM]; //记录最小生成树的图
int tot, f[MAXM], c[MAXM], x, fa[MAXM];//tot记录生成树原图中的边数，c是辅助数组，fa是最小生成树中并查集的部分使用的
struct Edge {
    int x, y, val;
}q[MAXM], d[MAXM], e[MAXM<<2];//q记录查询 d是辅助数组 e是最小生成树中用来存边的

int cmp1(Edge a, Edge b) { //按点排序
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

int cmp(Edge a, Edge b) { //按权值排序
    return a.val < b.val;
}

struct Bit {//树状数组用于维护后缀最小值
    int t[MAXM];
    void clr() { mem0(t); }
    void add(int x, int y) { //在点x插入一个值y，这里的y是一个下标，对应的值在c数组中
        while(x > 0) {
            if(c[y] < c[t[x]]) t[x] = y;
            x -= x & (-x);
        }
    }
    int ask(int x, int n) {//查询点x之后c值最小的下标
        int s = 0;
        while(x <= n) {
            if(c[s] > c[t[x]]) s = t[x];
            x += x & (-x);
        }
        return s;
    }
}T;

void add_edge(int u, int v, int w) //加边，用于计算最小生成树
{
    e[tot].x = u; e[tot].y = v;
    e[tot++].val = w;
}

void modui(int n) //莫队算法
{
    //输入查询
    rep (i, 1, n) scanf("%d %d", &q[i].x, &q[i].y), q[i].val = i;
    tot = 0;
    rep (k, 1, 4) {
        if(k == 2 || k == 4) rep (i, 1, n) swap(q[i].x, q[i].y);
        else if(k == 3) rep (i, 1, n) q[i].x = -q[i].x;
        sort(q + 1, q + n + 1, cmp1);
        rep (i, 1, n) d[i].x = q[i].y - q[i].x, d[i].y = i; //按照y-x排序，用于计算每个点的“排名”
        rep (i, 1, n) c[i] = q[i].x + q[i].y;
        c[0] = INF;   //这句绝对不能少，下面要用到
        sort(d + 1, d + n + 1, cmp1);
        rep (i, 1, n) f[d[i].y]  = i;//记录“排名”
        T.clr();
        dec (i, n, 1) {
            if(x = T.ask(f[i], n)) add_edge(q[i].val, q[x].val, c[x] - c[i]);
            T.add(f[i], i);
        }
    }
}

int findP(int x) {
    return x == fa[x] ? x : fa[x] = findP(fa[x]);
}

int kruskal(int n) //kruskal求最小生成树
{
    sort(e, e + tot, cmp);
    rep (i, 1, n) fa[i] = i, G[i].clear();
    rep (i, 0, tot - 1) {
        int x = findP(e[i].x), y = findP(e[i].y);
        if(x != y) {
            fa[y] = x;
            G[e[i].x].push_back(e[i].y);
            G[e[i].y].push_back(e[i].x);
        }
    }
    for (int i = 1; i <= n; i ++) if(fa[i] == i)
        return i;
}

void add_or_del(int pos, bool flag) {
    if(flag == true) { //代表在位置加入pos这个点的影响
    } else {//删除pos这个点的影响
    }
}

void record_ans(int id) { //记录答案
}

void dfs(int u, int fa, int l, int r)
{
    int L = q[u].x, R = -q[u].y, siz = G[u].size();
    for (int i = min(L, l), high = max(L, l); i < high; i ++)
        add_or_del(i, L < l);
    for (int i = min(r, R) + 1, high = max(r, R); i <= high; i ++)
        add_or_del(i, r < R);

    record_ans(q[u].val);

    rep (i, 0, siz - 1) if(G[u][i] != fa) {
        dfs(G[u][i], u, L, R);
    }

    for (int i = min(L, l), high = max(L, l); i < high; i ++)
        add_or_del(i, L > l);
    for (int i = min(r, R) + 1, high = max(r, R); i <= high; i ++)
        add_or_del(i, r > R);
}
