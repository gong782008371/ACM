//#pragma comment(linker, "/STACK:1677721600")
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
const int MAXN = 3145728 + 100;
const int MAXM = 110000;
const double eps = 1e-8;
LL MOD = 1000000007;
const double PI = 4.0 * atan(1.0);

int t;
char s[MAXN];

int main()
{
//    FIN;
    while(~scanf("%d%*c", &t)) while(t--) {
        gets(s);
        int f = -1, l = -1, len = strlen(s);
        rep (i, 0,len - 1) {
            if(s[i] == 'w' || (i > 0 && (s[i - 1] == 'v' && s[i] == 'v'))) {
                f = i; break;
            }
        }
        dec (i, len - 1, 0) {
            if(s[i] == 'h') {
                l = i; break;
            }
        }
        if(f == -1 || l == -1 || f >= l) {
            puts("No");
            continue;
        }
        int ok = 0;
        rep (i, f + 1, l - 1) {
            if(s[i] == 'y') { ok = 1; break; }
        }
        puts(ok ? "Yes" : "No");
    }
    return 0;
}
