queue<int>q;
bool inq[MAXN], cnt[MAXN];

//返回false表示有负权,否则求出单源最短路
bool SPFA(int s, int t)
{
    for(int i = 0; i < n; i ++) d[i] = (i == s ? 0 : INF);
    memset(inq, 0, sizeof(inq));   //   “在队列中”的标志
    memset(cnt, 0, sizeof(cnt));   //   所有点出队次数为0
    q.push(s);
    while(!q.empty())
    {
        int x = q.front(); q.pop();
        inq[x] = false;        //  清除“在队列中”的标志
        cnt[x] ++;
        if(cnt[t] > n) return false;
        for(int e = first[x]; e != -1; e = next[e]) if(d[v[e]] > d[x] + w[e])
        {
            d[v[e]] = d[x] +w[e];
            if(!inq[d[e]])   //   如果已经在队列中，就不要重复添加了
            {
                inq[v[e]] = true;
                q.push(v[e]);
            }
        }
    }
    return true;
}
