int d[MAXN], flow[MAXN][MAXN], cost[MAXN][MAXN], cap[MAXN][MAXN], p[MAXN];//p表示前驱结点
bool inq[MAXN];

int f, c;//保存最终的最小费用与最大流

void MCMF()
{
	queue<int>q;
	mem0(flow);
	c = f = 0;//最小费用为c最大流为f
	while(true)
	{
		//bellman_ford算法开始（在残量网络中找s-t的最短路）
		for(int i = 0; i < n; i ++) d[i] = (i==s) ? 0 : INF;
		mem0(inq);
		q.push(s);
		while(!q.empty())
		{
			int u = q.front(); q.pop();
			inq[u] = false;
			for(int v = 0; v < n; v ++) 
				if(cap[u][v] > flow[u][v] && d[v] > d[u] + cost[u][v])
				{
					d[v] = d[u] + cost[u][v];
					p[v] = u;
					if(!inq[v])
					{
						inq[v] = true;
						q.push(v);
					}
				}
		}
		//bellman_ford结束

		if(d[t] == INF) break;//汇点不可达，表明此时已经是最小费用最大流
		int a = INF;
		for(int u = t; u != s; u = p[u])//计算最小残量
			a = min(a, cap[p[u][u] - flow[p[u]][u]);

		for(int u = t; u != s; u = p[u])
		{
			flow[p[u]][u] += a;
			flow[u][p[u]] += a;
		}
		c += d[t] * a;//更新总费用与流量
		f += a;
	}
}