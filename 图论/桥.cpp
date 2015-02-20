//DFS��ͼ���ţ�dfs_clock��ʼ��Ϊ0, cut_cnt��ʼ��Ϊ0��pre�����ʼ��Ϊ0��lowͬ��
//�������е��ű߱�����cut�����У����԰���ĿҪ����ı��淽ʽ

struct Edge{
    int u, v;
    Edge(){}
    Edge(int _u, int _v){
        u = _u; v = _v;
    }
}cut[MAXM];
int pre[MAXN], low[MAXN];
int dfs_clock, cut_cnt;

int dfs(int u, int fa)//����ʱfa����һ������
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
            if(lowv > pre[u])//������>�ţ�û��=
                cut[++cut_cnt] = Edge(u, v);
        }
        else if(pre[v] < pre[u] && v != fa) {
            lowu = min(lowu, pre[v]);
        }
    }
    return low[u] = lowu;;
}
