struct cmp//定义优先队列的优先级比较
{
    bool operator() (Pair a, Pair b)
    {
        return a.first < b.first;
    }
};

bool done[MAXN];
typedef pair<int, int> Pair;//用于捆绑d值和序号顶点序号
void dijkstra(int s)
{
    mem(done);
    for(int i=0;i<=N;i++) d[i] = INF;//初始时将suoyoud值设置为+∞
    priority_queue<Pair, vector<Pair>, cmp>q;//定义一个优先队列
    q.push(make_pair(d[s]=0, s));//将起点放入队列中，且只有起点的d值为0
    while(!q.empty())//依次从优先队列中取出优先级最大的元素（也就是d值最小的点）直到为空
    {
        Pair top = q.top();  q.pop();
        int x = top.second;
        if(done[x]) continue;//如果此顶点已经算过了，不在讨论
        done[x] = true;
        for(int e = first[x]; e != -1; e = next[e])//枚举此个顶点的所有边
        {
            if(d[v[e]] > d[x] + w[e])
            {
                d[v[e]] = d[x] + w[e];
                q.push(make_pair(d[v[e]], v[e]));//将新的d值变小的点放进优先队列
            }
        }
    }
}
