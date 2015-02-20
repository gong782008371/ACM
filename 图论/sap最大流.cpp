
struct Edge { int to, cap, next; }edge[MAXM<<1];
int head[MAXN], tot;

int src, des;//源点，汇点
int dep[MAXN], gap[MAXN], pre[MAXN], aug[MAXN], cur[MAXN];

int SAP(int n)
{
    mem0(aug);   //aug保存当前对当前的增广路上的残量aug[u] = w表示从起点到点u的最大残量为w
    mem0(pre);   //pre保存的是增广路上的每一个点的前驱结点
    mem(dep, 0); //dep保存的是每一个点的深度，也就是它到汇点的最短距离
    mem(gap, 0); //gap[u] = w表示的是深度为u的节点的个数为w
    int max_flow = 0, u = src;//当前节点为源点
    aug[src] = INF;
    pre[src] = -1;
    gap[0] = n;
    for(int i = 0; i <= n; i ++)  //cur保存的是增广路径上的边的序号
        cur[i] = head[i];
    while(dep[src] < n)
    {
        if(u == des)
        {
            max_flow += aug[des]; //到达终点
            for(int v = pre[des]; v != -1; v = pre[v])
            {
                int e = cur[v];
                edge[e].cap   -= aug[des];//正向边减去路径的最小残量
                edge[e^1].cap += aug[des];
                aug[v] -= aug[des];         //修改增广量，下面会用到
                if(edge[e].cap == 0) u = v; //由于上面修改了增广量，不为0的路径依然可用，所以不用回退到源点（常数优化）
            }
        }
        int flag = 0;//从当前弧查找允许弧（注意下面是cur[u]）
        for(int e = cur[u]; e != -1; e = edge[e].next)
        {
            int v = edge[e].to;
            if(edge[e].cap > 0 && dep[u] == dep[v] + 1)//找到允许弧
            {
                flag = 1;
                pre[v] = u; cur[u] = e;
                aug[v] = MIN(aug[u], edge[e].cap);
                u = v;
                break;
            }
        }
        if(!flag)
        {
            if(--gap[dep[u]] == 0)   //gap优化，层次树出现断层则算法结束
                break;
            int min_dep = n;
            cur[u] = head[u];
            for(int e = head[u]; e != -1; e = edge[e].next)
            {
                int v = edge[e].to;
                if(edge[e].cap > 0 && dep[v] < min_dep)
                {
                    min_dep = dep[v];
                    cur[u] = e;  //修改标号的同时修改当前弧
                }
            }
            dep[u] = min_dep + 1;
            gap[dep[u]] ++;
            if(u != src) u = pre[u]; //回溯继续寻找允许弧
        }
    }
    return max_flow;
}
