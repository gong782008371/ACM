//**************************************************
//单源最短路径，没有边时dis为INF
//不可以有负权，节点编号从0开始
//**************************************************

void dijkstra(int s)
{
    for(int i=0;i<=N;i++) d[i] = INF;
    d[s] = 0;
    for(int i=0;i<N;i++)
    {
        int m = INF;
        for(int j = 0;j<N;j++)if(!vis[j] && d[j]<m)m=d[s=j];
        vis[s] = 1;
        for(int j=0;j<N;j++)if(d[j] > d[s]+Map[s][j])d[j]=d[s]+Map[s][j];
    }
}
