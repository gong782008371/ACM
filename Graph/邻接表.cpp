
#define for_edge(u) for(int i = head[u]; ~i; i = edge[i].nxt)
struct Edge {
    int u, v, w, nxt;
}edge[MAXM];
int head[MAXN], tot;

void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
}

void add_edge(int u, int v, int w) {
    edge[tot].u = u;
    edge[tot].v = v;
    edge[tot].w = w;
    edge[tot].nxt = head[u];
    head[u] = tot++;
}
