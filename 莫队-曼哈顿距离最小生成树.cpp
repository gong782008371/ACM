/******************************************************************************

Ī���㷨��ʹ�������پ�����С������ʵ��
�÷���
    modui(m);
    int root = kruskal(m);
    dfs(root, -1, 1, 0);

******************************************************************************/

int ans[MAXM];//���ڼ�¼��,ans[i]��ʾ��i����ѯ�Ĵ�
vector<int>G[MAXM]; //��¼��С��������ͼ
int tot, f[MAXM], c[MAXM], x, fa[MAXM];//tot��¼������ԭͼ�еı�����c�Ǹ������飬fa����С�������в��鼯�Ĳ���ʹ�õ�
struct Edge {
    int x, y, val;
}q[MAXM], d[MAXM], e[MAXM<<2];//q��¼��ѯ d�Ǹ������� e����С��������������ߵ�

int cmp1(Edge a, Edge b) { //��������
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

int cmp(Edge a, Edge b) { //��Ȩֵ����
    return a.val < b.val;
}

struct Bit {//��״��������ά����׺��Сֵ
    int t[MAXM];
    void clr() { mem0(t); }
    void add(int x, int y) { //�ڵ�x����һ��ֵy�������y��һ���±꣬��Ӧ��ֵ��c������
        while(x > 0) {
            if(c[y] < c[t[x]]) t[x] = y;
            x -= x & (-x);
        }
    }
    int ask(int x, int n) {//��ѯ��x֮��cֵ��С���±�
        int s = 0;
        while(x <= n) {
            if(c[s] > c[t[x]]) s = t[x];
            x += x & (-x);
        }
        return s;
    }
}T;

void add_edge(int u, int v, int w) //�ӱߣ����ڼ�����С������
{
    e[tot].x = u; e[tot].y = v;
    e[tot++].val = w;
}

void modui(int n) //Ī���㷨
{
    //�����ѯ
    rep (i, 1, n) scanf("%d %d", &q[i].x, &q[i].y), q[i].val = i;
    tot = 0;
    rep (k, 1, 4) {
        if(k == 2 || k == 4) rep (i, 1, n) swap(q[i].x, q[i].y);
        else if(k == 3) rep (i, 1, n) q[i].x = -q[i].x;
        sort(q + 1, q + n + 1, cmp1);
        rep (i, 1, n) d[i].x = q[i].y - q[i].x, d[i].y = i; //����y-x�������ڼ���ÿ����ġ�������
        rep (i, 1, n) c[i] = q[i].x + q[i].y;
        c[0] = INF;   //�����Բ����٣�����Ҫ�õ�
        sort(d + 1, d + n + 1, cmp1);
        rep (i, 1, n) f[d[i].y]  = i;//��¼��������
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

int kruskal(int n) //kruskal����С������
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
    if(flag == true) { //������λ�ü���pos������Ӱ��
    } else {//ɾ��pos������Ӱ��
    }
}

void record_ans(int id) { //��¼��
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
