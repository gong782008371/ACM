
struct Edge {
	int from, to, cap, flow, cost;
	Edge(){}
	Edge(int _u, int _v, int _c, int _f, int _cost){
		from = _u; to = _v; cap = _c;
		flow = _f; cost = _cost;
	}
};

struct MCMF
{
	int n, m, src, des;
	vector<Edge> edges;
	vector<int> G[MAXN];
	int inq[MAXN];
	int d[MAXN];
	int p[MAXN];
	int a[MAXN];

	void init(int n) {
		this->n = n;
		for(int i = 0; i < n; i ++) G[i].clear();
			edges.clear();
	}

	void add_edge(int from, int to, int cap, int cost) {
		edges.push_back(Edge(from, to, cap, 0, cost));
		edges.push_back(Edge(to, from, 0, 0, -cost));
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	bool bellman_ford(int s, int t, int& flow, int& cost) {
		for(int i = 0; i < n; i ++) d[i] = INF;
		mem0(inq);
		d[s] = 0; inq[s] = 1;
		p[s] = 0; a[s] = INF;

		queue<int>Q;
		Q.push(s);
		while(!Q.empty()) {
			int u = Q.front(); Q.pop();
			inq[u] = false;
			for(int i = 0; i < G[u].size(); i ++) {
				Edge& e = edges[G[u][i]];
				if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
					d[e.to] = d[u] + e.cost;
					p[e.to] = G[u][i];
					a[e.to] = min(a[u], e.cap - e.flow);
					if(!inq[e.to]) {
						Q.push(e.to);
						inq[e.to] = 1;
					}
				}
			}
		}
		if(d[t] == INF) return false;

		flow += a[t];
		cost += d[t] * a[t];

		int u = t;
		while(u != s) {
			edges[p[u]].flow += a[t];
			edges[p[u]^1].flow -= a[t];
			u = edges[p[u]].from;
		}
		return true;
	}

	int min_cost(int s, int t) {
		int flow =0, cost = 0;
		while(bellman_ford(s, t, flow, cost));
		return cost;
	}

};


//以下是使用邻接表存边，不是使用vector,某些时候比上述要稍快一下
/*******************************************************************/
struct Edge {
	int to, cap, flow, cost, next;
	Edge(){}
	Edge(int _n, int _v, int _c, int _f, int _cost){
		next = _n; to = _v; cap = _c;
		flow = _f; cost = _cost;
	}
};

struct MCMF
{
	int n, m, src, des;
	int head[MAXN], tot;
	Edge edges[MAXM];
	int inq[MAXN];
	int d[MAXN];
	int p[MAXN];
	int a[MAXN];

	void init(int n) {
	    this->tot = 0;
		this->n = n;
		mem1(head);
	}

	void add_edge(int from, int to, int cap, int cost) {
	    edges[tot] = Edge(head[from], to, cap, 0, cost);
	    head[from] = tot ++;
	    edges[tot] = Edge(head[to], from, 0, 0, -cost);
	    head[to] = tot ++;
	}

	bool bellman_ford(int s, int t, int& flow, int& cost) {
		for(int i = 0; i < n; i ++) {
            d[i] = INF;
            inq[i] = 0;
		}
		d[s] = 0; inq[s] = 1;
		p[s] = 0; a[s] = INF;

        queue<int>Q;
		Q.push(s);
		while(!Q.empty()) {
			int u = Q.front(); Q.pop();
			inq[u] = false;
			for(int i = head[u]; i != -1; i = edges[i].next) {
                int v = edges[i].to;
                if(edges[i].cap > edges[i].flow && d[v] > d[u] + edges[i].cost) {
					d[v] = d[u] + edges[i].cost;
					p[v] = i;
					a[v] = min(a[u], edges[i].cap - edges[i].flow);
					if(!inq[v]) {
						Q.push(v);
						inq[v] = 1;
					}
                }
			}
		}
		if(d[t] == INF) return false;

		flow += a[t];
		cost += d[t] * a[t];

		int u = t;
		while(u != s) {
			edges[p[u]].flow += a[t];
			edges[p[u]^1].flow -= a[t];
			u = edges[p[u]^1].to;
		}
		return true;
	}

	int min_cost(int s, int t) {
		int flow = 0, cost = 0;
		while(bellman_ford(s, t, flow, cost));
		return ans;
	}

};
/***************************************************************/
