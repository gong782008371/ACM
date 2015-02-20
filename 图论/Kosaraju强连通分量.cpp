//Kosaraju�㷨������ͼ��ǿ˫��ͨ����
//G��ԭͼ��G2��Gת�ú��ͼ�������б߶�����
//���scc_cnt��ǿ��ͨ�����ĸ��������Ϊi�Ķ�������sccno[i]���������

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
