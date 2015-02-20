bool Bellman_Ford(int s)//判断是否存在最短路，如果存在，则d值保留起点s的单源最短路
{
    for(int i = 1; i <= N; i ++) d[i] = INF;
    d[s] = 0;
    for(int i=1;i<N;i++)//由于由起点出发只需要N-1次就可以确定起点到其他所有点的最短路
    {
        for(int e = 0;e < M; e ++) //枚举每条边
        {
            int x = u[e], y = v[e];
            if(d[x] < INF) d[y] = MIN(d[y], d[x] + w[e]);//松弛
        }
    }
    for(int e = 0; e < M; e ++) if(d[u[e]] < INF)//再一次枚举所有边
    {
        int x = u[e], y = v[e];
        if(d[y] > d[x] + w[e]) return false;//如果还有顶点可以松弛，存在负权回路，不存在最短路
    }
    return true;
}
