
/***********************************************************
*                                                          *
*   Edmonds_Karp算法，求最大流（邻接矩阵存边）             *
*                                                          *
***********************************************************/

int src, des;
int cap[MAXN][MAXN], flow[MAXN][MAXN], pre[MAXN], a[MAXN];

int Edmonds_Karp(int n)
{
    queue<int>q;
    mem0(flow);//存增广时的实际流量
    int max_flow = 0;//最大流
    while(true)
    {
        mem0(a);//每次增广残量初始化为0
        a[src] = INF;//起点的残量为INF
        q.push(src);
        while(!q.empty())//BFS寻找增广路，并记录路径
        {
            int u = q.front(); q.pop();
            for(int v = 1; v <= n; v ++) if(!a[v] && cap[u][v]>flow[u][v])
            {
                pre[v]= u;//记录路径
                q.push(v);
                a[v] = MIN(a[u], cap[u][v] - flow[u][v]);//更新路径上的最小残量
            }
        }
        if(a[des] == 0) break;    //找不到残量，此时已经是最大流
        for(int u = des; u != src; u = pre[u])
        {
            flow[pre[u]][u] += a[des];  //更新正向与反向流量
            flow[u][pre[u]] -= a[des];
        }
        max_flow += a[des];//更新从src出发的总流量
    }
    return max_flow;
}
