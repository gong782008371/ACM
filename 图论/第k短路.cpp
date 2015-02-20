//#pragma comment(linker,"/STACK:102400000,102400000")
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define INF 1e9
#define inf (-((LL)1<<40))
#define lson k<<1, L, mid
#define rson k<<1|1, mid+1, R
#define mem0(a) memset(a,0,sizeof(a))
#define mem1(a) memset(a,-1,sizeof(a))
#define mem(a, b) memset(a, b, sizeof(a))
#define FOPENIN(IN) freopen(IN, "r", stdin)
#define FOPENOUT(OUT) freopen(OUT, "w", stdout)

//typedef __int64 LL;
//typedef long long LL;
const int MAXN = 1005;
const int MAXM = 100005;
const double eps = 1e-10;
//const LL MOD = 1000000007;

int N, M, K, S, T;
struct Edge {
    int v, w;
    Edge(){}
    Edge(int _v, int _w):v(_v), w(_w){}
};
vector<Edge>fEdge[1005], rEdge[1005];
int dis[MAXN], cnt[MAXN];
bool  vis[MAXN];

struct NODE {
    int f, g;
    int v;
    NODE(){}
    NODE(int _f, int _g, int _v):f(_f), g(_g), v(_v){}
    bool operator < (const NODE& A) const {
        return A.f < f;
    }
};

void init()
{
    mem0(cnt);
    for(int i=0;i<=N;i++)
    {
        fEdge[i].clear();
        rEdge[i].clear();
    }
    for(int i=0;i<M;i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        fEdge[u].push_back(Edge(v, w));
        rEdge[v].push_back(Edge(u, w));
    }
    scanf("%d%d%d", &S, &T, &K);
    if(S == T) K++;
}

void dijkstra(int start)
{
    mem0(vis);
    for(int i=0;i<=N;i++) dis[i] = INF;
    dis[start] = 0;
    priority_queue<NODE> que;
    que.push(NODE(0, 0, start));
    while(!que.empty())
    {
        NODE now = que.top(); que.pop();
        int from = now.v;
        if(vis[from]) continue;
        vis[from] = 1;
        for(int i=0;i<rEdge[from].size();i++)
        {
            int to = rEdge[from][i].v, val = rEdge[from][i].w;
            if(!vis[to] && dis[to] > dis[from] + val)
            {
                dis[to] = dis[from] + val;
                que.push( NODE(dis[to], 0, to) );
            }
        }
    }
}

int A_Star()
{
    if(dis[S] == INF)
        return -1;
    priority_queue<NODE> que;
    que.push(NODE(dis[S], 0, S));
    while(!que.empty())
    {
        NODE now = que.top(); que.pop();
        int from = now.v;
        cnt[from]++;
        if(cnt[T] == K) return now.f;
        if(cnt[from] > K) continue;
        for(int i=0;i<fEdge[from].size();i++)
        {
            int to = fEdge[from][i].v;
            int nG = now.g + fEdge[from][i].w;
            int nF = nG + dis[to];
            que.push( NODE(nF, nG, to) );
        }
    }
    return -1;
}

int main()
{
    //FOPENIN("in.txt");
    while(scanf("%d %d", &N, &M) == 2)
    {
        init();
        dijkstra(T);
        printf("%d\n", A_Star());
    }
    return 0;
}
