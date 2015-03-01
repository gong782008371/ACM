/********************************************************************

关于二分图的最大匹配的用处：
	最少顶点覆盖 = 二分图最大匹配
	DAG图的最小路径覆盖数=节点数（n）- 最大匹配数（m）
	二分图最大独立集=顶点数-二分图最大匹配

*********************************************************************/
//匈牙利算法复杂度O(n^2*m)

int N, M;//二分图两侧的定点个数
int Left[MAXM], G[MAXN][MAXM];//Left[v] = u表示右侧的v与左侧的u匹配
bool vis[MAXN];//是否访问过

bool DFS(int u)
{
	for(int v = 1; v <= M; v ++ ) if(G[u][v] && !vis[v])//首先走非匹配边
	{
		vis[v] = 1;
		if( Left[v] == -1 || DFS(Left[v]) )//再走匹配边
		{
			Left[v] = u;//找到增广路，重新设置匹配边
			return true;
		}
	}
	return false;
}

int hungary()
{
	int ret = 0;
	memset(Left, -1, sizeof(Left));
	for(int i = 1; i <= N; i ++ )
	{
		memset(vis, 0, sizeof(vis));
		if( DFS(i) ) ret ++ ;
	}
	return ret;
}
