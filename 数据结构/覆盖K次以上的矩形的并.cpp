/******************************************************************
求N个矩形的并
  给定N（N<=30000）个矩形，每个矩形的坐标范围在1e9内
  求被覆盖K（K<=10）次以上的矩形的总面积

******************************************************************/
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
template<class T> T CMP_MIN(T a, T b) { return a < b; }
template<class T> T CMP_MAX(T a, T b) { return a > b; }
template<class T> T MAX(T a, T b) { return a > b ? a : b; }
template<class T> T MIN(T a, T b) { return a < b ? a : b; }
template<class T> T GCD(T a, T b) { return b ? GCD(b, a%b) : a; }
template<class T> T LCM(T a, T b) { return a / GCD(a,b) * b;    }

//typedef __int64 LL;
typedef long long LL;
const int MAXN = 30005;
const int MAXM = 100005;
const double eps = 1e-10;
const int MOD = 9901;

int N, K, T;
LL Hash[MAXN<<1], cntHash;
int cnt[MAXN<<3], len[MAXN<<3][12];
struct Line {
    LL x1, x2, y;
    int flag;
    Line(){}
    Line(LL _x1, LL _x2, LL _y, int _flag)
    {
        x1 = _x1;
        x2 = _x2;
        y = _y;
        flag = _flag;
    }
    bool operator < (const Line& A)const
    {
        if(y != A.y) return y < A.y;
        return flag < A.flag;
    }
}line[MAXN<<1];

int bsearch(int low, int high, int num)
{
    while(low <= high)
    {
        int mid = (low + high) >> 1;
        if(Hash[mid] == num) return mid;
        if(Hash[mid] > num) high = mid - 1;
        else low = mid + 1;
    }
    return 0;
}

void buildTree(int k, int L, int R)
{
    cnt[k] = 0; mem0(len[k]);

    len[k][0] = Hash[R+1] - Hash[L];

    if(L == R) return ;

    int mid = (L + R) >> 1;

    buildTree(lson);    buildTree(rson);
}

void updateCur(int k, int L, int R)
{
    mem0(len[k]);
    if(cnt[k] >= K)
        len[k][K] = Hash[R+1] - Hash[L];
    else if(L == R)
        len[k][cnt[k]] = Hash[R+1] - Hash[L];
    else {
        for(int i=cnt[k];i<=K;i++)
            len[k][i] += len[k<<1][i-cnt[k]] + len[k<<1|1][i-cnt[k]];
        for(int i=K-cnt[k]+1;i<=K;i++)
            len[k][K] += len[k<<1][i] + len[k<<1|1][i];
    }
}

void update(int k, int L, int R, int l, int r, int flag)
{
    if(R < l || r < L) return ;

    if(l<=L && R<=r) { cnt[k] += flag; updateCur(k, L, R); return ; }

    int mid = (L + R) >> 1;

    update(lson, l, r, flag);    update(rson, l, r, flag);

    updateCur(k, L, R);
}

void init()
{
    int x1, x2, y1, y2;
    scanf("%d %d", &N, &K);
    for(int i=1;i<=N;i++)
    {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
         ++ x2; ++ y2;
        line[i] = Line(x1, x2, y1, 1);
        line[i+N] = Line(x1, x2, y2, -1);
        Hash[i] = x1;
        Hash[i+N] = x2;
    }
    sort(line + 1, line + 2*N + 1);

    sort(Hash + 1, Hash + 2*N + 1);
    cntHash = 0;
    for(int i = 1; i <= N*2; i ++ )
      if(i==1 || Hash[i-1] != Hash[i])
        Hash[++cntHash] = Hash[i];

    buildTree(1, 1, cntHash-1);
}

LL work()
{
    init();
    LL ans = 0;
    for(int i = 1; i <= 2 * N; i ++ )
    {
        if(i != 1)
        {
            ans += (line[i].y - line[i-1].y) * len[1][K];
        }
        int l  = bsearch(1, cntHash, line[i].x1);
        int r = bsearch(1, cntHash, line[i].x2);
        update(1, 1, cntHash-1, l, r-1, line[i].flag);
    }
    return ans;
}

int main()
{
    //FOPENIN("in.txt");
    scanf("%d", &T);
    for(int t = 1; t <= T; t ++ )
    {
        printf("Case %d: %lld\n", t, work());
    }
    return 0;
}
