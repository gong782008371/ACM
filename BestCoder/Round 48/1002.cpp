#pragma comment(linker, "/STACK:167772160")
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
#define INF 0x3f3f3f3f
#define inf (-((LL)1<<40))
#define lson k<<1, L, (L + R)>>1
#define rson k<<1|1,  ((L + R)>>1) + 1, R
#define mem0(a) memset(a,0,sizeof(a))
#define mem1(a) memset(a,-1,sizeof(a))
#define mem(a, b) memset(a, b, sizeof(a))
#define FIN freopen("in.txt", "r", stdin)
#define FOUT freopen("out.txt", "w", stdout)
#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define dec(i, a, b) for(int i = a; i >= b; i --)

template<class T> T MAX(T a, T b) { return a > b ? a : b; }
template<class T> T MIN(T a, T b) { return a < b ? a : b; }
template<class T> T GCD(T a, T b) { return b ? GCD(b, a%b) : a; }
template<class T> T LCM(T a, T b) { return a / GCD(a,b) * b;    }

//typedef __int64 LL;
typedef long long LL;
const int MAXN = 100000 + 100;
const int MAXM = 210000;
const double eps = 1e-8;
LL MOD = 1000000007;
const double PI = 4.0 * atan(1.0);

int n, m, t;
int c[MAXN], a, b, num[4];
int head[MAXN], to[MAXM], nxt[MAXM], tot = 0;
bool conflict;

void dfs(int u, int fa, int color) {
    num[color] ++;
    c[u] = color;
    for(int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
        if(v == fa) continue;
        if(c[v] == c[u]) conflict = true;
        else if(!c[v]) dfs(v, u, 3 - color);
    }
}

void add_edge(int U, int V) {
    to[tot] = V; nxt[tot] = head[U]; head[U] = tot++;
}

int main()
{
//    FIN;
    cin >> t;
    while(t--) {
        mem0(c);
        mem1(head); tot = 0;
        scanf("%d %d", &n, &m);
        rep (i, 1, m) {
            scanf("%d %d", &a, &b);
            add_edge(a, b);
            add_edge(b, a);
        }
        if(n < 2) {
            puts("Poor wyh");
            continue;
        }
        if(m == 0) {
            printf("%d %d\n", n - 1, 1);
            continue;
        }
        conflict = a = b = 0;
        rep (i, 1, n) if(!c[i]) {
            num[1] = num[2] = 0;
            dfs(i, -1, 1);
            a += max(num[1], num[2]);
            b += min(num[1], num[2]);
        }
        if(conflict) puts("Poor wyh");
        else cout << a << " " << b << endl;
    }
    return 0;
}

/*

1
1 0

1
5 0

*/
