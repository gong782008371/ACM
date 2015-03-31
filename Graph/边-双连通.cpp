//����dfs���˫��ͨ���������һ�������ͨ��������

struct Edge {
    int v, id;
    Edge(int _v = 0, int _id = 0) {
        v = _v; id = _id;
    }
    bool operator < (const Edge& A) const {
        return v < A.v;
    }
};

int pre[MAXN], bccno[MAXN];//��ʼ��Ϊ0
bool isB[MAXM], vis[MAXM];//���,isB=isBridge   vis���ڱ���ǲ����ر�
int dfs_clock, bcc_cnt;//��Ҫ��ʼ��Ϊ0,bcc_cnt���ڼ�¼��ͨ�����ĸ������±�Ϊ[1, bcc_cnt]
vector<Edge>G[MAXN], G2[MAXN];//��ʼ����գ�ԭͼ��������ͼ
vector<int>bcc[MAXN];//����գ�ÿ����ͨ�����������Ķ��㼯��

//��һ��dfs���ҳ����е���
int dfs(int u, int fa)
{
    int lowu = pre[u] = ++dfs_clock;
    int si = G[u].size();
    for(int i = 0; i < si; i ++) {
        int v = G[u][i].v, id = G[u][i].id;
        if(!pre[v]) {
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if(lowv > pre[u]) isB[id] = !vis[id];//����
        }
        else if(pre[v] < pre[u] && v != fa) {
            lowu = min(lowu, pre[v]);
        }
    }
    return lowu;
}

//������е��ر�,�ر߲��������ţ�ֻҪ�����ر�һ��Ҫ�������
void getVis(int n)
{
    mem0(vis);
    for (int i = 0; i < n; i ++) { //�±��0 ~ n - 1
        sort(G[i].begin(), G[i].end());
        int si = G[i].size();
        for (int j = 1; j < si; j ++) if(G[i][j].v == G[i][j - 1].v) {
            vis[G[i][j - 1].id] = vis[G[i][j].id] = 1;
        }
    }
}

void dfs2(int u) {//�ڶ���dfs�������ҳ����е�bcc
    if(vis[u]) return ;
    vis[u] = 1;
    bccno[u] = bcc_cnt; bcc[bcc_cnt].push_back(u);
    int si = G[u].size();
    for(int i = 0; i < si; i ++) if(!isB[G[u][i].id]) {
        dfs2(G[u][i].v);
    }
}

void init(int n) { //���ݳ�ʼ��
    dfs_clock = bcc_cnt = 0;
    mem0(pre); mem0(bccno); mem0(isB);
    for(int i = 0; i < n; i ++) {
        G2[i].clear(); bcc[i].clear();
    }
}

void find_bcc(int n)
{
    init(n);
    getVis(n); //���ر߱��Ϊ����������
    for(int i = 0; i < n; i ++) {//�ҵ����е��ţ���isB���
        if(!pre[i]) dfs(i, -1);
    }
    mem0(vis);
    for(int i = 0; i < n; i ++) if(!vis[i]) {//�ҵ�bcc��bcc���±��1��ʼ
        bcc_cnt ++;  dfs2(i);
    }
}

void find_bcc_edge(int n) {//���µ���ͨͼ��������ͼ�����ϱ�
    for(int u = 0; u < n; u ++) {
        int si = G[u].size();
        for(int i = 0; i < si; i ++) {
            int v = G[u][i].v, id = G[u][i].id;
            if(bccno[u] != bccno[v]) {
                G2[bccno[u]].push_back(Edge(bccno[v], id));
                G2[bccno[v]].push_back(Edge(bccno[u], id));//���������߲�Ҫ��һ��
            }
        }
    }
}
