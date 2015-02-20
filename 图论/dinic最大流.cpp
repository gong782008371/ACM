
/***************************************************************
*                                                              *
*        dinic算法求最大流（邻接表存边）                       *
*                                                              *
***************************************************************/

struct Edge { int to, cap, next; }edge[MAXM<<3];
int tot, head[MAXN];

int src, des, dis[MAXN];//源点，汇点，距离

void add_edge(int u, int v, int c)
{
    edge[tot].to = v; edge[tot].cap = c; edge[tot].next = head[u];
    head[u] = tot ++;
    edge[tot].to = u; edge[tot].cap = 0; edge[tot].next = head[v];
    head[v] = tot ++;
}

bool bfs()
{
    queue<int>q;   //BFS所用队列，如果要求速度可以自己写队列
    mem1(dis);     //距离源点的距离
    dis[src] = 0;
    q.push(src);
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        for(int i = head[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if(dis[v] == -1 && edge[i].cap > 0) //必须走允许边
            {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[des] != -1;//没有可以到达汇点的路径时，返回false
}

int dfs(int cur, int aug)//当前处在点cur，当前最大残量为aug
{
    if(cur == des || aug == 0)//到达终点或残量为0则回溯
        return aug;
    int flow = 0;
    for(int i = head[cur]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if ( dis[v] == dis[cur]+1 && edge[i].cap > 0 )//便利所有的允许边
        {
            int f = dfs( v, MIN(edge[i].cap, aug) );//DFS求路径上的残量
            edge[i].cap   -= f;    //正向边流量减少
            edge[i^1].cap += f;    //反向边增加
            flow += f;
            aug -= f;
            if(aug == 0)
                break;
        }
    }
    return flow; //返回流量
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
