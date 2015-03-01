
/***************************************************************
*                                                              *
*        dinic�㷨����������ڽӱ��ߣ�                       *
*                                                              *
***************************************************************/

struct Edge { int to, cap, next; }edge[MAXM<<3];
int tot, head[MAXN];

int src, des, dis[MAXN];//Դ�㣬��㣬����

void add_edge(int u, int v, int c)
{
    edge[tot].to = v; edge[tot].cap = c; edge[tot].next = head[u];
    head[u] = tot ++;
    edge[tot].to = u; edge[tot].cap = 0; edge[tot].next = head[v];
    head[v] = tot ++;
}

bool bfs()
{
    queue<int>q;   //BFS���ö��У����Ҫ���ٶȿ����Լ�д����
    mem1(dis);     //����Դ��ľ���
    dis[src] = 0;
    q.push(src);
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        for(int i = head[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if(dis[v] == -1 && edge[i].cap > 0) //�����������
            {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[des] != -1;//û�п��Ե������·��ʱ������false
}

int dfs(int cur, int aug)//��ǰ���ڵ�cur����ǰ������Ϊaug
{
    if(cur == des || aug == 0)//�����յ�����Ϊ0�����
        return aug;
    int flow = 0;
    for(int i = head[cur]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if ( dis[v] == dis[cur]+1 && edge[i].cap > 0 )//�������е������
        {
            int f = dfs( v, MIN(edge[i].cap, aug) );//DFS��·���ϵĲ���
            edge[i].cap   -= f;    //�������������
            edge[i^1].cap += f;    //���������
            flow += f;
            aug -= f;
            if(aug == 0)
                break;
        }
    }
    return flow; //��������
}

int dinic()
{
    int res = 0;
    while (bfs())
    {
        res += dfs(src, INF);
    }
    return res;
}
